#ifndef GRL_ERRORS_H
#define GRL_ERRORS_H
#define PRE_PARSING_ERROR 1
#define GLOBAL_FINDING_PARSER_ERROR 2
#define PARSING_ERROR 3
#define LEXER_ERROR 4
#define INPUT_ERROR 5

void yyerror(const char*);
void lexerror(const char*);
void inerror(const char*);
#endif //GRL_ERRORS_H