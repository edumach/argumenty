/***************/ 
/*  navelka.c  */
/***************/

#include <stdio.h>

int main(int argc, char *argv[])
{
    // Kontrola, zda byl zadán název souboru
    if (argc < 2)
    {
        fprintf(stderr, "Chybi nazev souboru!\n");
        return 1; 
    }

    FILE *fr;
    int c;

    // Otevreni souboru zadaneho jako argument
    fr = fopen(argv[1], "r");
    if (fr == NULL)
    {
        fprintf(stderr, "Chyba: Soubor %s nelze otevrit.\n", argv[1]);
        return 1; /* konec kvuli chybe */
    }

    // Ctení souboru a prevod na velka pismena
    while ((c = getc(fr)) != EOF)
    {
        // Prevod malych pismen na velka
        if (c >= 'a' && c <= 'z')
        {
            c -= 32;
        }
        putchar(c);
    }

    putchar('\n');
    fclose(fr);
    
    return 0;
}

