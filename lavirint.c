#include <stdio.h>
#include <stdlib.h>
#define USPEH 1
#define NEUSPEH 0

typedef enum {
	prazno,
	zid,
	pocetak,
	kraj
}	polje;

typedef enum {
	gore,
	desno,
	dole,
	levo
}	direkcija;

typedef struct cv {
	int a;
    int b;
	struct cv *next;
} cvor; 

cvor*  dodaj(cvor* glava,int x,int y) {
	cvor* novi=(cvor*)malloc(sizeof(cvor));
	if(novi==NULL) {
		printf("nema memorije\n");
		return glava;
	}
	novi->a=x;
	novi->b=y;
	novi->next=glava;
	return novi;
}

void citaj(cvor *vugla) {
	while(vugla!=NULL) {
		printf("%d %d\n",vugla->a+1,vugla->b+1); //ispisivacu +1 zato sto se tako u zadatku nikakvom trazi
		vugla=vugla->next;
	}
	return;
}

int velicina(cvor *vugla) {
	int i=0;
	while(vugla!=NULL) {
		i+=1;
		vugla=vugla->next;
	}
	return i;
}

polje** napravi(int xmax,int ymax) {
	int i,j;
	polje **lavirint=NULL;
	char buff;
	
	if( (xmax<=0) || (ymax<=0) )
		return NULL;

	lavirint=(polje**)malloc(xmax*sizeof(polje*));
	for(i=0;i<xmax;i++) {
		lavirint[i]=(polje*)malloc(ymax*sizeof(polje));
		for(j=0;j<ymax;j++) {
			scanf(" %c",&buff);
			if(buff=='#')
				lavirint[i][j]=zid;
			else if(buff=='.')
				lavirint[i][j]=prazno;
			else {
				printf("nesto ne valja");
				return NULL;
			}
		}
	}
	lavirint[0][0]=pocetak;
	lavirint[xmax-1][ymax-1]=kraj;
	return lavirint;
}

unsigned eskapada(polje **lavirint, int xmax,int ymax) {
	int x=0,y=0;
	direkcija d=gore;
	
	if( (xmax<=0) || (ymax<=0) )
		return NEUSPEH;
		
	goto preskok;
	
	petlja: 
	
		if( (lavirint[x][y]==pocetak) && (d==gore) )
			return NEUSPEH;
	
	preskok:
	
		if(lavirint[x][y]==kraj) return USPEH;

		if(d==gore) {
			if(x==0) { //ako je sa trenutne leve strane zid
				if(y+1>=ymax) { // da li je ispred mene zid?
					d=desno; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x][y+1]==zid) { // da li je ispred mene zid?
					d=desno; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					y+=1;
					goto petlja;
				}
			}
			else if(lavirint[x-1][y]==zid) { //ako je sa trenutne leve strane zid
				if(y+1>=ymax) { // da li je ispred mene zid?
					d=desno; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x][y+1]==zid) { // da li je ispred mene zid?
					d=desno; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					y+=1;
					goto petlja;
				}
			}
			else { // nema sa trenutne leve zida
				d=levo;
				x-=1; // menjam direkciju na levo i cinim korak u toj direkciji da bi bio zid sa trenutne leve
				goto petlja;
			}
		}
		
		else if(d==desno) {
			if(y+1>=ymax) { //ako je sa trenutne leve strane zid
				if(x+1>=xmax) { // da li je ispred mene zid?
					d=dole; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x+1][y]==zid) { // da li je ispred mene zid?
					d=dole; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					x+=1;
					goto petlja;
				}
			}
			else if(lavirint[x][y+1]==zid) { //ako je sa trenutne leve strane zid
				if(x+1>=xmax) { // da li je ispred mene zid?
					d=dole; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x+1][y]==zid) { // da li je ispred mene zid?
					d=dole; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					x+=1;
					goto petlja;
				}
			}
			else { // nema sa trenutne leve zida
				d=gore;
				y+=1; // menjam direkciju na levo i cinim korak u toj direkciji da bi bio zid sa trenutne leve
				goto petlja;
			}
		}	
		
		else if(d==dole) {
			if(x+1>=xmax) { //ako je sa trenutne leve strane zid
				if(y-1<0) { // da li je ispred mene zid?
					d=levo; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x][y-1]==zid) { // da li je ispred mene zid?
					d=levo; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					y-=1;
					goto petlja;
				}
			}
			else if(lavirint[x+1][y]==zid) { //ako je sa trenutne leve strane zid
				if(y-1<0) { // da li je ispred mene zid?
					d=levo; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x][y-1]==zid) { // da li je ispred mene zid?
					d=levo; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					y-=1;
					goto petlja;
				}
			}
			else { // nema sa trenutne leve zida
				d=desno;
				x+=1; // menjam direkciju na levo i cinim korak u toj direkciji da bi bio zid sa trenutne leve
				goto petlja;
			}
		}	
		
		else if(d==levo) {
			if(y-1<0) { //ako je sa trenutne leve strane zid
				if(x-1<0) { // da li je ispred mene zid?
					d=gore; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x-1][y]==zid) { // da li je ispred mene zid?
					d=gore; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					x-=1;
					goto petlja;
				}
			}
			else if(lavirint[x][y-1]==zid) { //ako je sa trenutne leve strane zid
				if(x-1<0) { // da li je ispred mene zid?
					d=gore; // ako da idem desno od trenutne direkcije
					goto petlja;
				}
				else if(lavirint[x-1][y]==zid) { // da li je ispred mene zid?
					d=gore; // ako da idem desno od trenutne direkcije
					goto petlja;					
				}
				else { //nastavljam pravo dok ne naletim
					x-=1;
					goto petlja;
				}
			}
			else { // nema sa trenutne leve zida
				d=dole;
				y-=1; // menjam direkciju na levo i cinim korak u toj direkciji da bi bio zid sa trenutne leve
				goto petlja;
			}
		}
	return 69;
}

void ispisi_lavirint(polje** lavirint,int xmax,int ymax){
	int i,j;
	if(lavirint==NULL) return;
	for(i=0;i<xmax;i++) {
		for(j=0;j<ymax;j++) {
			printf(" %d",lavirint[i][j]);
		}
		putchar('\n');
	}
	return;
}

void zadatak(polje** lavirint,int xmax,int ymax) {
	int i,j;
	cvor *lista=NULL;
	if(eskapada(lavirint,xmax,ymax)==NEUSPEH) { // ako vec nema izlaza, samo nabrajamo prazna polja
			for(i=0;i<xmax;i++){
				for(j=0;j<ymax;j++){
					if(lavirint[i][j]==prazno)
						lista=dodaj(lista,i,j);
				}
			}
	}
	else {	//samo prototip dok ne proverim korektnost, imam efikasnije resenje
	
			for(i=0;i<xmax;i++){
				for(j=0;j<ymax;j++){
					if(lavirint[i][j]==prazno){
						lavirint[i][j]=zid;
						if(eskapada(lavirint,xmax,ymax)==NEUSPEH)
							lista=dodaj(lista,i,j);
						lavirint[i][j]=prazno;
					}
				}
			}	
	
	}
	printf("%i\n",velicina(lista));
	citaj(lista);
}

int main() {
	polje** lavirint=NULL;
	int xmax,ymax;
	scanf("%d %d",&xmax,&ymax);
	lavirint=napravi(xmax,ymax);
	zadatak(lavirint,xmax,ymax);
//	printf("%u\n",eskapada(lavirint,xmax,ymax));
//	system("pause");
	return 0;
}
