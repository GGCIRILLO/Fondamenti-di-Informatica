/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 21 dicembre 2022, 21:51
 */

#include <iostream>
#include <fstream>

using namespace std;
#define MAX 11
/*
 * 
 */
typedef struct {
    char titolo[16];
    double prezzo;
    int pagine;
    int copie;
} libri;

void caricaDati (int&,libri [], bool&);
void stampa(int, libri []);
void newVet (int , libri [],  libri [], int&);
double valore (int, libri []);
void ricerca (int , libri []);

int main() {
    libri vettore[MAX];
    int riemp;
    bool esito=true;
    libri carrello_libri_non_diponibili[MAX];
    int riemp2;
    
    caricaDati(riemp, vettore, esito);
    if(!esito){
        cout<<"Ops...qualcosa è andato storto\n\nProgramma terminato";
        return -1;
    }
    stampa(riemp, vettore);
    newVet(riemp, vettore, carrello_libri_non_diponibili, riemp2);
    cout<<"\n\nCarrello libri non disponibili...\n";
    stampa(riemp2, carrello_libri_non_diponibili);
    cout<<"Valore del carrello: "<<valore(riemp2, carrello_libri_non_diponibili);
    cout<<endl<<endl;
    ricerca(riemp, vettore);

    return 0;
}

void caricaDati (int&riemp,libri v[], bool&esito){
    fstream file;
    file.open("copie.txt", ios::in);
    
    if (!file){
        cout<<"File non presente"<<endl;
        esito=false;
    }
    
    file>>riemp;
    if (riemp<=0){
        cout<<"Riempimento negativo o 0"<<endl;
        esito=false;
    }
    
    for(int i=0;i<riemp;i++){
        file>>v[i].titolo;
        file>>v[i].prezzo;
        file>>v[i].pagine;
        file>>v[i].copie;
    }
    file.close();
}

void stampa(int riemp, libri v[]){
    cout<<"Libreria:\nTitolo   Prezzo   Pagine   Copie"<<endl;
    for (int i=0;i<riemp;i++){
        cout<<v[i].titolo<<"  "<<v[i].prezzo<<"  "<<v[i].pagine<<"  "<<v[i].copie<<endl;
    }
}

void newVet (int riemp, libri v[],  libri carrello_libri_non_diponibili[], int&riemp2){
    riemp2=0;
    
    for (int i=0;i<riemp;i++){
        if(v[i].copie==0){
            riemp2++;
        }
    }
    
    int j=0;
    for (int i=0;i<riemp;i++){
        if(v[i].copie==0){
            carrello_libri_non_diponibili[j]=v[i];
            j++;
        }
    }
}

double valore (int riemp, libri v[]){
    double somma=0;
    
    for (int i=0;i<riemp;i++){
        somma=somma+v[i].prezzo;
    }
    return somma;
}

void ricerca (int riemp, libri v[]){
    char x;
    bool trovato=false;
    
    cout<<"Inserisci l'iniziale dei libri da cercare: ";
    cin>>x;
    
    for (int i=0;i<riemp;i++){
        if(v[i].titolo[0]==x){
            cout<<v[i].titolo<<"  "<<v[i].prezzo<<"  "<<v[i].pagine<<"  "<<v[i].copie<<endl;
            trovato=true;
        }
    }
    
    if (trovato==false){
        cout<<"Nessun libro trovato";
    }
}