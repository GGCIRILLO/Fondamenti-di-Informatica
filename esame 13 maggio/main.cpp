/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 6 dicembre 2022, 16:56
 */

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

/*Scrivere un programma per la gestione di un vettore di triangoli. 
 * Ogni triangolo è descritto dalla dimensione dei propri tre lati (valori reali).

Il programma deve essere strutturato utilizzando i prototipi di funzione. 
 * Inoltre, l’accesso agli elementi dei vettori deve essere implementato tramite 
 * l’utilizzo esplicito di puntatori. Il vettore deve essere gestito tramite 
 * allocazione dinamica. 

 Lettura dei lati dei triangoli da un file. Il programma deve generare il vettore dei 
 * triangoli leggendo i valori da un file di testo denominato triangoli.txt. 
 * Nel caso in cui il file non sia presente il programma deve terminare la propria 
 * esecuzione e mostrare un messaggio di errore. N.B. il programma NON deve chiedere 
 * all’utente di inserire nuovamente il file.

 Stampa a video delle caratteristiche dei triangoli. Il programma mostra a video 
 * le dimensioni dei triangoli caricati nel vettore.

Conteggio delle tipologie di triangoli contenuti nel vettore. Il programma valuta e 
 * stampa a video il numero delle cinque possibili tipologie di triangoli contenuti 
 * nel vettore (triangolo equilatero, triangolo isoscele, triangolo scaleno, triangolo 
 * rettangolo, triangolo rettangolo isoscele).

 Ordinamento del vettore. Il programma ordina e mostra a video il vettore dei triangoli. 
 * L’ordinamento deve avvenire in modalità crescente in base al perimetro dei triangoli.
 * 
 */
typedef struct {
    double lato1;
    double lato2;
    double lato3;
} triangoli;

triangoli* caricaDatiDaFile (int&, triangoli *, bool&);
void stampa (int, triangoli *);
int contatoreEquilateri (int, triangoli *);
int contatoreScaleni (int,triangoli *);
int contatoreIsosceli (int, triangoli *);
int contatoreRett (int, triangoli *);
int contatoreRettIso (int, triangoli *);
void ordinamentoCrescente (int, triangoli *);


int main() {
    int riemp;
    triangoli *vettore;
    bool esito;
    int equilatero, isoscele, scaleno, rettangolo, rettIsoscele;
    
    vettore=caricaDatiDaFile(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops..qualcosa è andato storto\n\nProgramma Terminato";
        return -1;
    } 
    cout<<"Triangoli presenti: \n";
    cout<<"               Lato 1\t\tLato 2\t\tLato 3\n";
    stampa(riemp, vettore);
    
    cout<<"\nControllo i triangoli...\n";
    equilatero=contatoreEquilateri(riemp, vettore);
    scaleno=contatoreScaleni(riemp, vettore);
    isoscele=contatoreIsosceli(riemp, vettore);
    rettangolo=contatoreRett(riemp, vettore);
    rettIsoscele=contatoreRettIso (riemp, vettore);
    
    cout<<"Ci sono "<<equilatero<<" triangoli equilateri\n";
    cout<<"Ci sono "<<scaleno<<" triangoli scaleni\n";
    cout<<"Ci sono "<<isoscele<<" triangoli isosceli\n";
    cout<<"Ci sono "<<rettangolo<<" triangoli rettangoli\n";
    cout<<"Ci sono "<<rettIsoscele<<" triangoli rettangoli isosceli\n";
    
    cout<<"\nOrdino in base al perimetro...\n";
    ordinamentoCrescente(riemp, vettore);
    cout<<"Nuovo vettore: \n";
    cout<<"               Lato 1\t\tLato 2\t\tLato 3\n";
    stampa(riemp, vettore);
    
    cout<<"\n\nProgramma terminato";

    return 0;
}

triangoli* caricaDatiDaFile (int& riemp, triangoli *v, bool& esito){
    fstream file;
    file.open("triangoli.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
        esito=false;
    } else {
        file>>riemp;
        
        v = new (nothrow) triangoli [riemp];
        if(!v){
            cout<<"Memoria non disponibile\n";
            esito=false;
        } else {
            for(int i=0;i<riemp;i++){
                file>>(v+i)->lato1;
                file>>(v+i)->lato2;
                file>>(v+i)->lato3;
            }
            
            esito = true;
            file.close();
        }
    }
    return v;
}

