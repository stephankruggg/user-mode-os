#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; //declaração das classes criadas nos trabalhos devem ser colocadas aqui
class Debug;
class System;
class Thread;
class Semaphore;
class Lists;
class Background;
class Boss;
class CollisionDetector;
class Enemy;
class Engine;
class Input;
class Laser;
class Missile;
class NormalEnemy;
class Player;
class Point;
class Projectile;
class Spaceship;
class Spawner;
class Sprite;
class Timer;
class Vector;
class Window;

//declaração da classe Traits
template<typename T>
struct Traits {
    static const bool debugged = true;
};

template<> struct Traits<CPU>
{
    static const unsigned int STACK_SIZE = 64000; //Adicionar aqui a declaração do tamanho da Pilha
    static const bool debugged = true;
};

template<> struct Traits<Debug>: public Traits<void>
{
    static const bool error = true;
    static const bool warning = true;
    static const bool info = true;
    static const bool trace = true;
};

template<> struct Traits<System>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Thread>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Semaphore>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Lists>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Background>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Boss>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<CollisionDetector>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Enemy>: public Traits<void>
{
    static const bool debugged = true;
};template<> struct Traits<Engine>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Input>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Laser>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Missile>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<NormalEnemy>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Player>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Point>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Projectile>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Spaceship>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Spawner>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Sprite>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Timer>: public Traits<void>
{
    static const bool debugged = true;
};template<> struct Traits<Vector>: public Traits<void>
{
    static const bool debugged = true;
};
template<> struct Traits<Window>: public Traits<void>
{
    static const bool debugged = true;
};

__END_API

#endif
