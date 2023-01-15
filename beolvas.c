#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "beolvas.h"
#include "strukturak.h"
#include <stdio.h>


void befejez(mezo *mezok);

//Ez a függvény beolvassa és eltárolja az összes mezõt egy mezo típusú mezok nevû tömbben, amit majd a többi modul függvényei fel fognak tudni használni.
void beolvas(mezo* mezok){
    FILE *rsz=fopen("szovegek.txt","r");
    int i=0,z=0;
    char sor[2000];
    while(fgets(sor,2000,rsz)){
        sor[strlen(sor)-1]='\0';
        sscanf(sor,"%d\t%[^\n]",&z,&mezok[i].szoveg);
        i++;
    }
    fclose(rsz);

    FILE * rv=fopen("valtozasok.txt","r");
    i=0;
    while(fgets(sor,2000,rv)){
        sor[strlen(sor)-1]='\0';
        sscanf(sor,"%d\t%c\t%d\t%d\t%d\t%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\n",&mezok[i].id,
               &mezok[i].type,&mezok[i].a,&mezok[i].b,&mezok[i].c,&mezok[i].d,&mezok[i].asz,&mezok[i].bsz,&mezok[i].csz,&mezok[i].dsz,&mezok[i].e,
               &mezok[i].u,&mezok[i].sz,&mezok[i].itemp,&mezok[i].itemm,&mezok[i].itemr,&mezok[i].sznev,&mezok[i].szu,&mezok[i].sze);
        befejez(&mezok[i]);
        i++;
    }
    fclose(rv);
}

//ez a függvény arra van használva, hogy egy megadott mezoben a sztringek végére odarakja a befejezõ nullát.
void befejez(mezo *m){
    m->asz[strlen(m->asz)]='\0';
    m->bsz[strlen(m->bsz)]='\0';
    m->csz[strlen(m->csz)]='\0';
    m->dsz[strlen(m->dsz)]='\0';
    m->sznev[strlen(m->sznev)]='\0';
    m->itemm[strlen(m->itemm)]='\0';
    m->itemp[strlen(m->itemp)]='\0';
    m->itemr[strlen(m->itemr)]='\0';
}
