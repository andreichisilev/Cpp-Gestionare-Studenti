// Red-Black-Trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string.h>
#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)
using namespace std;

ofstream ofs;
int g, choice, choiceCautare, choiceStergere, choiceParcurgere, choicePreordine, choiceInordine, choicePostordine;
struct Nod {
    int Numar_matricol;
    char nume[20];
    char prenume[20];
    int grupa;
    int an;
    Nod* tata;
    Nod* stanga;
    Nod* dreapta;
    int culoare;
};

typedef Nod* NodePtr;

class RedBlackTree {
private:

    NodePtr root;
    NodePtr TNULL;

    void stergArbore(NodePtr& nod)
    {
        if (nod != TNULL)
        {
            stergArbore(nod->stanga);
            stergArbore(nod->dreapta);
            delete nod;
            nod = TNULL;
        }
    }

    void initializeNULLNode(NodePtr nod, NodePtr tata) {
        nod->Numar_matricol = 0;
        nod->nume[19] = NULL;
        nod->prenume[19] = NULL;
        nod->grupa = 0;
        nod->an = 0;
        nod->tata = tata;
        nod->stanga = nullptr;
        nod->dreapta = nullptr;
        nod->culoare = 0;
    }

    //sync
    void syncHelper(NodePtr nod) {


        if (nod->stanga != NULL && nod->dreapta != NULL) {
            ofs << nod->Numar_matricol << ' ' << nod->nume << ' ' << nod->prenume << ' ' << nod->an << ' ' << nod->grupa << endl;
            //cout << "Numar_matricol: "<<nod->Numar_matricol <<"| Nume: "<<nod->nume<<"| Prenume: "<<nod->prenume<<"| An: "<<nod->an<<"| Grupa: "<<nod->grupa<<endl;
            syncHelper(nod->stanga);
            syncHelper(nod->dreapta);
        }
    }

    // Preordine
    void PreordineHelper(NodePtr nod) {
        if (nod != TNULL) {
            cout << "Numar matricol: " << nod->Numar_matricol << "| Nume: " << nod->nume << "| Prenume: " << nod->prenume << "| An: " << nod->an << "| Grupa: " << nod->grupa << endl;
            PreordineHelper(nod->stanga);
            PreordineHelper(nod->dreapta);
        }
    }

    // Inordine
    void InordineHelper(NodePtr nod) {
        if (nod != TNULL) {
            InordineHelper(nod->stanga);
            cout << "Numar matricol: " << nod->Numar_matricol << "| Nume: " << nod->nume << "| Prenume: " << nod->prenume << "| An: " << nod->an << "| Grupa: " << nod->grupa << endl;
            InordineHelper(nod->dreapta);
        }
    }

    // Postordine
    void PostordineHelper(NodePtr nod) {
        if (nod != TNULL) {
            PostordineHelper(nod->stanga);
            PostordineHelper(nod->dreapta);
            cout << "Numar matricol: " << nod->Numar_matricol << "| Nume: " << nod->nume << "| Prenume: " << nod->prenume << "| An: " << nod->an << "| Grupa: " << nod->grupa << endl;
        }
    }

    // Cautare dupa id
    NodePtr cautare_IDHelper(NodePtr nod, int Numar_matricol) {
        if (nod != NULL)
        {
            if (nod->Numar_matricol == Numar_matricol)
                return nod;
            if (Numar_matricol < nod->Numar_matricol)cautare_IDHelper(nod->stanga, Numar_matricol);
            else cautare_IDHelper(nod->dreapta, Numar_matricol);
        }
        else return NULL;
    }

    // Cautare dupa grupa
    void cautare_GrupaHelper(NodePtr nod, int grupa) {
        if (nod != NULL)
        {
            if (nod->grupa == grupa)
            {
                cout << endl << "\tID: " << nod->Numar_matricol << "| Nume: " << nod->nume << "| Prenume: " << nod->prenume << "| An: " << nod->an << "| Grupa: " << nod->grupa << endl;

                g = 1;
            }
            cautare_GrupaHelper(nod->stanga, grupa);
            cautare_GrupaHelper(nod->dreapta, grupa);
        }
        // else cout<<"nu am gasit";

    }

