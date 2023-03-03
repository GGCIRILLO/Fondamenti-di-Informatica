/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 13 dicembre 2022, 22:02 - 22:41
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*Scrivere un programma per la gestione di un vettore di Pietanze. 
 * Ogni pietanza è descritta dal nome della pietanza (stringa di al più 10 caratteri) e 
 * dal prezzo (valore reale).
 * Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, 
 * l’accesso agli elementi dei vettori deve essere implementato tramite l’utilizzo esplicito di 
 * puntatori. Il vettore deve essere gestito tramite allocazione dinamica. 
 * 
 * Lettura delle pietanze da un file. Il programma deve generare il vettore delle pietanze 
 * leggendo i valori da un file di testo denominato pietanze.txt. Nel caso in cui il file non sia 
 * presente il programma deve terminare la propria esecuzione e mostrare un messaggio di errore. 
 * N.B. il programma NON deve chiedere all’utente di inserire nuovamente il file. Per semplicità 
 * si supponga che i nomi delle pietanze abbiano tutti caratteri minuscoli e non presentino spazi 
 * bianchi.
 * Stampa a video delle caratteristiche delle pietanze. Il programma mostra a video le caratteristiche delle pietanze caricate nel vettore.

 * Ricerca delle prime due posizioni di una pietanza cercata dall’utente. 
 * Il programma chiede preventivamente all’utente di inserire il nome della pietanza da cercare. 
 * Il programma, successivamente, cerca e mostra a video le caratteristiche delle prime due pietanze 
 * con lo stesso nome cercato dall’utente. Il programma mostra a video un opportuno messaggio nel caso 
 * in cui nel vettore sia presente una sola pietanza con nome uguale al valore inserito dall’utente 
 * oppure non siano presenti pietanze con la caratteristica cercata.

 * Evidenziazione pietanze più costose. Il programma modifica il vettore delle pietanze memorizzato, 
 * evidenziando le pietanze il cui prezzo è maggiore al prezzo medio delle pietanze. 
 * Per evidenziare si intende che il programma trasforma in maiuscolo il primo carattere della 
 * pietanza.   


 */
typedef struct {
    char nome[11];
    double prezzo;
} pietanze;

pietanze* dati (int &, pietanze*, bool&);
void stampa(int, pietanze* );
void ricerca (int, pietanze*);
double calcoloMedia (int, pietanze*);
void evidenzio (int, pietanze*, double);

int main() {
    pietanze* menu;
    int riemp;
    bool esito;
    double media;
    
    menu=dati(riemp, menu, esito);
    if(esito==false){
        cout<<"Ops, qualcosa è andato storto...\n\nProgramma terminato";
        return -1;
    }
    stampa (riemp, menu);
    cout<<endl;
    ricerca(riemp, menu);
    cout<<endl;
    media=calcoloMedia(riemp, menu);
    //cout<<media;
    cout<<"Evidenzio pietanze più costose...(prezzo>"<<media<<")\n";
    evidenzio(riemp, menu, media);
    stampa(riemp, menu);

    return 0;
}

pietanze* dati (int &riemp, pietanze*v, bool& esito){
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
    v= new (nothrow) pietanze [riemp];
    
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

void stampa(int riemp, pietanze* v){
    cout<<"Menù\n   Piatto\t\tPrezzo\n";
    for(int i=0;i<riemp;i++){
        cout<<i<<": "<<(v+i)->nome<<"\t\t"<<(v+i)->prezzo<<endl;
    }
}

void ricerca (int riemp, pietanze*v){
    int n=0;
    int x=0;
    char elem[11];
    
    cout<<"Inserisci la pietanze da cercare: ";
    cin>>elem;
    
    for (int i=0;i<riemp;i++){
        if(strcmp(elem, (v+i)->nome)==0) n++;
    }
    switch (n){
        case 0:
            cout<<"Questa pietanza non è sul menù\n";
            break;
        case 1:
            cout<<"Una sola pietanza trovata nel menù\nPosizione:";
            for(int i=0;i<riemp;i++){
                if(strcmp(elem, (v+i)->nome)==0){
                    cout<<i<<endl;
                }
            }
            break;
        case 2: 
            cout<<"Trovate due pietanze nel menù\nPosizioni: ";
            for(int i=0;i<riemp;i++){
                if(strcmp(elem, (v+i)->nome)==0){
                    cout<<i<<", ";
                }
            }
            break;
        default:
            cout<<"Trovate più di due pietanze nel menù\nPrime due posizioni: ";
            for(int i=0;i<riemp;i++){
                if(strcmp(elem, (v+i)->nome)==0 && x<2){
                    cout<<i<<", ";
                    x++;
                }
            }
            break;      
}
}

double calcoloMedia (int riemp, pietanze*v){
    double med;
    double s;
    for (int i=0;i<riemp;i++){
        s=s+(v+i)->prezzo;
    }
    med=s/riemp;
    return med;
}

void evidenzio (int riemp, pietanze*v, double m){
    for (int i=0;i<riemp;i++){
        if((v+i)->prezzo>m){
        (v+i)->nome[0]=toupper((v+i)->nome[0]);
        }
    }
}