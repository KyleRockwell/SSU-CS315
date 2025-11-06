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

	//char currchar;
	std::string currWord;
	std::string currCode;
	while(!infile.eof()){
		
		std::getline(infile, currWord, ' ');
		std::getline(infile, currCode, '\n');
			
		header.push_back(std::pair<std::string, std::string>(currWord, currCode));
		currWord = "";
		currCode = "";	
	}
	infile.close();
	return NO_ERROR;
}


// go thru the .code file, and decode each word using the huffman tree
error_type decode(std::filesystem::path inputPath, std::filesystem::path outPath,  TreeNode* head) {
	std::ifstream infile(inputPath);
	std::ofstream outfile(outPath);
	if(!infile.is_open())
		return UNABLE_TO_OPEN_FILE;
	char currchar;
	TreeNode* node = head;	

	infile.get(currchar);
	while(!infile.eof()){
			if(currchar== '0'){
				node = node->leftSubtree();

				if(node->leftSubtree() == nullptr || node->rightSubtree() == nullptr){
					outfile<< node->value()<< "\n";
					node = head;
				}
			}
	
			else if(currchar == '1'){
				node = node->rightSubtree();
				
				if(node->rightSubtree() == nullptr|| node->leftSubtree() == nullptr){
					outfile<< node->value()<< "\n";
					node = head;
				}
			}	
			infile.get(currchar);
	}
	infile.close();	
	return NO_ERROR;
}


//go thru each value in header
	//if "1" create a right node if it does not exits
	//if "0" create a left node if it does not exist
	//if " " then the node is a leaf and should be populated with the value
	//do this until the input is empty, and return the node
	
// create a huffman decoder tree using the vector.
// header is vector of (word, code) pairs
TreeNode* HuffmanDecode(std::vector<std::pair<std::string, std::string>>& header){
	TreeNode* root = new TreeNode("");
	TreeNode* curr = root;
	for(size_t i = 0; i < header.size(); i++){
		std::string word = std::get<0>(header.at(i));
		std::string code = std::get<1>(header.at(i));
		

		for(size_t j = 0; j < code.size(); j++){
			
			if(code.at(j) == '0'){
				if(curr->leftSubtree() == nullptr){
					TreeNode* leftNode = new TreeNode("");
					curr->leftSubtree(leftNode);
					curr=curr->leftSubtree();
				}
				else{
					curr = curr->leftSubtree();
				}
			}
			else if(code.at(j) == '1'){
				if(curr->rightSubtree() == nullptr){
					TreeNode* rightNode = new TreeNode("");
					curr->rightSubtree(rightNode);
					curr=curr->rightSubtree();
				}
				else{
					curr = curr->rightSubtree();
				}
			}
		}
		curr->value(word);
		curr = root;
	}

	return root;	
}




int main(int argc, char *argv[]){

	//checking argument count	
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
	const std::string outputFile  = dirName + "/" + inputFileBaseName + ".tokens_decoded";
	
	//checking if files exist and are writable
	if(error_type status; (status = regularFileExistsAndIsAvailable(inputHdrFile)) != NO_ERROR)
		exitOnError(status, inputHdrFile);
	if(error_type status; (status = regularFileExistsAndIsAvailable(inputCodeFile)) != NO_ERROR)
		exitOnError(status, inputCodeFile);
	if(error_type status; (status = directoryExists(dirName)) != NO_ERROR)
		exitOnError(status, dirName);
	if(error_type status; (status = canOpenForWriting(outputFile)) != NO_ERROR)
		exitOnError(status, outputFile);


	
	//stores header in vector of (word, code) pairs	
	std::vector<std::pair<std::string, std::string>> pairs;
	readHeader(inputHdrFile, pairs);			
	

	//creates a huffman tree of the (word, code) pairs
	TreeNode* huffman = HuffmanDecode(pairs);
	
	//decodes the .code file using the huffman tree decoder
	decode(inputCodeFile, outputFile, huffman);

	return 0;
}
