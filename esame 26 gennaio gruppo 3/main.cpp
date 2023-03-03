/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 14 dicembre 2022, 18:37 - 19:40 (sistemato 20:00)
 */

#include <iostream>
#include <fstream>

using namespace std;

/*Scrivere un programma per la gestione di coppie di motori coassiali e memorizzati su file. 
 * Ogni coppia è caratterizzata da due campi di valori interi velocitaX e velocitaY.

Il programma deve fornire le funzionalità descritte di seguito, tenendo presente che i primi due 
 * requisiti sono precondizioni per l’esecuzione dei rimanenti. Il programma deve essere strutturato 
 * utilizzando i prototipi di funzione. 

Lettura dei dati delle velocità delle coppie presenti nel file. Il programma deve generare il vettore 
 * delle velocità di coppia leggendo i valori da un file di testo denominato motori.txt. 
 * Il file deve essere strutturato riportando nella prima linea il numero totale delle coppie presenti 
 * nel file. Le linee rimanenti riportano le caratteristiche delle coppie. Nel caso in cui il file non 
 * sia presente o il numero di coppie contenuti nel file sia maggiore di 30 allora il programma deve 
 * terminare la propria esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve 
 * chiedere all’utente di inserire nuovamente il file.

 * Stampa a video delle caratteristiche delle coppie memorizzate nel file. Il programma mostra a video 
 * le caratteristiche di tutte le coppie memorizzate nel file e caricate nel vettore.

 * Verifica se le coppie di motori hanno una configurazione palindroma. Il programma verifica se i 
 * motori sono memorizzati in configurazione palindroma. La sequenza dei suoi elementi se letta al 
 * contrario, rimane invariata. Il programma mostra a video un opportuno messaggio di errore. N.B. 
 * Di seguito sono riportati alcuni possibili esempi di vettori palindromi: (a, b, c, c, b, a) oppure 
 * (a, b, c, d, c, b, a). Il programma mostra a video un opportuno messaggio.

 * Scambio ottimizzato velocità minima asse X. Il programma scambia la prima coppia a velocitaX 
 * minima con l’ultima coppia a velocitaX minima. Il programma mostra a video il nuovo vettore ottenuto.
 * 
 */

typedef struct{
    int velx;
    int vely;
} motori;

motori* dati(int&,motori*, bool&);
void stampa (int, motori*);
void palindromo (int, motori*);
int minimo (int, motori*);
int posPrimomin (int, motori*, int);
int posUltmin (int, motori*, int);
void scambio (int, motori*, int, int);

int main() {
    motori*vettore;
    bool esito;
    int riemp;
    int min;
    
    vettore=dati(riemp, vettore, esito);
    stampa(riemp, vettore);
    cout<<endl;
    palindromo(riemp, vettore);
    cout<<"\nEffettuo scambio ottimizzato velocità minima asse X...\n";
    min=minimo(riemp, vettore);
    scambio(riemp, vettore,posPrimomin(riemp, vettore, min),posUltmin(riemp, vettore, min));
    stampa(riemp, vettore);
    

    return 0;
}

motori* dati(int& riemp,motori*v, bool&esito){
    fstream file;
    esito=true;
    file.open("motori.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
        esito=false;
    }
    
    file>>riemp;
    if(riemp<=0){
        cout<<"Riempimento negativo o 0\n";
        esito=false;
    }
   
    v=new (nothrow) motori[riemp];
    if(!v){
        cout<<"Memoria non disponibile\n";
        esito=false;
    }
    for (int i=0;i<riemp;i++){
        file>>(v+i)->velx;
        file>>(v+i)->vely;
    }
    file.close();
    return v;
}

void stampa (int riemp, motori*v){
    cout<<"            Vel X\tVel Y\n";
    for(int i=0;i<riemp;i++){
        cout<<"Coppia ["<<i<<"]: "<<(v+i)->velx<<"\t\t"<<(v+i)->vely<<endl;
    }
}

void palindromo (int riemp, motori*v){
    bool esito=false;
    int j=riemp-1;
    
    cout<<"Verifico vettore palindromo...\n";
    
    for (int i=0;i<riemp;i++){
            if((v+i)->velx==(v+j)->velx && (v+i)->vely==(v+j)->vely){
            esito=true;
            j--;
        }
    }
    
    if (esito){
        cout<<"Vettore palindromo\n";
    } else {
        cout<<"Vettore non palindromo\n";
    }
}

int minimo (int riemp, motori*v){
 int min=v->velx;
 for (int i=0;i<riemp;i++){
        if((v+i)->velx<min){
            min=(v+i)->velx;
        }
    }
 return min;
}   

int posPrimomin (int riemp, motori*v, int min){
    int pos=0;
    bool trovato=false;
    
    while(!trovato&&pos<riemp){
        if((v+pos)->velx==min){
            trovato=true;
        } else {
            pos++;
        }
    }
    return pos;
}

int posUltmin (int riemp, motori*v, int min){
    int pos=riemp;
    bool trovato=false;
    
    while(!trovato && pos>0){
        if((v+pos)->velx==min){
            trovato=true;
        } else pos--;
    }
    
    return pos;
}
void scambio (int riemp, motori*v, int x, int y){
    motori* temp;
    temp=new motori;
    
    *temp=*(v+x);
    *(v+x)=*(v+y);
    *(v+y)=*temp;
}