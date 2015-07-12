//
// Created by Andre Natal on 6/30/15.
//
#include <sphinxbase/ngram_model.h>
#include <string.h>

#ifndef PS_G2P_MAIN_H
#define PS_G2P_MAIN_H

#endif //PS_G2P_MAIN_H

struct winner_t get_winner_wid(ngram_model_t *model, char word_grapheme[], int32 history[], const int32 total_unigrams, int total_history, int offset_word);
void removeChar(char *str, char garbage);
int startsWith(const char *pre, const char *str);
void substring(char s[], char sub[], int p, int l);
char * g2p(char word[]);

struct winner_t
{
    size_t length_match;
    int winner_wid;
};