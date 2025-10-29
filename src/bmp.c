#ifndef _BMP
#define _BMP
#include "bmp.h"
#endif

#include <stdlib.h>
#include <stdio.h>

void readFile(FILE * file, BM_IMAGE * imgData){
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

        for(int i = 0; i < bmInfoHeader.height; i++){
            BM_PIXEL_24 pixelRow[(bmInfoHeader.width + 31) / 32 * 4];

            fread(&pixelRow, rowSize, 1, file);
            // Process pixelRow
            memcpy(&pixels[i * bmInfoHeader.width], &pixelRow, sizeof(pixelRow));
        }
        imgData->infoHeader = bmInfoHeader;
        imgData->pixels = pixels;
	}
}