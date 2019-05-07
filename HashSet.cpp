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
	/*for (int i = 0; i < nslots; i++) {
		if (slots[i]) {
			std::cout << "current: " << *slots[i] << std::endl;
		} else {
			std::cout << "current: " << std::endl;
		}
	}*/
	delete[](slots);
	delete(intfn);
	delete(strfn);
	delete(strfn2);
}

void HashSet::insert(const std::string & value){
	if (nitems >= nslots - 1) {
	
		std::string** slots_storage = this->slots;
		nslots *= 2;
		nitems = 0;
		this->intfn = new SquareRootHash(0, nslots);
		this->slots = new std::string*[nslots];

		for (int i = 0; i < nslots / 2; i++) {
			if (slots_storage[i])
				this->insert(*slots_storage[i]);
		}
		
		delete[](slots_storage);
	}

	nitems++;

	uint64_t index = intfn->hash(strfn->hash(value));
	while (this->slots[index]){
		index++;
		if (index > (uint64_t)nslots - 1)
			index = 0;
	}

	slots[index] = new std::string(value);
}

bool HashSet::lookup(const std::string & value) const{
	uint64_t index = intfn->hash(strfn->hash(value));
	while (slots[index]) {
		if (slots[index] == &value) {
			return true;
		}
		index++;
		if (index > (uint64_t)nslots - 1)
			index = 0;
	}
	return false;
}


