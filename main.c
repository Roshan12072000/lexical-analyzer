#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
void compilation(char ch, FILE *fptr);
int iskeyword(char *buffer)
{
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"};
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}
int isoperator(char ch)
{
    int i = 0;
    char operators[] = {'+', '-', '*', '/', '%', '=', '>', '<', '&', '|', '^', '!', '~', '.', ',', '(', ')', '[', ']', '?', ':', '\0'};
    while (operators[i] != '\0')
    {
        if (operators[i] == ch)
            return 1;
        i++;
    }
    return 0;
}
int mul_operators(char *opr)
{
    int i = 0;
    char *multi_operators[] = {"==", "!=", "--", "++", ">=", "<=", "&&", "||", "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "->"};
    for (int i = 0; i < 19; i++)
    {
        if (strcmp(multi_operators[i], opr) == 0)
            return 1;
    }
    return 0;
}
int spec_char(char ch)
{
    int i = 0;
    char sp_char[] = {'@', '$', ';', '{', '}'};
    while (sp_char[i] != '\0')
    {
        if (sp_char[i] == ch)
            return 1;
        i++;
    }
    return 0;
}
int main(int argc,char *argv[])
{
    char *str = argv[1];
    char *adres;
    if(argc < 2 || argc > 2)
    {
        printf("Please provide like this\n <./a.out> <filename.c>\n");
        exit(0);
    }
    if(adres = strstr(str,"."))
    {
        if((strcmp(adres,".c")) != 0)
        {
            printf("Error : Invalid extension\n");
            exit(0);
        }
    }
    else 
    {
     printf("Error : Invalid extension\n");
            exit(0);
    }
    FILE *fptr = fopen(str, "r");
    if (fptr == NULL)
    {
        perror("File can't open");
        return -1;
    }
    
    int n;
    int flag = 0, bracket = 0,flr = 0, count = 0, j = 0,quote = 0,LC = 0,bracket1 = 0;
    char ch, buffer[200], opr[5];
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '/' || ch == '#')
        {
        M:
            ch = fgetc(fptr);
            if (ch == '/')
            {
            L1:
                while ((ch = fgetc(fptr)) != '\n');
                ch = fgetc(fptr);
            }
            else
            {
                fseek(fptr, -2, SEEK_CUR);
                ch = fgetc(fptr);
            }
            if (ch == '#')
                goto L1;
            if (ch == '/')
                goto M;
        }
        if(ch == '\n')
        LC++;
        if(ch == '0')
        {
            buffer[count++] = ch;
            ch = fgetc(fptr);
            if(ch == 'x' || ch == 'X')
            {
                buffer[count++] = ch;
                while((ch = fgetc(fptr)) != ' ')
                {
                    if(ch == ';')
                    break;
                    else if(ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'F' || ch >= 'a' && ch <= 'f')
                    buffer[count++] = ch;
                    else 
                    {
                    printf("%s : %d : Error : invalid suffix \"%c\" on integer constant\n",str,LC,ch);
                    exit(0);
                    }
                }
                
            }
            else if(ch == 'b')
            {
                 buffer[count++] = ch;
                while((ch = fgetc(fptr)) != ' ')
                {
                    if(ch == ';')
                    break;
                    else if(ch == '1' || ch == '0')
                    buffer[count++] = ch;
                    else 
                    {
                    printf("%s : %d : Error : invalid suffix \"%c\" on integer constant\n",str,LC,ch);
                    exit(0);
                    }
                }
               
            }
            else
            {
                  fseek(fptr,-1L,SEEK_CUR);
                while((ch = fgetc(fptr)) != ' ')
                {
                    if(ch == ';')
                    break;
                    else if(ch >= '0' && ch <= '7')
                    buffer[count++] = ch;
                    else 
                    {
                   printf("%s : %d : Error : invalid suffix \"%c\" on integer constant\n",str,LC,ch);
                    exit(0);
                    }
                }
            }
            ch = buffer[count - 1];
              if(ch == '\n')
            LC++;
                fseek(fptr,-1L,SEEK_CUR);
                flag = 2;
                goto print;
          
        }
    
        if (ch == '\'')
        {
            quote++;
            printf("LITERAL"
                   "%12s\t",
                   ":");
            printf("%c", ch);
            ch = fgetc(fptr);
            if(ch == '\'')
            quote++;
            if(ch == ',')
            goto sjump;
            putchar(ch);
            ch = fgetc(fptr);
             if(ch == ',')
            {
               sjump :  printf("\n%s : %d : error :  missing terminating \' character\n",str, LC);
                    exit(0);
            }
            printf("%c", ch);
            if (ch == '0'){
                printf("%c",fgetc(fptr));
                quote++;
            }
            printf("\n");
        }
        else if (ch == '"')
        {
            flag = 1;
            buffer[count++] = ch;
            while ((ch = fgetc(fptr)) != '"')
            {
                if(ch == ',')
               {
                printf("%s : %d : error :  missing terminating \" character\n", str, LC);
                    exit(0);
               }
                buffer[count++] = ch;
            }
            buffer[count++] = ch;
            // ch = fgetc(fptr);
        }
        else if (ch == '_' || isalpha(ch))
        {
            // compilation(ch, fptr);
            buffer[count++] = ch;
            while ((ch = fgetc(fptr)) != ' ')
            {

                if (ch == '_' || isalnum(ch))
                {
                    buffer[count++] = ch;
                }
                else if (isoperator(ch) || ch == ';' || ch == '\'' || ch == '"')
                {
                    break;
                }
                else if (spec_char(ch) && ch != ';')
                {
                    printf("%s : %d : error : expected '=', ',', ';', 'asm' or '__attribute__' before '%c'\n", str,LC, ch);
                    exit(0);
                }
            }
            ch = buffer[count - 1];
            // printf("ch--->%c\n",ch);
              if(ch == '\n')
        LC++;
            fseek(fptr, -1L, SEEK_CUR);
        }
        else if (isdigit(ch) || ch == '.')
        {

            // printf("---->%c",ch);
            int isf = 0, isdl = 0;
            if (flag != 3)
                flag = 2;
            buffer[count++] = ch;
            while ((ch = fgetc(fptr)) != ' ')
            {
                if (ch == 'f' || ch == 'F')
                    isf = 1;
                else if (ch == 'l' || ch == 'L')
                {
                    isdl = 1;
                }

                if (isalpha(ch) && isf != 1 && isdl != 1)
                {
                    printf("%s : %d : error :  invalid suffix  on integer constant\n", str,LC);
                    exit(0);
                }
                else if (spec_char(ch) || isoperator(ch) && ch != '.')
                {
                    break;
                }
                
                buffer[count++] = ch;
                if (ch == '.' || isdl == 1)
                {
                    flag = 3;
                    // goto last;
                }
                else if (isf == 1)
                {
                    flag = 4;
                }
            }
            ch = buffer[count - 1];
              if(ch == '\n')
        LC++;
            fseek(fptr, -1L, SEEK_CUR);
        }

        else if (count > 0)
        {
           print :  buffer[count] = '\0';
            count = 0;
            if (flag == 1)
            {
                printf("LITERAL"
                       "%12s\t%s\n",
                       ":", buffer);
                flag = 0;
            }
            else if (flag == 2)
            {
                printf("NUMERIC CONSTANT"
                       "%3s\t%s\n",
                       ":", buffer);
                flag = 0;
            }
            else if (flag == 3)
            {
                printf("DOUBLE CONSTANT"
                       "%4s\t%s\n",
                       ":", buffer);
                flag = 0;
            }
            else if (flag == 4)
            {
                printf("FLOAT CONSTANT"
                       "%5s\t%s\n",
                       ":", buffer);
                flag = 0;
            }
            else if (iskeyword(buffer) == 1)
            {
                printf("KEYWORD"
                       "%12s\t%s\n",
                       ":", buffer);
            }
            else
                printf("IDENTIFIER"
                       "%9s\t%s\n",
                       ":", buffer);
        }
        if(ch == '\n')
        {
            if(quote % 2 == 1)
            {
                goto sjump;
            }
        }
        if (ch == '(')
        {
            bracket++;
        }
        else if (ch == ')')
            bracket1++;
        else if (bracket != bracket1 && ch == '\n')
        {
            printf("%s : %d : error : expected ')' before ';' token\n",str, LC);
            exit(0);
        }
        if (isoperator(ch) == 1)
        {

            opr[j++] = ch;
            ch = fgetc(fptr);
            opr[j++] = ch;
            opr[j] = '\0';
            if (mul_operators(opr) == 1)
            {
                {
                    printf("OPERATOR"
                           "%11s\t%s\n",
                           ":", opr);
                }
            }
            else
            {
                fseek(fptr, -1L, SEEK_CUR);
                printf("OPERATOR"
                       "%11s\t%c \n",
                       ":", opr[0]);
            }

        last:
            j = 0;
        }
        else if (spec_char(ch) == 1)
        {
            if(ch =='{')
            {
                flr++;
            }
            else if(ch == '}')
            flr--;
            printf("SPECIAL CHAR"
                   "%7s\t%c\n",
                   ":", ch);
        }
    }
    if(flr != 0)
     printf("Error : Missing of '{' \n");
    fclose(fptr);
    return 0;
}
