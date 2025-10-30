#ifndef _BMP
#define _BMP
#include "bmp.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int readFile(FILE * file, BM_IMAGE * imgData){
	BM_HEADER bmHeader;
    uint32_t headerSize; //Size of the info header

	// Test
	fread(&bmHeader, sizeof(BM_HEADER), 1, file);
	fread(&headerSize, sizeof(uint32_t), 1, file);

    
    imgData->header = bmHeader;

	if(bmHeader.signature != 0x4D42){
		printf("Not a valid BMP file!\n");
		fclose(file);
		return -1;
	}

	if(headerSize == 40){
		BM_INFO_HEADER bmInfoHeader;
		bmInfoHeader.headerSize = headerSize;
		fread(&bmInfoHeader.width, sizeof(BM_INFO_HEADER) - sizeof(uint32_t), 1, file);

		printInfoHeader(&bmInfoHeader);
		if(bmInfoHeader.bitCount != 24){
			printf("Only 24-bit BMP files are supported!\n");
			fclose(file);
			return -1;
		}
        imgData->header = bmHeader;     
        //Reading the pixel data
        size_t rowSize = ((bmInfoHeader.bitCount * bmInfoHeader.width + 31) / 32) * 4;
		
        BM_PIXEL_24* pixels = (BM_PIXEL_24*)malloc(rowSize * bmInfoHeader.height);
		printf("Row size: %zu\n", rowSize);	

        for(int i = 0; i < bmInfoHeader.height; i++){
            BM_PIXEL_24 pixelRow[bmInfoHeader.width + 1]; // +1 for possible padding
			printf("PixelRow size: %zu\n", sizeof(pixelRow));

            fread(&pixelRow, rowSize, 1, file);
			printf("Row size: %zu\n", rowSize);
            // Process pixelRow
            memcpy(&pixels[i * bmInfoHeader.width], &pixelRow, sizeof(BM_PIXEL_24) * bmInfoHeader.width);
        }
		
        imgData->infoHeader = bmInfoHeader;
        imgData->pixels = pixels;

		return 1;
	}
	return -1;
}
int freeImage(BM_IMAGE* imgData){
	if(imgData->pixels != NULL){
		free(imgData->pixels);
		imgData->pixels = NULL;
	}
	return 1;
}
void printNPixels(BM_IMAGE* imgData, int n){
	int totalPixels = imgData->infoHeader.width * imgData->infoHeader.height;
	if(n > totalPixels){
		n = totalPixels;
	}
	for(int i = 0; i < n; i++){
		BM_PIXEL_24 pixel = imgData->pixels[i];
		printf("Pixel %d: R=%u G=%u B=%u\n", i, pixel.red, pixel.green, pixel.blue);
	}
}

RenderTexture DrawBMPToTexture(BM_IMAGE* imgData){
	int width = imgData->infoHeader.width;
	int height = imgData->infoHeader.height;

	Image image = { 0 };
	image.data = imgData->pixels;
	image.width = width;
	image.height = height;
	image.mipmaps = 1;
	image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;	//This messes up the texture, because BMP file format has pixels in
													//BGR format

	Texture2D texture = LoadTextureFromImage(image);
	RenderTexture renderTexture = LoadRenderTexture(width, height);

	BeginTextureMode(renderTexture);
	ClearBackground(BLACK);
	DrawTexture(texture, 0, 0, WHITE);
	EndTextureMode();

	UnloadTexture(texture);

	return renderTexture;
}