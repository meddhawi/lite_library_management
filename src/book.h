#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string id;
    string judul;
    string penulis;
    bool tersedia;

public:
    // Constructor
    Book(string id, string judul, string penulis);
    
    // Getters
    string getId() const { return id; }
    string getJudul() const { return judul; }
    string getPenulis() const { return penulis; }
    bool isTersedia() const { return tersedia; }
    
    // Setters
    void setJudul(string judul) { this->judul = judul; }
    void setPenulis(string penulis) { this->penulis = penulis; }
    void setTersedia(bool status) { this->tersedia = status; }
};

#endif
