#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Ver casos de erro (retorno -1)...
    if(getcontext(&_context) == -1) {
    	std::cout << "Nao foi possivel salvar o contexto atual" << std::endl;
    	abort();
    }
}

void CPU::Context::load()
{
    if(setcontext(&_context) == -1) {
    	std::cout << "Nao foi possivel restaurar o contexto" << std::endl;
    	abort();
    }
}

CPU::Context::~Context()
{
    delete _stack;
}

void CPU::switch_context(Context *from, Context *to)
{
    if(swapcontext(&from->_context, &to->_context) == -1) {
    	std::cout << "Nao foi possivel fazer a troca de contextos" << std::endl;
    	abort();
    }
}

__END_API
