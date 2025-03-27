CC=gcc
CFLAGS=`pkg-config --cflags gtk4` -O2 -o main src/main.c src/parse_config.c `pkg-config --libs gtk4`

all:
	@echo "Build..."
	@$(CC) $(CFLAGS)

clean:
	@echo "Clean..."
	@rm main *.AppImage

run: all
	@echo "Run..."
	@./main

publish: all
	@echo "Publish..."
	@mkdir -p build
	@cp main build/kill-it-gtk

appimage: all
	@echo "Building AppImage..."
	@cp main kill-it-gtk.AppDir/kill-it-gtk
	@mkdir -p kill-it-gtk.AppDir
	@chmod +x kill-it-gtk.AppDir/AppRun
	@./build/appimagetool kill-it-gtk.AppDir

install: publish
	@echo "Installing kill-it-gtk..."
	@install build/kill-it-gtk /usr/bin

uninstall: 
	@echo "Uninstalling kill-it-gtk..."
	@rm /usr/bin/kill-it-gtk
