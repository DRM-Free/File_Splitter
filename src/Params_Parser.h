/*
 * Params_Parser.h
 *
 *  Created on: Mar 23, 2018
 *      Author: anael
 */

#ifndef PARAMS_PARSER_H_
#define PARAMS_PARSER_H_

#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <utility>      // std::pair, std::make_pair
#include <string>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;


struct parsed_Params{
	fs::path inPath;
	fs::path outPath;
	int headerLines; //number of lines atthe beginning that should be put at the beginning of each copied file (usually 1)
	int cycle; //number of files to be written, which is the number of lines that will be written in the "round robin" cycle (one per file)
};
parsed_Params parse_params(int argc, char* argv[]);


#endif /* PARAMS_PARSER_H_ */
