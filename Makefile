output:	main.o glad.o
	g++ -Wall main.o glad.o -o main -L Lib/lib-mingw-w64 -lglfw3 -lgdi32 -lopengl32
	python clear.py

main.o:	source/main.cpp
	g++ source/main.cpp -c -I include -I headers

glad.o: source/glad.c
	g++ source/glad.c include/glad/glad.h -c -I include -I headers
