#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "book.h"

using json = nlohmann::json;
using namespace std;

class DataHandler {
protected:
    string filename;
    vector<Book> books;
public:
    DataHandler(string fname) : filename(fname) {}
    virtual void loadData() = 0;
    virtual void saveData() = 0;
    virtual vector<Book>& getBooks() { return books; }
    virtual void addBook(const Book& book) { books.push_back(book); }
};

class JsonHandler : public DataHandler {
public:
    JsonHandler(string filename);
    void loadData() override;
    void saveData() override;
};
