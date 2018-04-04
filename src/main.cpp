/*
 * main.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: anael
 */

#include "Params_Parser.h"
#include "Generate_File_Names.h"
#include <fstream>

int main(int argc, char** argv){
	parsed_Params par = parse_params(argc,argv);
std::vector<std::string> visNames=generateNames(5,"roiNames-visRW");
for (auto names=visNames.begin();names!=visNames.end();++names){ //Adding proper extensions
	(*names)+=".csv";
}
std::vector<std::string> autoNames=generateNames(5,"roiNames-autoRW");
for (auto names=autoNames.begin();names!=autoNames.end();++names){  //Adding proper extensions
	(*names)+=".csv";
}

fs::path in=par.inPath;
fs::path autoin=par.inPath; //full path to auto file
autoin.append("roiNames-autoRW.csv");
fs::path visin=par.inPath;  //full path to vis file
visin.append("roiNames-visRW.csv");
fs::path out=par.outPath;

std::fstream visfs;
visfs.open (visin, std::fstream::in); //File opened for reading


std::fstream autofs;
autofs.open (autoin, std::fstream::in);  //File opened for reading



std::vector<std::fstream*> autoOutfs;
std::vector<std::fstream*> visOutfs;

//Now opening all relevant files for writing
int namepos=0;
for (auto files=visNames.begin();files!=visNames.end();++files){
	autoOutfs.push_back(new std::fstream);
autoOutfs.back()->open(visNames[namepos], std::fstream::out); //File opened for writing
++namepos;
}
namepos=0;
for (auto files=autoNames.begin();files!=autoNames.end();++files){
	visOutfs.push_back(new std::fstream);
	visOutfs.back()->open(visNames[namepos], std::fstream::out); //File opened for writing
++namepos;
}


std::string visHeader="";
std::string autoHeader="";
	 std::string line;

//Extracting proper headers to add to each files
for (int h = 0; h <= par.headerLines; ++h) {
	std::getline(visfs, line);
	visHeader+=line;
}
for (int h = 0; h <= par.headerLines; ++h) {
	std::getline(autofs, line);
	autoHeader+=line;
}

//Now writing these headers to each files
for (auto files=autoOutfs.begin();files!=autoOutfs.end();++files){
	(**files)<<autoHeader; //*files is a pointer to a fstream object
}
namepos=0;
for (auto files=visOutfs.begin();files!=visOutfs.end();++files){
	(**files)<<visHeader;
}

//Time to enter main loop and write all those silly lines :



		//Close all streams
		visfs.close();
		autofs.close();
		for (auto files=autoOutfs.begin();files!=autoOutfs.end();++files){
			(**files).close(); //close stream
		}
		namepos=0;
		for (auto files=visOutfs.begin();files!=visOutfs.end();++files){
			(**files).close(); //close stream
		}
	return 0;
}
