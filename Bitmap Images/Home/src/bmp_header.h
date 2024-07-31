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