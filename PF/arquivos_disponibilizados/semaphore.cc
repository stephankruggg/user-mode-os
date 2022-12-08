#include "semaphore.h"

__BEGIN_API

Semaphore::Semaphore(int v)
{
    _sem_value = v;
    _waiting = new Waiting_Queue();
}

void Semaphore::p()
{
    db<Semaphore>(TRC) << "Semaphore::p chamado.\n";
    if (_sem_value > 0)
    {
        db<Semaphore>(TRC) << "Chamando fdec.\n";
        fdec(_sem_value);
    } else
    {
        db<Semaphore>(TRC) << "Chamando sleep.\n";
        sleep();
    }
    db<Semaphore>(TRC) << "Semaphore::p finalizado.\n";
}

void Semaphore::v()
{
    db<Semaphore>(TRC) << "Semaphore::v chamado.\n";
    if (_waiting->empty())
    {
        db<Semaphore>(TRC) << "Chamando finc.\n";
        finc(_sem_value);
    } else
    {
        db<Semaphore>(TRC) << "Chamando wakeup.\n";
        wakeup();
    }
    db<Semaphore>(TRC) << "Semaphore::v finalizado.\n";
}

int Semaphore::fdec(volatile int & number)
{
    db<Semaphore>(TRC) << "Semaphore::fdec chamado.\n";
    return CPU::fdec(number);
}

int Semaphore::finc(volatile int & number)
{
    db<Semaphore>(TRC) << "Semaphore::finc chamado.\n";
    return CPU::finc(number);
}

void Semaphore::sleep()
{
    db<Semaphore>(TRC) << "Semaphore::sleep chamado.\n";

    db<Semaphore>(TRC) << "Inserindo thread na fila de waiting.\n";
    Thread * thread_to_sleep = Thread::running();
    _waiting->insert(thread_to_sleep->set_waiting_link());
    db<Semaphore>(TRC) << "Chamando sleep da thread.\n";
    thread_to_sleep->sleep();

    db<Semaphore>(TRC) << "Semaphore::sleep finalizado.\n";
}

void Semaphore::wakeup()
{
    db<Semaphore>(TRC) << "Semaphore::wakeup chamado.\n";

    db<Semaphore>(TRC) << "Obtendo thread a acordar.\n";
    Thread * thread_to_wakeup = _waiting->remove_head()->object();
    db<Semaphore>(TRC) << "Chamando wakeup da thread.\n";
    thread_to_wakeup->wakeup();

    db<Semaphore>(TRC) << "Semaphore::wakeup finalizado.\n";
}

void Semaphore::wakeup_all()
{
    db<Semaphore>(TRC) << "Semaphore::wakeup_all chamado.\n";
    while (!_waiting->empty())
    {
        db<Semaphore>(TRC) << "Chamando wakeup.\n";
        wakeup();
    }
    db<Semaphore>(TRC) << "Semaphore::wakeup_all finalizado.\n";
}

Semaphore::~Semaphore()
{
    db<Semaphore>(TRC) << "Semaphore::~Semaphore chamado.\n";
    if (_waiting)
    {
        db<Semaphore>(TRC) << "Chamando wakeup_all.\n";
        wakeup_all();
        delete _waiting;
    }
    db<Semaphore>(TRC) << "Semaphore::~Semaphore finalizado.\n";
}

__END_API