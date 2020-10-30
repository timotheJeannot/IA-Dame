#ifndef DEF_CASE
#define DEF_CASE


class Case{
    int colonne;
    int ligne;

public :

    Case(int x, int y);
    Case(Case &ca);
    Case();
    ~Case();
    int getColonne();
    int getLigne();
    void setColonne(int x);
    void setLigne(int y);
};

#endif