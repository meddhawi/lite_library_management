#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "book.h"
#include "data_handler.h"

const int WIDTH = 50;  // Add this at the top with other global declarations

// Utility functions for UI
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(char symbol, int width) {
    cout << '+' << string(width, symbol) << '+' << endl;
}

void printCenter(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    cout << '|' << string(padding, ' ') << text << string(width - padding - text.length(), ' ') << '|' << endl;
}

void printBox(const string& title, int width) {
    printLine('=', width);
    printCenter(title, width);
    printLine('=', width);
}

void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanMenu() {
    clearScreen();
    
    printBox("SISTEM MANAJEMEN PERPUSTAKAAN", WIDTH);
    cout << endl;
    
    printLine('-', WIDTH);
    printCenter("MENU UTAMA", WIDTH);
    printLine('-', WIDTH);
    printCenter("1. Tampilkan Daftar Buku", WIDTH);
    printCenter("2. Cari Buku", WIDTH);
    printCenter("3. Pinjam Buku", WIDTH);
    printCenter("4. Kembalikan Buku", WIDTH);
    printCenter("5. Tambah Buku Baru", WIDTH);
    printCenter("6. Update Status Buku", WIDTH);
    printCenter("7. Keluar", WIDTH);
    printLine('-', WIDTH);
    cout << "\nPilihan Anda: ";
}

// Fungsi untuk menampilkan detail buku
void tampilkanBuku(const Book& book, int width) {
    printLine('-', width);
    cout << "| ID      : " << left << setw(width-12) << book.getId() << "|" << endl;
    cout << "| Judul   : " << left << setw(width-12) << book.getJudul() << "|" << endl;
    cout << "| Penulis : " << left << setw(width-12) << book.getPenulis() << "|" << endl;
    cout << "| Status  : " << left << setw(width-12) 
         << (book.isTersedia() ? "Tersedia" : "Dipinjam") << "|" << endl;
    printLine('-', width);
}

// 1. Fungsi untuk menampilkan semua buku
void tampilkanDaftarBuku(const vector<Book>& books) {
    cout << "\nDaftar Buku Perpustakaan:\n";
    cout << "------------------------\n";
    if (books.empty()) {
        cout << "Tidak ada buku dalam database.\n";
        return;
    }
    
    for (const auto& book : books) {
        tampilkanBuku(book, WIDTH);
    }
}

// 2. Fungsi untuk mencari buku
void cariBuku(const vector<Book>& books) {
    string keyword;
    cout << "Masukkan judul atau penulis buku: ";
    cin.ignore();
    getline(cin, keyword);
    
    bool ditemukan = false;
    for (const auto& book : books) {
        if (book.getJudul().find(keyword) != string::npos || 
            book.getPenulis().find(keyword) != string::npos) {
            tampilkanBuku(book, WIDTH);
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Buku tidak ditemukan.\n";
    }
}

// 3. Fungsi untuk meminjam buku
void pinjamBuku(vector<Book>& books) {
    string id;
    cout << "Masukkan ID buku yang ingin dipinjam: ";
    cin >> id;
    
    for (auto& book : books) {
        if (book.getId() == id) {
            if (book.isTersedia()) {
                book.setTersedia(false);
                cout << "Buku '" << book.getJudul() << "' berhasil dipinjam.\n";
                return;
            } else {
                cout << "Maaf, buku sedang dipinjam.\n";
                return;
            }
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

// 4. Fungsi untuk mengembalikan buku
void kembalikanBuku(vector<Book>& books) {
    string id;
    cout << "Masukkan ID buku yang ingin dikembalikan: ";
    cin >> id;
    
    for (auto& book : books) {
        if (book.getId() == id) {
            if (!book.isTersedia()) {
                book.setTersedia(true);
                cout << "Buku '" << book.getJudul() << "' berhasil dikembalikan.\n";
                return;
            } else {
                cout << "Buku ini sudah ada di perpustakaan.\n";
                return;
            }
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

// 5. Fungsi untuk menambah buku baru
void tambahBuku(vector<Book>& books) {
    string id, judul, penulis;
    
    cout << "Masukkan ID buku: ";
    cin >> id;
    cin.ignore();
    
    // Cek apakah ID sudah ada
    for (const auto& book : books) {
        if (book.getId() == id) {
            cout << "ID buku sudah ada dalam sistem.\n";
            return;
        }
    }
    
    cout << "Masukkan judul buku: ";
    getline(cin, judul);
    
    cout << "Masukkan nama penulis: ";
    getline(cin, penulis);
    
    books.emplace_back(id, judul, penulis);
    cout << "Buku berhasil ditambahkan.\n";
}

// 6. Fungsi untuk mengupdate status buku
void updateStatusBuku(vector<Book>& books) {
    string id;
    cout << "Masukkan ID buku: ";
    cin >> id;
    
    for (auto& book : books) {
        if (book.getId() == id) {
            cout << "Status saat ini: " << (book.isTersedia() ? "Tersedia" : "Dipinjam") << endl;
            cout << "Update status menjadi (1: Tersedia, 0: Dipinjam): ";
            bool status;
            cin >> status;
            book.setTersedia(status);
            cout << "Status buku berhasil diupdate.\n";
            return;
        }
    }
    cout << "Buku dengan ID tersebut tidak ditemukan.\n";
}

// Main function dengan implementasi menu lengkap
int main() {
    JsonHandler handler("data/books.json");
    handler.loadData();
    
    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        clearScreen();
        
        switch(pilihan) {
            case 1: {
                printBox("DAFTAR BUKU PERPUSTAKAAN", WIDTH);
                tampilkanDaftarBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 2: {
                printBox("PENCARIAN BUKU", WIDTH);
                cariBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 3: {
                printBox("PEMINJAMAN BUKU", WIDTH);
                pinjamBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 4: {
                printBox("PENGEMBALIAN BUKU", WIDTH);
                kembalikanBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 5: {
                printBox("TAMBAH BUKU BARU", WIDTH);
                tambahBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 6: {
                printBox("UPDATE STATUS BUKU", WIDTH);
                updateStatusBuku(handler.getBooks());
                pauseScreen();
                break;
            }
            case 7: {
                clearScreen();
                printBox("TERIMA KASIH", WIDTH);
                printCenter("Sampai jumpa kembali!", WIDTH);
                printLine('=', WIDTH);
                break;
            }
            default: {
                printBox("ERROR", WIDTH);
                printCenter("Pilihan tidak valid!", WIDTH);
                printLine('=', WIDTH);
                pauseScreen();
            }
        }
        
        if (pilihan >= 3 && pilihan <= 6) {
            handler.saveData();
        }
        
    } while (pilihan != 7);

    return 0;
}
