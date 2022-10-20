#include "thread.h"
#include <iostream>
#include <cerrno>
#include <cstring>

__BEGIN_API

int Thread::_current_id = 0;
Thread * Thread::_running = NULL;
Thread Thread::_main;
Thread Thread::_dispatcher;
Thread::Ready_Queue Thread::_ready;
Thread::Suspended_Queue Thread::_suspended;

void Thread::init(void (*main)(void *))
{
    db<Thread>(TRC) << "Thread::init chamado.\n";

    db<Thread>(TRC) << "Criando fila de threads prontas.\n";
    new(&_ready)Ready_Queue();

    db<Thread>(TRC) << "Criando fila de threads suspensas.\n";
    new(&_suspended)Suspended_Queue();
    
    db<Thread>(TRC) << "Criando thread main.\n";
    std::string name = "main";
    new(&_main)Thread(main, (void*) name.data());
    
    db<Thread>(TRC) << "Criando thread dispatcher.\n";
    new(&_dispatcher)Thread(&Thread::dispatcher);
    
    db<Thread>(TRC) << "Trocando contexto para a thread main.\n";
    _running = &_main;
    _main._state = RUNNING;
    _main.context()->load();
}

void Thread::dispatcher()
{
    db<Thread>(TRC) << "Thread::dispatcher chamado.\n";
    while (_current_id > 2)
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

void Thread::suspend()
{
    db<Thread>(TRC) << "Thread::suspend chamado.\n";
    if (_state != SUSPENDED && _state != FINISHING) 
    {
        db<Thread>(TRC) << "Alterando estado para suspenso.\n";
        _state = SUSPENDED;
        _suspended_link = new Suspended_Queue::Element(this, (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
        _suspended.insert(_suspended_link);
        if (_running != this)
        {
            db<Thread>(TRC) << "Removendo thread da fila de prontos.\n";
            _ready.remove(this);
        } else {
            db<Thread>(TRC) << "Chamando Thread::yield().\n";
            yield();
        }
    }
    db<Thread>(TRC) << "Thread::suspend finalizado.\n";
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
    db<Thread>(TRC) << "Thread::thread_exit finalizado com sucesso. Cedendo a vez à próxima thread.\n";
    yield();
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
    
    db<Thread>(TRC) << "Thread::~Thread finalizado.\n";
}

__END_API
