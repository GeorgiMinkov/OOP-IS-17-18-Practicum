class Melody {

public:
    Melody();

    Melody(const string& name) ;

    Melody(const Melody& src);

    string getName() const;

    virtual string getType() const = 0;

    Melody& operator=(const Melody& src) ;

    friend ostream&operator<<(ostream& out, const Melody& src) ;

    void Deserialize(istream& stream);
protected:
    virtual void Serialize(ostream& out) const;
private:
    string name;
};

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

    void Deserialize(istream& in);

protected:
    virtual void Serialize(ostream& out) const ;
};

class Mix : public Melody {
    vector<Melody*> tree;
    string frontCover;
public:
    Mix();

    Mix(const string& name, const vector<Melody*>& tree, const string& frontCover) ;

    Mix(const Mix& src) ;

    Mix& operator=(const Mix& src);

    ~Mix() ;
    void playlist() const ;

    friend ostream& operator<<(ostream& out, const Mix& src);

    virtual string getType() const {
        return "Mix";
    }

    void addNewMelody(const string& type);

    void Deserialize(istream& in);

protected:
    virtual void Serialize(ostream& out) const ;
};
