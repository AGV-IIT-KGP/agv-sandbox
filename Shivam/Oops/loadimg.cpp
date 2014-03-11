#include <iostream>

int main()
{
	char* imageName= argv[1];

	Mat image;
	image = imread("home/aries/Desktop/image.jpg",0);
	imshow(image);
	return 0;

}