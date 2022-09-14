#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Ver casos de erro (retorno -1)...
    if (getcontext(&_context) == -1) {
    	std::cout << "Não foi possível salvar o contexto atual." << std::endl;
    	abort();
    }
}

void CPU::Context::load()
{
    if (setcontext(&_context) == -1) {
    	std::cout << "Não foi possível restaurar o contexto." << std::endl;
    	abort();
    }
}

CPU::Context::~Context()
{
    if (_stack) {
        delete _stack;
    }
}

void CPU::switch_context(Context *from, Context *to)
{
    if (swapcontext(&from->_context, &to->_context) == -1) {
    	std::cout << "Não foi possível fazer a troca de contextos." << std::endl;
    	abort();
    }
}

__END_API
