all:
	mkdir -p build
	gcc -o build/mogger_test src/main.c

install:
	sudo cp -r include/mogger.h /usr/local/include
