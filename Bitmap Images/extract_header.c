#include <stdio.h>

/*
 * unsigned short, short: 2
 * unsigned int, long, unsigned int, ing: 4
 */

#pragma pack(push, 1)

struct bmp_header {
    // header 14 bytes
    unsigned short signature;
    unsigned int file_size;
    unsigned int reserved;
    unsigned int data_offset;

    // info header
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xpixels_Per_M;
    unsigned int ypixels_Per_M;
    unsigned int colores_used;
    unsigned int imp_colors;
};

#pragma pack(pop)

void print_bmp_header(struct bmp_header header) {
    printf("BMP Header:\n");
    printf("Signature: %c%c\n", header.signature, *((char*)&header.signature + 1));
    printf("File Size: %u bytes\n", header.file_size);
    printf("Reserved: %lu\n", header.reserved);
    printf("Data Offset: %lu bytes\n", header.data_offset);
    printf("\nInfo Header:\n");
    printf("Size: %lu bytes\n", header.size);
    printf("Width: %lu pixels\n", header.width);
    printf("Height: %lu pixels\n", header.height);
    printf("Planes: %u\n", header.planes);
    printf("Bits Per Pixel (BPP): %u\n", header.bpp);
    printf("Compression: %lu\n", header.compression);
    printf("Image Size: %lu bytes\n", header.imageSize);
    printf("X Pixels Per Meter: %lu\n", header.xpixels_Per_M);
    printf("Y Pixels Per Meter: %lu\n", header.ypixels_Per_M);
    printf("Colors Used: %lu\n", header.colores_used);
    printf("Important Colors: %lu\n", header.imp_colors);
}

void main() {
    printf("short %d\nint %d\n\n", sizeof(short), sizeof(long));

    char img_name[] = "sample3.bmp";
    FILE *fptr = fopen(img_name, "rb");
    if(fptr == NULL) {
        printf("error opening file");
        return;
    }

    struct bmp_header header;
    fread(&header, sizeof(header), 1, fptr);
    printf("%s\n", img_name);
    print_bmp_header(header);
    return;
}
