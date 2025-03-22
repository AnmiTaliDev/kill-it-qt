CC=gcc
CFLAGS=`pkg-config --cflags gtk4` -o main src/main.c `pkg-config --libs gtk4`

all:
	@echo "Build..."
	@$(CC) $(CFLAGS)

clean:
	@echo "Clean..."
	@rm main

run: all
	@echo "Run..."
	@./main

publish: all
	@echo "Publish..."
	@mkdir -p build
	@cp main build/kill-it-gtk
	
