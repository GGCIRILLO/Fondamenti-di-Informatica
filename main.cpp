/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 5 dicembre 2022, 17:52
 */

#include <iostream>
#include <fstream>
using namespace std;

typedef struct{
    char nome[17];
    double dimensione;
    int dataCreazione;
    int dataUltimaModifica;
} file;

file* caricaFile (int&, file*, bool&);
void stampa (int, file *);
int sensoOrdinamento ();
void ordinamentoCrescente (int, file *);
void ordinamentoDecrescente (int, file *);
int contatore (int, file *);
void nuovoVettore (int, file*, file *);


int main () {
    int riemp;
    file *cartella;
    int senso;
    bool esito;
    int riemp2;
    file *cartella2;
    
    cartella=caricaFile(riemp, cartella, esito);
    if (esito==false){
        cout<<"Errore. Programma terminato";
        return -1;
    } else {
    
    cout<<"Documenti presenti:\n";
    cout<<"Nome\t\t\tDimensione\tCreazione\tUltima modifica\n";
    stampa(riemp, cartella);
    }
    
    cout<<endl;
    senso = sensoOrdinamento();
    
    if (senso==1){
        ordinamentoCrescente(riemp, cartella);
        cout<<"Ordino in senso crescente...\n";
    } else {
        ordinamentoDecrescente(riemp, cartella);
        cout<<"Ordino in senso decrescente...\n";
    }
        
    cout<<"Nome\t\t\tDimensione\tCreazione\tUltima modifica\n";
    stampa(riemp, cartella);
    
    cout<<endl;
    riemp2= contatore(riemp, cartella);
    cartella2 = new (nothrow) file[riemp2];
    nuovoVettore(riemp, cartella, cartella2);
    cout<<"I documenti con dimensione maggiore di 2 MB sono: \n";
    cout<<"Nome\t\t\tDimensione\tCreazione\tUltima modifica\n";
    stampa(riemp2, cartella2);

    
    

    cout<<"\n\nProgramma Terminato"<<endl;
    return 0;
}

file* caricaFile (int& riemp, file *cartella, bool& esito){
    fstream mioFile;
    mioFile.open("cartella.txt", ios::in);
    if(!mioFile){
        esito = false;
    } else {
    mioFile>>riemp;
    
    
    cartella= new (nothrow) file[riemp];
    if(!cartella){
        cout<<"Memoria non disponbile";
        esito = false;
    }
    
    for (int i=0;i<riemp;i++){
            mioFile>>(cartella+i)->nome;
            mioFile>>(cartella+i)->dimensione;
            mioFile>>(cartella+i)->dataCreazione;
            mioFile>>(cartella+i)->dataUltimaModifica;
        }
    
    esito = true;
    
    mioFile.close();
    }
    return cartella;
}

void stampa (int riemp, file *v){
    for (int i=0;i<riemp;i++){
        cout<<(v+i)->nome<<"\t\t\t"<<(v+i)->dimensione<<" MB\t"<<(v+i)->dataCreazione<<"\t\t"<<(v+i)->dataUltimaModifica<<endl;
}
}

int sensoOrdinamento (){
    int senso;
    do {
        cout<<"Digita 1 per scegliere l'ordinamento crescente o 2 per scegliere l'ordinamento decrescente: ";
        cin>>senso;
        if(senso<1 || senso>2){
            cout<<"Errore! Scelta non valida, riprova...\n";
        }
    } while (senso<1 || senso>2);
    return senso;
}

void ordinamentoCrescente (int riemp, file *v){
    double min;
    int pos;
    file *temp;
    temp = new (nothrow) file [1];
    
    for(int i=0;i<riemp-1;i++){
        min=(v+i)->dimensione;
        pos=i;
        for(int j=i+1;j<riemp;j++){
            if((v+j)->dimensione<min){
                min=(v+j)->dimensione;
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

void ordinamentoDecrescente (int riemp, file *v){
    double max;
    int pos;
    file *temp;
    temp = new (nothrow) file [1];
    
    for (int i=0;i<riemp-1;i++){
        max=(v+i)->dimensione;
        pos=i;
        for (int j=i+1;j<riemp;j++){
            if((v+j)->dimensione>max){
                max=(v+j)->dimensione;
                pos=j;
            }
        }
        if (i!=pos){
            *temp=*(v+i);
            *(v+i)=*(v+pos);
            *(v+pos)=*temp;
        }
        
    }
}

int contatore (int riemp, file *v){
    int riemp2;
    for(int i=0;i<riemp;i++){
        if((v+i)->dimensione>2.00){
            riemp2++;
        }
    }
    return riemp2;
}

void nuovoVettore (int riemp, file* v, file *v2){
    int j=0;
    for (int i=0;i<riemp;i++){
        if((v+i)->dimensione>2.00){
        *(v2+j)=*(v+i);
        j++;
        }
    }
}