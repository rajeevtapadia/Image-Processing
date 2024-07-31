#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_utils.cpp"

int main(int argc, char *argv[]) {
    int width, height;
    unsigned char *imageData = load_grayscale_bmp(argv[1], &width, &height);

    if (imageData) {
        display_grayscale_bmp(imageData, width, height);
        free(imageData);
    }

    return 0;
}
