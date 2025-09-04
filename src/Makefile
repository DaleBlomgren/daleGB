game:
	g++ -std=c++20 \
		main.cpp \
		./Memory/ROM.cpp \
		./Memory/MBC.cpp \
		./DMG-CPU/SM83.cpp \
		./DMG-CPU/executeCB.cpp \
		-o daleGB \
		$(shell pkg-config --cflags --libs sdl2)

clean:
	rm -rf *.o daleGB