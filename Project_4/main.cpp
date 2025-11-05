#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "Treenode.hpp"
#include "utils.hpp"
//make sure files exist and can be written



//function to read header file, and store pairs in std::vector<<std::pair<<std::string, std::string>>
error_type readHeader(std::filesystem::path inputPath, std::vector<std::pair<std::string, std::string>>& header){
	std::ifstream infile(inputPath);

	if(!infile.is_open())
		return UNABLE_TO_OPEN_FILE;

	char currchar;
	std::string currWord;
	std::string currCode;

	while(infile.get(currchar)) {
		while(isalpha(currchar)){
			currWord.push_back(currchar);
			infile.get(currchar);
		}
		while(infile.peek() == '1' || infile.peek()== '0'){
			infile.get(currchar);
			currCode.push_back(currchar);
		}
		header.push_back(std::pair<std::string, std::string>(currWord, currCode));
		currWord = "";
		currCode = "";	
	}
	infile.close();
	return NO_ERROR;
}





// create a huffman decoder tree using the vector.
TreeNode* HuffmanDecode(std::vector<std::pair<std::string, std::string>> header){
	TreeNode* root = new TreeNode("");


	//go thru each value in header
	//if "1" create a right node if it does not exits
	//if "0" create a left node if it does not exist
	//if " " then the node is a leaf and should be populated with the value
	//do this until the input is empty, and return the node
	return root;	
}



// go thru the .code file, and decode each word using the huffman tree
void decode(std::ostream os, std::istream codeFile, TreeNode* head) {
	

}

int main(int argc, char *argv[]){
		
	if (argc !=3) {
		std::cerr << "usage: " << argv[0] << " <filename.hdr> <filename.code>\n";
		return 1;
	}	
	//setting up files
	//expected input  "./huff_decode.x article.hdr article.code"
	const std::string dirName = std::string("input_output");
	const std::string inputHdrFile = dirName + "/" + std::string(argv[1]);
	const std::string inputCodeFile = dirName + "/" +  std::string(argv[2]);
	const std::string inputFileBaseName = baseNameWithoutHdr(inputHdrFile);
	//building output file path
	
	const std::string outputFile  = inputFileBaseName + ".tokens_decoded";
	std::cout<<outputFile << std::endl;
	
	//checking if files exist and are writable
	if(error_type status; (status = regularFileExistsAndIsAvailable(inputHdrFile)) != NO_ERROR)
		exitOnError(status, inputHdrFile);
	if(error_type status; (status = regularFileExistsAndIsAvailable(inputCodeFile)) != NO_ERROR)
		exitOnError(status, inputCodeFile);

	if(error_type status; (status = directoryExists(dirName)) != NO_ERROR)
		exitOnError(status, dirName);

	if(error_type status; (status = canOpenForWriting(outputFile)) != NO_ERROR)
		exitOnError(status, outputFile);
	std::vector<std::pair<std::string, std::string>> pairs;

	
	
	//stores header in vector of (word, code) pairs	
	readHeader(inputHdrFile, pairs);			
	
	//for checking that pair are stored properly
	for(size_t i  = 0; i < pairs.size(); i++){
		std::cout<<std::get<0>(pairs.at(i)) <<" " << std::get<1>(pairs.at(i)) << std::endl;
	}

	//creates a huffman tree of the (word, code) pairs
	TreeNode huffman = HuffmanDecode(pairs);

	return 0;
}
