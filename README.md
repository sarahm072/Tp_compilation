# Creation d'un Analyseur Lexical
Ce Tp a pour objectif de developper un analyseur lexical simple sans utiliser l’outil lex….(ou une variante du lex), en utilisant seulement 
un langage de programmation C.

## Etapes en Detail:
1- Definier les Type de Lexeme:

- Nous commencons par definir les differents types de lexemes que nous allons reconnaitre, comme les identificateurs, les nombres, les operateurs relationnels, et les mots-cles.

'''

    typedef{
         Identificateur,
         Nombre,
         Operateur,
         Mot_Cle,
         Unknow
         }TypeLexeme;
  
2-Definir la structure de Lexeme:
  - Nous creons une structure pour represnter un lexeme, qui inclut son type et sa valeur lexicale.

'''

    typedef struct{
        TypeLexeme Type;
        char lexeme[100];
        }Lexeme;

3-Ecrire des Fonctions pour Reconnaitre les lexeme:
  - Nous ecrivons des fonctions pour reconnaitre chaque type de lexeme.
   
     a-Reconnaitre  les identificateurs:

'''

    Lexeme is_identification(char *input){
    Lexeme l;  
    int i=0;
        //isalpha() verifier si input containt des alphabet. [a-zA-Z]
    if(isalpha(input[0])){  
      l.lexeme[i] = input[0];
      //isalnum() verifier si input containt des alphabet ou des nombres.[a-zA-Z0-9]
      while (isalnum(input[i]))   
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
  
    
   b- Reconnaitre  les Nombres:

'''

    Lexeme is_number(char *input){
    Lexeme l;
    int i=0;
      //isdigit() verifier si input containt des nombres [0-9]
    if(isdigit(input[i])){
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

   c- Reconnaitre  les Operateurs Relationnels:

'''

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

   d- Reconnaitre  les Mots-Cles:

'''

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

 4- Ecrire la Fonction Principale de l'Analyseur Lexical:
   - Nous assemblons toutes les fonctions de reconnaissance dans une seule fonction d'analyseur lexical.

'''

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

5-La Fonctions Main:

'''
 
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
