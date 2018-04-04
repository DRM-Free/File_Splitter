/*
 * main.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: anael
 */

#include "Params_Parser.h"
#include "Generate_File_Names.h"
#include <fstream>

//TODO maybe eliminate all this duplicated code with vis and auto files

int main(int argc, char** argv){
	parsed_Params par = parse_params(argc,argv);
std::vector<std::string> visNames=generateNames(5,"roiNames_visRW");
for (auto names=visNames.begin();names!=visNames.end();++names){ //Adding proper extensions
	(*names)+=".csv";
}
std::vector<std::string> autoNames=generateNames(5,"roiNames_autoRW");
for (auto names=autoNames.begin();names!=autoNames.end();++names){  //Adding proper extensions
	(*names)+=".csv";
}


//Paths and streams initiation
fs::path in=par.inPath;
fs::path autoin=par.inPath; //full path to auto file
autoin.append("roiNames-autoRW.csv");
fs::path visin=par.inPath;  //full path to vis file
visin.append("roiNames-visRW.csv");
const fs::path out=par.outPath;

std::fstream visfs;
visfs.open (visin, std::fstream::in); //File opened for reading


std::fstream autofs;
autofs.open (autoin, std::fstream::in);  //File opened for reading

//Deleting and re-creating output files, for a clean start
std::cout<<"Output folder "<<out<<" Will be erased and rewritten."<<std::endl<<"Confirm ?"<<std::endl;
std::string user_choice;
std::getline(std::cin,user_choice);
if(user_choice==(std::string)"\0" or user_choice==(std::string)"y"){ //User acceptance
	std::cout << "Proceeding to file operations" << std::endl;
	if(fs::exists(out)){
	fs::remove_all(out);
	fs::create_directory(fs::path(out));}
	else{
	fs::create_directory(fs::path(out));}
}

std::vector<std::fstream*> autoOutfs;
std::vector<std::fstream*> visOutfs;
fs::path outPath;

//Now opening all relevant files for writing
for (auto files=visNames.begin();files!=visNames.end();++files){
	visOutfs.push_back(new std::fstream);
	outPath=out;
	outPath.append(*files);
	visOutfs.back()->open(outPath, std::fstream::out); //File opened for writing
}
for (auto files=autoNames.begin();files!=autoNames.end();++files){
	autoOutfs.push_back(new std::fstream);
	outPath=out;
	outPath.append(*files);
	autoOutfs.back()->open(outPath, std::fstream::out); //File opened for writing
}


std::string visHeader="";
std::string autoHeader="";
	 std::string line;

//Extracting proper headers to add to each files
for (int h = 1; h <= par.headerLines; ++h) {
	std::getline(visfs, line);
	visHeader+=line;
}
for (int h = 1; h <= par.headerLines; ++h) {
	std::getline(autofs, line);
	autoHeader+=line;
}

//Now writing these headers to each files
for (auto files=autoOutfs.begin();files!=autoOutfs.end();++files){
	(**files)<<autoHeader<<std::endl; //*files is a pointer to a fstream object
}
for (auto files=visOutfs.begin();files!=visOutfs.end();++files){
	(**files)<<visHeader<<std::endl;
}

//Time to enter main loop and write all those silly lines :

int roundRobin=0;
while(std::getline(visfs, line)){//reading all vis file. Note that visfs ist not at beginning of file but already right after headers (presumably)
	*(visOutfs[roundRobin])<<line<<std::endl;
	++roundRobin;
	if(roundRobin==par.cycle){ //Write back to first file when round robin cycle is over
		roundRobin=0;
	}
}
roundRobin=0;
while(std::getline(autofs, line)){//reading all vis file. Note that visfs ist not at beginning of file but already right after headers (presumably)
	*(autoOutfs[roundRobin])<<line<<std::endl;
	++roundRobin;
	if(roundRobin==par.cycle){ //Write back to first file when round robin cycle is over
		roundRobin=0;
	}
}

		//Close all streams
		visfs.close();
		autofs.close();
		for (auto files=autoOutfs.begin();files!=autoOutfs.end();++files){
			(**files).close(); //close stream
		}
		for (auto files=visOutfs.begin();files!=visOutfs.end();++files){
			(**files).close(); //close stream
		}
		std::cout<<"Done"<<std::endl;
	return 0;
}
