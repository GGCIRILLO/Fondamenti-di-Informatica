/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 11 dicembre 2022, 17:59
 */

#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */

typedef struct {
    int ampiezza;
    int frequenza;
} segnali;

segnali* caricamentoDati (int&, segnali*, bool&);
void stampa (int, segnali* );
int ricercaMaxA (int, segnali* , int&);
segnali* vetMaxA (int , segnali*, int , segnali*, int);
int ricercaMaxF (int, segnali* , int&);
segnali* vetMaxF (int , segnali*, int , segnali*, int);
void ordinamento (int, segnali*);



int main() {
    int riemp;
    segnali*vettore;
    bool esito;
    int riemp2=0;
    int maxA;
    segnali*vettoreMaxA;
    int riemp3=0;
    int maxF;
    segnali* vettoreMaxF;
    
    vettore=caricamentoDati(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops, qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    cout<<"Segnali presenti:\n";
    stampa(riemp, vettore);
    
    cout<<"\nVettore massima Ampiezza\n";
    maxA=ricercaMaxA(riemp, vettore, riemp2);
    vettoreMaxA = vetMaxA(riemp, vettore, riemp2, vettoreMaxA, maxA);
    stampa(riemp2, vettoreMaxA);
    
    cout<<endl<<"Vettore massima Frequenza\n";
    maxF=ricercaMaxF(riemp, vettore, riemp3);
    vettoreMaxF=vetMaxF(riemp, vettore, riemp3, vettoreMaxF, maxF);
    stampa(riemp3,vettoreMaxF);
    
    cout<<"\nOrdino in base alla frequenza...\n";
    ordinamento(riemp, vettore);
    stampa(riemp, vettore);

    return 0;
}

segnali* caricamentoDati (int&riemp, segnali*v, bool& esito){
    fstream file;
    file.open("segnali.txt", ios::in);
    if(!file ){
        cout<<"File non presente\n";
        esito=false;
    } 
    file>>riemp;
    if(riemp<=0||riemp>30){
        cout<<"Riempimento negativo o 0\n";
        esito =false;
    } else {
        v=new (nothrow) segnali[riemp];
        if(!v){
            cout<<"Memoria non disponibile\n";
            esito=false;
        }
        for(int i=0;i<riemp;i++){
            file>>(v+i)->ampiezza;
            file>>(v+i)->frequenza;
        }
        esito=true;
        file.close();
    }
    return v;
}

void stampa (int riemp, segnali* v){
    cout<<"            Ampiezza\tFrequenza\n";
    for(int i=0;i<riemp;i++){
        cout<<"Segnale ["<<i<<"]: "<<(v+i)->ampiezza<<"\t"<<(v+i)->frequenza<<endl;
    }
}

int ricercaMaxA (int riemp, segnali* v, int&riemp2){
    int max=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->ampiezza>max){
            max=(v+i)->ampiezza;
        }
    }
    for (int i=0;i<riemp;i++){
        if((v+i)->ampiezza==max){
            riemp2++;
        }
    }
    return max;
}

segnali* vetMaxA (int riemp, segnali*v, int riemp2, segnali*v2, int max){
    int j=0;
    
    v2 = new segnali [riemp2];
    for(int i=0;i<riemp;i++){
        if((v+i)->ampiezza==max){
        *(v2+j)=*(v+i);
        j++;
        }
    }
    return v2;
}

int ricercaMaxF (int riemp, segnali* v, int&riemp2){
    int max=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->frequenza>max){
            max=(v+i)->frequenza;
        }
    }
    for (int i=0;i<riemp;i++){
        if((v+i)->frequenza==max){
            riemp2++;
        }
    }
    return max;
}

segnali* vetMaxF (int riemp, segnali*v, int riemp2, segnali*v2, int max){
    int j=0;
    
    v2 = new segnali [riemp2];
    for(int i=0;i<riemp;i++){
        if((v+i)->frequenza==max){
        *(v2+j)= *(v+i);
        j++;
        }
    }
    return v2;
}

void ordinamento (int riemp, segnali*v){
    int min, pos;
    segnali*temp;
    temp=new segnali;
    
    for (int i=0;i<riemp-1;i++){
        min=(v+i)->frequenza;
        pos=i;
        for(int j=i+1;j<riemp;j++){
            if((v+j)->frequenza<min){
                min=(v+j)->frequenza;
                pos=j;
            }
        }
        if(pos!=i){
        *temp=*(v+i);
        *(v+i)=*(v+pos);
        *(v+pos)=*(temp);
        }
    }
}
