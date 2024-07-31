#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_utils.cpp"

void gray_to_binary(unsigned char *image_data, int width, int height, short threshold) {
    int row_size = calc_grayscale_row_size(width);

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int idx = y * row_size + x;
            if (image_data[idx] > threshold) {
                image_data[idx] = 255;
            } else {
                image_data[idx] = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int width, height;
    unsigned char *image_data = load_grayscale_bmp(argv[1], &width, &height);

    if (image_data) {
        gray_to_binary(image_data, width, height, 128);
        display_grayscale_bmp(image_data, width, height);
        free(image_data);
    }
    return 0;
}