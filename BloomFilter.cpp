#include "BloomFilter.h"

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn) {
	this.k = k;
	this.m = m;

	bits = new uint64_t[(m / 64) +1];
	intfns = new IntegerHash[k];

	switch (strfn) {
	case "jenkins":
		this->strfn = new JenkinsHash();
		break;
	case "pearson":
		this->strfn = new PearsonHash();
		break;
	}


	switch (intfn) {
	case "division":
		for (int i = 0; i < k; i++)
			this->intfns[i] = new DivisionHash(i, m);
		break;
	case "reciprocal":
		for (int i = 0; i < k; i++)
			this->intfns[i] = new ReciprocalHash(i, m);
		break;
	case "squareroot":
		for (int i = 0; i < k; i++)
			this->intfns[i] = new SquareRootHash(i, m);
		break;
	}
}

BloomFilter::~BloomFilter() {
}

void BloomFilter::insert(const std::string & value) {
	uint64_t UIntValue = strfn->hash(value);
	for (int i = 0; i < k; i++) {
		uint16_t index = intfns->hash(UIntValue);
		bits[index / 64] = bits[index / 64] | (((uint64_t)1) << (index % 64));
	}
}

bool BloomFilter::lookup(const std::string & value) const {
	uint64_t UIntValue = strfn->hash(value);
	for (int i = 0; i < k; i++) {
		uint16_t index = intfns->hash(UIntValue, m);
		if (bits[index / 64] & (((uint64_t)1) << (index % 64)) == 0)
			return false;
	}
	return true;
}
