#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include <errno.h>
#include "traits.h"
#include "debug.h"


__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
            void defaultContext()
            {
            	db<CPU>(TRC) << "Construtor de Context iniciado\n";
                save();
                _stack = new char[STACK_SIZE];
                if (_stack == nullptr) {
                    db<CPU>(ERR) << "Não foi possível alocar memória para a pilha\n";
                    abort();
                } else {
                    _context.uc_link = 0;
                    _context.uc_stack.ss_sp = _stack;
                    _context.uc_stack.ss_size = STACK_SIZE;
                    _context.uc_stack.ss_flags = 0;
                }
                db<CPU>(TRC) << "Context construido com sucesso.\n";
            }
        public:
            Context() 
            {
                defaultContext();
            }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an)
            {
                defaultContext();
                errno = 0;
                db<CPU>(TRC) << "Associando funcao ao contexto( makecontext() ).\n";
                makecontext(&_context, (void (*)(void))func, sizeof...(Tn), an...);
                if(errno != 0) {
                    db<CPU>(ERR)<< "Erro apontado por makecontext()\n";
                    abort();
                }
                db<CPU>(TRC) << "Funcao associada com sucesso.\n";
            }

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:

        static void switch_context(Context *from, Context *to);

};

__END_API

#endif
