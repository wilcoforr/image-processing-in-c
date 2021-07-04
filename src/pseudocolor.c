/*
    Pseudocolor algorithm by wilcoforr
    Copyright 2021 MIT or something

    To pseudocolor an image - map a graylevel images RBB components into actual red, green, and blue pixels.

    algo:
        1) assumes a 256 graylevel image (aka RBG is 0-255 values for pixel)
        2) perform sobel edge detection 3x3
        3) upon completion edges within the image are highlighted in red
*/

/*

*/
void pseudo_edge(struct Image *image, struct Image *red, struct Image *blue, struct Image *green, int t) {
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
    




    
}



