/*
    Image Header used for image processing.
*/

typedef unsigned char BYTE;

typedef enum {
    BASIC = 0,
    UINT = 1,
    REAL = 2,
    COMPLEX = 4
} ImageType;

typedef struct Image {
    int rows;
    int columns;
    BYTE* data; //pointer to raw data of image
    ImageType image_type;
    //BYTE image_type;
};
