build:
	g++ -w -std=c++14 -Wfatal-errors -m32 -static-libstdc++ \
	./src/*.cpp \
	-o build/game.exe \
	-I "C:\_dev\SDL2\include" \
	-L "C:\_dev\SDL2\lib" \
	-I ".\lib\lua" \
	-L ".\lib\lua" \
	-llua53 \
	-lmingw32 \
	-lSDL2main \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer \
	-lSDL2
	     
clean:
	del build/game.exe
	     
run:
	build/game.exe
