program: cpu.o main.o main_class.o
	g++ cpu.o main.o main_class.o -o program

cpu.o: cpu.cc
	g++ -c cpu.cc

main.o: main.cc
	g++ -c main.cc
main_class.o: main_class.cc
	g++ -c main_class.cc

clean: 
	rm *.o program
