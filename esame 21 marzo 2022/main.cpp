/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: luigicirillo
 *
 * Created on 21 dicembre 2022, 22:31
 */

#include <iostream>
#include <fstream>
#include <string.h>
#define MAX 10
using namespace std;

/*
 * 
 */
typedef struct {
    char id[6];
    double vel;
    double temp;
} robot; 

void caricaDati (int&, robot[], bool&);
void stampa (int, robot []);
void maxtemp (int, robot []);
void ordinamento (int , robot []);
void cancellazione (int&, robot []);

int main() {
    robot vettore[MAX];
    int riemp;
    bool esito=true;
    
    caricaDati(riemp, vettore, esito);
    if(!esito){
        cout<<"Ops...qualcosa è andato storto";
        return -1;
    }
    stampa(riemp, vettore);
    cout<<endl;
    cout<<"\nOrdinamento alfabetico...\n";
    ordinamento(riemp, vettore);
    stampa(riemp, vettore);
    cout<<endl;
    cout<<"Evidenzio i tre robot a temperatura massima...\n";
    maxtemp(riemp, vettore);
    stampa(riemp, vettore);
    
    cout<<endl<<"Cancellazione bracci robotici con id che inizia tra \'a\' e \'d\' (anche maisucole\n";
    cancellazione(riemp,vettore);
    stampa(riemp, vettore);
    

    return 0;
}

void caricaDati (int&riemp, robot v[], bool&esito){
    fstream file;
    file.open("robot.txt", ios::in);
    
    if(!file){
        cout<<"File non presente"<<endl;
        esito=false;
    }
    file>>riemp;
    if (riemp<=0 || riemp>MAX ){
        cout<<"Memoria non disponibile";
        esito=false;
    }
    for(int i=0;i<riemp;i++){
        file>>v[i].id;
        file>>v[i].vel;
        file>>v[i].temp;
    }
    file.close();
}

void stampa (int riemp, robot v[]){
    cout<<"ID\tVelocità\tTemperatura\n";
    for(int i=0;i<riemp;i++){
        cout<<v[i].id<<"\t"<<v[i].vel<<"\t\t"<<v[i].temp<<endl;
    }
}

void maxtemp (int riemp, robot v[]){
    double max1=0, max2=0, max3=0;
    int n=0;
    
    for (int i=0;i<riemp;i++){
        if(v[i].temp>max1){
            max1=v[i].temp;
        }
    }
    for (int i=0;i<riemp;i++){
        if(v[i].temp>max2 && v[i].temp!=max1){
            max2=v[i].temp;
        }
    }
    for (int i=0;i<riemp;i++){
        if(v[i].temp>max3 && (v[i].temp!=max1 || v[i].temp!=max2 )){
            max3=v[i].temp;
        }
    }
    //cout<<max1<<" "<<max2<<" "<<max3<<endl;
    for (int i=0;i<riemp;i++){
        if(v[i].temp==max1 || v[i].temp==max2 || v[i].temp==max3) {
        for (int j=0;j<strlen(v[i].id);j++){
            v[i].id[j]=toupper(v[i].id[j]);
            }
        }
    }
}

void ordinamento (int riemp, robot v[]){
    robot temp;
    int pos;
    char min[6];
    
    for (int i=0;i<riemp-1;i++){
        strcpy(min, v[i].id);
        pos=i;
        for (int j=i+1;j<riemp;j++){
            if(strcmp(v[j].id, min)<0){
                strcpy(min, v[j].id);
                pos=j;
            }
        }
        if (pos!=i){
            temp=v[i];
            v[i]=v[pos];
            v[pos]=temp;
        }
    }
}

void cancellazione (int& riemp, robot v[]){
    for(int i=0;i<riemp;i++){
        if((v[i].id[0]>='A' && v[i].id[0]<='D' ) || (v[i].id[0]>='a' && v[i].id[0]<='d')){
            riemp--;
            for (int j=i;j<riemp;j++){
                v[j]=v[j+1];
            }
            i--;
        }
    }
}