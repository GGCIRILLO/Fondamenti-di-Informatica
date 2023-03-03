/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 10 dicembre 2022, 16:16 
 * 18:21(problema virgola-punto txt, pausa bevanda)
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*Scrivere un programma per la gestione di una libreria. La libreria può essere modellata 
 * come un vettore di copie di un libro. Ogni copia è descritta dal titolo del libro 
 * (stringa di al più 15 caratteri), dal prezzo (valore reale) e dal numero di pagine della 
 * copia (numero intero). Nella libreria ci possono essere più copie dello stesso libro, 
 * eventualmente con differente prezzo e/o numero di pagine.

 

Il programma deve essere strutturato utilizzando i prototipi di funzione. Inoltre, 
 * l’accesso agli elementi dei vettori deve essere implementato tramite l’utilizzo esplicito 
 * di puntatori. Il vettore deve essere gestito tramite allocazione dinamica. 

    
 * Lettura dei dati delle copie dei libri da un file. Il programma deve generare il vettore 
 * del magazzino leggendo i valori da un file di testo denominato copie.txt. Il file deve essere 
 * strutturato riportando le caratteristiche delle copie dei libri. Nel caso in cui il file non 
 * sia presente il programma deve terminare la propria esecuzione e mostrare un messaggio di 
 * errore. N.B. il programma NON deve chiedere all’utente di inserire nuovamente il file. 
 * Suggerimenti: si supponga per semplicità che (1) il prezzo dei libri sia sempre strettamente 
 * positivo, (2) il titolo non contiene spazi bianchi ed inizia con una lettera minuscola.


 * Stampa a video delle copie dei libri disponibili in libreria. Il programma mostra a video 
 * le caratteristiche delle copie disponibili in libreria.

            
 *  Ricerca di copie a minor costo per un dato titolo. Il programma chiede all’utente di 
 * inserire il titolo di un libro da cercare. Il programma restituisce il numero delle copie 
 * a prezzo minimo per il titolo cercato e il prezzo minimo della copia. Se non esiste una 
 * copia allora il programma mostra a video un opportuno messaggio di errore.

          

 * Costruzione di un carrello di 100 €. Il programma genera un nuovo vettore denominato carrello. 
 * Il programma automaticamente riempie il carrello prelevando in ordine le copie dalla libreria. 
 * Il carrello contiene il numero massimo di copie tale da non superare il costo massimo 
 * complessivo di 100€. Il programma mostra a video il carrello ottenuto.
 * 
 */

typedef struct {
    char titolo[16];
    double prezzo;
    int pagine;
} libro;

libro* caricamentoDati (int&, libro* , bool &);
void stampa (int, libro *);
void ricerca (int, libro*, char [16]);
libro* creazioneCarrello (int, libro*, libro*, int&, bool& );

int main() {
    int riemp;
    libro* vettore;
    bool esito;
    char elem[16];
    libro *carrello;
    int riemp2=0;
    bool esito2;
    
    vettore=caricamentoDati(riemp, vettore, esito);
    if(esito==false){
        cout<<"Ops.. qualcosa è andato storto..\n\nProgramma terminato";
        return -1;
    }
    cout<<"Libreria: \n";
    stampa(riemp, vettore);
    
    cout<<"\nInserisci il titolo del libro da cercare: ";
    cin>>elem;
    ricerca(riemp, vettore, elem);
    
    cout<<endl<<endl;
    carrello=creazioneCarrello(riemp, vettore, carrello, riemp2, esito2);
    if (esito2==false){
        cout<<"Errore! Non è stato possibile creare il carrello\n";
    } 
    cout<<"Carrello:\n";
    stampa(riemp2, carrello);

    return 0;
}

libro* caricamentoDati (int& riemp, libro* v, bool & esito){
    fstream file;
    file.open("copie.txt", ios::in);
    if(!file){
        cout<<"Errore! File non presente\n";
        esito = false;
    } else {
        file>>riemp;
        if(riemp<=0){
            cout<<"Errore! Riempimento negativo o 0\n";
            esito=false;
        } else {
        v = new (nothrow) libro[riemp];
        if(!v){
            cout<<"Errore! Memoria non disponibile";
            esito=false;
        }
        for (int i=0;i<riemp;i++){
            file>>(v+i)->titolo;
            file>>(v+i)->prezzo;
            file>>(v+i)->pagine;
        }
        
        esito=true;
        } }
    file.close();
    return v;
}

void stampa (int riemp, libro *v){
    cout<<"           Titolo\tPrezzo\t\tPagine\n";
    for(int i=0;i<riemp;i++){
        cout<<"Libro ["<<i<<"]: "<<(v+i)->titolo<<"\t"<<(v+i)->prezzo<<"\t\t"<<(v+i)->pagine<<endl;
    }    
}

void ricerca (int riemp, libro*v, char elem[16]){
    int n=0;
    double min;
    bool trovato=false;
    int k=0;
    
    while (!trovato && k<riemp){
                if (strcmp((v+k)->titolo, elem)==0){
                    trovato=true;
                } 
                k++;
            }
    
    for (int i=0;i<riemp;i++){
        if (strcmp((v+i)->titolo, elem)==0){
            n++;
        }
    }
    
    min=(v+k-1)->prezzo;

    switch (n){
        case 0: 
            cout<<"Non ci sono copie presenti in libreria\n";
            break;
        case 1:
            cout<<"Esiste una sola copia\nPrezzo minimo: ";
            cout<<min<<endl;
            break;
        default:
            cout<<"Esitono due o più copie\nPrezzo minimo: ";
            for (int i=0;i<riemp;i++){
                if(strcmp((v+i)->titolo, elem)==0){
                    if((v+i)->prezzo<min){
                        min=(v+i)->prezzo;
                    }
                }
            }
            cout<<min;
            break;
            }
}

libro* creazioneCarrello (int riemp, libro*v, libro*v2, int& riemp2, bool& esito){
    int j=0;;
    double somma=0;
    double somma1=0;
    
    for (int i=0;i<riemp;i++){
        if(somma<100){
        somma=somma+(v+i)->prezzo;
        riemp2++;
        }
    }
    if (riemp2<=0){
        cout<<"Carrello vuoto\n";
        esito=false;
    }else {
    v2= new libro[riemp2];
    
    for (int i=0;i<riemp;i++){
        if(somma1<100){
        somma1=somma1+(v+i)->prezzo;
        *(v2+j)=*(v+i);
        j++;
        }
    }
    esito=true;
    }
    return v2;
}