#include <cstdint>
#include <iostream>

#include "stb_image.h"

using namespace std;

class grabInfo
{
private:
	int imageWidth, imageHeight, imageChannels;

public:
	unsigned char* image{};

	bool checkImageInfo(); // will use to check width,height, channels

	int grabImageHeight();
	int grabImageWidth();

	void getRGB(uint8_t& red, uint8_t& green, uint8_t& blue);
};