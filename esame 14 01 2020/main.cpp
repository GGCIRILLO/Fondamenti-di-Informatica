/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 30 novembre 2022, 18:48
 */

#include <iostream>


using namespace std;

/* Scrivere un programma per la gestione delle immagini memorizzate in un disco. Il disco può essere modellato come un array di immagini. 
 * Ogni immagine è descritta da un valore intero, denominato id (identificativo), due valori reali denominati dimX e dimY che rappresentano 
 * rispettivamente le dimensioni in pixel dell’immagine e un valore long int definito bytes che rappresenta la dimensione in bytes dell’immagine memorizzata.

 * Il programma deve fornire le funzionalità descritte di seguito, tenendo presente che i primi tre requisiti sono precondizioni per l’esecuzione dei rimanenti. 
 * Il programma deve essere strutturato utilizzando i prototipi di funzione.

 * 1) Inserimento del numero di immagini memorizzate sul disco. Il programma chiede all’utente di inserire il numero di immagini memorizzate. 
 * Se l’utente inserisce un valore di dimensione esterno all’intervallo [1, 20] allora il programma deve mostrare un messaggio di errore e 
 * chiedere all’utente di inserire nuovamente la dimensione fin quando questa non sia corretta.

 * 2) Inserimento delle immagini. Il programma chiede all’utente di inserire le caratteristiche delle immagini memorizzate.
 *  N.B. Per semplicità non si devono eseguire controlli di validità dei valori inseriti dall’utente.

 * 3) Stampa a video delle caratteristiche delle immagini memorizzate. Il programma mostra a video i valori delle caratteristiche delle immagini memorizzate su disco.

 * 4) Rotazione della prima immagine a dimensione massima. Il programma ruota la prima immagine del disco che ha dimensione massima in termini di bytes. 
 * La rotazione avviene scambiando i valori dimX e dimY dell’immagine selezionata. Dopo l’inversione, il programma mostra a video l’identificativo 
 * dell’immagine ruotata e il nuovo stato della memoria. 

 * 5) Duplicazione delle immagini su disco. Il programma duplica tutte le immagini contenute su disco e mostra a video il nuovo vettore ottenuto.

 * 
 */
typedef struct {
    int id;
    double dimX;
    double dimY;
    long int bytes;
} immagini;

void riempimento (int&);
void inserimentoDati (int, immagini []);
void stampa (int, immagini []);
int rotazione (int, immagini []);
void duplicazione (int , immagini [], immagini []);


int main() {
    
    immagini disco[20];
    immagini disco2[40];
    int riemp;
    
    riempimento(riemp);
    cout<<"Inserisci i dati\n";
    inserimentoDati(riemp, disco);
    cout<<"\nGli elementi inseriti sono: \n";
    cout<<"           \tId\tDimX\tDimY\tBytes\n";
    stampa(riemp, disco);
    
    cout<<endl<<"Id dell'immagine da ruotare: "<<rotazione(riemp, disco)<<endl;
    
    cout<<"Nuovo stato memoria: \n";
    cout<<"           \tId\tDimX\tDimY\tBytes\n";
    stampa(riemp, disco);
    
    duplicazione(riemp, disco, disco2);
    cout<<"\nVettore duplicato: \n";
    cout<<"           \tId\tDimX\tDimY\tBytes\n";
    stampa (2*riemp, disco2);

    return 0;
}

void riempimento (int& riemp){
    do {
        cout<<"Inserisci il numero di immagini memorizzate sul disco: ";
        cin>>riemp;
        if (riemp<1||riemp>20){
            cout<<"Errore! Deve essere compreso tra 1 e 20. Riprova\n";
        }
    } while (riemp<1||riemp>20);
} 

void inserimentoDati (int riemp, immagini v[]) {
    for (int i=0;i<riemp;i++){
        cout<<"Immagine ["<<i<<"] :\nId: ";
        cin>>v[i].id;
        cout<<"DimX: ";
        cin>>v[i].dimX;
        cout<<"DimY: ";
        cin>>v[i].dimY;
        cout<<"Bytes: ";
        cin>>v[i].bytes;
        cout<<endl;
    }
} 

void stampa (int riemp, immagini v[]) {
    for (int i=0;i<riemp;i++){
        cout<<"Immagine ["<<i<<"]\t"<<v[i].id<<"\t"<<v[i].dimX<<"\t"<<v[i].dimY<<"\t"<<v[i].bytes<<endl;
    }
}

int rotazione (int riemp, immagini v[]){
    
    int maxid=v[0].id;
    long int maxbytes=v[0].bytes;
    double temp=0;
    
    for (int i=0;i<riemp;i++){
        if (v[i].bytes>maxbytes){
            maxbytes=v[i].bytes;
            
            temp=v[i].dimX;
            v[i].dimX=v[i].dimY;
            v[i].dimY=temp;
            
            maxid=v[i].id;
        }
    }
    return maxid;
}

void duplicazione (int riemp, immagini v[], immagini v2[]){
    for (int i=0;i<riemp;i++){
        v2[i]=v[i];
    }
    for (int i=0;i<riemp;i++){
        v2[riemp+i]=v[i];
    }
}

