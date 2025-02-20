#include "book.h"

Book::Book(string id, string judul, string penulis) {
    this->id = id;
    this->judul = judul;
    this->penulis = penulis;
    this->tersedia = true;
}
