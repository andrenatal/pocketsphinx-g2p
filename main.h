//
// Created by Andre Natal on 6/30/15.
//
#include <sphinxbase/ngram_model.h>
#include <stdlib.h>
#include <string.h>

#ifndef PS_G2P_MAIN_H
#define PS_G2P_MAIN_H

#endif //PS_G2P_MAIN_H

void print_char(char valor);
int32 get_winner_wid(ngram_model_t *model,  char letter, int32 *history, const int32 total_unigrams, int total_history);


