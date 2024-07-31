#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_utils.cpp"

double convert_to_radian(double degree) {
    return degree * M_PI / 180;
}

unsigned char *rotate(unsigned char *image_data, int width, int height, double degree, int *new_width, int *new_height) {
    double angle = convert_to_radian(degree);
    double sine = sin(angle);
    double cosine = cos(angle);

    // Calculate new dimensions
    *new_width = (int)(width * fabs(cosine) + height * fabs(sine));
    *new_height = (int)(width * fabs(sine) + height * fabs(cosine));

    // Allocate memory for the new image
    unsigned char *new_img = (unsigned char *)malloc(*new_width * *new_height);

    // Initialize new image with black (0)
    for (int i = 0; i < *new_width * *new_height; i++) {
        new_img[i] = 0;
    }

    // Calculate center of original and new image
    int cx = width / 2;
    int cy = height / 2;
    int new_cx = *new_width / 2;
    int new_cy = *new_height / 2;

    // Rotate each pixel of the original image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Translate point to origin
            int tx = x - cx;
            int ty = y - cy;

            // Rotate point
            int new_x = (int)(tx * cosine - ty * sine);
            int new_y = (int)(tx * sine + ty * cosine);

            // Translate point back to the new image center
            new_x += new_cx;
            new_y += new_cy;

            // Check if the new coordinates are within the bounds of the new image
            if (new_x >= 0 && new_x < *new_width && new_y >= 0 && new_y < *new_height) {
                new_img[new_y * *new_width + new_x] = image_data[y * width + x];
            }
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

    if (image_data) {
        int new_width, new_height;
        unsigned char *new_img = rotate(image_data, width, height, 45, &new_width, &new_height);
        display_grayscale_bmp(new_img, new_width, new_height);
        free(image_data);
        free(new_img);
    }

    return 0;
}