#include "ArrangementsTable.hpp"

ArrangementsTable::ArrangementsTable(unsigned n){
	this->n = n;
	this->resize(n + 1);

    (*this)[2].resize(1);
    (*this)[2][0].first.push_back(std::make_pair(0,1));
}
