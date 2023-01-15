#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

itemek *ujelem(item adat);
itemek *keres(itemek *fej,char *nev);
itemek *hozzaad(itemek*fej,item ujitem);
itemek *listatorol(itemek *fej);
itemek *torolelso(itemek *fej);
itemek *torles(itemek *fej,item torlendo);
void invkiir(itemek *fej,playerdata *p);
void invmentes(itemek *fej);

#endif // INVENTORY_H_INCLUDED
