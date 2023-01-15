#ifndef STRUKTURAK_H_INCLUDED
#define STRUKTURAK_H_INCLUDED
#include <stdbool.h>
typedef struct playerdata{
    int e;                  //A játékos ÉleterÕpontja
    int u;                  //A játékos ügyességpontja
    int sz;                 //A játékos szerencsepontja
    int emax;               //A játékos életerő pontjának a kezdeti értéke, ennél nem lehet több
    int umax;               //A játékos ügyesség pontjának a kezdeti értéke, ennél nem lehet több
    int szmax;              //A játékos szerencse pontjának kezdeti értéke, ennél nem lehet több
    int szmin;              //A játékos szerencse pontjainak minimuma (alapbol 0, de lehet megváltozik a játék folyamán)
}playerdata;

typedef struct item{
    int db;                 //Hány darab van abból az itemből
    char nev[90];           //Mi a neve az itemnek
    char felhaszn;          //Felhasználható-e?
    char valt;              //Mit tud megváltoztatni ha a felhasználó felhasználja
    int ertek;              //Mennyivel változtatja meg az előző adatnak az értékét
}item;

typedef struct itemek{
    item targy;
    struct itemek* next;
}itemek;




typedef struct mezo{
    int id;                 //Az adott mezõ azonosítója, a main-ben a most változo alapján dõl el, hogy melyik mezõ jelenjen meg
    char type;              //Az adott mezõ típusa (n-normál,h-harc,s-szerencse,v-vége)
    int a;                  //Normál mezõ esetében:az elsõ választási lehetõség, ha a felhasználó ezt választja, akkor eze a mezõn folytatódik a történet, szerencse mezõnél ha a játékosnak szerencséje van akkor ezen a mezõn folytatódik a történet
    int b;                  //Normál mezõ esetében:a második választási lehetõség, ha a felhasználó ezt választja, akkor eze a mezõn folytatódik a történet, szerencse mezõnél ha a játékosnak balszerencséje van akkor ezen a mezõn folytatódik a történet
    int c;                  //Normál mezõ esetében:a harmadik választási lehetõség, ha a felhasználó ezt választja, akkor eze a mezõn folytatódik a történet
    int d;                  //Normál mezõ esetében:a negyedik választási lehetõség, ha a felhasználó ezt választja, akkor eze a mezõn folytatódik a történet
    char asz[300];          //Az elsõ lehetõség leírása, ha az elsõt akarja választani a felhasználó akkor ez fog történni vele
    char bsz[300];          //A második lehetõség leírása, ha a másodikat akarja választani a felhasználó akkor ez fog történni vele
    char csz[300];          //A harmadik lehetõség leírása, ha a harmadikat akarja választani a felhasználó akkor ez fog történni vele
    char dsz[300];          //A negyedik lehetõség leírása, ha a negyediket akarja választani a felhasználó akkor ez fog történni vele
    int e;                  //Ennyivel változik a felhasználó életerõ pontja
    int u;                  //Ennyivel változik a felhasználó ügyesség pontja
    int sz;                 //Ennyivel változik a felhasználó szerencse pontja
    char itemp[50];         //Ezt a tárgyat szerzi a játékos az adott mezõn
    char itemm[50];         //Ezt a tárgyat veszti el a játékos az adott mezõn
    char itemr[50];         //Ez a tárgy szükséges az adott mezõrelépéshez
    char sznev[50];         //Ez az adott mezõn az ellenségnek a neve
    int szu;                //Ez az adott mezõn az ellenség ügyességpontja
    int sze;                //Ez az adott mezõn az ellenség életerõ pontja
    char szoveg[1500];      //Ez az adott mezõ története
}mezo;



#endif // STRUKTURAK_H_INCLUDED
