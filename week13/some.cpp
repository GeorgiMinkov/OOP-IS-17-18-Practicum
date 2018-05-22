// ЗАБЕЛЕЖКА = РЕШЕНИЕТО НЕ Е ДОВЪРШЕНО

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Song;

// ABSTRACT
    class Melody {

    public:
        Melody() {
            this->name = "default";
        }

        Melody(const string& name) {
            this->name = name;
        }

        Melody(const Melody& src) {
            this->name = src.name;
        }

        string getName() const {
            return this->name;
        }

        virtual string getType() const = 0;

        Melody& operator=(const Melody& src) {
            if (this != &src) {
                this->name = src.name;
            }

            return *this;
        }

        friend ostream&operator<<(ostream& out, const Melody& src) {
            src.Serialize(out);
            return out;
        }

        friend istream&operator>>(istream& in, Melody& src) {
            src.Deserialize(in);
            return in;
        }

    //    // FACTORY
    //
    //    static Melody* factory(string type) {
    //        if (type == "song") {
    //            return new Song("default", 0.0f, "author");
    //        } else {
    //            return new Mix();
    //        }
    //    }

    protected:
        virtual void Serialize(ostream& out) const {
            out << this->name;
        }

        virtual void Deserialize(istream& stream)
        {
            getline(stream, this->name);
        }

    private:
        string name;
    };

// CONCRETE
class Song : public Melody {
    float duration;
    string author;

public:
    Song() : Melody() {
        this->duration = 0.0f;
        this->author = "";
    }

    Song(const string& name, float duration, const string& author) : Melody(name) {
        this->duration = duration;
        this->author = author;
    }

    Song(const Song& src) : Melody(src) {
        this->author = src.author;
        this->duration = src.duration;
    }

    Song& operator=(const Song& src) {
        if (this != &src) {
            Melody::operator=(src);
            this->duration = duration;
            this->author = author;
        }

        return *this;
    }

    virtual string getType() const {
        return "Song";
    }

protected:
    virtual void Serialize(ostream& out) const {
        Melody::Serialize(out);
        out << endl << this->author << endl;
        out << this->duration;
    }

    virtual void Deserialize(istream& in) {
        Melody::Deserialize(in);
        in >> this->duration;
        getline(in, this->author);
    }
};

class Mix : public Melody {
    vector<Melody*> tree;
    string frontCover;
public:
    Mix() : Melody() {
        tree = vector<Melody*>();
        frontCover = "";
    }

    Mix(const string& name, const vector<Melody*>& tree, const string& frontCover) :
            Melody(name) {
        this->tree = tree;
        this->frontCover = frontCover;
    }

    Mix(const Mix& src) : Melody(src) {
        this->tree = src.tree;
    }

    Mix& operator=(const Mix& src) {
        if (this != &src) {
            Melody::operator=(src);
            this->tree = src.tree;
            this->frontCover = src.frontCover;
        }

        return *this;
    }

    ~Mix() {
        for (size_t index = 0; index < this->tree.size(); ++index) {
            delete this->tree[index];
        }
    }
    void playlist() const {
        for (size_t index = 0; index < tree.size(); ++index) {
            cout << index << ": " << *tree[index] << endl;
        }
    }

    virtual string getType() const {
        return "Mix";
    }

    void addNewMelody(const string& type) {
        // Melody* newMelody = Melody::factory(type);

        Melody* newMelody = nullptr;

        if (type == "song") {
            newMelody = new Song();
        } else {
            newMelody = new Mix();
        }

        cin >> *newMelody;

        this->tree.push_back(newMelody);
    }

    void Deserialize(istream& in) {
        Melody::Deserialize(in);

        cout << "FrontCover: ";
        in >> this->frontCover;

        cout << "Elements of Vectors: ";
        int number = 0;
        in >> number;

        this->tree.resize(number);

        while (number--) {
            cout << "Song | Mix";

            string choose = "";

            in >> choose;

            if (choose == "Song") {
                Melody *newElement = new Song();
                in >> *newElement;

                this->tree.push_back(newElement);
            } else {
                Melody *newElement = new Mix();
                in >> *newElement;

                this->tree.push_back(newElement);

            }
        }
    }

protected:
    virtual void Serialize(ostream& out) const {
        Melody::Serialize(out);

        out << endl << "Front Cover: " << this->frontCover << endl;

        for (size_t index = 0; index < this->tree.size(); ++index) {
            out << *(this->tree.at(index)) << endl;
        }
    }
};

int main() {
    Melody *mel = new Song("За тва съм роден", 3, "Боро Първи");

    vector<Melody*> tree;
    tree.push_back(mel);
    tree.push_back(mel);

    Melody *mix = new Mix("ХАП", tree, "Обложка");

    cout << *mix << endl;


    // mix->Deserialize(cin);
    // mix->addNewMelody("song");
    cout << "__________\n";
    cout << *mix << endl;

    Melody *megaMix = new Mix();

    cin >> *megaMix;

    delete mel;
    return 0;
}
