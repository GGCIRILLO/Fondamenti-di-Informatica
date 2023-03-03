/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 21 dicembre 2022, 19:33
 */

#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */
#define MAX 30
typedef struct {
    int temp;
    int pres;
} segnali;

void caricaDati (int&, segnali[], bool&);
void stampa (int, segnali []);
bool ricerca (int , segnali [], int&);
double minimo (int, segnali[], int&);
void newVet (int, segnali [], int&, segnali [], double);

int main() {
    segnali vettore[MAX];
    int riemp;
    bool esito=true;
    int pos;
    double min;
    segnali segnali_minimo_rapporto[MAX];
    int riemp2;
    
    caricaDati(riemp, vettore, esito);
    if(!esito){
        cout<<"Ops... qualcosa è anadato storto\n\nProgramma terminato";
        return -1;
    }
    stampa(riemp, vettore);
    cout<<endl;
    if (ricerca(riemp, vettore, pos)==true){
        cout<<"Trovato in posizione "<<pos;
    } else {
        cout<<"Nessun segnale trovato";
    }
    
    min=minimo(riemp, vettore, riemp2);
    cout<<endl<<"Ricerco elementi a minimo rapporto temperatura e pressione..."<<min<<endl;
    newVet(riemp, vettore, riemp2, segnali_minimo_rapporto, min);
    stampa(riemp2, segnali_minimo_rapporto);
    

    return 0;
}

void caricaDati (int&riemp, segnali v[], bool&esito){
    fstream file;
    file.open("segnali.txt", ios::in);
    if(!file){
        cout<<"File non presente"<<endl;
        esito=false;
    }
    file>>riemp;
   
    if(riemp<=0 || riemp>MAX){
        cout<<"Errore! Riempimento negativo o memoria non disponibile"<<endl;
        esito=false;
    }
    for (int i=0;i<riemp;i++){
        file>>v[i].temp;
        file>>v[i].pres;
    }
    file.close();
}

void stampa (int riemp, segnali v[]){
    cout<<"Segnali:\nTemperatura\tPressione"<<endl;
    for(int i=0;i<riemp;i++){
        cout<<v[i].temp<<"\t\t"<<v[i].pres<<endl;
    }
}

bool ricerca (int riemp, segnali v[], int &pos){
    int presUtente;
    pos=0;
    bool trovato=false;
    
    cout<<"Inserisci pressione da ricercare: ";
    cin>>presUtente;
    
    while (!trovato && pos<riemp){
        if(v[pos].pres==presUtente){
            trovato=true;
        } else {
            pos++;
        }
    }
    return trovato;
      
}

double minimo (int riemp, segnali v[], int&n){
    n=0;
     
    double min= (double) v[0].temp/(double)v[0].pres;
    
    for (int i=0;i<riemp;i++){
        if (((double)v[i].temp/(double)v[i].pres) <min){
            min=(double)v[i].temp/(double)v[i].pres;
        }
    }
    
    for (int i=0;i<riemp;i++){
    if (((double)v[i].temp/(double)v[i].pres) == min) n++;
    }
    return min;
}

void newVet (int riemp, segnali v[], int&j, segnali segnali_minimo_rapporto[], double min){
    j=0;
    
    for (int i=0;i<riemp;i++){
        if ((double)v[i].temp/(double)v[i].pres == min){
            segnali_minimo_rapporto[j]=v[i];
            j++;
        }
    }
    
}
