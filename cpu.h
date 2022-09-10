#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include <errno.h>
#include "traits.h"


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
                _stack = new char[STACK_SIZE];
                if (_stack == nullptr) {
                    std::cout << "Sem espaco para a alocacao da pilha" << std::endl;
                    abort();
                } else {
                    _context.uc_link = 0;
                    _context.uc_stack.ss_sp = _stack;
                    _context.uc_stack.ss_size = STACK_SIZE;
                    _context.uc_stack.ss_flags = 0;
                    save();
                }
            }
        public:
            Context() 
            {
                defaultContext();
            }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an)
            {
                // errno -> usado para erros
                defaultContext();
                errno = 0;
                makecontext(&_context, (void (*)(void))func, sizeof...(Tn), an...);
                if(errno != 0) {
                    std::cout << "Erro apontado por makecontext()" << std::endl;
                    abort();
                }
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
