/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 7 dicembre 2022, 18:12
 */

#include <iostream>
#include <fstream>


using namespace std;

/*Scrivere un programma per la gestione dei tralicci di illuminazione stradali. 
 * Ogni traliccio è descritto dal suo identificativo (numero intero), dai kilowattora 
 * che sta consumando (numero reale) e da un valore booleano indicante se il traliccio 
 * sia funzionante o meno.

 Il programma deve essere strutturato utilizzando i prototipi di funzione. 
 * Inoltre, l’accesso agli elementi dei vettori deve essere implementato tramite 
 * l’utilizzo esplicito di puntatori. Il vettore deve essere gestito tramite allocazione 
 * dinamica. 

 

    
 * Lettura dei lati dei tralicci da un file. Il programma deve generare il vettore 
 * delle immagini leggendo i valori da un file di testo denominato tralicci.txt. 
 * Nel caso in cui il file non sia presente il programma deve terminare la propria 
 * esecuzione mostrando un messaggio di errore. N.B. il programma NON deve chiedere 
 * all’utente di inserire nuovamente il file.

          

    
 * Stampa a video delle caratteristiche dei tralicci. Il programma mostra a video 
 * le caratteristiche dei tralicci caricati nel vettore.

          

Creazione di vettori di tralicci funzionanti a più consumo e a meno consumo. 
 * Il programma genera due vettori che contengono rispettivamente le descrizioni dei 
 * tralicci funzionanti a consumo più alto della media e a consumo basso della media. 
 * Nel primo vettore ci sono le descrizioni dei tralicci funzionanti il cui consumo è 
 * strettamente maggiore della media dei consumi. Il secondo vettore contiene le 
 * descrizioni dei tralicci funzionanti il cui consumo è strettamente inferiore alla 
 * media dei consumi. La media dei consumi va valutata solo tra i tralicci funzionanti. 
 * Lo studente gestisca le eccezioni e le commenti opportunamente. Ad esempio, si valutino 
 * possibili scenari di eccezione quali nessuno o un solo traliccio funzionante.

 

Ricerca dei primi tre tralicci funzionanti che consumano di più. 
 * Il programma cerca i primi tre tralicci che sono funzionanti e che stanno consumando 
 * più kilowattora. Lo studente gestisca le eccezioni e le commenti opportunamente. 
 * Esempi di possibili eccezioni sono: 1. Non ci sono tralicci funzionanti, 2. C’è un solo 
 * traliccio funzionante, 3. Ci sono due tralicci funzionanti, 4. Ci sono più di tre 
 * tralicci funzionanti che consumano più kilowattora. Il programma mostra a video gli 
 * identificativi trovati o un opportuno messaggio per gestire i casi di eccezione.
 * 
 */
typedef struct {
    int id;
    double kwh;
    bool stato;
} tralicci;

tralicci* caricamentoDati (int &, tralicci* , bool& );
void stampa (int, tralicci* );
double calcoloMedia (int riemp, tralicci*v);
tralicci* sopraMedia (int, tralicci *, int&, double );
tralicci* sottoMedia (int, tralicci*, int&, double);
void ricerca (tralicci *, int, double);


int main() {
    tralicci *vettore;
    int riemp;
    bool esito;
    double media;
    tralicci*vettore2;
    int riemp2=0;
    tralicci*vettore3;
    int riemp3=0;
    
    vettore=caricamentoDati(riemp, vettore, esito);
    if (esito==false){
        cout<<"Ops.. qualcosa è andato storto\n\nProgramma terminato";
        return -1;
    } 
    
    cout<<"Dati inseriti: \n";
    stampa(riemp, vettore);
    
    cout<<endl;
    media=calcoloMedia(riemp, vettore);
    cout<<media<<endl;
    
    cout<<"Analizzo i tralicci che consumano più della media generale...\n";
    vettore2=sopraMedia(riemp, vettore, riemp2, media);
    stampa(riemp2, vettore2);
    
    cout<<"\nAnalizzo i tralicci che consumano meno della medaìia generale..\n";    
    vettore3=sottoMedia(riemp, vettore, riemp3, media);
    stampa(riemp3, vettore3);
    cout<<endl;
    ricerca(vettore, riemp, media);

    return 0;
}

