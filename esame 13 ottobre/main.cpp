/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 17 dicembre 2022, 23:41
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*Scrivere un programma per la gestione di un magazzino di elettrodomestici. Il magazzino può essere 
 * modellato come un vettore di elettrodomestici. Ogni elettrodomestico è descritto dal prezzo (valore reale), 
 * dalla tipologia (che può assumere solo uno dei seguenti valori, ‘lavastoviglie’, ‘lavasciuga’, ‘lavatrice’, 
 * ‘asciugatrice’), la marca (stringa di al più 15 caratteri) e la disponibilità (valore logico).

Il programma deve fornire le funzionalità descritte di seguito, tenendo presente che i primi tre requisiti 
 * sono precondizioni per l’esecuzione dei rimanenti. 

Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, l’accesso agli elementi 
 * dei vettori deve essere implementato tramite l’utilizzo esplicito di puntatori. Il vettore deve essere gestito 
 * tramite allocazione dinamica.

Lettura degli elettrodomestici del magazzino da un file. Il programma deve generare il vettore del magazzino leggendo 
 * i valori da un file di testo denominato magazzino.txt. Il file deve essere strutturato riportando 
 * le caratteristiche degli elettrodomestici. Nel caso in cui il file non sia presente il programma deve terminare 
 * la propria esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve chiedere all’utente di inserire nuovamente il file. 
 * Suggerimenti: si supponga per semplicità che (1) il prezzo degli elettrodomestici sia sempre strettamente 
 * positivo, (2) la marca non contiene spazi bianchi ed inizia con una lettera minuscola.
Stampa a video degli elettrodomestici del magazzino. Il programma mostra a video tutti gli elettrodomestici del magazzino.
 * 
Generazione di vettore ordinato di elettrodomestici di un dato valore. Il programma 
 * chiede all’utente di inserire il prezzo da ricercare. 
 * Il programma genera un vettore contente gli elettrodomestici con prezzo uguale a 
 * quello inserito dall’utente. Il vettore è 
 * successivamente ordinato in ordine alfabetico in base alla marca dell’elettrodomestico. 
 * Se non esistono elettrodomestici con 
 * prezzo uguale a quello cercato il programma non genera il vettore e mostra un opportuno 
 * messaggio a video.

 * Valore magazzino. Il programma calcola per ogni tipologia il valore totale a magazzino 
 * degli elettrodomestici disponibili. 
 * Il programma mostra a video il valore ottenuto per ogni tipologia di elettrodomestico. 
 * La visualizzazione avviene in ordine 
 * decrescente in base al valore ottenuto. 

 * 
 */
typedef struct {
    char tipo [16];
    double prezzo;
    char marca[16];
    bool stato;
} elettrodomestici;

elettrodomestici* dati (int&, elettrodomestici*, bool&);
void stampa (int, elettrodomestici*);
elettrodomestici* newVet (int, elettrodomestici*, int&, elettrodomestici*);
void ordinamento (int, elettrodomestici*);
double* valore(int, elettrodomestici*, double*, int);
    
int main() {
    int riemp;
    elettrodomestici* vettore;
    bool esito;
    elettrodomestici* Nvettore;
    int riemp2;
    double*somma;
    int a=5;
    
    
    vettore=dati(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops, qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    stampa(riemp, vettore);
    cout<<endl<<endl;
    Nvettore=newVet(riemp, vettore, riemp2, Nvettore);
    if (riemp2!=0){
    ordinamento(riemp2, Nvettore);
    stampa(riemp2, Nvettore);
    }
    somma=valore(riemp, vettore, somma, a);
    
    

    return 0;
}

elettrodomestici* dati (int&riemp, elettrodomestici* v, bool&esito){
    fstream file;
    esito=true;
    
    file.open("magazzino.txt", ios::in);
    if(!file){
        cout<<"File non esistente\n";
        esito=false;
    }
    file>>riemp;
    
    v=new (nothrow) elettrodomestici[riemp];
    
    if(!v){
        cout<<"Memoria non disponibile\n";
        esito=false;
    }
    for(int i=0;i<riemp;i++){
        file>>(v+i)->tipo;
        file>>(v+i)->prezzo;
        file>>(v+i)->marca;
        file>>(v+i)->stato;
    }
    file.close();
    return v;
}

void stampa (int riemp, elettrodomestici*v){
    cout<<"Tipo\t\tPrezzo\tMarca\t\tDisponibilità\n";
    for(int i=0;i<riemp;i++){
     cout<<(v+i)->tipo<<"\t"<<(v+i)->prezzo<<"\t"<<(v+i)->marca<<"\t\t";
     if((v+i)->stato==0) cout<<"Disponibile";
     else cout<<"Non diponibile";
     cout<<endl;
    }
}

elettrodomestici* newVet (int riemp, elettrodomestici* v, int& n, elettrodomestici*v2){
    double elem;
    int j=0;
    cout<<"Inserisici prezzo da cercare: ";
    cin>>elem;
    
    for (int i=0;i<riemp;i++){
        if((v+i)->prezzo==elem) n++;
    }
    
    if(n==0){
        cout<<"Non ci sono elettrodomestici al prezzo cercato\n";
    } else {
        v2 = new elettrodomestici[n];
        for (int i=0;i<riemp;i++){
            if((v+i)->prezzo==elem){
            *(v2+j)=*(v+i);
            j++;
            }
        }
    }
    return v2;
}

void ordinamento (int riemp, elettrodomestici*v){
    elettrodomestici* temp;
    temp = new elettrodomestici;
    int pos;
    
    for (int i=0;i<riemp-1;i++){
        pos=i;
        for (int j=i+1;j<riemp;j++){
            if(strcmp((v+i)->marca, (v+j)->marca)<0){
                pos=j;
            }
        }
        if(i!=pos){
        *temp=*(v+i);
        *(v+i)=*(v+pos);
        *(v+pos)=*temp;
        }
    }
}

double* valore(int riemp, elettrodomestici*v, double*somma, int a){
    somma = new double [a];    
    for (int k=0;k<4;k++){
    for (int i=0;i<riemp-1;i++){
        if((v+i)->stato==0){
            somma[k]=(v+i)->prezzo;
            for (int j=i+1;j<riemp;j++){
                if((v+i)->tipo == (v+j)->tipo){
                    somma[k]=somma[k]+(v+j)->prezzo;
                }
            }
        }
    }
  }
    
   //ordinamento vettore somma
    double min, temp;
    int pos;
    for (int i=0;i<3;i++){
        min=somma[i];
        pos=i;
        for(int j=i+1;j<4;j++){
            if(somma[j]<min){
                min=somma[j];
                pos=j;
            }
        }
        if(i!=pos){
         temp=somma[i];
         somma[i]=somma[pos];
         somma[pos]=temp;
        }     
    }   
    return somma;
}