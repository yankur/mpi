//
// Created by kurlyana on 07.06.2020.
//

#include "update.h"

void upd(int width, int height, double *temp1, double *temp2, double delta_t, double delta_y, double delta_x, double alpha) {
    for (int i = 1; i < height - 1; ++i){
        for (int j = 1; j < width - 1; ++j) {
            auto t_k = (temp1 + i * width + j);
            auto t_k1 = (temp2 + i * width + j);
            *t_k1 = *t_k + delta_t * alpha * (
                (*(temp1 + (i + 1) * width + j) + *(temp1 + (i - 1) * width + j) - 2 * *t_k) / (delta_x) +
                (*(temp1 + i * width + j + 1) + *(temp1 + i * width + j - 1) - 2 * *t_k) / delta_y);
    }
}
