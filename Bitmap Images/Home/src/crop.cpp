#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_utils.cpp"

unsigned char *crop(unsigned char *image_data, int width, int height, int x_start, int y_start, int x_end, int y_end) {
    if (!(x_start < width || x_end < width || y_start < height || y_end < height)) {
        printf("invalid offset\n");
        exit(1);
    }
    int row_size = calc_grayscale_row_size(width);
    int cropped_width = x_end - x_start;
    int cropped_height = y_end - y_start;
    int cropped_row_size = calc_grayscale_row_size(cropped_width);

    unsigned char *new_img = (unsigned char *)malloc(cropped_row_size * cropped_height);

    for (int y = 0; y < cropped_height; y++) {
        for (int x = 0; x < cropped_width; x++) {
            int cropped_idx = (y * cropped_row_size) + x;
            int original_idx = (y_start + y) * row_size + (x_start + x);
           
            new_img[cropped_idx] = image_data[original_idx];
        }
    }
    return new_img;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("error: image name required as argument");
        exit(1);
    }
    int width, height;
    unsigned char *image_data = load_grayscale_bmp(argv[1], &width, &height);
    printf("original image size: %d x %d\n", width, height);

    if (image_data) {
        unsigned char *new_img = crop(image_data, width, height, 100, 100, 400, 400);
        display_grayscale_bmp(new_img, 300, 300);
        free(image_data);
        free(new_img);
    }

    return 0;
}