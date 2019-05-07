#include "HashSet.h"
void HashSet::rehash() {
}

HashSet::HashSet(){
	nslots = 64;
	nitems = 0;
	this->intfn = new SquareRootHash(0, nslots);
	this->strfn = new JenkinsHash();
	this->strfn2 = new PearsonHash();
	this->slots = new string*[nslots];
}

HashSet::~HashSet(){
}

void HashSet::insert(const std::string & value){
	if (nitems > nslots) {
		string** slots_storage = this->slots;

		nslots *= 2;
		this->intfn = new SquareRootHash(0, nslots);
		this->slots = new string*[nslots];

		for each (string* str in slots_storage) {
			this->insert(str);
		}
	}
	nitems++;

	uint64_t index = intfn->hash(strfn->hash(value));
	while (*slots[index] != NULL)
		index++;
	
	*slots[index] = value;
}

bool HashSet::lookup(const std::string & value) const{
	return false;
}
