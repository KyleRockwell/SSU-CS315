//
// Created by Ali Kooshesh on 9/27/25.
//

#include "Scanner.hpp"

#include <utility>
#include <iostream>
#include <fstream>
#include "utils.hpp"
#include <cctype>
Scanner::Scanner(std::filesystem::path inputPath) {
    // You complete this...
	inputPath_  = inputPath;
}
error_type Scanner::tokenize(std::vector<std::string>& words) {
	//if the input directory does not exist, return DIR_NOT_FOUND
	//if the file is miss, FILE_NOT_FOUND
	//if unable to open UNABLE_TO_OPEN_FILE
	if(error_type status; (status = directoryExists(inputPath_.parent_path())) != NO_ERROR){
		return status;
	}
	if(error_type status; (status = regularFileExists(inputPath_)) != NO_ERROR){
		return status;
	}
	std::ifstream file(inputPath_);
	if(!file.is_open())
		return UNABLE_TO_OPEN_FILE;

	char currchar; 
	std::string currToken = "";

	while(file.get(currchar)) {
		if(isalpha(currchar) ){
			currchar = std::tolower(currchar);
			currToken.push_back(currchar);
		}	
		else if((currchar == '\'') && isalpha(currToken.back()) && isalpha(file.peek())){
			currToken.push_back('\'');
		}
		else{
			if(!currToken.empty()){
				words.push_back(currToken);
			}	
			
			currToken = std::string(); 
		}
		
       }
	file.close();	
    return NO_ERROR;
}
error_type Scanner::tokenize(std::vector<std::string>& words, const std::filesystem::path& outputFile) {
	std::ofstream file(outputFile);
	error_type error = tokenize(words);
	if(error != NO_ERROR){
		return error;
	}
	if(error_type status; (status = canOpenForWriting(outputFile)) != NO_ERROR)
		return status;
	for(size_t i = 0; i < words.size(); i++){
		//words[i] >> outputFile;
		file << words[i];
	}	
	file.close();
	return NO_ERROR;
}


