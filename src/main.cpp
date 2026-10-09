#define STB_IMAGE_IMPLEMENTATION

#include <grabInfo.h>

int main()
{
	int width{}, height{}, channels{};

	unsigned char* image = stbi_load("../assets/input/Test.jpeg", &width, &height, &channels, 3);

	if (image == nullptr)
	{
		cerr << "Failed to load image: " << stbi_failure_reason() << endl;
		return false;
	}

	// read out info
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	cout << "Original channels: " << channels << endl;

	// retrieve info

    int red = image[0];
    int green = image[1];
    int blue = image[2];

    std::cout << "Pixel (0,0)\n"
        << "R= " << red << endl
        << "G= " << green << endl
        << "B= " << blue << endl;

    stbi_image_free(image);

    return 0;
}
