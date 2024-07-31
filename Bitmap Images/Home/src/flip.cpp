#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_utils.cpp"

void flip_vertically(unsigned char *image_data, int width, int height) {
    int row_size = calc_grayscale_row_size(width);

    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            int idx = y * row_size + x;
            int opposite_idx = (height - y - 1) * row_size + x;
            unsigned char temp = image_data[idx];
            image_data[idx] = image_data[opposite_idx];
            image_data[opposite_idx] = temp;
        }
    }
}

void flip_horizontally(unsigned char *image_data, int width, int height) {
    int row_size = calc_grayscale_row_size(width);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width / 2; x++) {
            int idx = (y * row_size) + x;
            int opposite_idx = (y * row_size) + (width - x - 1);

            unsigned char temp = image_data[idx];
            image_data[idx] = image_data[opposite_idx];
            image_data[opposite_idx] = temp;

        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("error: image name required as argument");
        exit(1);
    }
    int width, height;
    unsigned char *image_data = load_grayscale_bmp(argv[1], &width, &height);

    if (image_data) {
        flip_vertically(image_data, width, height);
        // flip_horizontally(image_data, width, height);
        display_grayscale_bmp(image_data, width, height);
        free(image_data);
    }

    return 0;
}