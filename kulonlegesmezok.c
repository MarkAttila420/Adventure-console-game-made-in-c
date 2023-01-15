#include <stdio.h>
#include "kiiratas.h"
#include "beolvas.h"
#include "econio.h"
#include "strukturak.h"
#include "fuggvenyek.h"
#include "inventory.h"
#ifdef _WIN32
    #include <windows.h>
#endif

void husz(mezo m,int *hely, playerdata *p, itemek *fej){
    econio_clrscr();
    kiiratas(m,*p);
    int valasz=rosszvalasz(2,"Melyiket választod? ");
    if(valasz==-1){
        while(valasz==-1){
        invkiir(fej,&*p);
        kiiratas(m,*p);
        valasz=rosszvalasz(2,"Melyiket választod? ");
        }
    }
    if(valasz==-2){
        invmentes(fej);
        mentes(m,*p,&*hely);
    }
    else if(valasz==2){
        *hely=m.b-1;
    }
    else if(valasz==1){
        econio_clrscr();
        printf("Életerő pontod: %d / %d\nSzerencse pontod: %d / %d\nÜgyesség pontod: %d / %d\n",p->e,p->emax,p->sz,p->szmax,p->u,p->umax);
        vonal();
        printf("Az első szám: ");
        scanf("%d",&valasz);
        if(valasz==15){
            printf("A második szám: ");
            scanf("%d",&valasz);
            if(valasz==10){
                printf("A harmadik szám: ");
                scanf("%d",&valasz);
                if(valasz==22){
                    *hely=m.a-1;
                }
                else{
                    *hely=m.b-1;
                }
            }
            else{
                *hely=m.b-1;
            }
        }
        else{
            *hely=m.b-1;
        }
    }
}

void nk(mezo m,int *hely, playerdata *p, itemek *fej){
    econio_clrscr();
    kiiratas(m,*p);
    normalm(m,&*hely,&*p,fej);
    p->szmin=6;
}

void hh(mezo m,int *hely, playerdata *p, itemek *fej){
    econio_clrscr();
    kiiratas(m,*p);
    itemek *temp;
    int valasz;
    valasz=rosszvalasz(1,"Melyiket választod? ");
    if(valasz==-1){
        while(valasz==-1){
        invkiir(fej,&*p);
        kiiratas(m,*p);
        valasz=rosszvalasz(2,"Melyiket választod? ");
        }
    }
    if(valasz==-2){
        invmentes(fej);
        mentes(m,*p,&*hely);
    }
    for(int x=0;x<=1;x++){
        econio_clrscr();
        int db=0;
        printf("Életerő pontod: %d / %d\nSzerencse pontod: %d / %d\nÜgyesség pontod: %d / %d\n",p->e,p->emax,p->sz,p->szmax,p->u,p->umax);
        vonal();
        for(temp=fej;temp;temp=temp->next){
            if(strstr(temp->targy.nev,"Életerő Itala")!=NULL||strstr(temp->targy.nev,"Ügyesség Itala")!=NULL||strstr(temp->targy.nev,"Szerencse Itala")!=NULL||strstr(temp->targy.nev,"Élelem")!=NULL){
                #ifdef _WIN32
                SetConsoleCP(CP_UTF8);
                SetConsoleOutputCP(CP_UTF8);
                #endif
                printf("[%d]\t%d db %s\n",db+1,temp->targy.db,temp->targy.nev);
                #ifdef _WIN32
                SetConsoleCP(1250);
                SetConsoleOutputCP(1250);
                #endif
            }
            else{
                #ifdef _WIN32
                SetConsoleCP(1250);
                SetConsoleOutputCP(1250);
                #endif
                printf("[%d]\t%d db %s\n",db+1,temp->targy.db,temp->targy.nev);
            }
            db++;
        }
        vonal();
        #ifdef _WIN32
            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
        #endif
        valasz=rosszvalasz(db,"Melyikből veszítesz el egyet? ");
        temp =fej;
        for(int i=0;i<valasz-1;i++){
            temp=temp->next;
        }
        if(temp->targy.db==1){
            fej=torles(fej,temp->targy);
        }
        else{
            char kivalasztott[50];
            strcpy(kivalasztott,temp->targy.nev);
            temp=keres(fej,kivalasztott);
            temp->targy.db--;
        }
    }
    *hely=m.a-1;
}

void szt(mezo m,int *hely, playerdata *p, itemek *fej){
    m.sze=p->e;
    m.szu=p->u;
    econio_clrscr();
    kiiratas(m,*p);
    harcm(m,&*hely,&*p,fej);
}

void sznny(mezo m,int *hely, playerdata *p, itemek *fej){
    econio_clrscr();
    int pont=rand()%6+1+rand()%6+1;
    m.type='s';
    kiiratas(m,*p);
    int valasz=rosszvalasz(1,"Melyiket választod? ");
    if(valasz==-1){
        while(valasz==-1){
        invkiir(fej,&*p);
        kiiratas(m,*p);
        valasz=rosszvalasz(2,"Melyiket választod? ");
        }
    }
    if(valasz==-2){
        invmentes(fej);
        mentes(m,*p,&*hely);
    }
    else{
        if(p->e >= pont){
            *hely=m.a-1;
        }
        if(p->e < pont){
            *hely=m.b-1;
        }
    }

    m.type='k';
}

void szho(mezo m,int *hely, playerdata *p, itemek *fej){
    econio_clrscr();
    int szam=rand()%6+1;
    kiiratas(m,*p);

    p->e-=szam;
    int valasz=rosszvalasz(1,"Melyiket választod? ");
    *hely=m.a-1;
}


void kulonlegesm(mezo m,int *hely,playerdata *p,itemek *fej){
    switch(m.id){
    case 20:
        husz(m,&*hely,&*p,fej);
        econio_clrscr();
        break;
    case 49:
        nk(m,&*hely,&*p,fej);
        econio_clrscr();
        break;
    case 63:
        hh(m,&*hely,&*p,fej);
        econio_clrscr();
        break;

    case 110:
        szt(m,&*hely,&*p,fej);
        econio_clrscr();
        break;
    case 148:
        sznny(m,&*hely,&*p,fej);
        econio_clrscr();
        break;
    case 165:
    case 8:
        szho(m,&*hely,&*p,fej);
        econio_clrscr();
        break;

    default:
        econio_clrscr();
        printf("Valami hiba történt.");
        getchar();
        break;

    }

}
