#include <iostream>
#include <cstring>

using namespace std;

class Exam {
    char* classification;
    int score;

    void copyElement(const char* classification, const int& score);
    void destroy();
public:
    Exam();
    Exam(const char* classification, const int& score);
    Exam(const Exam& src);
    ~Exam();

    Exam& operator=(const Exam& src);

    Exam operator+(const int& bonus);
    Exam operator*(const int& coef);

    Exam& operator+=(const int& bonus);

    const int getScore() const;
};

void Exam::copyElement(const char* classification, const int& score) {
    this->destroy();

    this->classification = new char[strlen(classification) + 1];
    strcpy(this->classification, classification);
    cout << "this -> " << this->classification << " | " << classification << endl;
    cout << "this -> " << this->score << " | " << score << endl;
    this->score = score;
}

void Exam::destroy() {
    if (this->classification != NULL) {
        delete[] this->classification;
    }
}

Exam::Exam() {
    this->classification = NULL;
    this->score = 0;
}

Exam::Exam(const char* classification, const int& score) {
    this->copyElement(classification, score);
}

Exam::Exam(const Exam& src) {
    this->classification = new char[strlen(src.classification) + 1];
    strcpy(this->classification, classification);
    this->score = src.score;
}

Exam::~Exam() {
    this->destroy();
}

Exam& Exam::operator=(const Exam& src) {
    if (this != &src) {
        this->destroy();
        this->copyElement(src.classification, src.score);
    }

    return *this;
}


Exam Exam::operator*(const int& coef) {
    return Exam(this->classification, (this->score * coef));
}

Exam& Exam::operator+=(const int& bonus) {
    this->score += bonus;

    return *this;
}

const int Exam::getScore() const {
    return this->score;
}

int main()
{
    Exam test("someTest", 10);
    cout << "Score: " << test.getScore() << endl;

    test += 10;
    cout << "Score: " << test.getScore() << endl;

   // test = test * 10;
    cout << "New score from operator+" << test.getScore() << endl;
    return 0;
}
