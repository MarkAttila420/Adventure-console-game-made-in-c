#include "strukturak.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#endif


itemek *ujelem(item adat){
    itemek *uj=(itemek*)malloc(sizeof(itemek));
    if(uj){
        uj->next=NULL;
        uj->targy.db=adat.db;
        strcpy(uj->targy.nev,adat.nev);
        uj->targy.ertek=adat.ertek;
        uj->targy.felhaszn=adat.felhaszn;
        uj->targy.valt=adat.valt;
    }
    return uj;
}

itemek *keres(itemek *fej,char *nev){
    while(fej){
        if(strstr(fej->targy.nev,nev)!=NULL){
            return fej;
        }
        fej=fej->next;
    }
    return NULL;
}

itemek *hozzaad(itemek*fej,item ujitem){
    itemek *uj=ujelem(ujitem);
    if(!uj){
        printf("Valami probléma van.");
        return fej;
    }
    if(!fej){
        return uj;
    }
    uj->next=fej;
    return uj;
}
itemek *listatorol(itemek *fej){
    itemek *temp;
    while(fej){
        temp=fej->next;
        free(fej);
        fej=temp;
    }
}

itemek *torolelso(itemek *fej){
    if(!fej){
        return NULL;
    }
    itemek *temp=fej->next;
    free(fej);
    return temp;
}

itemek *torles(itemek *fej,item torlendo){
    if(!fej){
        return NULL;
    }
    if(strcmp(fej->targy.nev,torlendo.nev)==0){
        return torolelso(fej);
    }
    itemek *temp=NULL,*mozgo;
    for(temp=fej->next,mozgo=fej;temp;mozgo=temp,temp=temp->next){
        if(strcmp(temp->targy.nev,torlendo.nev)==0){
            mozgo->next=temp->next;
            free(temp);
            return fej;
        }
    }
    return fej;
}

void invkiir(itemek *fej,playerdata *p){
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    econio_clrscr();
    printf("Életerő pontod: %d / %d\nSzerencse pontod: %d / %d\nÜgyesség pontod: %d / %d\n",p->e,p->emax,p->sz,p->szmax,p->u,p->umax);
    vonal();
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
    itemek *temp;
    int db=0;
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
        else
            printf("[%d]\t%d db %s\n",db+1,temp->targy.db,temp->targy.nev);
        db++;
    }
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    printf("[%d]\tVissza.\n",db+1);
    vonal();
    int valasz=rosszvalasz(db+1,"Melyik lehetőséget választod? ");
    while(valasz==-1||valasz==-2){
        valasz=rosszvalasz(db+1,"Melyik lehetőséget választod? ");
    }
    if(valasz==db+1){
        econio_clrscr();
    }
    else if(valasz<db+1){
        temp =fej;
        for(int i=0;i<valasz-1;i++){
            temp=temp->next;
        }
        if(temp->targy.felhaszn=='i'){
            if(temp->targy.db==1){
                fej=torles(fej,temp->targy);
            }
            else{
                char kivalasztott[50];
                strcpy(kivalasztott,temp->targy.nev);
                temp=keres(fej,kivalasztott);
                temp->targy.db--;
            }
            if(temp->targy.valt=='e'){
                if(p->e+temp->targy.ertek<=p->emax)
                    p->e+=temp->targy.ertek;
                else if(p->e+temp->targy.ertek>p->emax)
                    p->e=p->emax;
            }
            if(temp->targy.valt=='u'){
                if(p->u+temp->targy.ertek<=p->umax)
                    p->u+=temp->targy.ertek;
                else if(p->u+temp->targy.ertek>p->umax)
                    p->u=p->umax;
            }
            if(temp->targy.valt=='s'){
                if(p->sz+temp->targy.ertek<=p->szmax)
                    p->sz+=temp->targy.ertek;
                else if(p->sz+temp->targy.ertek>p->szmax)
                    p->sz=p->szmax;
            }
            invkiir(fej,&*p);
        }
        else{
            econio_clrscr();
            printf("Ez a tárgy nem használható fel.\n");
            vonal();
            printf("Nyomj egy gombot a visszalépéshez! ");
            getchar();
            invkiir(fej,&*p);
        }
    }

    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
}

void invmentes(itemek *fej){
    FILE *invment=fopen("inventory.txt","w");
    econio_clrscr();
    if(invment==NULL)
        printf("Valami baj van!");
    else{
        itemek *temp=fej;
        while(temp){
            fprintf(invment,"%d\t%s\t%c\t%c\t%d\n",temp->targy.db,temp->targy.nev,temp->targy.felhaszn,temp->targy.valt,temp->targy.ertek);
            temp=temp->next;
        }
    }
    fej= listatorol(fej);
    fclose(invment);
}




