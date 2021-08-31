#include "image.h"

void histogram_equalization(struct Image* image, struct Image* image_1) {
    int x,y,i,j = 0;
    int history_equalization[256];
    float history[256];
    float sum = 0.0f;
    for (i = 0; i < 256; i++) {
        sum = 0.0f;
        for (j = 0; j < 256; j++) {
            sum = sum + history[j];
            history_equalization[i] = (int) (255 * sum * 0.5);
        }
        for (y = 0; y < image->rows; y++) {
            for (x = 0; x < image->columns; x++) {
                *(image_1)->data + x + (long) y * image->columns 
                        = history_equalization[*(image->data + x + (long) y * image->columns)];
            }
        }
    }
}