/*
    Basic Image Processing Program example 1 with Convolve
*/

/* C std lib */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

/* custom image header */
#include "image.h"


int main (void) {
    /* extern magic cuz functions are defined after main */
    extern void
        Image_in(struct Image* in), 
        Convolve(struct Image* in, struct Image* out, struct Image* mask),
        Image_out(struct Image* out);

    /* init */
    struct Image in, out, mask;
    /* indexes for mask generation section */
    signed char* temp = NULL;

    in.rows = out.rows = 256;
    in.columns = out.columns = 256;
    in.image_type = out.image_type = BASIC;

    //https://linux.die.net/man/3/calloc
    in.data = (BYTE*) calloc(in.rows, in.columns);

    if (!in.data) {
        perror("Input image data invalid.");
    }

    out.data = (BYTE*) calloc(out.rows, out.columns);

    if (!out.data) {
        perror("Output image data invalid.");
    }

    /* 5x5 mask set up */
    mask.rows = mask.columns = 5;
    mask.image_type = BASIC;
    int mask_data_size = mask.rows * mask.columns;
    mask.data = (BYTE*) malloc(mask_data_size); //25 for this example

    /*
        init the 5x5 mask image as LaPlacian http://www.cse.dmu.ac.uk/~sexton/WWWPages/HIPR/html/log.html
    [
        [-1, -1, -1, -1, -1],
        [-1, -1, -1, -1, -1],
        [-1, -1, 24, -1, -1],
        [-1, -1, -1, -1, -1],
        [-1, -1, -1, -1, -1]
    ]
   
    */

   //set all mask values to -1
   temp = (signed char*) mask.data;
   for (int i = 0; i < mask_data_size; ++i) {
       *temp = -1;
       ++temp;
   }

    //fix the middle one - the magic number 24 in the middle of the 2d array/matrice, aka indice 13

    temp = (signed char*) mask.data + 13; //13 is middle indice to make 24
    *temp = 24;

    Image_in(&in);
    Convolve(&in, &mask, &out);
    Image_out(&out);

    //cleanup
    free(in.data);
    free(out.data);
    free(mask.data);

    return EXIT_SUCCESS;
}

void Image_in(struct Image* img) {
    FILE* ifile = NULL;

    const char* input_file_name = "MYIMAGE.RAW";
    const char* read_binary = "rb";

    errno_t err;
    err = fopen_s(&ifile, input_file_name, read_binary);

    char buffer_list[100];

    for (int i = 0; i < img->rows; ++i) {
        fread_s(buffer_list, img->data + i * img->columns, img->columns, 1, ifile);
    }

    fclose(ifile);
}

// 2D discrete Convolution 
void Convole(struct Image* in, struct Image* mask, struct Image* out) {
    long i, j, m, n, idx, jdx = 0;
    int ms, im, val = 0;
    BYTE* temp = NULL;

    //outer summation loop
    for (i = 0; i < in->rows; ++i) {
        for (j = 0; j < in->columns; ++j) {
            val = 0;

            for (m = 0; m < mask->rows; ++m) {
                for (n = 0; n < mask->columns; ++n) {
                    ms = (signed char) *(mask->data + m * mask->rows + n);

                    idx = i - m;
                    jdx = j - n;
                    if (idx >= 0 && jdx >= 0) {
                        im = *(in->data + idx * in->rows + jdx);
                    }
                    val += ms * im;
                }
            
                //control for overflow todo: clean this up lol or use the right data types
                if (val > 255) {
                    val = 255;
                }

                if (val < 0) {
                    val = 0;
                }
            
                temp = out->data + i * out->rows + j;
                *temp = (unsigned char) val; //BYTE here later
            }
        }
    }
}

// output the image to a file (either by creating one or overwriting the existing one)

void Image_out (struct Image *out) {
    FILE* ofile = NULL;

    const char* output_file_name = "CONVOUT.RAW";
    const char* write_binary = "wb";
    
    errno_t err;
    err = fopen_s(&ofile, output_file_name, write_binary);
    
    for (int i = 0; i < out->rows; ++i) {
        fwrite(out->data + i * out->columns, out->columns, 1, ofile); //todo later: fwrite_s
    }

    fclose(ofile);
}
