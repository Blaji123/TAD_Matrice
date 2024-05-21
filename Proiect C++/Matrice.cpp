#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;

// complexity: Theta(1)
Matrice::Matrice(int m, int n) {
	/* de adaugat */
    if(m<=0 || n<=0){
        throw std::exception();
    }
    this->numberOfLines = m;
    this->numberOfColumns = n;
    this->m = MAX;
    this->elements = new Triplet[m];
    this->next = new int[m];
    this->firstFree = 0;
    for(int i=0;i<m;i++){
        this->elements[i].initialise();
        this->next[i] = -1;
    }
}

//complexity: Theta(1)
int Matrice::nrLinii() const{
	return this->numberOfLines;
}

//complexity: Theta(1)
int Matrice::nrColoane() const{
	return this->numberOfColumns;
}

//complexity: Theta(m)
//TElem Matrice::element(int i, int j) const{
//	if(i<0 || j<0 || i>=this->numberOfLines || j>=this->numberOfColumns){
//        throw std::exception();
//    }
//    for(int k=0;k<m;k++)
//        if(this->elements[k].linie == i && this->elements[k].coloana == j){
//            return this->elements[k].valoare;
//        }
//    return NULL_TELEMENT;
//}

//complexity: Worst : Theta(m), avg: Theta(1)
TElem Matrice::element(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->numberOfLines || j >= this->numberOfColumns) {
        throw std::exception();
    }

    // Calculate the hash position
    int position = hash(Triplet{i, j, 0});

    // Check if the element is at the calculated position
    if (this->elements[position].linie == i && this->elements[position].coloana == j) {
        return this->elements[position].valoare;
    }

    // If not found at the initial position, follow the next pointers
    int current = position;
    while (this->next[current] != -1) {
        current = this->next[current];
        if (this->elements[current].linie == i && this->elements[current].coloana == j) {
            return this->elements[current].valoare;
        }
    }
    // Element not found
    return NULL_TELEMENT;
}

/*
 * functie redimensioneaza()
 *      daca this->numberOfLines<=0 && this->numberOfColumns<=0 atunci
 *          @std::exception()
 *      sfDaca
 *      this->numberOfLines <- 2 * this->numberOfLines
 *      this->numberOfColumns <- 2 * this->numberOfColumns
 * sfFunctie
 * complexity:Theta(1)
 */
void Matrice::redimensioneaza(){
    if(this->numberOfLines<=0 && this->numberOfColumns<=0){
        throw std::exception();
    }
    this->numberOfLines = 2 * this->numberOfLines;
    this->numberOfColumns = 2 * this->numberOfColumns;
}

//complexity : Worst case: Theta(m), avg: Theta(1)
TElem Matrice::modifica(int i, int j, TElem e) {
    if(i<0 || j<0 || i>=this->numberOfLines || j>=this->numberOfColumns){
        throw std::exception();
    }
    int currentValue = this->element(i,j);
    //cazul in care elementul nu exista si trebuie adaugat
    if(currentValue == 0){
        Triplet newTriplet{i,j,e};
        int position = this->hash(newTriplet);

        //cazul in care pozitie este libera
        if(this->elements[position].linie ==-1 && this->elements[position].coloana==-1){
            this->elements[position] = newTriplet;
            this->next[position] = -1;
        }else {
            if (this->firstFree == this->m) {
                resize();
            }
            int current = position;
            while (this->next[current] != -1)
                current = this->next[current];
            this->elements[firstFree] = newTriplet;
            this->next[firstFree] = -1;
            this->next[current] = firstFree;
            updateFirstFree();
        }
        return NULL_TELEMENT;
        //cazul in care trebuie sa actualizam elementul
        }else{
        int position = hash(Triplet{i, j, 0});

        // Check if the element is at the calculated position
        if (this->elements[position].linie == i && this->elements[position].coloana == j) {
            TElem oldValue = this->elements[position].valoare;
            this->elements[position].valoare = e;
            return oldValue;
        }

        // If not found at the initial position, follow the next pointers
        int current = position;
        while (this->next[current] != -1) {
            current = this->next[current];
            if (this->elements[current].linie == i && this->elements[current].coloana == j) {
                TElem oldValue = this->elements[position].valoare;
                this->elements[position].valoare = e;
                return oldValue;
            }
        }
    }
    return NULL_TELEMENT;
}

//complexity: Theta(m)
void Matrice::updateFirstFree() {
    firstFree++;
    while(firstFree < m && this->elements[firstFree].linie!=-1 && this->elements[firstFree].coloana!=-1)
        firstFree++;
}

//complexity : Theta(m)
void Matrice::resize() {
    int oldCapacity = this->m;
    this->m *= 2; // Double the capacity

    Triplet* oldElements = this->elements;
    int* oldNext = this->next;

    this->elements = new Triplet[this->m];
    this->next = new int[this->m];

    // Reinitialize all elements and next pointers
    for (int i = 0; i < this->m; i++) {
        this->elements[i].initialise();
        this->next[i] = -1;
    }

    // Copy old elements to the resized arrays
    for (int i = 0; i < oldCapacity; i++) {
        if (oldElements[i].valoare != 0) { // If the element is not empty
            int position = hash(oldElements[i]);
            if (this->elements[position].linie == -1 && this->elements[position].coloana == -1) {
                // If the position is empty, just copy the element
                this->elements[position] = oldElements[i];
                this->next[position] = -1;
            } else {
                // If the position is occupied, find a new position using linear probing
                int current = position;
                while (this->next[current] != -1)
                    current = this->next[current];
                this->elements[firstFree] = oldElements[i];
                this->next[firstFree] = -1;
                this->next[current] = firstFree;
                updateFirstFree();
            }
        }
    }

    // Deallocate memory for old arrays
    delete[] oldElements;
    delete[] oldNext;

    // Update firstFree
    updateFirstFree();
}

//complexity : Theta(1)
int Matrice::hash(Triplet element) const {
    return (element.linie + element.coloana) % m;
}


