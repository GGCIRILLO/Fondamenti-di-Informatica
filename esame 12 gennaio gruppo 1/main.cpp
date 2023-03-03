/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 20 dicembre 2022, 15:16
 */

#include <iostream>
#include <fstream>

using namespace std;
#define MAX 100
/*
 * 
 */
typedef struct {
    int id;
    int cons;
    int tot;
    double valore;
} furgoni;

void dati (int&, furgoni []);
void stampa (int, furgoni []);
void efficienza (int, furgoni []);
void cancellazione (int&, furgoni []);

    
int main() {
    int riemp;
    furgoni vettore [MAX];
    
    dati(riemp, vettore);
    stampa(riemp, vettore);
    cout<<endl;
    
    cout<<"Cerco furgoni a maggiore efficienza...\n";
    efficienza(riemp, vettore);
    
    cout<<"\n\nI furgoni che hanno terminato le consegne tornano al magazzino...\n";
    cancellazione(riemp, vettore);
    stampa(riemp, vettore);

    return 0;
}

void dati (int&riemp, furgoni v []){
    fstream file;
    do {
        cout<<"Inserisci il numero di furgoni: ";
        cin>>riemp;
        if(riemp<=0 || riemp>100){
            cout<<"Errore! Deve essere maggiore di zero e minore di cento. Riprova...\n";
        }
    } while (riemp<=0 || riemp>100);
    
    file.open("furgoni.txt", ios::in);
    if(!file){
        cout<<"Errore, file non esistente";
    }
    for (int i=0;i<riemp;i++){
        file>>v[i].id;
        file>>v[i].cons;
        file>>v[i].tot;
        file>>v[i].valore;
    }
}

void stampa (int riemp, furgoni v[]){
    cout<<"Furgoni "<<endl;
    cout<<"ID\tDa Consegnare\tTotali\tValore\n";
    for(int i=0;i<riemp;i++){
        cout<<v[i].id<<"\t"<<v[i].cons<<"\t\t"<<v[i].tot<<"\t"<<v[i].valore<<endl;
    }
}

void efficienza (int riemp, furgoni v[]){
    int max=v[0].tot - v[0].cons;
    
    for (int i=0;i<riemp;i++){
        if (v[i].tot - v[i].cons > max){
            max=v[i].tot - v[i].cons;
        }
    }
    
    cout<<"ID\tDa consegnare\t\tTotali\tValore"<<endl;
    for (int i=0;i<riemp;i++){
        if(v[i].tot - v[i].cons==max){
           cout<<v[i].id<<"\t"<<v[i].cons<<"\t\t"<<v[i].tot<<"\t"<<v[i].valore<<endl;
        }
    }
}

void cancellazione (int& riemp, furgoni v[]){
    for (int i=0;i<riemp;i++){
        if (v[i].cons==0){
            riemp--;
            for (int j=i;j<riemp;j++){
            v[j]=v[j+1];
            }
            i--;
        }
    }
}
