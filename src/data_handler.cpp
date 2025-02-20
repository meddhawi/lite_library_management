#include "data_handler.h"
#include <fstream>
#include <iostream>

JsonHandler::JsonHandler(string filename) : DataHandler(filename) {}

void JsonHandler::loadData() {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Tidak dapat membuka file");
        }

        json data = json::parse(file);
        books.clear();

        for (const auto& book : data["books"]) {
            books.emplace_back(
                book["id"],
                book["judul"],
                book["penulis"]
            );
            books.back().setTersedia(book["tersedia"]);
        }
    }
    catch (const exception& e) {
        cout << "Error loading data: " << e.what() << endl;
    }
}

void JsonHandler::saveData() {
    try {
        json data;
        for (const auto& book : books) {
            json bookJson;
            bookJson["id"] = book.getId();
            bookJson["judul"] = book.getJudul();
            bookJson["penulis"] = book.getPenulis();
            bookJson["tersedia"] = book.isTersedia();
            data["books"].push_back(bookJson);
        }

        std::ofstream file(filename);
        file << data.dump(4);
    }
    catch (const exception& e) {
        cout << "Error saving data: " << e.what() << endl;
    }
}
