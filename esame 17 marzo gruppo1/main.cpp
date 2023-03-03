/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 11 dicembre 2022, 15:37
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Scrivere un programma per la gestione di un magazzino di elettrodomestici. 
 * Il magazzino può essere modellato come un vettore di elettrodomestici. 
 * Ogni elettrodomestico è descritto dal prezzo (valore reale), dalla tipologia 
 * (che può assumere solo uno dei seguenti valori, ‘lavastoviglie’, ‘lavasciuga’, ‘lavatrice’, 
 * ‘asciugatrice’), la marca (stringa di al più 15 caratteri) e la disponibilità (valore logico).

Il programma deve fornire le funzionalità descritte di seguito, tenendo presente che i primi 
 * tre requisiti sono precondizioni per l’esecuzione dei rimanenti. 

Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, l’accesso 
 * agli elementi dei vettori deve essere implementato tramite l’utilizzo esplicito di puntatori. 
 * Il vettore deve essere gestito tramite allocazione dinamica. 
 * 
 * Lettura degli elettrodomestici del magazzino da un file. Il programma deve generare 
 * il vettore del magazzino leggendo i valori da un file di testo denominato magazzino.txt. 
 * Il file deve essere strutturato riportando le caratteristiche delle pietanze. Nel caso 
 * in cui il file non sia presente il programma deve terminare la propria esecuzione e mostrare 
 * un messaggio di errore. N.B. il programma NON deve chiedere all’utente di inserire nuovamente 
 * il file. Suggerimenti: si supponga per semplicità che (1) il prezzo degli elettrodomestici 
 * sia sempre strettamente positivo, (2) la marca non contiene spazi bianchi ed inizia con una 
 * lettera minuscola.
 * 
 * Stampa a video degli elettrodomestici del magazzino. Il programma mostra a video tutti gli 
 * elettrodomestici del magazzino.

         
 * Generazione di vettori ordinati di elettrodomestici disponibili e non disponibili. 
 * Il programma genera due vettori di elettrodomestici. Uno dei due vettori contiene solo gli 
 * elettrodomestici disponibili, l’alto vettore contiene solo gli elettrodomestici non disponibili.
 *  Entrambi i vettori devono essere ordinati in senso crescente in base al prezzo. 
 * Il programma mostra a video i due vettori ottenuti.

         
 * Evidenziazione di tutti gli elettrodomestici a massimo prezzo di un dato tipo. 
 * Il programma chiede all’utente di inserire una tipologia di elettrodomestico. 
 * Il programma evidenzia (cambiando in maiuscolo tutti i caratteri) la marca di tutti gli 
 * elettrodomestici a massimo prezzo per la tipologia cercata. Il programma mostra a video 
 * il vettore degli elettrodomestici modificato.
 * 
 */

typedef struct {
    char tipo[15];
    double prezzo;
    char marca[15];
    bool stato;
} elettrodomestici;

elettrodomestici* caricamentoDati (int&, elettrodomestici*, bool&);
void stampa (int, elettrodomestici*);
int contaElem(int, elettrodomestici* , int);
elettrodomestici* nuovoVettore (int, elettrodomestici*, elettrodomestici*, int);
void ordinamento(int, elettrodomestici*);
void cerco (char [15]);
double massimoPrezzo (int, elettrodomestici*, char [15]);
void evidenzio (int , elettrodomestici*, char[15], double);


