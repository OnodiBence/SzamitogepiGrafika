all:
	gcc kokarda.c -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -o kokarda.exe

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o cube -Wall -Wextra -Wpedantic
