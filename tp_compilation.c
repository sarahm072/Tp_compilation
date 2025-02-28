#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

typedef enum{
  Identificateur,
  Nombre,
  Operateur,
  Mot_Cle,
  Unknow
}TypeLexeme;

typedef struct{
   TypeLexeme Type;
   char lexeme[100];
}Lexeme;

const char* typeToString(TypeLexeme type) {
    switch (type) {
        case Identificateur: return "Identificateur";
        case Nombre: return "Nombre";
        case Operateur: return "Operateur";
        case Mot_Cle: return "Mot_Cle";
        case Unknow: return "Unknow";
        default: return "Unknown Type";
    }
}

Lexeme is_identification(char *input){
    Lexeme l;
    int i=0;
    if(isalpha(input[0])){  
        //isalpha() verifier si input containt des alphabet. [a-zA-Z]
      l.lexeme[i] = input[0];
      while (isalnum(input[i]))
            //isalnum() verifier si input containt des alphabet ou des nombres.[a-zA-Z0-9]
      {
        l.lexeme[i] = input[i];
        i++;
      }
      l.lexeme[i]='\0';
      l.Type=Identificateur;
    }else{
      l.Type=Unknow;
    }
    return l;
}

Lexeme is_number(char *input){
    Lexeme l;
    int i=0;
    if(isdigit(input[i])){
        //isdigit() verifier si input containt des nombres [0-9]
      while (isdigit(input[i]))
      {
        
        l.lexeme[i] = input[i];
        i++;
      }
      l.lexeme[i]='\0';
      l.Type=Nombre;
    }else{
      l.Type=Unknow;
    }
    return l;
}

Lexeme is_Operateur(char *input) {
    Lexeme l;
    if (strncmp(input, "<=", 2) == 0 || strncmp(input, ">=", 2) == 0 ||
        strncmp(input, "==", 2) == 0 || strncmp(input, "<>", 2) == 0) {
        strncpy(l.lexeme, input, 2);
        l.lexeme[2] = '\0';
        l.Type = Operateur;
    } else if (*input == '<' || *input == '>') {
        l.lexeme[0] = *input;
        l.lexeme[1] = '\0';
        l.Type = Operateur;
    } else {
        l.Type = Unknow;
    }
    return l;
}

Lexeme is_MotCle(char *input) {
    Lexeme l;
    const char *keywords[] = {"var", "begin", "end", "if", "then", "else", "program"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) { 
        if (strcmp(input, keywords[i]) == 0) {
            strcpy(l.lexeme, input);
            l.Type = Mot_Cle;
            return l;
        }
    }
    l.Type = Unknow;
    return l;
}

Lexeme Analuseur_lexical(char *input) {
    Lexeme mot;
    mot.Type = Unknow; 
    while (*input != '\0') {
        if (isalpha(*input)) {
            mot = is_identification(input);
            if (mot.Type == Identificateur) { 
                mot = is_MotCle(input);
                if (mot.Type == Unknow) { 
                    mot.Type = Identificateur;
                }
            }
        } else if (isdigit(*input)) {
            mot = is_number(input);
        } else if (*input == '<' || *input == '>' || *input == '=') {
            mot = is_Operateur(input);
        } else if (isspace(*input)) {
            input++;
            continue;
        } else {
            mot.Type = Unknow;
                        input++; 
        }
        break; 
    }
    return mot;
}
int main() {
    char input[100];
    printf("Enter Lexeme : ");
    scanf("%s", input);

    if (strlen(input) == 0) {
        printf("Empty input.\n");
        return 1;
    }

    Lexeme result = Analuseur_lexical(input); 
    printf("The lexeme is: %s\n", result.lexeme);
    printf("The type is: %s\n", typeToString(result.Type));

    return 0;
}
