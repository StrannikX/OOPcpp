run: Main
	./Main

clean:
	rm Main Main.o

Main: Main.o
	g++ Main.o -o Main

Main.o: Main.cpp Container.hpp Base.hpp Shapes.hpp ShapeFactory.hpp
	g++ -c -std=c++14 -Wall -pedantic -O2 -o Main.o Main.cpp
