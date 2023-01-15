#ifndef FUGGVENYEK_H_INCLUDED
#define FUGGVENYEK_H_INCLUDED
void mentes(mezo m,playerdata p,int *hely);
void vonal();
bool szerencse(playerdata *p);
int rosszvalasz(int db,char *str);
int szornysebez(playerdata *p,int *szerencsevolt,int *valasz);
int playersebez(playerdata *p,int * szerencsevolt,mezo *m,int *valasz);
void dontetlen(int *szerencsevolt,int *valasz);

void normalm(mezo m,int *hely,playerdata *p,itemek *fej);
void szerencsem(mezo m,int *hely,playerdata *p,itemek *fej);
void harcm(mezo m,int *hely,playerdata *p,itemek *fej);
void vegem(int *hely);

#endif // FUGGVENYEK_H_INCLUDED
