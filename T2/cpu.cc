#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Ver casos de erro (retorno -1)...
    if (getcontext(&_context) == -1) {
    	db<CPU>(ERR) << "Não foi possível salvar o contexto atual.\n";
    	abort();
    }
}

void CPU::Context::load()
{
    if (setcontext(&_context) == -1) {
    	db<CPU>(ERR) << "Não foi possível restaurar o contexto.\n";
    	abort();
    }
}

CPU::Context::~Context()
{
    if (_stack) {
    	db<CPU>(TRC) << "Contexto deletado, memória desalocada.\n";
        delete _stack;
    }
}

void CPU::switch_context(Context *from, Context *to)
{
    if (swapcontext(&from->_context, &to->_context) == -1) {
    	db<CPU>(ERR) << "Não foi possível fazer a troca de contextos na CPU.\n";
    }
}

__END_API
