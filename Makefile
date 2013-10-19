snake:	Snake.cpp
	g++ -I /usr/include/SDL -o snake Snake.cpp  -lSDL

clean:
	rm snake
