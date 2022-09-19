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

void CPU::switch_context(Context *from, Context *to)
{
    if (swapcontext(&from->_context, &to->_context) == -1) 
    {
    	db<CPU>(ERR) << "Não foi possível realizar a troca de contextos na CPU.\n";
    }
}

__END_API