void stampa (int riemp, triangoli *v){
    for(int i=0;i<riemp;i++){
        cout<<"Triangolo ["<<i<<"]: "<<(v+i)->lato1<<"\t\t"<<(v+i)->lato2<<"\t\t"<<(v+i)->lato3<<endl;
    }
}

int contatoreEquilateri (int riemp, triangoli *v) {
    int x=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->lato2==(v+i)->lato1&&(v+i)->lato2==(v+i)->lato3){
            x++;
        }
    }
    return x;
}

int contatoreScaleni (int riemp,triangoli *v){
    int x=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->lato2!=(v+i)->lato1 && (v+i)->lato2!=(v+i)->lato3 && (v+i)->lato1!=(v+i)->lato3){
            x++;
        }
    }
    return x;
}

int contatoreIsosceli (int riemp, triangoli *v){
    int x=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->lato2==(v+i)->lato1||(v+i)->lato2==(v+i)->lato3||(v+i)->lato1==(v+i)->lato3){
            x++;
        }
    }
    return x;
}

int contatoreRett (int riemp, triangoli *v){
    double ipotenuse [riemp];
    double cateto1 [riemp];
    double cateto2 [riemp];
    double pitagora [riemp];
    int x=0;
    
    for (int i=0;i<riemp;i++){
        //riconosco le ipotenuse e icateti per poter applicare pitagora
        if ((v+i)->lato2>(v+i)->lato1 && (v+i)->lato2>(v+i)->lato3){
            ipotenuse[i]=(v+i)->lato2;
            cateto1[i]=(v+i)->lato1;
            cateto2[i]=(v+i)->lato3;
        }
        if ((v+i)->lato1>(v+i)->lato2 && (v+i)->lato1>(v+i)->lato3){
            ipotenuse[i]=(v+i)->lato1;
            cateto1[i]=(v+i)->lato2;
            cateto2[i]=(v+i)->lato3;
        }
        if((v+i)->lato3>(v+i)->lato2 && (v+i)->lato3>(v+i)->lato1){
            ipotenuse[i]=(v+i)->lato3;
            cateto1[i]=(v+i)->lato2;
            cateto2[i]=(v+i)->lato1;
        }
        
        pitagora[i] = sqrt(pow(cateto1[i],2)+pow(cateto2[i],2));
        //se la radice della somma dei quadrati dei cateti e' uguale all'ipotenusa 
        //allora e' un triangolo rettangolo
        if (pitagora[i]==ipotenuse[i]) {
            x++;
        }
    }
    return x;
}

int contatoreRettIso (int riemp, triangoli *v){
double ipotenuse [riemp];
    double cateto1 [riemp];
    double cateto2 [riemp];
    double pitagora [riemp];
    int x=0;
    
    for (int i=0;i<riemp;i++){
    if((v+i)->lato2==(v+i)->lato1||(v+i)->lato2==(v+i)->lato3||(v+i)->lato1==(v+i)->lato3){
        
        if ((v+i)->lato2>(v+i)->lato1 && (v+i)->lato2>(v+i)->lato3){
            ipotenuse[i]=(v+i)->lato2;
            cateto1[i]=(v+i)->lato1;
            cateto2[i]=(v+i)->lato3;
        }
        if ((v+i)->lato1>(v+i)->lato2 && (v+i)->lato1>(v+i)->lato3){
            ipotenuse[i]=(v+i)->lato1;
            cateto1[i]=(v+i)->lato2;
            cateto2[i]=(v+i)->lato3;
        }
        if((v+i)->lato3>(v+i)->lato2 && (v+i)->lato3>(v+i)->lato1){
            ipotenuse[i]=(v+i)->lato3;
            cateto1[i]=(v+i)->lato2;
            cateto2[i]=(v+i)->lato1;
        }
        
        pitagora[i] = sqrt(pow(cateto1[i],2)+pow(cateto2[i],2));
        if (pitagora[i]==ipotenuse[i]) {
            x++;
        }
    }
}
    return x;
}

void ordinamentoCrescente (int riemp, triangoli *v){
    double min, min2;
    triangoli *temp;
    int pos;
    temp= new triangoli;
    
    for (int i=0;i<riemp-1;i++){
        min=(v+i)->lato2+(v+i)->lato1+(v+i)->lato3;
        pos=i;
        for(int j=i+1;j<riemp;j++){
            min2=(v+j)->lato2+(v+j)->lato1+(v+j)->lato3;
            if (min2<min){
                min=min2;
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