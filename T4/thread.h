#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime> 
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> Ready_Queue;
    typedef Ordered_List<Thread> Suspended_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        SUSPENDED,
        FINISHING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */ 
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */ 
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */ 
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * Retorna o contexto da thread.
     */ 
    Context * context();

    /*
     * Despachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield(); 

    /*
     * Este método deve suspender a thread em execução até que a thread “alvo” finalize. 
     * O inteiro retornado por join() é o argumento recebido por thread_exit().
     */
    int join();

    /*
     * Suspende a Thread até que resume() seja chamado.
     */
    void suspend();

    /*
     * Coloca uma Thread que estava suspensa de volta para a fila de prontos.
     */
    void resume();

    /*
     * Coloca uma Thread que estava suspensa de volta para a fila de prontos.
     */
    void set_current_suspended(Suspended_Queue * new_suspended_queue);

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

private:
    static Thread * _running;
    static int _current_id;
    static Thread _main; 
    static CPU::Context * _main_context;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    
    int _id;
    int _exit_code;
    Context * volatile _context;
    Suspended_Queue * _suspended;
    Suspended_Queue * _current_suspended;
    Ready_Queue::Element * _link;
    Suspended_Queue::Element * _suspended_link;
    
    volatile State _state;

};

template<typename ... Tn>
inline Thread::Thread(void (* entry)(Tn ...), Tn ... an) /* inicialização de _link */
{
    if (entry == NULL)
    {
        db<Thread>(ERR) << "Construtor de Thread falhou por ponteiro nulo. Finalizando execução.\n";
        abort();
    }

    db<Thread>(TRC) << "Criando o contexto da Thread.\n";
    _id = _current_id++;
    _context = new Context(entry, an...);
    _exit_code = -1;
    _state = READY;
    _suspended = new Suspended_Queue();
    _current_suspended = _suspended;

    if (_id > 0) 
    {
        db<Thread>(TRC) << "Inserindo thread na fila.\n";
        _link = new Ready_Queue::Element(this, (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
        _ready.insert(_link); 
    }
}

__END_API

#endif
