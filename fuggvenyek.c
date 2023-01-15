#include "strukturak.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#endif

//ezt a fuggvenyt felhasználja az ebben a modulban lévő többi függvény, ahhoz, hogy létrehozzon, vagy ha létezik akkor felülírja a "mentes.txt" -t, amiben a jelenlegi adatok vannak eltarolva.
void mentes(mezo m,playerdata p,int *hely){
    FILE *ment=fopen("mentes.txt","w");
    if(ment==NULL){
        econio_clrscr();
        printf("Valami baj volt a mentéssel!");
    }
    else{
        fprintf(ment,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",m.id,p.e,p.emax,p.u,p.umax,p.sz,p.szmax,p.szmin);
        fclose(ment);
        *hely=-1;
        econio_clrscr();
        printf("A mentés sikeres volt. Nyomj egy gombot a bezáráshoz.");
        getchar();
    }
}

//ez a fuggveny kiír egy 100 hosszu vonalat, a többi modulban is fel van hasznalva.
void vonal(){
    printf("+");
    for(int i=1;i<=98;i++){
        printf("-");
    }
    printf("+\n");
}

// ez a függvény dönti el, hogy a felhasználónak szerencséje van-e vagy nincs, ha igen, akkor true-val tér vissza
bool szerencse(playerdata *p){
    int pont=rand()%6+1+rand()%6+1;
    int sz=p->sz;
    if(sz>p->szmin){
        if(pont<=sz){
            return true;
        }
        else if(pont>sz){
            return false;
        }
    }
    return false;
}

//ez a függvény arra van használva, hogy a felhasználó ha nem megfelelő lehetőséget választ a felhasználó, akkor újra megkérdezi, hogy mit válasz, a db az a választási lehetőségek darabszámát jelöli(az eszköztár és a mentés kilépést nem számolja bele)
int rosszvalasz(int db,char *str){
    bool rossz=true;
    do{
        printf("%s",str);
        char n=getchar();
        char *valasz=(char*)malloc(sizeof(char));
        int x=0;
        valasz[0]=n;
        while(valasz[x]!='\n'){
            x++;
            valasz=(char*)realloc(valasz,x+1*sizeof(char));
            valasz[x]=getchar();
        }
        valasz[x]='\0';
        int intvalasz=atoi(valasz);
        if(valasz[1]=='\0'){
            if(valasz[0]=='i'||valasz[0]=='I'){
                rossz=false;
                free (valasz);
                return -1;
            }
            if(valasz[0]=='q'||valasz[0]=='Q'){
                rossz=false;
                free (valasz);
                return -2;
            }
        }
        for(int i=1;i<=db;i++){
            if(i==intvalasz){
                rossz=false;
                i=db;
                free (valasz);
                return intvalasz;
            }
        }
        free (valasz);
    }while(rossz);
}

int szornysebez(playerdata *p,int *szerencsevolt,int *valasz){
    playerdata masolat;
    masolat.e=p->e;
    masolat.sz=p->sz;
    printf("Az ellenséged megsebzett.(veszítesz 2 életerő pontot)\n");
    vonal();
    printf("Választási lehetőségek:\n[1]\tTovább.\n[2]\tSzerencse használata.\n");
    vonal();
    *valasz=rosszvalasz(2,"Melyik lehetőséget választod? ");
    if(*valasz==1){
        masolat.e-=2;
    }
    else if(*valasz==2&&szerencse(&masolat)){
        *szerencsevolt=1;
        masolat.e--;
    }
    else if(*valasz==2&&!szerencse(&masolat)){
        *szerencsevolt=-1;
        masolat.e-=3;
    }
    p->e=masolat.e;
    p->sz=masolat.sz;
    return -1;
}
int playersebez(playerdata *p,int * szerencsevolt,mezo *m,int *valasz){
    playerdata masolat;
    masolat.e=p->e;
    masolat.sz=p->sz;
    masolat.szmin=p->szmin;
    printf("Megsebezted az ellenségedet.(veszít 2 életerő pontot)\n");
    vonal();
    printf("Választási lehetőségek:\n[1]\tTovább.\n[2]\tSzerencse használata.\n");
    vonal();
    *valasz=rosszvalasz(2,"Melyik lehetőséget választod? ");
    if(*valasz==1){
        m->sze-=2;
    }
    else if(*valasz==2&&szerencse(&masolat)){
        *szerencsevolt=1;
        m->sze-=3;
    }
    else if(*valasz==2&&!szerencse(&masolat)){
        *szerencsevolt=-1;
        m->sze--;
    }
    p->e=masolat.e;
    p->sz=masolat.sz;
    return 1;
}

void dontetlen(int *szerencsevolt,int *valasz){
    printf("Kivédtétek egymás támadását.(senki se veszít életerőpontot.)\n");
    vonal();
    printf("Választási lehetőségek:\n[1]\tTovább.\n");
    vonal();
    *valasz=rosszvalasz(1,"Melyik lehetőséget választod? ");
}

//ez a függvény a csak a main-ben lesz felhasználva. A felhasználó döntése alapján megváltoztatja a main-beli most változó értékét, és ezzel meghatározza, hogy melyik mező következik
void normalm(mezo m,int *hely,playerdata *p,itemek *fej){
    playerdata masolt=*p;
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    int valasz;
    if(m.d!=0)
        valasz=rosszvalasz(4,"Melyik lehetőséget választod? ");
    else if(m.c!=0)
        valasz=rosszvalasz(3,"Melyik lehetőséget választod? ");
    else if(m.b!=0)
        valasz=rosszvalasz(2,"Melyik lehetőséget választod? ");
    else
        valasz=rosszvalasz(1,"Melyik lehetőséget választod? ");
    switch(valasz){
    case 4:
        *hely=m.d-1;
        econio_clrscr();
        break;
    case 3:
        *hely=m.c-1;
        econio_clrscr();
        break;
    case 2:
        *hely=m.b-1;
        econio_clrscr();
        break;
    case 1:
        *hely=m.a-1;
        econio_clrscr();
        break;
    case -2:
        invmentes(fej);
        mentes(m,masolt,&*hely);
        break;
    case -1:
        invkiir(fej,&*p);
        break;
    default:
        printf("Valami probléma van.");
        break;
    }
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
}

//ez a függvény csak a main-ben lesz felhasználva. A szerencse függvény felhasználásával eldönti, hogy melyik melyik mezőn folytatódik a történet, azzal, hogy megváltoztatja a main-beli most változó értékét.
void szerencsem(mezo m,int *hely,playerdata *p,itemek *fej){
    playerdata masolt=*p;
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    int valasz=rosszvalasz(1,"Melyik lehetőséget választod? ");
    if(valasz==1&&szerencse(&*p)){
        *hely=m.a-1;
        econio_clrscr();
    }
    else if(valasz==1&&!szerencse(&*p)){
        *hely=m.b-1;
        econio_clrscr();
    }
    else if(valasz==-2){
        invmentes(fej);
        mentes(m,masolt,&*hely);
    }
    else if(valasz==-1){
        invkiir(fej,&*p);
    }
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
}

//ez a függvény csak a main-ben lesz felhasználva. A játékos életerő pontját megváltoztatja, az alapján, hogy mennyi sebzést szenved el, és ha sikeresen legyőzi az ellenséget, akkor folytathatja a játékot, ha elfogy az életerőpontja, akkor vége van a játéknak
void harcm(mezo m,int *hely,playerdata *p,itemek *fej){
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    playerdata masolt=*p;
    int valasz;
    bool harcvege=false;
    int tamadas,sztamadas,dobas,szerencsevolt,pvsz; //első kettő a támadóerők, a dobás, volt e szerencse az előző körben, player vagy szörny sebzett
    valasz=rosszvalasz(1,"Melyik lehetőséget választod? ");
    if(valasz==-2){
        invmentes(fej);
        mentes(m,masolt,&*hely);
    }
    else if(valasz==-1){
        invkiir(fej,&*p);
    }
    else{
        #ifdef _WIN32
            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
        #endif
        while(!harcvege){
            econio_clrscr();
            dobas=rand()%6+1+rand()%6+1;
            sztamadas=m.szu+dobas;
            dobas=rand()%6+1+rand()%6+1;
            tamadas=masolt.u+dobas;
            printf("Életerő pontod: %d / %d\nSzerencse pontod: %d / %d\nTámadóerőd: %d\n",p->e,p->emax,p->sz,p->szmax,tamadas);
            vonal();
            #ifdef _WIN32
            SetConsoleCP(1250);
            SetConsoleOutputCP(1250);
            #endif
            printf("A(z) %s ellen harcolsz.\n",m.sznev);
            #ifdef _WIN32
            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
            #endif
            printf("Életerőpontja: %d\nTámadóereje: %d\n",m.sze,sztamadas);
            vonal();
            if(szerencsevolt==1&&pvsz==1){
                printf("Szerencséd volt, komolyabb sebet ejtettél rajta.(egyel több életerő pontot veszít)\n");
                if(p->szmin<p->sz){
                    p->sz--;
                }
                vonal();
            }
            else if(szerencsevolt==-1&&pvsz==1){
                printf("Balszerencséd volt, a sebzés puszta karcolás. (egyel kevesebb életerőpontot veszít)\n");
                if(p->szmin<p->sz){
                    p->sz--;
                }
                vonal();
            }
            else if(szerencsevolt==1&&pvsz==-1){
                printf("Szerencséd van, sikrült elkerülnöd a teljes csapást.(eggyel kevesebb életerő pontot vesztettél)\n");
                if(p->szmin<p->sz){
                    p->sz--;
                }
                vonal();
            }
            else if(szerencsevolt==-1&&pvsz==-1){
                printf("Balszerencséd volt,komolyabb találat ért.(egyel több életerő pontot vesztettél)\n");
                if(p->szmin<p->sz){
                    p->sz--;
                }
                vonal();
            }
            szerencsevolt=0;
            pvsz=0;
            if(sztamadas>tamadas){
                pvsz=szornysebez(&*p,&szerencsevolt,&valasz);
            }
            else if(sztamadas<tamadas){
                pvsz=playersebez(&*p,&szerencsevolt,&m,&valasz);
            }
            else{
                dontetlen(&szerencsevolt,&valasz);
            }
            while(valasz==-1||valasz==-2){
                if(sztamadas!=tamadas){
                valasz=rosszvalasz(2,"Melyik lehetőséget választod? ");
                }
                else{
                valasz=rosszvalasz(1,"Melyik lehetőséget választod? ");
                }
            }
            if(m.sze<=0){
                harcvege=true;
                *hely=m.a-1;
                econio_clrscr();
            }
            else if(p->e<=0){
                harcvege=true;
                *hely=-1;
                econio_clrscr();
            }
        }
        #ifdef _WIN32
            SetConsoleCP(1250);
            SetConsoleOutputCP(1250);
        #endif
    }

}

//ez a függvény törli a "mentes.txt"-ben lévő adatokat és hejettük 0-kat ír.
void vegem(int *hely){
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    *hely=-1;
    printf("A kalandod véget ért. Nyomj egy gombot a kilépéshez!\n");
    vonal();
    FILE * torl=fopen("mentes.txt","w");
    FILE *invtorol=fopen("inventory.txt","w");
    if(invtorol==NULL||torl==NULL)
        printf("Valami baj van!");
    else{
        fprintf(invtorol,"0\t0\t0\t0\t0");
        fprintf(torl,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",0,0,0,0,0,0,0,0);
    }
    fclose(invtorol);
    fclose(torl);

    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
}
