#include "thread.h"
#include <iostream>
#include <cerrno>
#include <cstring>

__BEGIN_API

int Thread::_current_id = 0;
Thread * Thread::_running = NULL;
Thread * Thread::_main = NULL;

int Thread::switch_context(Thread * prev, Thread * next)
{
    db<Thread>(TRC) << "Thread::switch_context() chamado.\n";
    if (prev == NULL or next == NULL)
    {
    	db<Thread>(WRN) << "Thread::switch_context() falhou por ponteiro nulo.\n";
        return -1;
    }
    if (prev->context() == NULL or next->context() == NULL)
    {
    	db<Thread>(WRN) << "Thread::switch_context() falhou por ponteiro nulo.\n";
        return -1;
    }
    
    _running = next;
    
    if (CPU::switch_context(prev->context(), next->context()) != 0)
    {
    	_running = prev;
        db<Thread>(WRN) << "Não foi possível realizar a troca de contextos entre as threads. Erro: " << strerror(errno) << "\n";
        return -1;
    }
    
    db<Thread>(TRC) << "Thread::switch_context() concluído com sucesso.\n";
    return 0;
}

void Thread::thread_exit (int exit_code)
{
    db<Thread>(TRC) << "Thread::thread_exit() chamado.\n";
    if (_context)
    {
    	db<Thread>(TRC) << "Pilha desalocada com sucesso.\n";
        delete _context;
    }
    _current_id--;
    db<Thread>(TRC) << "Thread::thread_exit() finalizado com sucesso.\n";
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

__END_API
