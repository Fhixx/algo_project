#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

using namespace std;

FILE *file;
struct Film
{
    char judul[100];
    int tahunRilis;
    char genre[50];
    float rating;
    Film *kanan;
    Film *kiri;
};
Film *awal = nullptr;
Film *akhir = nullptr;

bool listKosong()
{
    return (awal == nullptr);
}

int main (){


    return 0;
}