#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/include/fs.h"
#include "./include/cws_token.h"
#include "./include/cws_lexer.h"

int main(int argc, char **argv) {
    CWSLexer_T* l = init_cws_lexer(read_file_fs("src/cws/examples/server.cws"));
    CWSToken_T* t = cws_lexer_scan_next_token(l);
    while(t->token_type != EOF) {
        printf("token(%s, %d (%s))\n", t->token_value, t->token_type, cws_token_to_string(t));
        t = cws_lexer_scan_next_token(l);
    }

    return 0;
}