    // Cautare dupa nume
    NodePtr cautare_NumeHelper(NodePtr nod, char nume[20]) {
        if (nod != NULL)
        {
            if (strcmp(nod->nume, nume) == 0)
                return nod;
            if (strcmp(nume, nod->nume) < 0)cautare_NumeHelper(nod->stanga, nume);
            else cautare_NumeHelper(nod->dreapta, nume);
        }
        else return NULL;
    }

    // Pentru a echilibra arborele dupa stergere
    void StergereFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->culoare == 0) {
            if (x == x->tata->stanga) {
                s = x->tata->dreapta;
                if (s->culoare == 1) {
                    s->culoare = 0;
                    x->tata->culoare = 1;
                    rotatieStanga(x->tata);
                    s = x->tata->dreapta;
                }

                if (s->stanga->culoare == 0 && s->dreapta->culoare == 0) {
                    s->culoare = 1;
                    x = x->tata;
                }
                else {
                    if (s->dreapta->culoare == 0) {
                        s->stanga->culoare = 0;
                        s->culoare = 1;
                        rotatieDreapta(s);
                        s = x->tata->dreapta;
                    }

                    s->culoare = x->tata->culoare;
                    x->tata->culoare = 0;
                    s->dreapta->culoare = 0;
                    rotatieStanga(x->tata);
                    x = root;
                }
            }
            else {
                s = x->tata->stanga;
                if (s->culoare == 1) {
                    s->culoare = 0;
                    x->tata->culoare = 1;
                    rotatieDreapta(x->tata);
                    s = x->tata->stanga;
                }

                if (s->dreapta->culoare == 0) {
                    s->culoare = 1;
                    x = x->tata;
                }
                else {
                    if (s->stanga->culoare == 0) {
                        s->dreapta->culoare = 0;
                        s->culoare = 1;
                        rotatieStanga(s);
                        s = x->tata->stanga;
                    }

                    s->culoare = x->tata->culoare;
                    x->tata->culoare = 0;
                    s->stanga->culoare = 0;
                    rotatieDreapta(x->tata);
                    x = root;
                }
            }
        }
        x->culoare = 0;
    }

    void Translatie(NodePtr u, NodePtr v) {
        if (u->tata == nullptr) {
            root = v;
        }
        else if (u == u->tata->stanga) {
            u->tata->stanga = v;
        }
        else {
            u->tata->dreapta = v;
        }
        v->tata = u->tata;
    }

    //stergere dupa Numar_matricol
    void deleteNod_IDHelper(NodePtr nod, int cheie) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (nod != TNULL) {
            if (nod->Numar_matricol == cheie) {
                z = nod;
            }

            if (nod->Numar_matricol <= cheie) {
                nod = nod->dreapta;
            }
            else {
                nod = nod->stanga;
            }
        }

        if (z == TNULL) {
            cout << "Nu exista niciun student cu numarul matricol introdus." << endl;
            return;
        }

        y = z;
        int y_culoare_initiala = y->culoare;
        if (z->stanga == TNULL) {
            x = z->dreapta;
            Translatie(z, z->dreapta);
        }
        else if (z->dreapta == TNULL) {
            x = z->stanga;
            Translatie(z, z->stanga);
        }
        else {
            y = minim(z->dreapta);
            y_culoare_initiala = y->culoare;
            x = y->dreapta;
            if (y->tata == z) {
                x->tata = y;
            }
            else {
                Translatie(y, y->dreapta);
                y->dreapta = z->dreapta;
                y->dreapta->tata = y;
            }

            Translatie(z, y);
            y->stanga = z->stanga;
            y->stanga->tata = y;
            y->culoare = z->culoare;
        }
        delete z;
        if (y_culoare_initiala == 0) {
            StergereFix(x);
        }
    }

    //stergere dupa grupa
    void deleteNod_GrupaHelper(NodePtr nod, int cheie) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (nod != TNULL) {
            if (nod->grupa == cheie) {
                z = nod;
            }

            if (nod->grupa <= cheie) {
                nod = nod->dreapta;
            }
            else {
                nod = nod->stanga;
            }
        }

        if (z == TNULL) {
            cout << "Nu exista studenti in grupa cautata." << endl;
            return;
        }

        y = z;
        int y_culoare_initiala = y->culoare;
        if (z->stanga == TNULL) {
            x = z->dreapta;
            Translatie(z, z->dreapta);
        }
        else if (z->dreapta == TNULL) {
            x = z->stanga;
            Translatie(z, z->stanga);
        }
        else {
            y = minim(z->dreapta);
            y_culoare_initiala = y->culoare;
            x = y->dreapta;
            if (y->tata == z) {
                x->tata = y;
            }
            else {
                Translatie(y, y->dreapta);
                y->dreapta = z->dreapta;
                y->dreapta->tata = y;
            }

            Translatie(z, y);
            y->stanga = z->stanga;
            y->stanga->tata = y;
            y->culoare = z->culoare;
        }
        delete z;
        if (y_culoare_initiala == 0) {
            StergereFix(x);
        }
    }

    //stergere dupa nume
    void deleteNod_NumeHelper(NodePtr nod, char nume[20]) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (nod != TNULL) {
            if (strcmp(nod->nume, nume) == 0) {
                z = nod;
            }

            if (strcmp(nod->nume, nume) <= 0) {
                nod = nod->dreapta;
            }
            else {
                nod = nod->stanga;
            }
        }

        if (z == TNULL) {
            cout << "Nu exista niciun student cu acest nume." << endl;
            return;
        }

        y = z;
        int y_culoare_initiala = y->culoare;
        if (z->stanga == TNULL) {
            x = z->dreapta;
            Translatie(z, z->dreapta);
        }
        else if (z->dreapta == TNULL) {
            x = z->stanga;
            Translatie(z, z->stanga);
        }
        else {
            y = minim(z->dreapta);
            y_culoare_initiala = y->culoare;
            x = y->dreapta;
            if (y->tata == z) {
                x->tata = y;
            }
            else {
                Translatie(y, y->dreapta);
                y->dreapta = z->dreapta;
                y->dreapta->tata = y;
            }

            Translatie(z, y);
            y->stanga = z->stanga;
            y->stanga->tata = y;
            y->culoare = z->culoare;
        }
        delete z;
        if (y_culoare_initiala == 0) {
            StergereFix(x);
        }
    }


    // Pentru a echilibra arborele dupa inserare
    void InserareFix(NodePtr k) {
        NodePtr u;
        while (k->tata->culoare == 1) {
            if (k->tata == k->tata->tata->dreapta) {
                u = k->tata->tata->stanga;
                if (u->culoare == 1) {
                    u->culoare = 0;
                    k->tata->culoare = 0;
                    k->tata->tata->culoare = 1;
                    k = k->tata->tata;
                }
                else {
                    if (k == k->tata->stanga) {
                        k = k->tata;
                        rotatieDreapta(k);
                    }
                    k->tata->culoare = 0;
                    k->tata->tata->culoare = 1;
                    rotatieStanga(k->tata->tata);
                }
            }
            else {
                u = k->tata->tata->dreapta;

                if (u->culoare == 1) {
                    u->culoare = 0;
                    k->tata->culoare = 0;
                    k->tata->tata->culoare = 1;
                    k = k->tata->tata;
                }
                else {
                    if (k == k->tata->dreapta) {
                        k = k->tata;
                        rotatieStanga(k);
                    }
                    k->tata->culoare = 0;
                    k->tata->tata->culoare = 1;
                    rotatieDreapta(k->tata->tata);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->culoare = 0;
    }

    //afisare
    void afisareHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->culoare ? "ROSU" : "NEGRU";
            cout << root->Numar_matricol << "(" << sColor << ")" << endl;
            afisareHelper(root->stanga, indent, false);
            afisareHelper(root->dreapta, indent, true);
        }
    }

public:


    //initializare arbore
    RedBlackTree() {
        TNULL = new Nod;
        TNULL->culoare = 0;
        TNULL->stanga = nullptr;
        TNULL->dreapta = nullptr;
        root = TNULL;
    }


    ~RedBlackTree() {
        stergArbore();
    }

    void stergArbore() {
        stergArbore(this->root);
    }

    //preordine apelare
    void preordine() {
        PreordineHelper(this->root);
    }

    //inordine apelare
    void inordine() {
        InordineHelper(this->root);
    }

    //postordine apelare
    void postordine() {
        PostordineHelper(this->root);
    }

    //sync apelare
    void sync() {
        ofs.open("Studenti.txt");
        syncHelper(this->root);
        ofs.close();
    }

    //cautare apelare Numar_matricol
    NodePtr cautare_ID(int k) {
        return cautare_IDHelper(this->root, k);
    }


    //cautare apelare grupa
    void cautare_Grupa(int k) {
        g = 0;
        cautare_GrupaHelper(this->root, k);
        if (g == 0)cout << "Nu exista studenti in grupa introdusa";
    }


    //cautare apelare nume
    NodePtr cautare_Nume(char nume[20]) {
        return cautare_NumeHelper(this->root, nume);
    }


    //minim
    NodePtr minim(NodePtr nod) {
        while (nod->stanga != TNULL) {
            nod = nod->stanga;
        }
        return nod;
    }

    //maxim
    NodePtr maxim(NodePtr nod) {
        while (nod->dreapta != TNULL) {
            nod = nod->dreapta;
        }
        return nod;
    }

    //succesor
    NodePtr succesor(NodePtr x) {
        if (x->dreapta != TNULL) {
            return minim(x->dreapta);
        }

        NodePtr y = x->tata;
        while (y != TNULL && x == y->dreapta) {
            x = y;
            y = y->tata;
        }
        return y;
    }

    //predecesor
    NodePtr predecesor(NodePtr x) {
        if (x->stanga != TNULL) {
            return maxim(x->stanga);
        }

        NodePtr y = x->tata;
        while (y != TNULL && x == y->stanga) {
            x = y;
            y = y->tata;
        }

        return y;
    }

    //rotatie stanga
    void rotatieStanga(NodePtr x) {
        NodePtr y = x->dreapta;
        x->dreapta = y->stanga;
        if (y->stanga != TNULL) {
            y->stanga->tata = x;
        }
        y->tata = x->tata;
        if (x->tata == nullptr) {
            this->root = y;
        }
        else if (x == x->tata->stanga) {
            x->tata->stanga = y;
        }
        else {
            x->tata->dreapta = y;
        }
        y->stanga = x;
        x->tata = y;
    }

    //rotatie dreapta
    void rotatieDreapta(NodePtr x) {
        NodePtr y = x->stanga;
        x->stanga = y->dreapta;
        if (y->dreapta != TNULL) {
            y->dreapta->tata = x;
        }
        y->tata = x->tata;
        if (x->tata == nullptr) {
            this->root = y;
        }
        else if (x == x->tata->dreapta) {
            x->tata->dreapta = y;
        }
        else {
            x->tata->stanga = y;
        }
        y->dreapta = x;
        x->tata = y;
    }

    // Inserare nod dupa Numar_matricol
    void inserare_ID(int cheie, char nume[20], char prenume[20], int an, int grupa) {
        NodePtr nod = new Nod;
        nod->tata = nullptr;
        nod->Numar_matricol = cheie;
        strcpy(nod->nume, nume);
        strcpy(nod->prenume, prenume);
        nod->an = an;
        nod->grupa = grupa;
        nod->stanga = TNULL;
        nod->dreapta = TNULL;
        nod->culoare = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (nod->Numar_matricol < x->Numar_matricol) {
                x = x->stanga;
            }
            else {
                x = x->dreapta;
            }
        }

        nod->tata = y;
        if (y == nullptr) {
            root = nod;
        }
        else if (nod->Numar_matricol < y->Numar_matricol) {
            y->stanga = nod;
        }
        else {
            y->dreapta = nod;
        }

        if (nod->tata == nullptr) {
            nod->culoare = 0;
            return;
        }

        if (nod->tata->tata == nullptr) {
            return;
        }

        InserareFix(nod);
    }

    // Inserare nod dupa nume
    void inserare_nume(int cheie, char nume[20], char prenume[20], int an, int grupa) {
        NodePtr nod = new Nod;
        nod->tata = nullptr;
        nod->Numar_matricol = cheie;
        strcpy(nod->nume, nume);
        strcpy(nod->prenume, prenume);
        nod->an = an;
        nod->grupa = grupa;
        nod->stanga = TNULL;
        nod->dreapta = TNULL;
        nod->culoare = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (strcmp(nod->nume, x->nume) < 0) {
                x = x->stanga;
            }
            else {
                x = x->dreapta;
            }
        }

        nod->tata = y;
        if (y == nullptr) {
            root = nod;
        }
        else if (strcmp(nod->nume, y->nume) < 0) {
            y->stanga = nod;
        }
        else {
            y->dreapta = nod;
        }

        if (nod->tata == nullptr) {
            nod->culoare = 0;
            return;
        }

        if (nod->tata->tata == nullptr) {
            return;
        }

        InserareFix(nod);
    }

    // Inserare nod dupa an
    void inserare_an(int cheie, char nume[20], char prenume[20], int an, int grupa) {
        NodePtr nod = new Nod;
        nod->tata = nullptr;
        nod->Numar_matricol = cheie;
        strcpy(nod->nume, nume);
        strcpy(nod->prenume, prenume);
        nod->an = an;
        nod->grupa = grupa;
        nod->stanga = TNULL;
        nod->dreapta = TNULL;
        nod->culoare = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (nod->an < x->an) {
                x = x->stanga;
            }
            else {
                x = x->dreapta;
            }
        }

        nod->tata = y;
        if (y == nullptr) {
            root = nod;
        }
        else if (nod->an < y->an) {
            y->stanga = nod;
        }
        else {
            y->dreapta = nod;
        }

        if (nod->tata == nullptr) {
            nod->culoare = 0;
            return;
        }

        if (nod->tata->tata == nullptr) {
            return;
        }

        InserareFix(nod);
    }

    // Inserare nod dupa grupa
    void inserare_grupa(int cheie, char nume[20], char prenume[20], int an, int grupa) {
        NodePtr nod = new Nod;
        nod->tata = nullptr;
        nod->Numar_matricol = cheie;
        strcpy(nod->nume, nume);
        strcpy(nod->prenume, prenume);
        nod->an = an;
        nod->grupa = grupa;
        nod->stanga = TNULL;
        nod->dreapta = TNULL;
        nod->culoare = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (nod->grupa < x->grupa) {
                x = x->stanga;
            }
            else {
                x = x->dreapta;
            }
        }

        nod->tata = y;
        if (y == nullptr) {
            root = nod;
        }
        else if (nod->grupa < y->grupa) {
            y->stanga = nod;
        }
        else {
            y->dreapta = nod;
        }

        if (nod->tata == nullptr) {
            nod->culoare = 0;
            return;
        }

        if (nod->tata->tata == nullptr) {
            return;
        }

        InserareFix(nod);
    }

    NodePtr getRoot() {
        return this->root;
    }

    void delete_NodID(int Numar_matricol) {
        deleteNod_IDHelper(this->root, Numar_matricol);
    }

    void delete_NodGrupa(int grupa) {
        deleteNod_GrupaHelper(this->root, grupa);
    }

    void delete_NodNume(char nume[20]) {
        deleteNod_NumeHelper(this->root, nume);
    }

    void afisare() {
        if (root) {
            afisareHelper(this->root, "", true);
        }
    }
};
//end clasa
RedBlackTree rbt_ID, rbt_nume, rbt_an, rbt_grupa;


