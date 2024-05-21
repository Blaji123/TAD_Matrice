#include <assert.h>
#include "Matrice.h"
#include "TestExtins.h"
#include <iostream>
#include <exception>

using namespace std;


void testCreeaza() {
	Matrice m(10,10);
	assert(m.nrLinii() == 10);
	assert(m.nrColoane() == 10);
	for(int i=0; i<m.nrLinii(); i++)
	  for(int j=0; j<m.nrColoane(); j++)
		assert(m.element(i,j) == NULL_TELEMENT);
}

void testAdauga() {
	Matrice m(10,10);
	for(int j=0; j<m.nrColoane(); j++)
		m.modifica(4,j,3);
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane(); j++)
		if (i==4)
		  assert(m.element(i,j) == 3);
		else {
            assert(m.element(i, j) == NULL_TELEMENT);
        }
}

void testQuantity() {//scopul e sa adaugam multe date
	Matrice m(300,300);
	for(int i=m.nrLinii()/2; i<m.nrLinii(); i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {
		int v1=j;
		int v2=m.nrColoane()-v1-1;
           if (i%2==0 && v1%2==0) {
               m.modifica(i, v1, i * v1);
           }
		else
	            if (v1%3==0) {
                    m.modifica(i, v1, i + v1);
                }
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0) {
                    m.modifica(i, v2, i + v2);
                }
	   }
	}
	for(int i=0; i<=m.nrLinii()/2; i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {	
		int v1=j;
		int v2=m.nrColoane()-v1-1;
		if (i%2==0 && v1%2==0) {
            m.modifica(i, v1, i * v1);
        }
		else
	            if (v1%3==0)
			m.modifica(i, v1, i+v1);
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0)
			m.modifica(i, v2, i+v2);
	   }
	}		
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane()/2; j++)
		if (i%2==0 && j%2==0) {
            assert(m.element(i, j) == i * j);
        }
		else
	            if (j%3==0) {
                    assert(m.element(i, j) == i + j);
                }
                else
                    assert(m.element(i,j) == 0);
}

void testExceptii() {
	Matrice m(10,10);
	try {
		m.element(-1,-1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
    try {
		m.modifica(12,0,1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
	try {
		assert(m.nrLinii());
	}
	catch (exception&) {
		assert(false); //nu ar trebui sa arunce exceptie
	}
}

void testRedimensionare(){
    Matrice m{10, 10};
    m.modifica(1,1,2);
    assert(m.element(1,1)==2);
    m.modifica(2,2,5);
    assert(m.element(2,2)==5);
    m.modifica(3,3,5);
    assert(m.element(3,3)==5);
    try{
        m.modifica(11,11,15);
        assert(false);
    }catch(exception&){
        assert(true);
    }
    m.redimensioneaza();
    m.modifica(15, 15, 10);
    assert(m.element(15,15)==10);
    m.modifica(17,17,15);
    assert(m.element(17,17)==15);
    try{
        m.modifica(23,23,11);
        assert(false);
    }catch (exception&){
        assert(true);
    }
//    Matrice m2{0,0};
//    try{
//        m2.redimensioneaza();
//        assert(false);
//    }catch (exception&){
//        assert(true);
//    }
}

void testAllExtins() {
	testCreeaza();
	testAdauga();
	testQuantity();
	testExceptii();
    testRedimensionare();
}
