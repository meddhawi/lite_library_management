#include <iostream>
#include <iomanip>
#include "book.h"
#include "data_handler.h"

void tampilkanMenu() {
    cout << "\nSistem Manajemen Perpustakaan\n";
    cout << "1. Tampilkan Daftar Buku\n";
    cout << "2. Cari Buku\n";
    cout << "3. Pinjam Buku\n";
    cout << "4. Kembalikan Buku\n";
    cout << "5. Tambah Buku Baru\n";
    cout << "6. Update Status Buku\n";
    cout << "7. Keluar\n";
    cout << "Pilihan Anda: ";
}

// Fungsi untuk menampilkan detail buku
void tampilkanBuku(const Book& book) {
    cout << "ID: " << book.getId() << endl
         << "Judul: " << book.getJudul() << endl
         << "Penulis: " << book.getPenulis() << endl
         << "Status: " << (book.isTersedia() ? "Tersedia" : "Dipinjam") << endl
         << "------------------------" << endl;
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
        tampilkanBuku(book);
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
            tampilkanBuku(book);
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
        
        switch(pilihan) {
            case 1:
                tampilkanDaftarBuku(handler.getBooks());
                break;
            case 2:
                cariBuku(handler.getBooks());
                break;
            case 3:
                pinjamBuku(handler.getBooks());
                break;
            case 4:
                kembalikanBuku(handler.getBooks());
                break;
            case 5:
                tambahBuku(handler.getBooks());
                break;
            case 6:
                updateStatusBuku(handler.getBooks());
                break;
            case 7:
                cout << "Terima kasih telah menggunakan sistem perpustakaan.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
        
        // Simpan perubahan ke file setiap kali ada modifikasi data
        if (pilihan >= 3 && pilihan <= 6) {
            handler.saveData();
        }
        
    } while (pilihan != 7);

    return 0;
}
