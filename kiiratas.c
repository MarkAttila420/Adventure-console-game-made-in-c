#include <stdio.h>
#include "kiiratas.h"
#include "beolvas.h"
#include "econio.h"
#include "strukturak.h"
#ifdef _WIN32
    #include <windows.h>
#endif

//ez a függvény kiírja a megadott mezőt a képernyőre, és a játékos adatait.
void kiiratas(mezo m,playerdata p){
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    econio_clrscr();
    printf("Életerő pontod: %d / %d\nSzerencse pontod: %d / %d\nÜgyesség pontod: %d / %d\n",p.e,p.emax,p.sz,p.szmax,p.u,p.umax);
    vonal();
    int sor=4;
    bont(m.szoveg,false,&sor);
    printf("\n");
    vonal();
    sor+=2;
    if(m.a!=0&&m.type=='n'||m.type=='k'){
        printf("Választási lehetõségek:\n[1]\t");
        sor++;
        bont(m.asz,true,&sor);
        if(m.b!=0){
            printf("\n[2]\t");
            sor++;
            bont(m.bsz,true,&sor);
            if(m.c!=0){
                printf("\n[3]\t");
                sor++;
                bont(m.csz,true,&sor);
                if(m.d!=0){
                    printf("\n[4]\t");
                    sor++;
                    bont(m.dsz,true,&sor);
                }
            }
        }
        printf("\n[i]\tEszköztár megnyitása.\n[q]\tMentés és kilépés.\n");
        vonal();
    }
    else if(m.type=='s'||m.type=='h'){
        printf("Választási lehetőségek:\n[1]\tTovább.\n[i]\tEszköztár megnyitása.\n[q]\tMentés és kilépés.\n");
        vonal();
    }
}

/*ez a függvény arra jó, hogy az adott szöveget kiírja, olyan formában, hogy ha egy sor 100 karakter hosszú, akkor új sort kezd,
bemenetnek a kiírandó sztringet kapja, egy sor változót ami számolja, hogy jelenleg a képernyő hanyadik sorában jár.
és egy bool-t, ami azért kell, mert ha a kapott sztring az egy választási lehetőség, akkor nem a sor elején kell kezdődjön a kiiratás,
hanem előtte kell legyen egy tabulátorjel. */
void bont(char *str,bool opcio,int *sor){
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
    int s=*sor;
    int hossz=0;
    if(opcio)//akkor true, ha a mezőben van választási lehetőség
        hossz=4;
    for(int i=0;str[i]!='\0';i++){
        hossz+=printf("%c",str[i]);
        if(hossz>=100){
            for(int j=i+1;str[j]!=' ';j--){
                if(str[j-1]==' '){
                    econio_gotoxy(100-i+j-1,s);
                    if(opcio)
                        econio_gotoxy(104-i+j-1,s);
                    for(int x=0;x<i-j+1;x++){
                        printf(" ");
                    }
                    printf("\n");
                    i=j-1;
                    s++;
                    hossz=0;
                    if (opcio){
                        printf("\t");
                        hossz=4;
                    }
                }
            }
        }
    }
    *sor=s;
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
}
