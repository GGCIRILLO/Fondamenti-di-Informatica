/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 14 dicembre 2022, 22:27 - 23:27
 */

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

/*Scrivere un programma per la gestione delle pietanze del menù di un ristorante e memorizzati su file. 
 * Il menù può essere modellato come un vettore di pietanze. Ogni pietanza è descritta dal prezzo 
 * (valore reale) e dal nome (stringa di 15 caratteri).

Il programma deve fornire le funzionalità descritte di seguito, tenendo presente che i primi tre 
 * requisiti sono precondizioni per l’esecuzione dei rimanenti. 

Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, l’accesso agli 
 * elementi dei vettori deve essere implementato tramite l’utilizzo esplicito di puntatori. 
 * Il vettore deve essere gestito tramite allocazione dinamica. 

 Lettura delle pietanze del menu da un file. Il programma deve generare il vettore del menù leggendo 
 * i valori da un file di testo denominato menu.txt. Il file deve essere strutturato riportando le 
 * caratteristiche delle pietanze. Nel caso in cui il file non sia presente il programma deve terminare 
 * la propria esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve chiedere all’
 * utente di inserire nuovamente il file. Suggerimento: si supponga per semplicità che i nomi delle 
 * pietanze non contengano spazi e che abbiano solo caratteri alfabetici minuscoli. 
 * Si supponga inoltre che il prezzo delle pietanze sia sempre strettamente positivo.

Stampa a video del menù. Il programma mostra a video le pietanze del menù.

Generazione di vettori delle pietanze che iniziano per gruppi di caratteri. Il programma genera 
 * due vettori v1 e v2. Il primo vettore contiene tutte le pietanze del menu che iniziano con i 
 * caratteri dell’intervallo [a, d], il secondo vettore contiene tutte le pietanze del menu che 
 * iniziano con i caratteri dell’intervallo [m, p]. Inoltre, le iniziali dei caratteri delle pietanze 
 * di v1 e v2 devono essere maiuscole. Il programma mostra a video i due vettori ottenuti.

Ordinamento del menu in ordine alfabetico. Il programma ordina le pietanze del menù in ordine 
 * alfabetico e mostra a video il nuovo menù ottenuto.
 * 
 */

typedef struct {
    double prezzo;
    char nome [16];
} pietanze;

pietanze* dati (int &, pietanze*, bool&);
void stampa (int, pietanze*);
pietanze* nuovoVettore(int, pietanze*, pietanze*, int&, char, char);
void ordinamento (int , pietanze*);

int main() {
    pietanze* vettore;
    int riemp;
    bool esito;
    int riemp2;
    pietanze*vetAD;
    char a='a';
    char d='d';
    int riemp3;
    pietanze*vetMP;
    char m='m';
    char p='p';
    
    
    vettore=dati(riemp, vettore, esito);
    if (esito==false){
        cout<<"Ops, qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    stampa (riemp, vettore);
    cout<<endl;
    vetAD=nuovoVettore(riemp, vettore, vetAD, riemp2, a, d);
    cout<<"Pietanze A-D:\n";
    stampa(riemp2, vetAD);
    vetMP=nuovoVettore(riemp, vettore, vetMP, riemp3, m, p);
    cout<<endl<<"Pietanze M-P\n";
    stampa (riemp3, vetMP);
    
    cout<<"\nMetto in ordine alfabetico...\n";
    ordinamento(riemp, vettore);
    stampa(riemp, vettore);
    
    cout<<"\n\nProgramma Terminato";

    return 0;
}

pietanze* dati (int &riemp, pietanze*v, bool&esito){
    fstream file;
    esito=true;
    
    file.open("pietanze.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
        esito=false;
    }
    file>>riemp;
    if(riemp<=0){
        cout<<"Riempimento negativo o 0\n";
        esito=false;
    }
    v= new (nothrow) pietanze[riemp];
    if(!v){
        cout<<"Memoria non disponibile\n";
        esito=false;
    }
    for (int i=0;i<riemp;i++){
        file>>(v+i)->nome;
        file>>(v+i)->prezzo;
    }
    file.close();
    return v;
}

void stampa (int riemp, pietanze*v){
    cout<<"Menu\nPiatto\t\tPrezzo"<<endl;
    for (int i=0;i<riemp;i++){
        cout<<(v+i)->nome<<"\t\t"<<(v+i)->prezzo<<endl;
    }
}

pietanze* nuovoVettore(int riemp, pietanze*v, pietanze*v2, int& riemp2, char x, char y){
    riemp2=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->nome[0]>=x && (v+i)->nome[0]<=y){
            riemp2++;
        }
    }
    
    v2= new pietanze[riemp2];
    
    int j=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->nome[0]>=x && (v+i)->nome[0]<=y){
            *(v2+j)=*(v+i);
            j++;
        }
    }
    return v2;
}

void ordinamento (int riemp, pietanze*v){
    pietanze*temp;
    int pos;
    char min[16];
    temp=new pietanze;
    
    for (int i=0;i<riemp-1;i++){
        strcpy(min,(v+i)->nome);
        pos=i;
        for (int j=i;j<riemp;j++){
            if(strcmp(min,(v+j)->nome)>0){
                strcpy(min,(v+j)->nome);
                pos=j;
            }
        }
        
        if(pos!=i){
        *temp=*(v+i);
        *(v+i)=*(v+pos);
        *(v+pos)=*temp;
        }
    }
}