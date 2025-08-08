game:
	g++ -std=c++20 \
		main.cpp \
		./Memory/ROM.cpp \
		./Memory/Memory.cpp \
		-o daleGB \
		$(shell pkg-config --cflags --libs sdl2)

clean:
	rm -rf *.o daleGB