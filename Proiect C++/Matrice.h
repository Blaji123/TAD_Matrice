#pragma once

typedef int TElem;


#define NULL_TELEMENT 0
#define MAX 10

class Triplet{
public:
    int linie;
    int coloana;
    TElem valoare;

    Triplet() = default;
    Triplet(int linie, int coloana, TElem valoare) : linie{linie}, coloana{coloana}, valoare{valoare}{}
    void initialise(){
        this->linie = -1;
        this->coloana = -1;
        this->valoare = 0;
    }
};


class Matrice {

private:
	/* aici e reprezentarea */
    int numberOfLines;
    int numberOfColumns;
    Triplet* elements;
    int* next;
    int m;
    int firstFree;

    void updateFirstFree();
    int hash(Triplet element) const;
    void resize();

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

    void redimensioneaza();

};







