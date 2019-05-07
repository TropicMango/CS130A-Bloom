#include "HashSet.h"
#include <iostream>
void HashSet::rehash() {
	// hash set expansion

	std::string** slots_storage = this->slots;
	nslots *= 2;
	nitems = 0;
	delete(intfn);
	this->intfn = new SquareRootHash(1, nslots);
	this->slots = new std::string*[nslots];
	for (int i = 0; i < nslots; slots[i++] = NULL);
	// valgrind initalization

	for (int i = 0; i < nslots / 2; i++) {
		if (slots_storage[i]) {
			this->insert(*slots_storage[i]);
			delete(slots_storage[i]);
		}
	}

	delete[](slots_storage);
}

HashSet::HashSet(){
	nslots = 8;
	nitems = 0;
	this->intfn = new SquareRootHash(1, nslots);
	this->strfn = new JenkinsHash();
	this->strfn2 = new PearsonHash();
	this->slots = new std::string*[nslots];
	for(int i=0; i<nslots; slots[i++] = NULL);
	// valgrind initalization
}

HashSet::~HashSet(){
	for (int i = 0; i < nslots; i++) {
		if (slots[i]) {
			delete(slots[i]);
		}
	}
	delete[](slots);
	delete(intfn);
	delete(strfn);
	delete(strfn2);
}

void HashSet::insert(const std::string & value){
	if (nitems >= nslots - 1) {
		rehash();
	}

	nitems++;

	// hash set probing
	uint64_t index = this->intfn->hash(this->strfn->hash(value));
	while (this->slots[index]){
		index++;
		if (index > (uint64_t)nslots - 1)
			index = 0;
	}
	
	//delete(slots[index]);
	slots[index] = new std::string(value);
}

bool HashSet::lookup(const std::string & value) const{
	int check = 0;
	//in the case the list is full and searching for a none existant value
	uint64_t index = this->intfn->hash(this->strfn->hash(value));
	while (slots[index]) {
		if (*slots[index] == value) {
			return true;
		}
		index++;
		if (index > (uint64_t)nslots - 1) {
			index = 0;
		}
		if (check > nslots - 1) {
			break;
		}
		check++;
	}
	return false;
}