void PrintMenu()
{
    cout << endl << "\tGESTIONARE STUDENTI" << endl << endl;
    cout << "\t\t [1] INSERARE " << endl;
    cout << "\t\t [2] STERGERE " << endl;
    cout << "\t\t [3] AFISARE " << endl;
    cout << "\t\t [4] PARCURGERE " << endl;
    cout << "\t\t [5] CAUTARE " << endl;
    cout << "\t\t [6] IESIRE" << endl;
}


void introducereDate() {
    int Numar_matricol, grupa, an;
    char nume[20], prenume[20];
    cout << endl << "Numar matricol: "; cin >> Numar_matricol;
    cout << "Nume: "; cin >> nume;
    cout << "Prenume: "; cin >> prenume;
    cout << "An: "; cin >> an;
    cout << "Grupa: "; cin >> grupa;

    rbt_ID.inserare_ID(Numar_matricol, nume, prenume, an, grupa);
    rbt_grupa.inserare_grupa(Numar_matricol, nume, prenume, an, grupa);
    rbt_an.inserare_an(Numar_matricol, nume, prenume, an, grupa);
    rbt_nume.inserare_nume(Numar_matricol, nume, prenume, an, grupa);
    rbt_ID.sync();
}

void introducereDateFisier()
{
    int Numar_matricol, grupa, an;
    char nume[20], prenume[20];

    ifstream in;
    in.open("Studenti.txt");

    if (in.fail()) {
        cout << "Fisierul nu a putut fi deschis" << endl;
        exit(1);
    }

    while (true) {
        in >> Numar_matricol >> nume >> prenume >> an >> grupa;
        if (in.eof()) break;
        rbt_ID.inserare_ID(Numar_matricol, nume, prenume, an, grupa);
        rbt_grupa.inserare_grupa(Numar_matricol, nume, prenume, an, grupa);
        rbt_an.inserare_an(Numar_matricol, nume, prenume, an, grupa);
        rbt_nume.inserare_nume(Numar_matricol, nume, prenume, an, grupa);

    }
    in.close();
}

