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

void sisipFilm(char judulBaru[100], int tahun, char genreBaru[50], float ratingBaru)
{

    Film *NB = new Film;
    strcpy(NB->judul, judulBaru);
    NB->tahunRilis = tahun;
    strcpy(NB->genre, genreBaru);
    NB->rating = ratingBaru;
    NB->kanan = nullptr;
    NB->kiri = nullptr;

    if (listKosong())
    {
        awal = NB;
        akhir = NB;
    }
    else if (tahun <= awal->tahunRilis)
    {
        NB->kanan = awal;
        awal->kiri = NB;
        awal = NB;
    }
    else
    {
        Film *bantu = awal;
        while (bantu->kanan != nullptr && tahun > bantu->kanan->tahunRilis)
        {
            bantu = bantu->kanan;
        }
        NB->kanan = bantu->kanan;
        if (bantu->kanan != nullptr)
        {
            bantu->kanan->kiri = NB;
        }
        else
        {
            akhir = NB;
        }
        NB->kiri = bantu;
        bantu->kanan = NB;
    }
}

void buatListBaru()
{
    // Hapus semua node yang ada di list
    while (awal != nullptr)
    {
        Film *hapus = awal;
        awal = awal->kanan;
        delete hapus;
    }
    akhir = nullptr;

    // Baca ulang dari file dan isi list
    FILE *file = fopen("FavoFilm.dat", "r");
    if (!file)
    {
        cout << "Gagal membuka file untuk inisialisasi list.\n";
        return;
    }

    char judul[100], genre[50];
    int tahun;
    float rating;

    while (fscanf(file, "%[^;];%d;%[^;];%f\n", judul, &tahun, genre, &rating) == 4)
    {
        sisipFilm(judul, tahun, genre, rating);
    }

    fclose(file);
}

void hapusFilm(char judulHapus[100])
{
    if (listKosong())
    {
        cout << "List masih kosong.\n";
        return;
    }

    if (awal == akhir && strcmp(awal->judul, judulHapus) == 0)
    {
        delete awal;
        awal = nullptr;
        akhir = nullptr;
        cout << "Film \"" << judulHapus << "\" berhasil dihapus.\n";
        return;
    }

    if (strcmp(awal->judul, judulHapus) == 0)
    {
        Film *hapus = awal;
        awal = awal->kanan;
        if (awal != nullptr)
            awal->kiri = nullptr;
        delete hapus;
        cout << "Film \"" << judulHapus << "\" berhasil dihapus.\n";
        return;
    }

    Film *bantu = awal;
    while (bantu->kanan != nullptr && strcmp(bantu->kanan->judul, judulHapus) != 0)
    {
        bantu = bantu->kanan;
    }

    if (bantu->kanan != nullptr && strcmp(bantu->kanan->judul, judulHapus) == 0)
    {
        Film *hapus = bantu->kanan;
        bantu->kanan = hapus->kanan;
        if (hapus->kanan != nullptr)
        {
            hapus->kanan->kiri = bantu;
        }
        else
        {
            akhir = bantu;
        }
        delete hapus;
        cout << "Film \"" << judulHapus << "\" berhasil dihapus.\n";
    }
    else
    {
        cout << "Film dengan judul \"" << judulHapus << "\" tidak ditemukan.\n";
    }
}

void cariFilm(char judulCari[100])
{
    if (listKosong())
    {
        cout << "List kosong.\n";
        return;
    }

    Film *bantu = awal;
    bool found = false;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->judul, judulCari) == 0)
        {
            cout << "Film ditemukan:\n";
            cout << "Judul     : " << bantu->judul << "\n";
            cout << "Tahun     : " << bantu->tahunRilis << "\n";
            cout << "Genre     : " << bantu->genre << "\n";
            cout << "Rating    : " << bantu->rating << "\n";
            found = true;
            break;
        }
        bantu = bantu->kanan;
    }
    if (!found)
        cout << "Film dengan judul \"" << judulCari << "\" tidak ditemukan.\n";
}


void tampilkanFilm()
{
    if (listKosong())
    {
        cout << "List kosong.\n";
        return;
    }
    Film *bantu = awal;
    cout << "----------------------------------------\n";
    cout << "        Daftar Film Kesukaan:\n";
    cout << "----------------------------------------\n";
    while (bantu != nullptr)
    {
        cout << "Judul     : " << bantu->judul << "\n";
        cout << "Tahun     : " << bantu->tahunRilis << "\n";
        cout << "Genre     : " << bantu->genre << "\n";
        cout << "Rating    : " << bantu->rating << "\n";
        cout << "----------------------------------------\n";
        bantu = bantu->kanan;
    }
}

void simpanKeFile()
{
    FILE *file = fopen("FavoFilm.dat", "w");
    if (!file)
    {
        cout << "Gagal menyimpan ke file.\n";
        return;
    }

    Film *bantu = awal;
    while (bantu != nullptr)
    {
        fprintf(file, "%s;%d;%s;%.2f\n",
                bantu->judul,
                bantu->tahunRilis,
                bantu->genre,
                bantu->rating);
        bantu = bantu->kanan;
    }

    fclose(file);
}

int main (){


    return 0;
}