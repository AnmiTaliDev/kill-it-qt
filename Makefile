all:
	gcc `pkg-config --cflags gtk4` -o main src/main.c `pkg-config --libs gtk4`
clean:
	rm main

run: all
	./main

