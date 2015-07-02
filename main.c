//
// Created by Andre Natal on 6/30/15.
// anatal@mozilla.com
//

#include "main.h"
#include <sphinxbase/ngram_model.h>
#include <stdlib.h>
#include <string.h>

int main() {
    logmath_t *logmath = logmath_init(1.0001f, 0, 0);
    ngram_model_t *model = ngram_model_read(NULL,"/Users/anatal/Downloads/g2p-model/cmudict-g2p.lm.dmp",NGRAM_AUTO,logmath);
    const int32 *total_unigrams = ngram_model_get_counts(model);
    int32 history[1000];
    int32 winner_wid = 0;

    // start with sentence
    int32 wid_sentence = ngram_wid(model,"<s>");
    history[0] = wid_sentence;
    int totalh = 0;
    char word_grapheme[] = "jose";
    for (int j = 0 ; j <= (int) strlen(word_grapheme)-1 ; j++) {
        //char letter = 'l' ;//word_grapheme[j];
        char letter = word_grapheme[j];

        //printf("letter %c %i \n" , letter, j);

        winner_wid = get_winner_wid(model,letter,history,*total_unigrams,j+1);

        printf(" letter %c winner id %i \n" , letter,  winner_wid);
        history[j+1] = winner_wid;
        totalh = j+1;
    }

    for (int w = 0; w <= totalh; w++){
        const char* word;
        word = ngram_word(model, history[w]);
        printf(" %s " , word);
    }

    free(logmath);
    ngram_model_free(model);
    return 0;
}


int32 get_winner_wid(ngram_model_t *model, char letter, int32 *history, const int32 total_unigrams, int total_history)
{
    //printf("letter %s total unigrams %i \n" , letter, total_unigrams);
    //printf("letra aqui %c " , letter);

    int32 winner_wid = 0;
    int32 current_prob = -2147483647;

    for (int32 i = 0; i <= total_unigrams; i++) {

        const char *vocab = ngram_word(model, i);

        if (vocab == NULL)
            continue;

        char *new_vocab;
        new_vocab = strdup(vocab);

        char *pch = strtok(new_vocab, "}");

        if ( letter  == *pch) {

            int32 nused[0];
            const int32 prob = ngram_ng_prob(model, i, history, total_history, nused);
            if (current_prob < prob) {
                current_prob = prob;
                winner_wid = i;
            }
/*
            printf(" vocab( %s ) %i %i", new_vocab, prob, i);

            while (pch != NULL) {
                printf(" %s ", pch);
                pch = strtok(NULL, " ,.-");
            }
            printf("\n");
            */
        }
       free(new_vocab);
    }

    return winner_wid;
}