#include <iostream>
#include <cstring>

using namespace std;

class Person {
private:

    char* name;
    int age;

public:
    Person();
    Person(const char*, int);
    Person(const Person&);
    Person& operator=(const Person&);
    ~Person();

    const char* getName() const;
    int getAge() const;

    friend ostream &operator<<(ostream &, const Person &);
};

Person::Person() {
    this->name = nullptr;
    this->age = 0;
}

Person::Person(const char * name, int age) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->age = age;
}

Person::Person(const Person &other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);

    this->age = other.age;
}

Person& Person::operator=(const Person &other) {
    if (this != &other)
    {
        delete [] this->name;

        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        this->age = other.age;
    }
    return * this;
}

Person::~Person() {
    delete [] this->name;
}

const char* Person::getName() const {
    return this->name;
}

int Person::getAge() const {
    return this->age;
}

ostream &operator<<(std::ostream &output, const Person& person)
{
    output << "Name: " << person.name << endl;
    output << "Age:" << person.age << endl;
    return output;
}


class Student: public Person{
private:
    char* university;
    int term;

public:
    Student();
    Student(const char*, int, const char*, int);
    Student(const Student&);
    Student& operator=(const Student&);
    ~Student();

    const char* getUniversity() const;
    int getTerm() const;

    friend ostream &operator<<(ostream &, const Student &);
};

Student::Student(): Person() {
    this->university = nullptr;
    this->term = 1;
}

Student::Student(const char * name, int age,
                 const char* university, int term) :
        Person(name, age) {
    this->university = new char[strlen(university) + 1];
    strcpy(this->university, university);

    this->term = term;
}

Student::Student(const Student &other) : Person(other) {
    this->university = new char[strlen(other.university) + 1];
    strcpy(this->university, other.university);

    this->term = other.term;
}

Student& Student::operator=(const Student &other) {
    if (this != &other)
    {
        Person::operator=(other);
        delete [] this->university;

        this->university = new char[strlen(other.university) + 1];
        strcpy(this->university, other.university);

        this->term = other.term;
    }
    return *this;
}

Student::~Student() {
    delete [] this->university;
}

const char* Student::getUniversity() const {
    return this->university;
}

int Student::getTerm() const {
    return this->term;
}

ostream &operator<<(std::ostream &output, const Student& student)
{
    output << "Name: " << student.getName() << endl;
    output << "Age:" << student.getAge() << endl;
    output << "University: " << student.university << endl;
    output << "Term: " << student.term << endl;
    return output;
}


int main()
{
    Person one;
    Person two("Krisi", 22);
    Person three(two);
    Person four = three;

    cout << four;

    Student first_term;
    Student second_term("Panda", 21, "PandaUniversity", 2);
    cout << second_term;
    Student third_term(second_term);
    Student forth_term = third_term;

    cout << forth_term;

}