#include "thread.h"
#include <iostream>
#include <cerrno>
#include <cstring>

__BEGIN_API

int Thread::_current_id = 0;
Thread * Thread::_running = NULL;
Thread Thread::_main;
CPU::Context * Thread::_main_context;
Thread Thread::_dispatcher;
Thread::Ready_Queue Thread::_ready;

void Thread::init(void (*main)(void *))
{
    db<Thread>(TRC) << "Thread::init chamado.\n";
    
    db<Thread>(TRC) << "Criando thread main.\n";
    std::string name = "main";
    new(&_main)Thread(main, (void*) name.data());
    _main_context = _main.context();
    
    db<Thread>(TRC) << "Criando thread dispatcher.\n";
    new(&_dispatcher)Thread(&Thread::dispatcher);
    
    db<Thread>(TRC) << "Trocando contexto para a thread main.\n";
    _running = &_main;
    _main._state = RUNNING;
    _main_context->load();
}

void Thread::dispatcher()
{
    db<Thread>(TRC) << "Thread::dispatcher chamado.\n";
    while (!_ready.empty())
    {   
        db<Thread>(TRC) << "Escolhendo próxima thread a ser executada.\n";
        Thread * next_thread = _ready.remove_head()->object();
        
        db<Thread>(TRC) << "Reinserindo thread dispatcher na fila.\n";
        _dispatcher._state = READY;
        _ready.insert(_dispatcher._link);
        
        db<Thread>(TRC) << "Trocando contexto para a thread da vez.\n";
        _running = next_thread;
        next_thread->_state = RUNNING;
        switch_context(&_dispatcher, next_thread);
    }
    
    db<Thread>(TRC) << "Trocando contexto para a thread main.\n";
    _dispatcher._state = FINISHING;
    switch_context(&_dispatcher, &_main);
}

void Thread::yield()
{
    db<Thread>(TRC) << "Escolhendo próxima thread a ser executada.\n";
    Thread * next_thread = _ready.remove_head()->object();
    if (_running->_state != FINISHING && _running->_state != SUSPENDED)
    {   
    	db<Thread>(TRC) << "Rodando não está suspensa nem terminando.\n";
        if (_running != &_main)
        {
            db<Thread>(TRC) << "Reinserindo thread na fila.\n";
            int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            _running->_link->rank(now);
            _ready.insert(_running->_link);
        }
        _running->_state = READY;
    }
    
    db<Thread>(TRC) << "Trocando contexto para a thread da vez.\n";
    Thread * current = _running;
    next_thread->_state = RUNNING;
    _running = next_thread;
    switch_context(current, next_thread);
}

int Thread::join()
{
    db<Thread>(TRC) << "Thread::join chamado.\n";
    if (this != _running && !_ready.empty())
    {
        _running->set_current_suspended(this->_suspended);
        _running->suspend();
    }
    db<Thread>(TRC) << "Thread::join finalizado.\n";
    return _exit_code;
}

void Thread::suspend()
{
    db<Thread>(TRC) << "Thread::suspend chamado.\n";
    if (_state != SUSPENDED && _state != FINISHING) 
    {
        db<Thread>(TRC) << "Alterando estado para suspenso.\n";
        _state = SUSPENDED;
        _suspended_link = new Suspended_Queue::Element(this, (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
        _current_suspended->insert(_suspended_link);
        if (_running != this)
        {
            db<Thread>(TRC) << "Removendo thread da fila de prontos.\n";
            _ready.remove(this);
        } else {
            db<Thread>(TRC) << "Chamando Thread::yield.\n";
            yield();
        }
    }
    db<Thread>(TRC) << "Thread::suspend finalizado.\n";
}
void Thread::resume() 
{
    db<Thread>(TRC) << "Thread::resume chamado. \n";
    if (_state == SUSPENDED)
    {
        db<Thread>(TRC) << "Alterando o estado da thread. \n";
        _state = READY;
        if (this != &_main)
        {
        	int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        	_link->rank(now);
        	_ready.insert(_link);
        }
        delete _suspended_link;
    }
    db<Thread>(TRC) << "Thread::resume finalizado. \n";
}

int Thread::switch_context(Thread * prev, Thread * next)
{
    db<Thread>(TRC) << "Thread::switch_context chamado.\n";
    if (prev == NULL or next == NULL)
    {
    	db<Thread>(WRN) << "Thread::switch_context falhou por ponteiro nulo.\n";
        return -1;
    }
    if (prev->context() == NULL or next->context() == NULL)
    {
    	db<Thread>(WRN) << "Thread::switch_context falhou por ponteiro nulo.\n";
        return -1;
    }
    
    _running = next;
    
    if (CPU::switch_context(prev->context(), next->context()) != 0)
    {
    	_running = prev;
        db<Thread>(WRN) << "Não foi possível realizar a troca de contextos entre as threads. Erro: " << strerror(errno) << "\n";
        return -1;
    }
    
    db<Thread>(TRC) << "Thread::switch_context concluído com sucesso.\n";
    return 0;
}

int Thread::id()
{
    db<Thread>(TRC) << "Acessando id da Thread.\n";
    return _id;
}

void Thread::set_current_suspended(Suspended_Queue * new_suspended_queue)
{
    _current_suspended = new_suspended_queue;
}

CPU::Context * Thread::context()
{
    db<Thread>(TRC) << "Acessando contexto da Thread.\n";
    return _context;
}

void Thread::thread_exit (int exit_code)
{
    db<Thread>(TRC) << "Thread::thread_exit chamado.\n";
    _state = FINISHING;
    _current_id--;

    while (!_suspended->empty())
    {
        Thread * thread_to_be_resumed = _suspended->remove_head()->object();
        thread_to_be_resumed->set_current_suspended(_suspended);
        thread_to_be_resumed->resume();
    }

    _exit_code = exit_code;
    db<Thread>(TRC) << "Thread::thread_exit finalizado com sucesso.\n";
    if (_running != &_main)
    {
        db<Thread>(TRC) << "Cedendo a vez à próxima thread.\n";
        yield();
    }
}

Thread::~Thread()
{
    db<Thread>(TRC) << "Thread::~Thread chamado.\n";
    
    if (_context)
    {
        delete _context;
        db<Thread>(TRC) << "Pilha desalocada com sucesso.\n";
    }

    if (_link)
    {
        delete _link;
        db<Thread>(TRC) << "_link desalocado com sucesso.\n";
    }

    if (_suspended)
    {
        db<Thread>(TRC) << "_suspended desalocado com sucesso.\n";
        delete _suspended;
    }
    
    db<Thread>(TRC) << "Thread::~Thread finalizado.\n";
}

__END_API
