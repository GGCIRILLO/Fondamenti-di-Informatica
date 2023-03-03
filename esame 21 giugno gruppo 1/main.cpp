/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 8 dicembre 2022, 21:45
 * Finito 22:54
 */

#include <iostream>
#include <fstream>

using namespace std;

/*Scrivere un programma per la gestione di un vettore di Immagini. Ogni immagine è descritta 
 * dalla dimensione dei propri due lati (lato x e lato y di valori reali) e dalla dimensione 
 * in byte (valore long int).

 
 * Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, 
 * l’accesso agli elementi dei vettori deve essere implementato tramite l’utilizzo esplicito 
 * di puntatori. Il vettore deve essere gestito tramite allocazione dinamica. 

 

       
 * Lettura dei lati delle immagini da un file. Il programma deve generare il vettore 
 * delle immagini leggendo i valori da un file di testo denominato immagini.txt. 
 * Nel caso in cui il file non sia presente il programma deve terminare la propria 
 * esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve chiedere 
 * all’utente di inserire nuovamente il file.

          

         
 * Stampa a video delle caratteristiche delle immagini. Il programma mostra a video 
 * le caratteristiche delle immagini caricate nel vettore.

          

         
 * Ricerca delle prime due posizioni di una immagine di lato x cercato dall’utente. 
 * Il programma chiede preventivamente all’utente di inserire la dimensione del lato x 
 * dell’immagine da cercare. Il programma, successivamente, calcola e mostra a video la 
 * posizione delle prime due immagini che hanno il lato x uguale al valore cercato dall’utente. 
 * Il programma mostra a video un opportuno messaggio nel caso in cui nel vettore sia presente 
 * una sola immagine con lato x uguale al valore inserito dall’utente oppure non siano presenti 
 * immagini con la caratteristica cercata.

          


 * Generazione nuovo vettore a minore densità. Il programma genera un nuovo vettore a partire 
 * dal vettore delle immagini memorizzato. Il nuovo vettore contiene tutte le immagini la cui 
 * densità è minore o uguale alla densità media delle immagini del vettore memorizzato. 
 * La densità è definita come il rapporto tra la dimensione e l’area dell’immagine.
 * 
 */

typedef struct {
    double latox;
    double latoy;
    long int dim;
} immagini; 

immagini* caricamentoDaFile (int&, immagini*, bool&);
void stampa (int, immagini*);
void ricercaLatox (int, immagini *, double);
double densita (int, immagini*);
immagini* nuovoVettore (int, immagini*, immagini*, int&, double, bool&);


int main() {
    immagini* vettore;
    int riemp;
    bool esito;
    double latoCercato;
    double media;
    immagini* vettoreDensitaMinore;
    int riemp2=0;
    bool esito2;
    
    vettore=caricamentoDaFile(riemp, vettore, esito);
    if (esito==false){
        cout<<"Ops.. qualcosa è andato storto\n\nProgramma terminato";
        return -1;
    }
    
    cout<<"Gli elementi del vettore sono:\n";
    stampa(riemp, vettore);
    
    cout<<"\nInserisci il lato X da cercare: ";
    cin>>latoCercato;
    ricercaLatox (riemp, vettore, latoCercato);
    
    cout<<endl<<endl;
    media= densita(riemp, vettore);
    //cout<<media;
    vettoreDensitaMinore=nuovoVettore(riemp, vettore, vettoreDensitaMinore, riemp2, media, esito2);
    if(esito2==false){
        cout<<"Nessun immagine a densità minore della media presente\n";
    } else {
        cout<<"Immagini a densità minore della media:\n";
        stampa(riemp2, vettoreDensitaMinore);
    }
   
    

    return 0;
}

immagini* caricamentoDaFile (int& riemp, immagini*v, bool& esito){
    fstream file;
    file.open("immagini.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
             esito=false;
    } 
    file>>riemp;
    if(riemp<=0){
        cout<<"Il riempimento deve essere strettamente maggiore di zero";
        esito=false;
    } else {
        v= new (nothrow) immagini[riemp];
        if (!v){
            cout<<"Memoria non disponibile\n";
            esito=false;
        }
    for(int i=0;i<riemp;i++){
        file>>(v+i)->latox;
        file>>(v+i)->latoy;
        file>>(v+i)->dim;
    }
    esito=true;
    }
    file.close();
    return v;
}

void stampa (int riemp, immagini*v){
    cout<<"              Lato X\tLato Y\t\tDimensione\n";
    for (int i=0;i<riemp;i++){
        cout<<"Immagine ["<<i<<"]: "<<(v+i)->latox<<"\t"<<(v+i)->latoy<<"\t\t"<<(v+i)->dim<<endl;
    }
}

void ricercaLatox (int riemp, immagini *v, double elem){
    int n=0;
    int c=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->latox==elem){
            n++;
        }
    }
    
    switch (n){
        case 0: 
            cout<<"Nessun elemento con lato x="<<elem<<endl;
            break;
        case 1: 
            cout<<"Un solo elemento trovato con lato x="<<elem<<" alla posizione ";
            for (int i=0;i<riemp;i++){
                if((v+i)->latox==elem){
                    cout<<i;
                }
            }
            break;
        case 2:
            cout<<"Due elementi trovato con lato x="<<elem<<"\nPosizioni trovate: ";
            for (int i=0;i<riemp;i++){
                if((v+i)->latox==elem) {
                    cout<<i<<" ";
                }
            }
            break;
        default : 
            cout<<"Ci sono più di due elementi con lato x="<<elem<<"\nLe prime due posizioni trovate sono: ";
            for (int i=0;i<riemp;i++){
                if((v+i)->latox==elem && c<2) {
                    cout<<i<<" ";
                    c++;
                }
            }
            break;
    }
    
}

double densita (int riemp, immagini*v){
    double s=0;
    double media;
    for(int i=0;i<riemp;i++){
        s=s+(((v+i)->latox * v[i].latoy)/(v+i)->dim);
    }
    media=s/riemp;
    return media;
}

immagini* nuovoVettore (int riemp, immagini*v, immagini* v2, int& riemp2, double media, bool& esito){
    for(int i=0;i<riemp;i++){
        if(((v+i)->latox * v[i].latoy)/(v+i)->dim<media) riemp2++;
    } 
    if(riemp2<=0){
        esito=false;
    } else {
    v2=new immagini[riemp2];
    int j=0;
    for (int i=0;i<riemp;i++){
    if(((v+i)->latox * v[i].latoy)/(v+i)->dim<media){
    *(v2+j)=*(v+i);
    j++;
    }
    }
    esito=true;
    }
    return v2;
}