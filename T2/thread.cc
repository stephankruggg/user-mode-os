#include "thread.h"
#include <iostream>

__BEGIN_API

int Thread::_current_id = 0;
Thread * Thread::_running = NULL;
Thread * Thread::_main = NULL;

int Thread::switch_context(Thread * prev, Thread * next)
{
    db<Thread>(TRC) << "Thread::switch_context() chamado\n";
    if (prev == NULL or next == NULL)
    {
    	db<Thread>(WRN) << "Thread::switch_context() falhou por ponteiro nulo\n";
        return -1;
    }
    errno = 0;
    CPU::switch_context(prev->context(), next->context());
    if(errno != 0) {
    	return -1;
    }
    _running = next;
    db<Thread>(TRC) << "Thread::switch_context() concluido com sucesso.\n";
    return 0;
}

void Thread::thread_exit (int exit_code)
{
    db<Thread>(TRC) << "Thread::thread_exit() chamado\n";
    if (_context)
    {
    	db<Thread>(TRC) << "Pilha desalocada com sucesso/n";
        delete _context;
    }
    _current_id--;
    db<Thread>(TRC) << "Thread::thread_exit() finalizado com sucesso.\n";
}

int Thread::id()
{
    return _id;
}

CPU::Context * Thread::context()
{
    return _context;
}

__END_API
