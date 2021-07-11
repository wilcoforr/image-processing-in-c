/*
    Pseudocolor algorithm by wilcoforr
    Copyright 2021 MIT or something

    To pseudocolor an image - map a graylevel images RBB components into actual red, green, and blue pixels.

    algo:
        1) assumes a 256 graylevel image (aka RBG is 0-255 values for pixel)
        2) perform sobel edge detection 3x3
        3) upon completion edges within the image are highlighted in red
*/

#include "image.h"

/*

*/
void pseudo_edge(struct Image *image, struct Image *red, struct Image *blue, struct Image *green, int T) {
    int X, Y, x1, y1;
    int mask1[3][3];

    int mask2[3][3];
    int GX, GY, EDGE;

    long int R, R1;

    //todo: reorg this 2d matrice mess into something better lol
    mask1[0][0] = -1;
    mask1[1][0] = -2;
    mask1[2][0] = -1;

    mask1[0][1] = 0;
    mask1[1][1] = 0;
    mask1[2][1] = 0;

    mask1[0][2] = 1;
    mask1[1][2] = 2;
    mask1[2][2] = 1;


    mask2[0][0] = -1;
    mask2[1][0] = 0;
    mask2[2][0] = 1;

    mask2[0][1] = -2;
    mask2[1][1] = 0;
    mask2[2][1] = 2;
    
    mask2[0][2] = -1;
    mask2[1][2] = 0;
    mask2[2][2] = 1;

    for (Y = 1; Y < image->rows-1; Y++) {
        for (X = 1; X < image->columns - 1; X++) {
            GX = 0;
            GY = 0;
            for (y1 = -1; y1 <= 1; y1++) {
                for (x1 = -1; x1 <= 1; x1++) {
                    R = X + x1 + (long) (Y + y1) * image->columns;
                    GX += mask1[x1 + 1][y1 + 1] * *(image->data + R);

                    R1 = X + (long) Y * image->columns;
                    GY += mask2[x1 + 1][y1 + 1] * *(image->data + R);
                }
            }

            EDGE = abs(GX) + abs(GY);

            if (EDGE > T) {
                *(red->data + R1) = 255;
                *(blue->data + R1) = 0;
                *(green->data + R1) = 0;
            }
            else {
                *(red->data + R1) = *(image->data + R1);
                *(blue->data + R1) = *(image->data + R1);
                *(green->data + R1) = *(image->data + R1);
            }
        }
    }


    //more stuff
}



