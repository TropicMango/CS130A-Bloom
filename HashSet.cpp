#include "HashSet.h"
#include <iostream>
void HashSet::rehash() {
}

HashSet::HashSet(){
	nslots = 8;
	nitems = 0;
	this->intfn = new SquareRootHash(1, nslots);
	this->strfn = new JenkinsHash();
	this->strfn2 = new PearsonHash();
	this->slots = new std::string*[nslots];
}

HashSet::~HashSet(){
	delete[](slots);
	delete(intfn);
	delete(strfn);
	delete(strfn2);
}

void HashSet::insert(const std::string & value){
	if (nitems == nslots) {
	
		std::string** slots_storage = this->slots;
		
		nslots *= 2;
		nitems = 0;
		delete(intfn);
		
		this->intfn = new SquareRootHash(1, nslots);
		this->slots = new std::string*[nslots];

		for(int i = 0; i < nslots / 2; i++) {
			std::cout << "--------" << slots_storage[i] << "--------" << std::endl;
			this->insert(*slots_storage[i]);
			std::cout << "-------inserted---------" << std::endl;
			delete(slots_storage[i]);
		}
		std::cout << "------3--------" << std::endl;
	}
	nitems++;

	uint64_t index = intfn->hash(strfn->hash(value));
	while (slots[index])
		index++;
	slots[index] = new std::string(value);
}

bool HashSet::lookup(const std::string & value) const{
	uint64_t index = intfn->hash(strfn->hash(value));
	return slots[index];
}