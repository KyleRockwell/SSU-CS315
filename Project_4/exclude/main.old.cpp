#include <iostream>
#include <fstream>
#include <filesystem> 
#include <string>
#include <vector>
#include "Scanner.hpp"
#include "BinSearchTree.hpp"
#include "utils.hpp"
#include "PriorityQueue.hpp"
#include "HuffmanTree.hpp"
int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = dirName + "/"+ std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" +  inputFileBaseName + ".tokens";
    
    const std::string wordFreqFileName =dirName + "/" + inputFileBaseName + ".freq";

    const std::string hdrFileName = dirName + "/" +  inputFileBaseName + ".hdr";
    const std::string codeFileName = dirName + "/" +  inputFileBaseName + ".code";
// The next several if-statement make sure that the input file, the directory exist
// and that the output file is writeable.
 if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
     exitOnError(status, inputFileName);


 if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
     exitOnError(status, dirName);

 if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
     exitOnError(status, wordTokensFileName);

 std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.
    fs::path freqFilePath(wordFreqFileName);
    auto fileToWords = Scanner(tokensFilePath);
    auto fileToTokens = Scanner(inputFileName);
    if( error_type status; (status = fileToTokens.tokenize(words,tokensFilePath )) != NO_ERROR){
            std::cout<<"exiting\n";
            exitOnError(status, inputFileName);
    }
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
            exitOnError(status, inputFileName);


    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    BinSearchTree BST;
   BST.bulkInsert(words);
   std::vector<std::pair<std::string, int>> wordpair;

  BST.inorderCollect( wordpair);
	std::pair<std::string, int> minfreq, maxfreq;
  if(wordpair.size() > 0){
  	 minfreq = wordpair.at(0);
 	  maxfreq = wordpair.at(0);
  }
  
  for( size_t i = 0; i < wordpair.size(); i++){
	 if(std::get<int>(wordpair.at(i)) <  std::get<int>(minfreq)){
		 minfreq = wordpair.at(i);
	 }
	 if(std::get<int>(wordpair.at(i)) > std::get<int>(maxfreq)){
		 maxfreq = wordpair.at(i);
	}
  }
  std::cout<<"BST height: " <<BST.height() <<std::endl; 
  std::cout<<"BST unique words: " <<BST.size() <<std::endl;
  std::cout<<"Total tokens: " <<words.size() <<std::endl;
  std::cout<<"Min frequency: " << std::get<int>(minfreq) <<std::endl;
  std::cout<<"Max frequency: " << std::get<int>(maxfreq) <<std::endl;
	std::vector<TreeNode*> nodes;
	for(size_t i = 0; i < wordpair.size(); i++){
		TreeNode *node = new TreeNode(std::get<std::string>(wordpair.at(i)), std::get<int>(wordpair.at(i)));
		nodes.push_back(node);
		
	}
	
	PriorityQueue prioqueue(nodes);




	std::ofstream freqfile(wordFreqFileName);
	prioqueue.print(freqfile);
	freqfile.close();

	HuffmanTree hufftree = HuffmanTree::buildFromCounts(wordpair);
	std::ofstream headerFile(hdrFileName);
	hufftree.writeHeader(headerFile);
	headerFile.close();
	std::ofstream codeFile(codeFileName);
	hufftree.encode(words, codeFile);
	codeFile.close();	
    return 0;
}
