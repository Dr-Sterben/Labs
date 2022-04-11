#include <stdio.h>
#include <stdlib.h>

#define LENGTH 1000
#define _CRT_SECURE_NO_WARNINGS

char voidW[] = "void";
char intW[] = "int";
char charW[] = "char";
char longW[] = "long";
int pos = 0;

int isVoid(char *checker, int a)
{
    for (int i = 0; i < a + 1; i++)
    {
        if (checker[i] != voidW[i])
            return 0;
    }
    return 1;
}
int isInt(char *checker, int a)
{
    for (int i = 0; i < a + 1; i++)
    {
        if (checker[i] != intW[i])
            return 0;
    }
    return 1;
}
int isChar(char *checker, int a)
{
    for (int i = 0; i < a + 1; i++)
    {
        if (checker[i] != charW[i])
            return 0;
    }
    return 1;
}
int isLong(char *checker, int a)
{
    for (int i = 0; i < a + 1; i++)
    {
        if (checker[i] != longW[i])
            return 0;
    }
    return 1;
}

void stringCopyTo(char *string, char *functions)
{
    int a = 0;
    while (string[a] != 0)
    {
        if (string[a] == '\n')
            break;
        else if (string[a] == '{')
            functions[pos + a] = ';';
        else
            functions[pos + a] = string[a];
        pos++;
    }
}

// void HeaderEdit(FILE korm, FILE header) {
void HeaderEdit()
{
    char *checker = (char *)malloc(LENGTH * sizeof(char));
    int a = 0, b = 0, flag = 0;
    char *string = (char *)malloc(LENGTH * sizeof(char));
    char *functions = (char *)malloc(10000000 * sizeof(char));
    FILE *in = fopen("Korm.cpp", "r");
    
    if (in == NULL)
    {
        printf("ERROR");
        // getchar();
    }
    else
    {
        while (!feof(in))
        {
    printf("kek 1\n");
            fgets(string, LENGTH, in);
            printf("%s\n", string);
            a = 0;
            while ((string[a] != ' ') && (string[a] != '*'))
            { //������ �����
                checker[a] = string[a];
                a++;
            }
            checker[a] = 0;
            b = 0;
            while (string[b] != 0)
            {
                if (string[b] == '{')
                    flag = 1;
                b++;
            }
            if (((isChar(checker, a)) || (isInt(checker, a)) || (isLong(checker, a)) || (isVoid(checker, a))) && (flag == 1))
                stringCopyTo(checker, functions);
        }
        functions[pos] = 0;

        fclose(in);
    }

    FILE *out = fopen("KormHeader.txt", "w");
    if (out == NULL) printf("ERROR");
    else {
        fprintf(out, "%s", functions);
        printf("%s\n", functions);
        fclose(out);
    }
}