void GetChoice()
{
    cout << endl << "Alege una din optiunile de mai sus: ";
    cin >> choice;
    switch (choice)//switch meniu principal
    {
    case 1: //Pentru INSERARE
    {
        int again;
        do
        {
            cout << "Introduceti datele pe care doriti sa le inserati: ";
            introducereDate();
            cout << "Doriti sa inserati din nou?[introduceti 0 daca nu]: ";
            cin >> again;
            cout << endl;
        } while (again != 0);
        break; }



    case 2: //Pentru STERGERE
    {
        cout << "\tDupa ce criteriu realizati stergerea?: " << endl;
        cout << "\t\t [1] Numar matricol " << endl;
        cout << "\t\t [2] Nume " << endl;
        cin >> choiceStergere;
        switch (choiceStergere)
        {
        case 1://Stergere dupa Numar matricol
        {int again2;
        do {
            cout << "Introduceti numarul matricol al studentului pe care doriti sa il stergeti: ";
            int element;
            cin >> element;
            rbt_ID.delete_NodID(element);
            rbt_ID.sync();
            rbt_ID.~RedBlackTree();
            rbt_grupa.~RedBlackTree();
            rbt_nume.~RedBlackTree();
            introducereDateFisier();
            cout << "Doriti sa stergeti din nou?[introduceti 0 daca nu]: ";
            cin >> again2;
            cout << endl;
        } while (again2 != 0);

        break;
        }
        case 2://Stergere dupa nume
        {int again2;
        do {
            cout << "Introduceti numele studentului pe care doriti sa il stergeti: ";
            char nume[20];
            cin >> nume;
            rbt_nume.delete_NodNume(nume);
            rbt_nume.sync();
            rbt_ID.~RedBlackTree();
            rbt_grupa.~RedBlackTree();
            rbt_nume.~RedBlackTree();
            introducereDateFisier();
            cout << "Doriti sa stergeti din nou?[introduceti 0 daca nu]: ";
            cin >> again2;
            cout << endl;
        } while (again2 != 0);

        break; }

        default: cout << "Valoarea introdusa este invalida\n";
        }

        break;
    }



    case 3: //Pentru AFISARE
    {
        cout << endl << "Arborele este: " << endl;
        rbt_grupa.afisare();
        break;
    }



    case 4: //Pentru PARCURGERE
    {
        cout << "\tCe parcurgere doriti sa realizati: " << endl;
        cout << "\t\t [1] Preordine " << endl;
        cout << "\t\t [2] Inordine " << endl;
        cout << "\t\t [3] Postordine " << endl;
        cin >> choiceParcurgere;
        switch (choiceParcurgere) {

        case 1: //Pentru PREORDINE
        {
            cout << "\tDupa ce criteriu realizati parcurgerea?: " << endl;
            cout << "\t\t [1] Numar matricol " << endl;
            cout << "\t\t [2] Nume " << endl;
            cout << "\t\t [3] Grupa " << endl;
            cin >> choicePreordine;
            switch (choicePreordine) {
            case 1:
                rbt_ID.preordine();
                break;

            case 2:
                rbt_nume.preordine();
                break;

            case 3:
                rbt_grupa.preordine();
                break;

            default: cout << "Valoarea introdusa este invalida\n";
            }
            break; }

        case 2: //Pentru INORDINE
        {
            cout << "\tDupa ce criteriu realizati parcurgerea?: " << endl;
            cout << "\t\t [1] Numar matricol " << endl;
            cout << "\t\t [2] Nume " << endl;
            cout << "\t\t [3] Grupa " << endl;
            cin >> choiceInordine;
            switch (choiceInordine) {
            case 1:
                rbt_ID.inordine();
                break;

            case 2:
                rbt_nume.inordine();
                break;

            case 3:
                rbt_grupa.inordine();
                break;

            default: cout << "Valoarea introdusa este invalida\n";
            }
            break; }

        case 3: //Pentru POSTORDINE
        {
            cout << "\tDupa ce criteriu realizati parcurgerea?: " << endl;
            cout << "\t\t [1] Numar matricol " << endl;
            cout << "\t\t [2] Nume " << endl;
            cout << "\t\t [3] Grupa " << endl;
            cin >> choicePostordine;
            switch (choicePostordine) {
            case 1:
                rbt_ID.postordine();
                break;

            case 2:
                rbt_nume.postordine();
                break;

            case 3:
                rbt_grupa.postordine();
                break;

            default: cout << "Valoarea introdusa este invalida\n";
            }
            break; }
        default: cout << "Valoarea introdusa este invalida\n";
        }
        break; }



    case 5: //Pentru CAUTARE
    {
        int Numar_matricol, grupa;
        char nume[20];
        cout << "\tDupa ce criteriu realizati cautarea?: " << endl;
        cout << "\t\t [1] Numar matricol " << endl;
        cout << "\t\t [2] Nume " << endl;
        cout << "\t\t [3] Grupa " << endl;
        cin >> choiceCautare;
        switch (choiceCautare) {
            NodePtr nodul;
        case 1: //Cautare dupa Numar matricol
        {cout << "Introduceti numarul matricol al studentului cautat: ";
        cin >> Numar_matricol;
        nodul = rbt_ID.cautare_ID(Numar_matricol);
        if (nodul == NULL)cout << "Studentul nu exista!" << endl;
        else
            cout << "Studentul cautat este: " << endl << "\tNumar Matricol: " << nodul->Numar_matricol << "| Nume: " << nodul->nume << "| Prenume: " << nodul->prenume << "| An: " << nodul->an << "| Grupa: " << nodul->grupa << endl;

        break;
        }


        case 2: //Cautare dupa Nume
        {cout << "Introduceti numele studentului pe care doriti sa il cautati: ";
        cin >> nume;
        nodul = rbt_nume.cautare_Nume(nume);
        if (nodul == NULL)cout << "Studentul nu exista!" << endl;
        else
            cout << "Studentul cautat este: " << endl << "\tNumar matricol: " << nodul->Numar_matricol << "| Nume: " << nodul->nume << "| Prenume: " << nodul->prenume << "| An: " << nodul->an << "| Grupa: " << nodul->grupa << endl;
        break;
        }


        case 3: //Cautare dupa Grupa
        {cout << "Introduceti grupa studentilor pe care ii cautati: ";
        cin >> grupa;
        rbt_grupa.cautare_Grupa(grupa);

        break;
        }


        default: cout << "Valoarea introdusa este invalida\n";
        }
        break; }



    case 6: //Iesire
    {
        break;
    }



    default: cout << "Valoarea introdusa este invalida\n";
    }
}


int main() {
    introducereDateFisier();
    do
    {
        PrintMenu();
        GetChoice();
    } while (choice != 6);
    return 0;
}