/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 21 dicembre 2022, 15:14
 */

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/*Scrivere un programma per la gestione dei ripetitori TV e memorizzati su file.
 *  Ogni ripetitore tv è caratterizzato da due quattro campi, longitudine (valore reale), 
 * latitudine (valore reale), polarizzazione (orizzontale oppure verticale), Operatore 
 * (stringa di al massimo 15 caratteri), ad esempio Rai1, Mediaset2, etc. Il programma deve 
 * fornire le funzionalità descritte di seguito, tenendo presente che i primi due requisiti 
 * sono precondizioni per l’esecuzione dei rimanenti. Il programma deve essere strutturato 
 * utilizzando i prototipi di funzione. 

Lettura dei dati delle velocita dei ripetitori presenti nel file. Il programma deve generare il 
 * vettore dei ripetitori leggendo i valori da un file di testo denominato ripetitori.txt. Il file 
 * deve essere strutturato riportando nella prima linea il numero totale delle coppie presenti nel file. 
 * Le linee rimanenti riportano le caratteristiche delle coppie. Nel caso in cui il file non sia presente 
 * o il numero di ripetitori contenuti nel file sia maggiore di 30 allora il programma deve terminare 
 * la propria esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve chiedere all’utente di inserire nuovamente il file.

 * Stampa a video delle caratteristiche dei ripetitori memorizzati nel file. Il programma mostra a video le caratteristiche di tutti i ripetitori memorizzati nel file e caricati nel vettore.

 * Ricerca del ripetitore più vicino per un dato operatore. 
 * Il programma chiede all’utente di inserire la propria posizione in termini di longitudine e 
 * latitudine e l’operatore di cui si vuole trovare il ripetitore. Il programma cerca all’interno 
 * del vettore il primo ripetitore più vicino per l’operatore richiesto. Il programma mostra a video 
 * le caratteristiche del ripetitore trovato. Se non esiste ripetitore per l’operatore cercato il programma 
 * mostra a video un opportuno messaggio. N.B. applicare la formula della distanza euclidea per il calcolo della distanza. 
 * 
 * Eliminazione dei ripetitori a polarizzazione orizzontale. Il programma elimina dal vettore tutti i ripetitori che hanno polarizzazione orizzontale.
 * 
 */
#define MAX 6

typedef struct {
    double longi;
    double lat;
    int pol;
    char operatore[16];
} ripetitore;

void caricaDati (int&, ripetitore [], bool&);
void stampa (int, ripetitore []);
void ricerca (int, ripetitore []);
void rimozione (int&, ripetitore []);
    
    
int main() {
    ripetitore ripetitori[MAX];
    int riemp;
    bool esito;
    
    caricaDati(riemp, ripetitori, esito);
    if(esito==false){
        cout<<"Ops.. qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    stampa(riemp, ripetitori);
    cout<<endl;
    ricerca(riemp, ripetitori);
    
    cout<<"\nElimino ripetitori orizzontali...\n";
    rimozione(riemp, ripetitori);
    stampa(riemp, ripetitori);

    return 0;
}

void caricaDati (int& riemp, ripetitore v[], bool&esito){
    fstream file;
    esito=true;
    
    do {
        cout<<"Inserisci il riempimento del vettore: ";
        cin>>riemp;
        if(riemp<=0 || riemp>MAX){
            cout<<"Errore! Deve appartenere a [1,6]. Riprova...\n";
        }
    } while (riemp<=0 || riemp>MAX);
    
    file.open("ripetitori.txt", ios::in);
    if(!file){
        esito=false;
        cout<<"File non esistente\n";
    }
    for (int i=0;i<riemp;i++){
        file>>v[i].longi;
        file>>v[i].lat;
        file>>v[i].pol;
        file>>v[i].operatore;
    }
    file.close();
}

void stampa (int riemp, ripetitore v[]){
    cout<<"Ripetitori\nLongitudine\tLatitudine\tPolarizzazione\tOperatore"<<endl;
    for(int i=0;i<riemp;i++){
        cout<<v[i].longi<<"\t\t"<<v[i].lat<<"\t\t";
        if(v[i].pol==0) cout<<"Orizzontale\t";
        else cout<<"Verticale\t";
        cout<<v[i].operatore<<endl;
    }
}

void ricerca (int riemp, ripetitore v[]){
    double min=999999.999;
    double mintemp=0;
    double lon;
    double lat;
    char op[16];
    int pos=10;
    
    cout<<"Inserisci la tua posizione\nLongitudine: ";
    cin>>lon;
    cout<<"Latitudine: ";
    cin>>lat;
    cout<<"Operatore di riferimento: ";
    cin>>op;
    
    for (int i=0;i<riemp;i++){
        if(strcmp(op, v[i].operatore)==0){
            mintemp=((v[i].longi - lon)*(v[i].longi - lon)) + ((v[i].lat - lat)*(v[i].lat - lat));
            if(mintemp<min){
                min=mintemp;
                pos=i;
            }
        }
        
    }
    if (pos!=10){
        cout<<"Ripetitore più vicino alla posizione "<<pos<<endl<<"Caratteristiche: \n";
        cout<<"Longitudine\tLatitudine\tPolarizzazione\tOperatore"<<endl;
        cout<<v[pos].longi<<"\t\t"<<v[pos].lat<<"\t\t";
        if(v[pos].pol==0) cout<<"Orizzontale\t";
        else cout<<"Verticale\t";
        cout<<v[pos].operatore<<endl;
    } else {
        cout<<"Nessun ripetitore trovato"<<endl;
    }
}

void rimozione (int&riemp, ripetitore v[]){

    for (int i=0;i<riemp;i++){
        if (v[i].pol == 0){
            riemp--;
            for (int j=i;j<riemp;j++){
            v[j]=v[j+1];
            }  
            i--;
        }
    }
}