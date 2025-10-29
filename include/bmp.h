#include <inttypes.h>

//http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
#pragma pack(1)
typedef struct{
	uint16_t signature;
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t dataOffset;
}BM_HEADER;

//40 bytes in size, BITMAPINFOHEADER
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
    
} BM_PIXEL_24;
#pragma pack()

//Higher level struct
typedef struct{
    BM_HEADER header;
    BM_INFO_HEADER infoHeader;
    BM_PIXEL_24* pixels;
} BM_IMAGE;


void printInfoHeader(BM_INFO_HEADER* infoHeader);
void printHeader(BM_HEADER* header);
BM_PIXEL_24 * readFile(FILE * file);        //The file is not closed inside this function, it's the users responsibility 