/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 17 dicembre 2022, 00:27 - 1:20
 */

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/*Scrivere un programma per la gestione di un vettore di triangoli. 
 * Ogni triangolo è descritto dalla dimensione dei propri tre lati (valori reali).

Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, 
 * l’accesso agli elementi dei vettori deve essere implementato tramite l’utilizzo esplicito 
 * di puntatori. Il vettore deve essere gestito tramite allocazione dinamica. 

 Lettura dei lati dei triangoli da un file. Il programma deve generare il vettore dei triangoli 
 * leggendo i valori da un file di testo denominato triangoli.txt. Nel caso in cui il file non sia 
 * presente il programma deve terminare la propria esecuzione e mostrare un messaggio di errore. 
 * N.B. il programma NON deve chiedere all’utente di inserire nuovamente il file.

 Stampa a video delle caratteristiche dei triangoli. Il programma mostra a video le dimensioni 
 * dei triangoli caricati nel vettore.

Conteggio delle occorrenze dei triangoli rettangoli. Il programma valuta e stampa a video il 
 * numero delle occorrenze dei triangoli rettangoli contenuti nel file.

Generazione vettore triangoli a perimetro minore della media. Il programma crea un nuovo 
 * vettore contenente tutti i triangoli che hanno perimetro inferiore della media di tutti i 
 * perimetri dei triangoli contenuti nel file.
 * 
 */

typedef struct {
    double l1;
    double l2;
    double l3;
} triangolo;

triangolo* dati(int&, triangolo*, bool&);
void stampa (int, triangolo*);
int contRett (int, triangolo*);
double ricercaPMedio (int, triangolo*);
triangolo* newVet (int, triangolo*, int&, triangolo*, double);

int main() {
    triangolo* vettore;
    bool esito;
    int riemp;
    triangolo* vettorePer;
    int riemp2;
    
    
    vettore=dati(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops, qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    stampa(riemp, vettore);
    
    cout<<"\n\nConto i triangoli rettangoli... Ne sono stati trovati : "<<contRett(riemp, vettore);
    
    cout<<"\n\nPerimetro medio: "<<ricercaPMedio(riemp, vettore)<<endl;
    cout<<"Creazione nuovo vettore di triangoli con perimetro maggiore della media...\n";
    vettorePer=newVet(riemp, vettore,riemp2, vettorePer, ricercaPMedio(riemp, vettore));
    stampa(riemp2, vettorePer);
    
    return 0;
}

triangolo* dati(int&riemp, triangolo*v, bool&esito){
    fstream file;
    esito=true;
    
    file.open("triangoli.txt", ios::in);
    if(!file){
        cout<<"File non esistente\n";
        esito=false;
    }
    file>>riemp;
    if(riemp<=0){
        cout<<"Riempimento negativo o 0\n";
        esito=false;
    }
    v= new (nothrow) triangolo[riemp];
    if(!v){
        cout<<"Memoria non disponibile\n";
        esito=false;
    }
    for (int i=0;i<riemp;i++){
        file>>(v+i)->l1;
        file>>(v+i)->l2;
        file>>(v+i)->l3;       
    }
    
    file.close();
    return v;
}

void stampa (int riemp, triangolo*v){
    cout<<"               Lato1\tLato2\tLato3\n";
    for(int i=0;i<riemp;i++){
        cout<<"Triangolo ["<<i<<"]: "<<(v+i)->l1<<"\t"<<(v+i)->l2<<"\t"<<(v+i)->l3<<endl;
    }
}    


int contRett (int riemp, triangolo*v){
    int occ=0;    
    
    
    double ipotenusa, cateto1, cateto2, pitagora;
    
    for(int i=0;i<riemp;i++){
        //controllo chi sono ipotenusa e cateto per verificare teorema pitagora
        if ((v+i)->l1>(v+i)->l2 && (v+i)->l1>(v+i)->l3){
           ipotenusa=(v+i)->l1;
           cateto1=(v+i)->l2;
           cateto2=(v+i)->l3;
        }
        if((v+i)->l2>(v+i)->l1 && (v+i)->l2>(v+i)->l3){
            ipotenusa=(v+i)->l2;
            cateto1=(v+i)->l1;
            cateto2=(v+i)->l3;
        }
        if ((v+i)->l3>(v+i)->l1 && (v+i)->l3>(v+i)->l2){
            ipotenusa = (v+i)->l3;
            cateto1= (v+i)->l2;
            cateto2=(v+i)->l1;
        }
        pitagora = sqrt(pow(cateto1,2)+pow(cateto2,2));
        if (pitagora == ipotenusa) occ++;
    } 
   
    return occ;
}

double ricercaPMedio (int riemp, triangolo*v){
    double media;
    double somma;
    for (int i=0;i<riemp;i++){
        somma=somma+(v+i)->l1+(v+i)->l2+(v+i)->l3;
    }
    media = somma/riemp;
    
    return media;
}

triangolo* newVet (int riemp, triangolo*v, int&riemp2, triangolo* v2, double media){
    riemp2=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->l1 + (v+i)->l2 + (v+i)->l3 >media){
            riemp2++;
        }
    }
    
    v2 = new triangolo[riemp2];
    int j=0;
    for (int i=0;i<riemp;i++){
    if((v+i)->l1 + (v+i)->l2 + (v+i)->l3 >media){
           *(v2+j)=*(v+i);
           j++;
        }
    }
    return v2;
}