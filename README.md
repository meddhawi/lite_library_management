# Sistem Manajemen Perpustakaan

Aplikasi berbasis command line untuk mengelola data buku perpustakaan dengan fitur dasar peminjaman dan pengembalian buku.

## Fitur

- Menampilkan daftar buku
- Pencarian buku berdasarkan judul/penulis 
- Peminjaman buku
- Pengembalian buku
- Menambah buku baru
- Update status buku
- Penyimpanan data dalam format JSON

## Teknologi yang Digunakan

- C++11
- nlohmann/json library untuk pengelolaan data JSON
- Makefile untuk kompilasi

## Persyaratan Sistem

- G++ compiler dengan dukungan C++11
- Make build tool
- Git (untuk clone repository)

## Cara Menjalankan Aplikasi

1. Clone repository
bash
git clone <repository-url>
cd <nama-folder>
make

2. Compile program menggunakan make
bash
make

3. Jalankan aplikasi
bash
./library_app

## Struktur Data JSON

Data buku disimpan dalam format JSON dengan struktur sebagai berikut:

## Penggunaan Program

1. Menampilkan daftar buku: Pilih menu 1 untuk melihat semua buku yang ada di perpustakaan
2. Mencari buku: Pilih menu 2 dan masukkan kata kunci judul/penulis
3. Meminjam buku: Pilih menu 3 dan masukkan ID buku yang ingin dipinjam
4. Mengembalikan buku: Pilih menu 4 dan masukkan ID buku yang ingin dikembalikan
5. Menambah buku: Pilih menu 5 dan ikuti instruksi untuk memasukkan detail buku
6. Update status buku: Pilih menu 6 untuk mengubah status ketersediaan buku
7. Keluar: Pilih menu 7 untuk mengakhiri program

## Pengembangan

Kode sumber terdiri dari beberapa komponen utama:
- `main.cpp`: Program utama dan implementasi menu
- `book.h/cpp`: Class untuk objek buku
- `data_handler.h/cpp`: Class untuk penanganan data JSON

## Lisensi

[Sesuaikan dengan lisensi yang digunakan]

## Kontribusi

[Panduan kontribusi jika project open source]
