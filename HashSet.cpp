#include "HashSet.h"
void HashSet::rehash() {
}

HashSet::HashSet(){
	nslots = 64;
	nitems = 0;
	this->intfn = new SquareRootHash(1, nslots);
	this->strfn = new JenkinsHash();
	this->strfn2 = new PearsonHash();
	this->slots = new std::string*[nslots];
}

HashSet::~HashSet(){
}

void HashSet::insert(const std::string & value){
	if (nitems > nslots) {
		std::string** slots_storage = this->slots;

		nslots *= 2;
		nitems = 0;
		this->intfn = new SquareRootHash(0, nslots);
		this->slots = new std::string*[nslots];

		for(int i = 0; i < nslots / 2; i++) {
			this->insert(*slots_storage[i]);
		}
	}
	nitems++;

	uint64_t index = intfn->hash(strfn->hash(value));
	while (slots[index])
		index++;
	
	*slots[index] = value;
}

bool HashSet::lookup(const std::string & value) const{
	uint64_t index = intfn->hash(strfn->hash(value));
	return slots[index];
}
