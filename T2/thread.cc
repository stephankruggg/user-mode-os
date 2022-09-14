#include "thread.h"
#include <iostream>

__BEGIN_API

int Thread::_current_id = 0;
Thread * Thread::_running = NULL;
Thread * Thread::_main = NULL;

int Thread::switch_context(Thread * prev, Thread * next)
{
    if (prev == NULL or next == NULL)
    {
        return -1;
    }
    CPU::switch_context(prev->context(), next->context());
    _running = next;
    return 0;
}

void Thread::thread_exit (int exit_code)
{
    if (_context)
    {
        delete _context;
    }
    _current_id--;
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