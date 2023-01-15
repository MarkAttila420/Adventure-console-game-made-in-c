#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "beolvas.h"
#include "kiiratas.h"
#include "strukturak.h"
#include "fuggvenyek.h"
#include "debugmalloc.h"
#ifdef _WIN32
    #include <windows.h>
#endif

//ez a függvény csak a teszteléshez van használva, a végleges verzióban már nem lesz benne, arra jó, hogy egy mezőnek kiírja egy sorban az összes adatát.
void kiir(mezo mezok){
    printf("id: %d, ",mezok.id);
    printf("type: %c, ",mezok.type);
    printf("a: %d, b: %d, c: %d, d: %d, ",mezok.a,mezok.b,mezok.c,mezok.d);
    printf("asz: %s, bsz: %s, csz: %s, dsz: %s, ",mezok.asz,mezok.bsz,mezok.csz,mezok.dsz);
    printf("e: %d, u: %d, sz: %d, ",mezok.e,mezok.u,mezok.sz);
    printf("itemp: %s, itemm: %s, itemr: %s, sznev: %s, ",mezok.itemp,mezok.itemm,mezok.itemr,mezok.sznev);
    printf("szu: %d, sze: %d,",mezok.szu,mezok.sze);
    printf("szoveg: %s\n",mezok.szoveg);

}

