#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    if (getcontext(&_context) == -1) 
    {
    	db<CPU>(ERR) << "Não foi possível salvar o contexto atual. Finalizando execução.\n";
    	abort();
    }
}

void CPU::Context::load()
{
    if (setcontext(&_context) == -1) 
    {
    	db<CPU>(ERR) << "Não foi possível restaurar o contexto. Finalizando execução.\n";
    	abort();
    }
}

CPU::Context::~Context()
{
    if (_stack) 
    {
    	db<CPU>(TRC) << "Contexto deletado, memória desalocada.\n";
        delete _stack;
    }
}

int CPU::switch_context(Context *from, Context *to)
{
    if (swapcontext(&from->_context, &to->_context) == -1) 
    {
    	db<CPU>(ERR) << "Não foi possível realizar a troca de contextos na CPU.\n";
        return -1;
    }
    return 0;
}

int CPU::finc(volatile int & number)
{
    db<CPU>(TRC) << "CPU::finc chamado.\n";

    int sum = 1;
    asm("lock xadd %1, %0;"
        :"+m"(number), "=r"(sum)
        :"1"(sum));

    db<CPU>(TRC) << "CPU::finc finalizado.\n";
    return sum;
}

int CPU::fdec(volatile int & number)
{
    db<CPU>(TRC) << "CPU::fdec chamado.\n";

    int sum = -1;
    asm("lock xadd %1, %0;"
        :"+m"(number), "=r"(sum)
        :"r"(sum));

    db<CPU>(TRC) << "CPU::fdec finalizado.\n";
    return sum;
}

__END_API
