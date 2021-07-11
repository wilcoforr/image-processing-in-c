#include "image.h"

#define idx(Im, i, j) \
    *(Im->data + (i)*Im->columns + (j))

void rotate_90_degrees(struct Image *input, struct Image *output)
{
    int i, j, k = 0;

    k = input->columns;
    for (i = 0; i < input->rows; ++i)
    {
        k = input->columns;
        for (j = 0; j < input->columns; ++j)
        {
            idx(output, k--, i) = idx(input, i, j);
        }
    }
}