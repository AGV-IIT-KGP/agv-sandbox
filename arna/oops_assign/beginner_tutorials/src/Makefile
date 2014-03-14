
all: image run

image: image_proc101.cpp
	g++ -g $^ -o $@ -Wall `pkg-config opencv --cflags --libs`
run:
	./image
clean:
	rm image
