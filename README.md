# Jazyk C: Jak fungují argumenty příkazu

> Jednoduché programy v C demonstrující přebírání argumentů z terminálu


## Východiska
Většina příkazů v Linuxu je napsána v jazyce C, což jim umožňuje efektivně pracovat s nízkoúrovňovými funkcemi operačního systému a nabízet výkonné nástroje pro správu systému. 

🌐 Zdrojové kódy příkazů: [github.com/wertarbyte/coreutils/tree/master/src](https://github.com/wertarbyte/coreutils/tree/master/src)

Tyto příkazy fungují převážně neinteraktivně – při spuštění načítají své argumenty z pole `argv`, které je předáváno jako parametr hlavní funkce `main`. Díky tomu jsou schopny přijímat a zpracovávat vstupy z příkazové řádky, což jim umožňuje provádět specifické úkoly na základě zadaných parametrů bez nutnosti uživatelské interakce v průběhu běhu.

Jinými slovy, interaktivní práce pomocí funkcí jako `scanf` a `printf` je v nástrojích napsaných v jazyce C pro Linux méně obvyklá, protože C byl navržen pro jiný způsob interakce. Místo přímé komunikace s uživatelem je většina C programů pro Linux psána tak, aby fungovala ve stylu "*command-line arguments in, results out*". Tímto způsobem programy mohou načítat vstupy z příkazové řádky, provést požadovanou operaci a vrátit výstup, aniž by vyžadovaly interakci během běhu. 

Tento přístup výrazně usnadňuje řetězení příkazů a skriptování, což je základem automatizace a efektivity v unixových systémech.

Je to stejné, jako když v terminálu zadáte příkaz pro výpis obsahu souboru `cat`:

```
$ cat soubor
```
Převzatým argumentem je řetězec `soubor`. Dá se říct, že pokud program reaguje na jemu předané argumenty, je to obecně velmi užitečná vlastnost. Ne vždy je totiž interakce programu s uživatelem vítaná, neboť mnohé úkoly lze zpracovávat dávkově, a tedy mnohem rychleji.

Chceme-li tedy v programech využít možnost práce s argumenty, definujeme hlavičku funkce `main` typicky takto:

```c
int main(int argc, char *argv[])
```

Prvním parametrem je proměnná `argc`, která v sobě nese **informaci o počtu parametrů**. Druhý parametr `argv` pak představuje **pole řetězců, ve kterých jsou tyto jednotlivé parametry uloženy**. Ve skutečnosti je `argv` *pole ukazatelů na řetězce* (proto ta hvězdička), nicméně díky zaměnitelnosti ukazatele a pole lze na něj pohlížet i tímto jednodušším způsobem. Z historických důvodů se pojmenovávají vždy právě `argc` a `argv` i když to není podmínkou. Budeme to respektovat i my.

Kromě samotných parametrů je v poli `argv`, jako jeho nultá položka, uložen i řetězec se jménem spouštěného programu. Hodnota parametru `argc` uvažuje i tento řetězec. Pokud tedy programu předáme např. tři parametry, bude mít `argc` hodnotu `4` (index 0 až 3).

**Příklad:** Mějme funkci `main` nadefinovanou výše uvedeným způsobem a přeložený program spustíme se dvěma parametry:

```bash
./program par1 par2
```

Pak bude v proměnné `argc` uložena hodnota **3**. První tři položky pole budou obsahovat tyto **řetězce**:

```
argv[0] = ./program
argv[1] = par1
argv[2] = par2
```

## 💾 Program: `main_arg.c`

Vyzkoušejte si jednoduchý program `main_arg.c`, který načte jemu předané parametry a spolu s údajem o jejich počtu je vypíše:

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    
    printf("Pocet parametru: %d\n", argc);
    
    for (i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    
    return 0;
}
```

### Kompilace a spuštění (pro neznalé):

**Kompilace:**

```
$ gcc main_arg. -o main_arg
```
kde `-o main_arg` je název zkompilovaného programu.

**Spuštění:**
```
$ ./main_arg 2 56
```
**Výstup:**
```
Pocet parametru: 3
argv[0] = ./main_arg
argv[1] = 2
argv[2] = 56
``` 

Vyzkoušejte i jiné argumenty a jiné počty.




## Převodní funkce

Všechny předané argumenty jsou v programu interpretovány jako **řetězce**. Jestliže jedním z argumentů je např. číslo `25`, je uvnitř programu řetězec  `"25"`. 

> Ono je to s těmi řetězci v C trochu složitější, neboť C nezná typ "řetězec" jako Python nebo Java, ale pouze **pole znaků**. "25" uloží do pole o délce 3 znaky (bajty): `'2'`, `'5'` a ukončovací znak `\0`:
>
> ```c 
> char s[3] = "25";
>``` 


Je tedy nutné takto načtený argument nejprve převést na číslo (přesněji **načíst do číselné proměnné**) pomocí příslušných funkcí z knihovny `stdlib.h`:

```c
#include <stdlib.h>
...
atoi(); /* prevede na int */
atof(); /* prevede na float */
atol(); /* prevede na long */
```

Všechny tři analyzují řetězec dokud nedosáhnou konce nebo nenarazí na neplatný znak. Zbytek řetězce (pokud existuje) je ignorován. Příklady návratových hodnot převodních funkcí:

```c
char a[] = { "007Bond” };
/*
  atol ... 7
  atof ... 7.000000
  atoi ... 7
*/

char a[] = { “Bond007” };
/*
  atol ... 0
  atof ... 0.000000
  atoi ... 0
*/
```

## 💾 Program: `soucet.c`

Program `soucet.c` převezme dvě čísla jako argument a vypíše jejich součet. program kvůli jednoduchosti neobsahuje 

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a;
    int b;
    
    a = atoi(argv[1]); /* prvni argument */
    b = atoi(argv[2]); /* druhy argument */

    printf("%d + %d = %d\n", a, b, a + b);
    
    return 0;
}
```
Vyzkoušejte např. s tím "Bondem":

```
$ ./soucet 007 007Bond
```


## 💾 Program: `navelka.c`

Program `navelka.c` převede všechny znaky souboru převzatého jako argument na velká písmena.

Spuštění: `$ ./navelka soubor`

```c
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
```

Zkuste:

```
$ ./navelka /home/machac/cvicne/alice.txt
```

## Příkaz `return`

Ukončení programu v C zajišťuje příkaz `return` nikoliv dosažení jeho posledního řádku. Jinými slovy, jakmile program narazí na příkaz `return n;`, **okamžitě ukončí jeho běh a vrátí systému číslo v jeho argumentu**. Proto je funkce `main` datového typu `int` -- vrací číslo:

- Správná deklarace funkce `main`:
	```c
	int main(void)
	{
	    // telo funkce
		
        return 0;
    }
	```
 
- Chybná deklarace funkce `main`:

  ```c
	main()
	{
	    // telo funkce
		
	    return 0;
    }
	```

Platí, že: 
- Pokud jej do kódu nezapíšete, přidá jej na konec funkce `main` překladač `gcc` sám (defaultně přidá `return 0;`).
- `return 0;` .. znamená úspěšné ukončení programu. 
- `return 1;` .. znamená ukončení programu s chybou.

## Odchycení návratové hodnoty
V terminálu si můžeme nechat vypsat návratovou hodnotu nejen svých programů v C, ale i jakéhokoliv příkazu. Stačí do terminálu zapsat:

```bash
$ echo $?
```
Pokud `echo` vypíše `0`, skončil příkaz úspěšně, pokud `1`, skončil s chybou. Vyzkoušejte si to sami:

```bash
machac@TuX  ~
$ wc /home/machac/cvicne/alice.txt
  3601  26470 148576 /home/machac/cvicne/alice.txt

machac@TuX  ~
$ echo $?
0

machac@TuX  ~
$ wc /home/machac/cvicne/alice
wc: /home/machac/cvicne/alice: No such file or directory

machac@TuX  ~
$ echo $?
1

machac@TuX  ~
$
```

## 💾 Program `wc2.c`

Program podobný programu (příkazu) `wc` si můžeme napsat i sami. Náš program se bude jmenovat  `wc2` a jako argument načte textový soubor. V něm spočítá a nakonec vypíše počet řádků, znaků, slov a tako samotný název souboru. Pokud soubor nebude existovat, vypíše chybové hlášení.

> Toto je pouze primitivní příklad, originální program `wc` je [mnohem rozsáhlejší](https://github.com/wertarbyte/coreutils/blob/master/src/wc.c).

Spuštění: `$ ./wc2 soubor`

```c
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
```
### Kontrola

```bash
machac@TuX  ~
$ wc /home/machac/cvicne/alice.txt
  3601  26470 148576 /home/machac/cvicne/alice.txt

machac@TuX  ~
$ ./wc2 /home/machac/cvicne/alice.txt
  3601  32521  148576 /home/machac/cvicne/alice.txt

machac@TuX  ~
$ echo $?
0

machac@TuX  ~
$
```
