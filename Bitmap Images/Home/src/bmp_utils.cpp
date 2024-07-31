#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_header.h"

int calc_grayscale_row_size(int width) {
    /*
     * rowSize is the memory required for a single row of pixels
     * in bmp image pixels rows are stored with padding 4
     * for performance reasons
     * thus to round up we add 3 and bitwise and with 11111100 ie ~3
     */

    return (width + 3) & ~3;
}

int calc_rgb_row_size(int width) {
    return (width * 3 + 3) & ~3;
}

unsigned char *load_grayscale_bmp(const char *filename, int *width, int *height) {
    FILE *img = fopen(filename, "rb");
    if (!img) {
        perror("Failed to open img");
        return NULL;
    }

    bmp_header header;

    fread(&header, sizeof(header), 1, img);

    if (header.signature != 0x4D42) {
        fclose(img);
        fprintf(stderr, "Not a BMP img\n");
        return NULL;
    }

    *width = header.width;
    *height = header.height;

    fseek(img, header.data_offset, SEEK_SET);

    // for color image
    // int row_size = calc_rgb_row_size(*width);

    // for grayscale image
    int row_size = calc_grayscale_row_size(*width);

    unsigned char *data = (unsigned char *)malloc(row_size * (*height));

    if (data == NULL) {
        fclose(img);
        perror("Failed to allocate memory");
        return NULL;
    }

    fread(data, row_size, *height, img);
    fclose(img);

    return data;
}

void display_grayscale_bmp(const unsigned char *data, int width, int height) {
    int i, j;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    if (graphresult() != grOk) {
        fprintf(stderr, "Graphics initialization failed\n");
        return;
    }

    int rowSize = (width + 3) & ~3; 
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            int index = (height - 1 - j) * rowSize + i; 
            unsigned char intensity = data[index];
            int color = COLOR(intensity, intensity, intensity); 
            putpixel(i, j, color);
        }
    }

    // Wait for user input
    getch();
    closegraph();
}

void display_rgb_bmp(const unsigned char *data, int width, int height) {
    int i, j;

    // Set the video mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    if (graphresult() != grOk) {
        fprintf(stderr, "Graphics initialization failed\n");
        return;
    }

    // Draw the BMP image
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            int index = (height - 1 - j) * width * 3 + i * 3;                 // BMP files are stored bottom-to-top
            int color = COLOR(data[index + 2], data[index + 1], data[index]); // RGB to graphics.h color format
            putpixel(i, j, color);
        }
    }

    getch();
    closegraph();
}