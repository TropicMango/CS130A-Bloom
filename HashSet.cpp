#include "HashSet.h"
void HashSet::rehash() {
}

HashSet::HashSet(){
	nslots = 1;
	nitems = 0;
	this->intfn = new SquareRootHash();
}

HashSet::~HashSet(){
}

void HashSet::insert(const std::string & value){
}

bool HashSet::lookup(const std::string & value) const{
	return false;
}
