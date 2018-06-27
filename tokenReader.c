#include <mem.h>
#include <ctype.h>

#include "headers/loader.h"
#include "headers/executor.h"
#include "headers/utilities.h"
#include "headers/tokenReader.h"

#define TOKEN program->currentToken
#define CHAR program->currentChar

struct Command commands[] = {
        "LOOP", LOOP,
        "DO", DO,
        "IF", IF,
        "THEN", THEN,
        "ELSE", ELSE,
        "END", END,
        "ENDIF", ENDIF
};

int getIdCommand(char *command) ;

int isWhite(char c) {
    if (c == ' ' || c == '\t') return 1;
    else return 0;
}

int isDelim(char c) {
    if (strchr(" :+-=/%*()", c) || c == '\r' || c == '\n')
        return 1;
    return 0;
}

void readToken(struct Program *program) {
    char *token = TOKEN.name;
    TOKEN.id = 0;
    TOKEN.type = 0;

    while (isWhite(*CHAR))
        CHAR++;

    //Проверка конца программы
    if (*CHAR == 0) {
        *TOKEN.name = 0;
        TOKEN.id = FINISHED;
        TOKEN.type = DELIMITER;
        return;
    }

    //Проверка конца строки
    if (*CHAR == '\n') {
        *token++ = *CHAR++;
        *token = '\0';
        TOKEN.id = EOL;
        TOKEN.type = DELIMITER;
        return;
    }

    //Првоерка разделителя
    if (strchr(":=+-*/%()<>", *CHAR)) {
        //Ищем знак присваивания

        if (*CHAR == ':') {
            *token++ = *CHAR++;
            if (*CHAR == '=') {
                *token++ = *CHAR++;
                *token = '\0';
            } else
                printError("\":=\" expected.");
        } else {
            *token++ = *CHAR++;
            *token = '\0';
        }
        TOKEN.type = DELIMITER;
        return;
    }

    //Проверка на число
    if (isdigit(*CHAR)) {
        while (!isDelim(*CHAR))
            *token++ = *CHAR++;
        *token = '\0';
        TOKEN.type = NUMBER;
        return;
    }

    //Проверка на букву
    if (isalpha(*CHAR)) {
        while (!isDelim(*CHAR))
            *token++ = *CHAR++;
        *token = '\0';
        TOKEN.id = getIdCommand(TOKEN.name);
        if (!TOKEN.id)
            TOKEN.type = VARIABLE;
        else
            TOKEN.type = COMMAND;
        return;
    }

    printError("Syntax error! Unknown token.");

}

int getIdCommand(char *command) {
    for (int i = 0; *commands[i].name; i++) {
        if (!strcmp(commands[i].name, command))
            return commands[i].id;
    }
    return 0;
}