int main() {
    int riemp;
    bool esito;
    elettrodomestici* vettore;
    int riemp2, riemp3, d=0, nd=1;
    elettrodomestici* vettoreDisponibili;
    elettrodomestici* vettoreNonDisponibili;
    char tipoUtente[15];
    double maxPrezzo;
    
    
    
    vettore=caricamentoDati(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops..qualcosa è andato storto\n\nProgramma terminato";
        return -1;
    } 
    cout<<"Elettrodomestici in magazzino: \n";
    stampa(riemp, vettore);
    
    riemp2=contaElem(riemp, vettore, d);
    riemp3=contaElem(riemp, vettore, nd);
    
    vettoreDisponibili = new elettrodomestici[riemp2];
    vettoreNonDisponibili = new elettrodomestici[riemp3];
    
    vettoreDisponibili= nuovoVettore(riemp, vettore, vettoreDisponibili, d);
    vettoreNonDisponibili= nuovoVettore(riemp, vettore, vettoreNonDisponibili, nd);
    
    cout<<"\nElettrodomestici disponibili (prezzo crescente):\n";
    ordinamento(riemp2, vettoreDisponibili);
    stampa(riemp2, vettoreDisponibili);
    
    cout<<"\nElettrodomestici non disponibili (prezzo crescente):\n";
    ordinamento(riemp3, vettoreNonDisponibili);
    stampa(riemp3, vettoreNonDisponibili);
    
    cout<<endl;
    cerco(tipoUtente);
    maxPrezzo=massimoPrezzo(riemp, vettore, tipoUtente);
    cout<<"Maggior prezzo trovato: "<<maxPrezzo<<endl;
    evidenzio(riemp, vettore, tipoUtente, maxPrezzo);
    stampa(riemp, vettore);

    return 0;
}
elettrodomestici* caricamentoDati (int&riemp, elettrodomestici* v, bool& esito){
    fstream file;
    file.open("magazzino.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
        esito=false;
    } else {
        file>>riemp;
        if(riemp<=0){
            esito=false;
            cout<<"Riempimento negativo o 0\n";
        }
        v=new (nothrow) elettrodomestici[riemp];
        
        if(!v){
            cout<<"Memoria non disponibile\n";
            esito=false;
        }
            
        for (int i=0;i<riemp;i++){
            file>>(v+i)->tipo;
            file>>(v+i)->prezzo;
            file>>(v+i)->marca;
            file>>(v+i)->stato;
        }
        esito=true;
        file.close();
        
    }
    return v;
}

void stampa (int riemp, elettrodomestici*v){
    cout<<"Tipo\t\tPrezzo\tMarca\t\tDisponibilità\n";
    for(int i=0;i<riemp;i++){
        cout<<(v+i)->tipo<<"\t"<<(v+i)->prezzo<<"\t"<<(v+i)->marca<<"\t\t";
        if((v+i)->stato==0) cout<<"Presente";
        else cout<<"Non presente";
        cout<<endl;
    }
}

int contaElem(int riemp, elettrodomestici* v, int disp){
    int n=0;
    for(int i=0;i<riemp;i++){
        if((v+i)->stato==disp){
            n++;
        }
    }
    return n;
}



elettrodomestici* nuovoVettore (int riemp, elettrodomestici*v, elettrodomestici*v2, int disp){
    int j=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->stato==disp){
            *(v2+j)=*(v+i);
            j++;
        }
    }
    return v2;
}

void ordinamento(int riemp, elettrodomestici*v){
    double min;
    elettrodomestici*temp;
    int pos;
    temp=new elettrodomestici;
    
    for (int i=0;i<riemp-1;i++){
        min=(v+i)->prezzo;
        pos=i;
        for(int j=i+1;j<riemp;j++){
            if((v+j)->prezzo<min){
                min=(v+j)->prezzo;
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

void cerco (char elem[15]){
    
    do{
        cout<<"Inserisci il tipo di elettrodomestico da cercare: ";
        cin>>elem;
        if (strcmp(elem,"lavatrice")!=0&&strcmp(elem,"lavastoviglie")!=0&& strcmp(elem,"asciugatrice")!=0&& strcmp(elem,"lavasciuga")!=0){
            cout<<"Tipo non esistente...Riprova\n";
        }
    } while (strcmp(elem,"lavatrice")!=0&&strcmp(elem,"lavastoviglie")!=0&& strcmp(elem,"asciugatrice")!=0&& strcmp(elem,"lavasciuga")!=0);
        
}

double massimoPrezzo (int riemp, elettrodomestici*v, char cercato[15]){
    int pos=0;
    double max;
    bool trovato=false;
    while (!trovato && pos<riemp){
        if(strcmp(cercato, (v+pos)->tipo)==0){
            trovato=true;
        } else pos++;
    }
    max=(v+pos)->prezzo;
    for(int i=pos;i<riemp;i++){
        if(strcmp(cercato, (v+i)->tipo)==0 && (v+i)->prezzo>max){
            max=(v+i)->prezzo;
        }
    }
    
    return max;
}

void evidenzio (int riemp, elettrodomestici*v, char cercato[15], double max){
    for(int i=0;i<riemp;i++){
        if(strcmp(cercato,(v+i)->tipo)==0 && (v+i)->prezzo==max){
            for (int j=0;j<strlen((v+i)->marca);j++){
            (v+i)->marca[j]=toupper((v+i)->marca[j]);
            }
        }
    }
}

