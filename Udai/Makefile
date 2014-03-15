all: image run
image: OOPass.cpp
	g++ -g $^ -o $@ -Wall `pkg-config opencv --cflags --libs`
run:
	./image
clean:
	rm image
