/***********/
/*  wc2.c  */
/***********/

#include <stdio.h> 

int main(int argc, char *argv[])
{
    // Kontrola, zda byl zadan nazev souboru
    if (argc < 2)
    {
        fprintf(stderr, "Chybi nazev souboru!\n");
        return 1; /* konec kvuli chybe */
    }    

    int c, znak = 0, radek = 0, slovo = 0;
    FILE *fr;

    // Otevrení souboru zadaného jako argument
    fr = fopen(argv[1], "r");
    if (fr == NULL)
    {
        fprintf(stderr, "Chyba: Soubor %s nelze otevrit.\n", argv[1]);
        return 1; /* konec kvuli chybe */
    }

    while ((c = getc(fr)) != EOF)
    {
        /* znaky */
        znak++;

        /* radky */
        if(c == '\n') radek++;

        /* slova */
        if(c == 32) slovo++;
    }

    /* vystup */
    slovo += radek; /* pricti koncova slova pred \n */
    printf("  %3d  %3d  %3d %s\n", radek, slovo, znak, argv[1]);

	fclose(fr);

    return 0; 
} 

