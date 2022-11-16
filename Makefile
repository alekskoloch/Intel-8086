precompile:
	g++ Headers\headers.h -I"C:\Studia\PROGRAMOWANIE\MY PROJECTS\xLIB\SFML-2.5.1\include" -DSFML_STATIC

all: compile link

compile:
	g++ -c main.cpp Intel8086.cpp Graphics\GraphicsSettings.cpp -I"C:\Studia\PROGRAMOWANIE\MY PROJECTS\xLIB\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ main.o Intel8086.o GraphicsSettings.o -o main -L"C:\Studia\PROGRAMOWANIE\MY PROJECTS\xLIB\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main