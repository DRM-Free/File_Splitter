/*
 * Params_Parser.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: anael
 */

#include "Params_Parser.h"

parsed_Params parse_params(int argc, char* argv[]) {
	parsed_Params par;
	par.inPath="";
	par.outPath="";
	par.headerLines=0; //optionnal
	par.cycle=0;
    if (argc < 7)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Not enough arguments." << std::endl <<"Usage is -in <data_location> -out <output_location> -cy <cycle number>"<<std::endl; // Inform the user of how to use the program
        std::cout << "optionnal argument : -he <number> defines the number of header lines, to be copied at the beginning of each result files"<<std::endl; // Inform the user of how to use the program
        std::cin.get(); //Just to keep the console open after execution so user can read error msg
        exit(0);
    				}
    if (argc > 9)
    				{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
            std::cout << argc << " arguments were given " << std::endl;
            std::cout << "Not enough arguments." << std::endl <<"Usage is -in <data_location> -out <output_location> -cy <cycle number>"<<std::endl; // Inform the user of how to use the program
        std::cout << "optionnal argument : -he <number> defines the number of header lines, to be copied at the beginning of each result files"<<std::endl; // Inform the user of how to use the program
            std::cin.get();
            exit(0);
        			}
    else
    		{ // if we got enough parameters...
        for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
                                          * Note that we're starting on 1 because we don't need to know the
                                          * path of the program, which is stored in argv[0] */
            if (i + 1 != argc) // Check that we haven't finished parsing already
            {
                if (argv[i] == (std::string)"-in")
                {
                    // We know the next argument *should* be the path to data:
                	par.inPath = argv[i + 1];
                	++i;
                }
                else if (argv[i] == (std::string)"-out")
                {
                	par.outPath = argv[i + 1];
                	++i;
                }
                else if (argv[i] == (std::string)"-he")
                                {
                                	par.headerLines=std::stoi(argv[i + 1]);
                                }
                else if (argv[i] == (std::string)"-cy")
                                                {
                	par.cycle=std::stoi(argv[i + 1]);

                                                }
                else
                {
                    std::cout << "Invalid argument :"<< argv[i] << std::endl; // Inform the user of how to use the program
                    std::cout <<"Usage is -in <data_location> -out <output_location> -cy <cycle number>"<<std::endl; // Inform the user of how to use the program

            std::cin.get();
                    exit(0);
                }
            }
        }
        if((par.inPath=="")or(par.outPath=="")or(par.cycle==0)){
        	std::cout<<"Invalid arguments"<<std::endl<<"Usage is -in <data_location> -out <output_location> -cy <cycle number>"<<std::endl; // Inform the user of how to use the program
            std::cout << "optionnal argument : -he <number> defines the number of header lines, to be copied at the beginning of each result files"<<std::endl; // Inform the user of how to use the program
                std::cin.get();
                exit(0);
        }
        if(par.headerLines==0){
                            std::cout<<"Optionnal header number parameter -he not provided. Assuming 1 header line"<<std::endl;
                                        		par.headerLines=1;
}return par;
}
}