int main(){
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif

    econio_set_title("Az Ítélet Labirintusa");
    srand(time(0));
    mezo mezok[200];
    bool voltmar[200];
    for(int i=0;i<200;i++){
        voltmar[i]=false;
    }
    playerdata tempplyr,plyr;
    bool end=false,uj=false;
    int tempmost,most,emax,umax,szmax,elozomost;
    itemek *fej=NULL;
    char sor[1000];

    printf("Választási lehetőségek:\n[1]\tJáték elezdése az elejéről.\n[2]\tMentés betöltése.\n");
    vonal();
    int valasz;
    do{
        valasz=rosszvalasz(2,"Melyiket választod? ");
    }while(valasz==-1||valasz==-2);
    econio_clrscr();

    beolvas(mezok);
    FILE * elozo=fopen("mentes.txt","r");
    FILE * invmentett=fopen("inventory.txt","r");
    if(elozo!=NULL&&invmentett!=NULL&&valasz==2){
        fgets(sor,1000,elozo);
        if(sor[0]!='0'){
            sscanf(sor,"%d\t%d\t%d\t%d\t%d\t%d\t%d",&most,&plyr.e,&plyr.emax,&plyr.u,&plyr.umax,&plyr.sz,&plyr.szmax);
        }
        else
            uj=true;
        if(!uj){
            char invsor[90];
            while(fgets(invsor,90,invmentett)){
                invsor[strlen(invsor)-1]='\0';
                item uj;
                sscanf(invsor,"%d\t%[^\t]\t%c\t%c\t%d\n",&uj.db,&uj.nev,&uj.felhaszn,&uj.valt,&uj.ertek);
                uj.nev[strlen(uj.nev)]='\0';
                fej=hozzaad(fej,uj);
            }
        }
    }
    else
        uj=true;
    fclose(elozo);
    fclose(invmentett);
    if(uj){
        printf("Az alábbi 3 Varázsital közül egyet magaddal vihetsz a kalandodra:\n"
               "[1]\tÜgyesség Itala (visszaállítja ügyesség pontjaidat a kezdeti értékre)\n"
               "[2]\tÉleterő Itala (visszaállítja életerő pontjaidat a kezdeti értékre)\n"
               "[3]\tSzerencse Itala (visszaállítja szerencse pontjaidat a kezdeti értékre)\n");
        vonal();
        do{
            valasz=rosszvalasz(3,"Melyiket szeretnéd magaddal vinni? ");
        }while(valasz==-2||valasz==-1);

        item ital;
        ital.db=2;
        ital.felhaszn='i';

        item elelem;
        elelem.db=5;
        strcpy(elelem.nev,"Élelem (visszatölt 4 Életerő pontot.)");
        elelem.felhaszn='i';
        elelem.valt='e';
        elelem.ertek=4;

        switch(valasz){
        case 1:
            strcpy(ital.nev,"Ügyesség Itala (visszaállítja ügyesség pontjaidat a kezdeti értékre)");
            ital.valt='u';
            ital.ertek=12;
            break;
        case 2:
            strcpy(ital.nev,"Életerő Itala (visszaállítja életerő pontjaidat a kezdeti értékre)");
            ital.valt='e';
            ital.ertek=24;
            break;
        case 3:
            strcpy(ital.nev,"Szerencse Itala (visszaállítja szerencse pontjaidat a kezdeti értékre)");
            ital.valt='s';
            ital.ertek=12;
            break;
        }
        fej=hozzaad(fej,ital);
        fej=hozzaad(fej,elelem);

        most=1;
        plyr.e=(rand()%6+1)+(rand()%6+1)+12;
        plyr.emax=plyr.e;
        plyr.sz=(rand()%6+1)+6;
        plyr.szmax=plyr.sz;
        plyr.u=(rand()%6+1)+6;
        plyr.umax=plyr.u;
        char kezdes[2500];
        int sorhossz=0;
        FILE * kezdet=fopen("alap.txt","r");
        fgets(kezdes,2500,kezdet);
        fclose(kezdet);
        kezdes[strlen(kezdes)]='\0';
        econio_clrscr();
        bont(kezdes,false,&sorhossz);
        printf("\n");
        vonal();
        printf("Választási lehetőségeid:\n[1]\tTovább.\n");
        vonal();
        do{
            valasz=rosszvalasz(1,"Írj be egy \"1\"-est a folytatáshoz! ");
        }while(valasz==-1||valasz==-2);
        econio_clrscr();
    }
    most--;
    while(!end){
        if(!voltmar[most]){

            if(plyr.e+mezok[most].e<=plyr.emax)
                plyr.e+=mezok[most].e;
            else if(plyr.e+mezok[most].e>plyr.emax)
                plyr.e=plyr.emax;

            if(plyr.u+mezok[most].u<=plyr.umax)
                plyr.u+=mezok[most].u;
            else if(plyr.u+mezok[most].u>plyr.umax)
                plyr.u=plyr.umax;

            if(plyr.sz+mezok[most].sz<=plyr.szmax)
                plyr.sz+=mezok[most].sz;
            else if(plyr.sz+mezok[most].sz>plyr.szmax)
                plyr.sz=plyr.szmax;
            if(plyr.sz+mezok[most].sz<plyr.szmin)
                plyr.sz=plyr.szmin;

            if(strcmp(mezok[most].itemp,"0")!=0){
                item ujitem;
                sscanf(mezok[most].itemp,"%d;%[^;];%c;%d;%c",&ujitem.db,&ujitem.nev,&ujitem.valt,&ujitem.ertek,&ujitem.felhaszn);
                ujitem.nev[strlen(ujitem.nev)]='\0';
                itemek* temp=keres(fej,ujitem.nev);
                if(temp==NULL){
                    fej=hozzaad(fej,ujitem);
                }
                else{
                    temp->targy.db+=ujitem.db;
                }
            }
            if(strcmp(mezok[most].itemm,"0")!=0){
                int dbminusz;
                char itemnev[30];
                sscanf(mezok[most].itemm,"%d;%[^\0]",&dbminusz,&itemnev);
                itemnev[strlen(itemnev)]='\0';
                itemek *temp =keres(fej,itemnev);
                if(temp->targy.db==1){
                    fej=torles(fej,temp->targy);
                }
                else{
                    temp->targy.db-=dbminusz;
                }
            }
            if(strcmp(mezok[most].itemr,"0")!=0){
                char elveszik;
                int dbminusz;
                char itemnev[30];
                item itemminusz;
                sscanf(mezok[most].itemr,"%d;%c;%[^\0]",&dbminusz,&elveszik,&itemnev);
                itemnev[strlen(itemnev)]='\0';
                itemek *temp=keres(fej,itemnev);
                if (temp==NULL){
                    econio_clrscr();
                    #ifdef _WIN32
                        SetConsoleCP(CP_UTF8);
                        SetConsoleOutputCP(CP_UTF8);
                    #endif
                    printf("Nem tudsz ide lépni, mert hiányzik az eszköztáradból a(z) \"%s\" nevű tárgy.\n",itemnev);
                    vonal();
                    printf("Nyomj egy gombot a visszalépéshez.");
                    #ifdef _WIN32
                        SetConsoleCP(1250);
                        SetConsoleOutputCP(1250);
                    #endif
                    getchar();
                    econio_clrscr();
                    most=elozomost;
                }
                else if(elveszik=='i'){
                    if(temp->targy.db-dbminusz<0){
                        econio_clrscr();
                        #ifdef _WIN32
                        SetConsoleCP(CP_UTF8);
                        SetConsoleOutputCP(CP_UTF8);
                        #endif
                        printf("Nem tudsz ide lépni, mert nincs elég az eszköztáradban a(z) \"%s\" nevű tárgyból.\n",itemnev);
                        vonal();
                        printf("Nyomj egy gombot a visszalépéshez.");
                        #ifdef _WIN32
                        SetConsoleCP(1250);
                        SetConsoleOutputCP(1250);
                        #endif
                        getchar();
                        econio_clrscr();
                        most=elozomost;
                    }
                    else if(temp->targy.db-dbminusz==0){
                        temp=torles(fej,temp->targy);
                    }
                    else if(temp->targy.db-dbminusz>0){
                        temp->targy.db-=dbminusz;
                    }
                }
            }
        }

        kiiratas(mezok[most],plyr);
        voltmar[most]=true;
        elozomost=most;
        switch(mezok[most].type){
        case'n':
            normalm(mezok[most],&most,&plyr,fej);
            break;
        case'h':
            harcm(mezok[most],&most,&plyr,fej);
            break;
        case's':
            szerencsem(mezok[most],&most,&plyr,fej);
            break;
        case'v':
            vegem(&most);
            fej=listatorol(fej);
            break;
        case 'k':
            kulonlegesm(mezok[most],&most,&plyr,fej);
            break;
        default:
            printf("Ez a mező még nincsen beprogramozva");
            end=true;
            break;
        }
        if(plyr.e<=0){
            #ifdef _WIN32
                SetConsoleCP(CP_UTF8);
                SetConsoleOutputCP(CP_UTF8);
            #endif
            printf("Meghaltál! ");
            #ifdef _WIN32
                SetConsoleCP(1250);
                SetConsoleOutputCP(1250);
            #endif
            fej=listatorol(fej);
            vegem(&most);
        }
        if(most<=-1){
            end=true;
        }
    }
    return 0;
}
