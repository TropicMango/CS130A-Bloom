#include "BloomFilter.h"

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn) {
	this->k = k;
	this->m = m;

	this->bits = new uint64_t[(m / 64) +1];
	for(int i=0; i<(m/64)+1; bits[i++] = (uint64_t)0);
	// valgrind initalization
	
	this->intfns = new IntegerHash*[k];
	for(int i=0; i<k; intfns[i++] = NULL);
	// valgrind initalization
	
	// why can't cpp switch with strings T^T
	if(strfn == "jenkins") {
		this->strfn = new JenkinsHash();
	}else if(strfn == "pearson"){
		this->strfn = new PearsonHash();
	}else{
		// default
		this->strfn = new JenkinsHash();
	}


	if(intfn == "division"){
		for (int i = 0; i < k; i++)
			this->intfns[i] = new DivisionHash(i, m);
	} else if(intfn == "reciprocal"){
		for (int i = 0; i < k; i++)
			this->intfns[i] = new ReciprocalHash(i, m);
	} else if(intfn == "squareroot"){
		for (int i = 0; i < k; i++)
			this->intfns[i] = new SquareRootHash(i, m);
	} else {
		// default
		for (int i = 0; i < k; i++)
			this->intfns[i] = new SquareRootHash(i, m);
	}
}

BloomFilter::~BloomFilter() {
	for (int i = 0; i < k; i++) {
		delete(intfns[i]);
	}
	delete[](intfns);
	delete[](bits);
	delete(strfn);
}

void BloomFilter::insert(const std::string & value) {
	uint64_t UIntValue = strfn->hash(value);
	for (int i = 0; i < k; i++) {
		uint16_t index = intfns[i]->hash(UIntValue);
		bits[index / 64] = bits[index / 64] | (((uint64_t)1) << (index % 64));
		// push bits into position then bitwise or to make the number at the position 1
	}
}

bool BloomFilter::lookup(const std::string & value) const {
	uint64_t UIntValue = strfn->hash(value);
	for (int i = 0; i < k; i++) {
		uint64_t index = intfns[i]->hash(UIntValue);
		uint64_t index_check = (((uint64_t)1) << (index % 64));
		if ((bits[index / 64] & index_check) == 0)
			// bit wise and to eliminate all bits that is not of interest
			return false;
	}
	return true;
}