tralicci* caricamentoDati (int &riemp, tralicci* v, bool& esito){
    fstream file;
    file.open("tralicci.txt", ios::in);
    if(!file){
        cout<<"File non presente\n";
        esito=false;
    } else {
        file>>riemp;
        if (riemp<=0){
            cout<<"Riempimento negativo o 0\n";
            esito = false;
        } else {
        v= new (nothrow) tralicci[riemp];
        if (!v){
            cout<<"Memoria non disponibile\n";
            esito=false;
        } else {
            for (int i=0;i<riemp;i++){
                file>>(v+i)->id;
                file>>(v+i)->kwh;
                file>>(v+i)->stato;
            }
            esito = true;
            file.close();
        }
        
        }
    }
    
    return v;
}

void stampa (int riemp, tralicci* v){
    for(int i=0;i<riemp;i++){
        cout<<"Traliccio ["<<i<<"] : "<<(v+i)->id<<"\t"<<(v+i)->kwh<<" KWH\t";
        if ((v+i)->stato==0) cout<<"Attivo";
        else cout<<"Spento";
        cout<<endl;
    }
}

double calcoloMedia (int riemp, tralicci*v){
double somma=0;
    double media;
    for(int i=0;i<riemp;i++){
        somma=somma+(v+i)->kwh;
    }
    media=somma/riemp;
    return media;
}

tralicci* sopraMedia (int riemp, tralicci *v, int& riemp2, double media){
    tralicci*v2;
    riemp2=0;
    
    for (int i=0;i<riemp;i++){
        if ((v+i)->kwh>media&&(v+i)->stato==0) riemp2++;
    }
    if (riemp2==1){
        cout<<"Un solo traliccio attivo consuma più della media generale\n";
    } 
    if (riemp2==0){
        cout<<"Nessuno traliccio attivo consuma più della media generale\n";
    }
    
    v2= new tralicci[riemp2];
    
    int j=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->kwh>media&&(v+i)->stato==0){
        *(v2+j)=*(v+i);
        j++;
        }
    }
    return v2;
}

tralicci* sottoMedia (int riemp, tralicci*v, int& riemp3, double media){
    tralicci* v3;
    riemp3=0;
    
    for (int i=0;i<riemp;i++){
        if ((v+i)->kwh<media&&(v+i)->stato==0) riemp3++;
    }
    if (riemp3==1){
        cout<<"Un solo traliccio attivo consuma meno della media generale\n";
    } 
    if (riemp3==0){
        cout<<"Nessuno traliccio attivo consuma meno della media generale\n";
    }
    
    v3 = new tralicci[riemp3];
    
    int j=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->kwh<media && (v+i)->stato==0){
        *(v3+j)=*(v+i);
        j++;
        }
    }
    return v3;
}

void ricerca (tralicci *v, int riemp, double media){
    int n=0;
    int c=0;
    
    for (int i=0;i<riemp;i++){
        if ((v+i)->kwh>media && (v+i)->stato==0){
            n++;
        }
    }
    switch (n){
            case (0): 
                cout<<"Non ci sono tralicci attivi che consumano più della media\n";
                break;
            case (1): 
                cout<<"C'è solo un traliccio attivo che consuma più della media\n";
                break;
            case (2):
                cout<<"Ci sono solo due tralicci attivi che consumano più della media\n";
                break;
            case (3):
                cout<<"Ci sono tre tralicci attivi che consumano più della media\n";
                for (int i=0;i<riemp;i++){
                    if ((v+i)->kwh>media && (v+i)->stato==0){
                        
                        cout<<"ID: "<<(v+i)->id<<endl;
                    }
                }
                break;
            default: 
                cout<<"Ci sono più di tre tralicci attivi che consumano più della media\n";
                for (int i=0;i<riemp;i++){
                    if ((v+i)->kwh>media && (v+i)->stato==0 && c<3){
                        cout<<"ID: "<<(v+i)->id<<endl;
                        c++;
                    }
                }
                break;
        }
}