#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char *keywords[] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void"
};

int isKeyword(char word[])
{
    int i;

    for (i = 0; i < 9; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    char filename[50];
    char ch, next;
    char token[100];
    int i;

    printf("Enter input file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 0;
    }

    printf("\nTokens:\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        /* Ignore whitespace */
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        /* Handle comments and division operator */
        if (ch == '/')
        {
            next = fgetc(fp);

            /* Single-line comment */
            if (next == '/')
            {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF)
                    ;
 
                continue;
            }

            /* Multi-line comment */
            if (next == '*')
            {
                while (1)
                {
                    ch = fgetc(fp);

                    if (ch == '*' && fgetc(fp) == '/')
                        break;

                    if (ch == EOF)
                        break;
                }

                continue;
            }

            /* Division operator */
            ungetc(next, fp);

            printf("Operator: /\n");
            continue;
        }

        /* Identifier or keyword */
        if (isalpha(ch) || ch == '_')
        {
            i = 0;

            while (isalnum(ch) || ch == '_')
            {
                if (i < MAX - 1)
                    token[i++] = ch;

                ch = fgetc(fp);
            }

            token[i] = '\0';

            ungetc(ch, fp);

            if (isKeyword(token))
                printf("Keyword: %s\n", token);
            else
                printf("Identifier: %s\n", token);

            continue;
        }

        /* Number */
        if (isdigit(ch))
        {
            i = 0;

            while (isdigit(ch) || ch == '.')
            {
                if (i < MAX - 1)
                    token[i++] = ch;

                ch = fgetc(fp);
            }

            token[i] = '\0';

            ungetc(ch, fp);

            printf("Number: %s\n", token);

            continue;
        }

        /* Operators */
        if (ch == '+' || ch == '-' ||
            ch == '*' || ch == '%' ||
            ch == '=' || ch == '<' ||
            ch == '>')
        {
            next = fgetc(fp);

            /* Two-character operators */
            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '='))
            {
                printf("Operator: %c%c\n", ch, next);
            }
            else
            {
                printf("Operator: %c\n", ch);
                ungetc(next, fp);
            }

            continue;
        }

        /* Symbols */
        if (ch == ';' || ch == ',' ||
            ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == '[' || ch == ']')
        {
            printf("Symbol: %c\n", ch);
            continue;
        }

        /* Unknown character */
        printf("Unknown: %c\n", ch);
    }

    fclose(fp);

    return 0;
}