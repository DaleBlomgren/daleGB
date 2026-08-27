game:
	g++ -std=c++20 \
		main.cpp \
		GameBoy.cpp \
		./Memory/ROM.cpp \
		./Memory/MBC.cpp \
		./DMG-CPU/SM83.cpp \
		./DMG-CPU/executeCB.cpp \
		-o ../build/daleGB \
		$(shell pkg-config --cflags --libs sdl2)

clean:
	rm -rf *.o ../build/daleGB