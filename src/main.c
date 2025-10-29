#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "bmp.h"

void printHeader(BM_HEADER* header){
	printf("\n--- BMP Header ---\n");
	printf("Signature: 0x%X\n", header->signature);
	printf("Signature(ascii): %c%c\n", header->signature, header->signature >> 8);
	printf("File Size: %u\n", header->fileSize);
	printf("Reserved: %u\n", header->reserved);
	printf("Data Offset: %u\n", header->dataOffset);
}

void printInfoHeader(BM_INFO_HEADER* infoHeader){
	//This is what ai is usefull for
	printf("\n--- BMP Info Header ---\n");
	printf("Header Size: %u\n", infoHeader->headerSize);
	printf("Width: %u\n", infoHeader->width);
	printf("Height: %u\n", infoHeader->height);
	printf("Planes: %u\n", infoHeader->planes);
	printf("Bit Count: %u\n", infoHeader->bitCount);
	printf("Compression: %u\n", infoHeader->compression);
	printf("Image Size: %u\n", infoHeader->imageSize);
	printf("X Pixels Per Meter: %u\n", infoHeader->xPixelsPerMeter);
	printf("Y Pixels Per Meter: %u\n", infoHeader->yPixelsPerMeter);
	printf("Colors Used: %u\n", infoHeader->colorsUsed);
	printf("Colors Important: %u\n", infoHeader->colorsImportant);
}

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Usage: %s <bmp file>\n", argv[0]);
		return -1;
	}

	
	FILE* f = fopen(argv[1], "rb");
	if(!f){
		printf("Error opening file %s\n", argv[1]);
		return -1;
	}
	BM_IMAGE imgData;
	BM_PIXEL_24 * pixels = readFile(f);

	fclose(f);

	//Raylib setup
	InitWindow(800, 600, "BMP Viewer");
	ClearBackground(RAYWHITE);



	Image img = LoadImageFromMemory(".bmp", (const unsigned char*)pixels, sizeof(BM_PIXEL_24) * 800 * 600);

	//printf("Signature: 0x%X\n", bmHeader.signature);
	//printf("Signature: %c%c\n", bmHeader.signature, bmHeader.signature >> 8);
	//printHeader(&bmHeader);
	//printf("Header size: %d\n", headerSize);	
	return 0;
}
