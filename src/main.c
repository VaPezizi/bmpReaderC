#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html

typedef struct{
	uint16_t signature;
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t dataOffset;
}BM_HEADER;

typedef struct{
	uint32_t headerSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitCount;		// Bits per pixel
	uint32_t compression;
	uint32_t imageSize;
	uint32_t xPixelsPerMeter;
	uint32_t yPixelsPerMeter;
	uint32_t colorsUsed;
	uint32_t colorsImportant;
} BM_INFO_HEADER;

typedef struct{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t * reserved;
} BM_PIXEL;

int main(int argc, char* argv[]){
	printf("Hello World!\n");	
	return 0;
}
