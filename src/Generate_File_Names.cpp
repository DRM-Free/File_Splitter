/*
 * Generate_File_Names.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: anael
 */




#include "Generate_File_Names.h"
/**
 * Simple name generation, no zero padding at the beginning
 * TODO: add padding (example : 1 becomes 001 if there are less than 1000 names to generate
 */
std::vector<std::string> generateNames(int range,
		std::string nameComplement) {
	uint codingNumber = ceil(log(range)); //If range <100 then CodingNumber will be <=2 therefore coding names with 2 numbers
//SEE verify file name generation
	std::vector<std::string> names;
	std::string curName="";
	std::string number="";
	for (int i = 0; i < range; ++i) {
	curName=nameComplement;
	number=std::to_string(i);
	while(number.size()<codingNumber){
		number.insert(number.begin(),'0');
	}
	curName+=number;
	names.push_back(curName);
	}
return names;
}
