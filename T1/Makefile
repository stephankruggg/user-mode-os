main: cpu.o main.o main_class.o
	g++ cpu.o main.o main_class.o -o main

cpu.o: cpu.cc cpu.h
	g++ -c cpu.cc

main.o: main.cc 
	g++ -c main.cc

main_class.o: main_class.cc main_class.h
	g++ -c main_class.cc

clean: 
	rm *.o main
