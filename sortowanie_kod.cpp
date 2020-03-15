#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;



void fill_increasing(int *T, unsigned int n) {
    unsigned int i;
    for(i=0;i<n;i++){
        *(T+i)=i;
    }
}

void fill_random(int *T, unsigned int n) {
    unsigned int i;
    for(i=0;i<n;i++){
        *(T+i)=rand()%10000;
    }
}

void fill_decreasing(int *T, unsigned int n) {
    unsigned int i;
    for(i=0;i<n;i++){
        *(T+i)=n-i;
    }
}

void fill_vshape(int *T, unsigned int n) {
    unsigned int i;
    int *begin=T;
    int *end=T+n-1;
    *begin=n;
    for(i=0;i<n/2;i++){
        *end=*begin-1;
        *(begin+1)=*end-1;
        begin++;
        end--;
    }
}



void zamien(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}



void selection_sort(int *T, unsigned int n) {
    unsigned int i,j;
    for(i=0;i<n-1;i++){
        unsigned int min=i;
        for(j=i;j<n;j++){
            if(*(T+j)<*(T+min))min=j;
        }
        zamien(T+i,T+min);
    }
}


void insertion_sort(int *T, unsigned int n) {
    int *left,*right;
    unsigned int i,j;
    for(i=1;i<n;i++){
        left=T+i-1;
        right=T+i;
        for(j=0;j<i;j++){
            if(*left>*right){
                zamien(left,right);
                left--;
                right--;
            }
            else break;
        }
    }
}



unsigned int dzielenie(int *T,unsigned int a,unsigned int b){//a, b pierwszy i ostatni element tablicy(indeksy)
    unsigned int i=a,x=a;
        for(i;i<b;i++){
        if(T[i]<=T[b]){
            if(T[i]!=T[x])zamien(&T[i],&T[x]);
            x++;
        }
    }
    if(T[b]!=T[x])zamien(&T[b],&T[x]);
    return x;
}


unsigned int dzielenie_losowe(int *T,unsigned int a,unsigned int b){//a, b pierwszy i ostatni element tablicy(indeksy)
    unsigned int x=a+rand()%(b-a+1);
    zamien(&T[x],&T[b]);
    return dzielenie(T,a,b);
}

void quick_sort_l(int *T, unsigned int a, unsigned int b) {//a, b pierwszy i ostatni element tablicy(indeksy)

        unsigned int x=dzielenie(T,a,b);
        if(x!=a)quick_sort_l(T,a,x-1);
        if(x!=b)quick_sort_l(T,x+1,b);
}

void quick_sort_r(int *T, unsigned int a, unsigned int b) {//a, b pierwszy i ostatni element tablicy(indeksy)

        unsigned int x=dzielenie_losowe(T,a,b);
        if(x!=a)quick_sort_r(T,a,x-1);
        if(x!=b)quick_sort_r(T,x+1,b);
}

void quick_sort_random(int *T, unsigned int n){
        quick_sort_r(T,0,n-1);
    }

void quick_sort_last(int *T, unsigned int n){
    quick_sort_l(T,0,n-1);
}



void usun_korzen(int *heap,unsigned int index,unsigned int rozmiar){//rozmniar - liczba elementów kopca, index - badany element kopca


    unsigned int l=2*index+1;
    unsigned int r=2*index+2;
    unsigned int argmin;
    if(l<rozmiar){
        if(r>=rozmiar || heap[l] < heap[r]){
            argmin=l;
        }
        else argmin=r;
        if(heap[argmin]<heap[index]){
        zamien(&heap[argmin],&heap[index]);
        usun_korzen(heap,argmin,rozmiar);
    }
    }

}
void heap_sort(int *T, unsigned int n) {

    unsigned int i,syn, rodzic, rozmiar=n;

    int heap[n];

    for(i=0;i<n;i++){
        heap[i]=T[i];
    }

    for(i=1;i<n;i++){
            syn=i;
            rodzic=(i-1)/2;
        while(heap[syn]<heap[rodzic]){
            zamien(&heap[syn],&heap[rodzic]);
            syn=rodzic;
            if(rodzic!=0)rodzic=(rodzic-1)/2;
        }
    }//robienie kopca


    for(i=0;i<n;i++){

        T[i]=heap[0];
        rozmiar--;
        heap[0]=heap[rozmiar];
        usun_korzen(heap, 0,rozmiar);

    }//wype³nianie tablicy

}



void czy_posortowane(int *T,unsigned int n){
    for(unsigned int i=1;i<n;i++){
        if(T[i]<T[i-1])cout<<"is not sorted!";
    }

}



void (*rodzaj_wypelnienia[])(int *,unsigned int ) = {fill_increasing, fill_decreasing,fill_vshape, fill_random};
string nazwa_wypelnienia[] = {"Fill_increasing", "Fill_decreasing", "Fill_vshape    ", "Fill_random    "};
void (*rodzaj_sortowania[])(int *,unsigned int) = {heap_sort,quick_sort_last,quick_sort_random,selection_sort, insertion_sort};
string nazwa_sortowania[] = { "Heap_sort      ","Quick_sort_last", "Quick_sort_rand" ,"Selection_sort ", "Insertion_sort "};
unsigned int wielkosc_tablicy[] = {500,1000,2000,4000,8000,16000,32000,64000,128000,256000};


int main()
{
    unsigned int i,j,k;
    unsigned int n;
    srand(time(NULL));

    fstream plik_out;

    plik_out.open("plik_wynikowy.txt", ios::out);

    clock_t start;
    clock_t stop;


    for(i=0;i<sizeof(rodzaj_sortowania)/sizeof(*rodzaj_sortowania);i++){

        plik_out<<endl<<endl<<endl<<nazwa_sortowania[i]<<" ";
        cout<<endl<<endl<<endl<<nazwa_sortowania[i]<<" ";
        for(k=0;k<sizeof(wielkosc_tablicy)/sizeof(*wielkosc_tablicy);k++){
            plik_out<<setw(10)<<wielkosc_tablicy[k];
            cout<<setw(10)<<wielkosc_tablicy[k];
        }

        for(j=0;j<sizeof(rodzaj_wypelnienia)/sizeof(*rodzaj_wypelnienia);j++){

                plik_out<<endl<<nazwa_wypelnienia[j]<<" ";
                cout<<endl<<nazwa_wypelnienia[j]<<" ";

            for(k=0;k<sizeof(wielkosc_tablicy)/sizeof(*wielkosc_tablicy);k++){

                n=wielkosc_tablicy[k];
                //cout<<n<<": ";
                int *tablica = new int[n];

                rodzaj_wypelnienia[j](tablica,n);



                start = clock();
                rodzaj_sortowania[i](tablica,n);

                stop = clock();
                czy_posortowane(tablica,n);

                //printf("%3.6f\t",((double)(stop-start)/(double)CLOCKS_PER_SEC));

                plik_out<<setw(10)<<(double)(stop-start)/(double)CLOCKS_PER_SEC;
                cout<<setw(10)<<(double)(stop-start)/(double)CLOCKS_PER_SEC;


                delete[] tablica;
                if(k==6&&i==1&&j!=3)break;
            }

        }
    }

    plik_out.close();





    return 0;
}
