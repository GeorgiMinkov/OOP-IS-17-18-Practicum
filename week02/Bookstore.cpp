#include <iostream>
#include <fstream>
#include <cstring>

const short ISBN_NUMBER_OF_DIGITS = 14;
const short CHAR_BUFFER = 64;
const short MAX_NUMBER_OF_BOOKS = 128;

struct Book {
    char bookName[CHAR_BUFFER];
    char authorName[CHAR_BUFFER];
    char ISBN[ISBN_NUMBER_OF_DIGITS];
    char genre[CHAR_BUFFER];
    float price;
};

struct Bookstore {
    Book books[MAX_NUMBER_OF_BOOKS];
    short currentNumberOfBooks;
};

void readBook(std::ifstream &fileInput, Book &book) {
    fileInput.getline(book.bookName, CHAR_BUFFER);
    fileInput.getline(book.authorName, CHAR_BUFFER);
    fileInput.getline(book.ISBN, CHAR_BUFFER);
    fileInput.getline(book.genre, CHAR_BUFFER);
    fileInput >> book.price;
    fileInput.get();
    fileInput.get();
}

void initializeBookstore(Bookstore &store, const char *fileName) {
    std::ifstream fileInput;

    fileInput.open(fileName);

    if (!fileInput.is_open()) {
        std::cout << "Cannot open file to read\n";
        return ;
    }

    fileInput >> store.currentNumberOfBooks; // will read number of books
    fileInput.get(); // to escape new line symbol

    for (int i = 0; i < store.currentNumberOfBooks; ++i) {
        readBook(fileInput, store.books[i]);
    }

    fileInput.close();
}

// next functions are only to show you different control on data
//void printBook(const Book &book) {
//    std::cout << book.bookName << std::endl;
//    std::cout << book.authorName << std::endl;
//    std::cout << book.ISBN << std::endl;
//    std::cout << book.genre << std::endl;
//    std::cout << book.price << std::endl;
//}

// for education purpose
//void printBook(std::ofstream &fileOutput, const Book &book) { // function overload
//    fileOutput << book.bookName << std::endl;
//    fileOutput << book.authorName << std::endl;
//    fileOutput << book.ISBN << std::endl;
//    fileOutput << book.genre << std::endl;
//    fileOutput << book.price << std::endl;
//    fileOutput << std::endl;
//}

void printBook(std::ostream &out, const Book &book) { // function with ostream - upper class for ofstream and can be use for cout
    out << book.bookName << std::endl;
    out << book.authorName << std::endl;
    out << book.ISBN << std::endl;
    out << book.genre << std::endl;
    out << book.price << std::endl;
    out << std::endl;
}

void printBooks(const Bookstore &store) {
    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        printBook(std::cout, store.books[index]);
        // printBook(store.books[index]);
        std::cout << std::endl;
    }
}

bool hasBookWithISBN(const Bookstore &store, const char *isbn) {
    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (!strcmp(store.books[index].ISBN, isbn)) {
            return true;
        }
    }

    return false;
}

void getAllBooksByAuthorName(const Bookstore &store, const char *authorName, const char *outputFileName) {
    std::ofstream fileOutput(outputFileName);

    if (!fileOutput.is_open()) {
        std::cout << "Cannot open file\n";
        return;
    }

    std::size_t numberOfBooks = 0;
// това е вариант ако знаем, че няма да има повече от 9 книги в един резултат, защо ще имаме проблем с това решение ако имаме повече книги?
//    std::size_t numberOfBooks = 0;
//
//    fileOutput << numberOfBooks << std::endl;
//
//    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
//        if (!strcmp(store.books[index].authorName, authorName)) {
//            ++numberOfBooks;
//            printBook(fileOutput, store.books[index]);
//        }
//    }
//
//    fileOutput.seekp(std::ios::beg);
//    fileOutput << numberOfBooks << std::endl;

    // иначе най - лесното (не е ефективно) първо намираме броя срещания, а след това попълваме тези срещания

    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (!strcmp(store.books[index].authorName, authorName)) {
            ++numberOfBooks;
        }
    }

    fileOutput << numberOfBooks << std::endl;

    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (!strcmp(store.books[index].authorName, authorName)) {
            printBook(fileOutput, store.books[index]);
        }
    }

    fileOutput.seekp(std::ios::beg);
    fileOutput << numberOfBooks << std::endl;

    fileOutput.close();
}

void getAllBooksByGenre(const Bookstore &store, const char *genre, const char *outputFileName) {
    std::ofstream fileOutput(outputFileName);

    if (!fileOutput.is_open()) {
        std::cout << "Cannot open file\n";
        return;
    }

    std::size_t numberOfBooks = 0;


    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (!strcmp(store.books[index].genre, genre)) {
            ++numberOfBooks;
        }
    }

    fileOutput << numberOfBooks << std::endl;

    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (!strcmp(store.books[index].genre, genre)) {
            printBook(fileOutput, store.books[index]);
        }
    }

    fileOutput.close();
}


void getAllBooksCheaperThan(const Bookstore &store, float price, const char *outputFileName) {
    std::ofstream fileOutput(outputFileName);

    if (!fileOutput.is_open()) {
        std::cout << "Cannot open file\n";
        return;
    }

    std::size_t numberOfBooks = 0;


    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (store.books[index].price < price) {
            ++numberOfBooks;
        }
    }

    fileOutput << numberOfBooks << std::endl;

    for (std::size_t index = 0; index < store.currentNumberOfBooks; ++index) {
        if (store.books[index].price < price) {
            printBook(fileOutput, store.books[index]);
        }
    }

    fileOutput.close();
}

int main() {

    Bookstore store;

    initializeBookstore(store, "/home/georgiminkov/CLionProjects/OOP/Structures/file.txt");

    printBooks(store);


    getAllBooksByAuthorName(store, "Ivan Vazov", "byAuthor.txt");

    getAllBooksByGenre(store, "Fantasy Fiction", "byGenre.txt");

    getAllBooksCheaperThan(store, 20, "byPrice.txt");

    return 0;
}