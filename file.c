#include "file.h"

#pragma pack(1)

struct BITMAPFILEHEADER {
	unsigned short type; //specifies the file type
	unsigned int size; //specifies the size in bytes of the bitmap file
	unsigned short reserved1; //reserved; must be 0
	unsigned short reserved2; //reserved; must be 0
	unsigned int offset; //species the offset in bytes from the bitmapfileheader to the bitmap bits
};

struct BITMAPINFOHEADER {
	unsigned int size; //specifies the number of bytes required by the struct
	int width; //specifies width in pixels
	int height; //species height in pixels
	unsigned short planes; //specifies the number of color planes, must be 1
	unsigned short bitCount; //specifies the number of bit per pixel
	unsigned int compression; //spcifies the type of compression
	unsigned int sizeImage; //size of image in bytes
	int xPixelsPerMeter; //number of pixels per meter in x axis
	int yPixelsPerMeter; //number of pixels per meter in y axis
	unsigned int colorsUsed; //number of colors used by th ebitmap
	unsigned int colorsImportant; //number of colors that are important
};

#pragma pack(4)

unsigned char* loadImage(char* filename, int* width, int* height) {
	//open filename in read binary mode
	FILE* filePtr = fopen(filename, "rb");

	if (filePtr == NULL)
		return NULL;

	struct BITMAPFILEHEADER bitmapFileHeader;
	fread(&bitmapFileHeader, sizeof(struct BITMAPFILEHEADER), 1, filePtr);

	//verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42) {
		fclose(filePtr);
		return NULL;
	}

	struct BITMAPINFOHEADER bitmapInfoHeader;
	fread(&bitmapInfoHeader, sizeof(struct BITMAPINFOHEADER), 1, filePtr);

	*width = bitmapInfoHeader.width;
	*height = bitmapInfoHeader.height;

	//move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

	//allocate enough memory for the bitmap image data
	unsigned char* bitmapImage = (unsigned char*)malloc(bitmapInfoHeader.sizeImage);

	if (!bitmapImage) {
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	//read in the bitmap image data
	fread(bitmapImage, bitmapInfoHeader.sizeImage, 1, filePtr);

	if (bitmapImage == NULL) {
		fclose(filePtr);
		return NULL;
	}

	fclose(filePtr);
	return bitmapImage;
}