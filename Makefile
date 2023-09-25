output:	main.o
	g++ -Wall main.o -o main

main.o:	main.cpp
	g++ main.cpp -c -I utils -I primitives -I octree -I renderizador_opengl/include

