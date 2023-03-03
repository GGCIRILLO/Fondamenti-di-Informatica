/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 21 dicembre 2022, 18:00
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*
 * 
 */

typedef struct {
    double prezzo;
    char tipo [16];
    char marca [16];
    bool stato;
} elettr;

elettr* dati (int&, elettr*, bool&);
void stampa (int , elettr*);
void newVet (int riemp, elettr*v, elettr* lavatrici, int &nlavat, elettr* asciugatrici, int&nasciug, elettr* lavasciuga, int&nlavasc, elettr*lavastoviglie, int&nlavast);
void ordinamento (int, elettr*);


int main() {
    elettr* vettore;
    int riemp;
    bool esito=true;
    elettr*lavatrici;
    int nlavat;
    elettr* asciugatrici;
    int nasciug;
    elettr* lavasciuga;
    int nlavasc;
    elettr*lavastoviglie;
    int nlavast;
    
    vettore=dati(riemp, vettore, esito);
    if(!esito){
        cout<<"Ops... qualcosa è andato storto\n\nProgramma terminato";
        return -1;
    }
    
    stampa(riemp, vettore);
    newVet(riemp, vettore, lavatrici, nlavat, asciugatrici, nasciug, lavasciuga, nlavasc,lavastoviglie,nlavast);
    ordinamento(nlavat,lavatrici);
    ordinamento(nasciug, asciugatrici);
    ordinamento(nlavasc, lavasciuga);
    ordinamento(nlavast, lavastoviglie);
    
    cout<<"Lavatrici:"<<endl;
    stampa(nlavat, lavatrici);
    cout<<"Asciugatrici: "<<endl;
    stampa(nasciug, asciugatrici);
    cout<<"Lavasciuga: "<<endl;
    stampa(nlavasc, lavasciuga);
    cout<<"Lavastoviglie: "<<endl;
    stampa(nlavast, lavastoviglie);
    
    

    return 0;
}

elettr* dati (int&riemp, elettr*v, bool&esito){
    fstream file;
    
    file.open("magazzino.txt", ios::in);
    if(!file){
        cout<<"File non presente"<<endl;
        esito=false;
    }
    file>>riemp;
    v= new (nothrow) elettr[riemp];
    if(!v){
        cout<<"Memoria non disponibile"<<endl;
        esito=false;
    }
    for (int i=0;i<riemp;i++){
        file>>(v+i)->prezzo;
        file>>(v+i)->tipo;
        file>>(v+i)->marca;
        file>>(v+i)->stato;
    }
    file.close();
    return v;
}

void stampa (int riemp, elettr*v){
    cout<<"Magazzino: \nPrezzo\tTipo\t\t\tMarca\tStato"<<endl;
    for(int i=0;i<riemp;i++){
        cout<<(v+i)->prezzo<<"\t"<<(v+i)->tipo<<"\t\t"<<(v+i)->marca<<"\t";
        if((v+i)->stato==0) cout<<"Disponibile"<<endl;
        else cout<<"Non disponibile"<<endl;
    }
}

void newVet (int riemp, elettr*v, elettr* lavatrici, int &nlavat, elettr* asciugatrici, int&nasciug, elettr* lavasciuga, int&nlavasc, elettr*lavastoviglie, int&nlavast){
    nlavat=0;
    nasciug=0;
    nlavasc=0;
    nlavast=0;
    
    for(int i=0;i<riemp;i++){
        if (strcmp((v+i)->tipo, "lavatrice")) nlavat++;
        if (strcmp((v+i)->tipo, "asciugatrice")) nasciug++;
        if (strcmp((v+i)->tipo, "lavasciuga")) nlavasc++;
        if (strcmp((v+i)->tipo, "lavastoviglie")) nlavast++;
    }
    
    lavatrici= new elettr[nlavat];
    asciugatrici =new elettr[nasciug];
    lavasciuga=new elettr[nlavasc];
    lavastoviglie=new elettr[nlavast];
    
    int a=0, b=0, c=0, d=0;
    
    for (int i=0;i<riemp;i++){
        if (strcmp((v+i)->tipo, "lavatrice")){
        *(lavatrici+a)=*(v+i);
        a++;
        }
        if (strcmp((v+i)->tipo, "asciugatrice")){
        *(asciugatrici+b)=*(v+i);
        b++;
        }
        if (strcmp((v+i)->tipo, "lavasciuga")){
        *(lavasciuga+c)=*(v+i);
        c++;
        }
        if (strcmp((v+i)->tipo, "lavastoviglie")){
        *(lavastoviglie+d)=*(v+i);
        d++;
        }
    }
    
    
}

void ordinamento (int riemp, elettr*v){
    int pos;
    elettr*temp;
    char min [16];
    temp=new elettr[1];
    
    for (int i=0;i<riemp-1;i++){
        strcpy(min,(v+i)->tipo);
        pos=i;
        for(int j=i+1;j<riemp;j++){
            if(strcmp(min, (v+i)->tipo)<0){
                pos=j;
                strcpy(min,(v+j)->tipo);
            }
        }
        if (i!=pos){
            *temp=*(v+i);
            *(v+i)=*(v+pos);
            *(v+pos)=*temp;
        }
    }
}