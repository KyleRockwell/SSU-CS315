## Student Information
Name: Kyle Rockwell
ID: 008657669

## Collaboration and sources
    cplusplus.com
        - ifstream
        - isalpha
        - string
        - std::io
        - and several more
    https://www.ascii-code.com/
       cppreference.com 
## implementation Detals
  A huffman tree decoder. It takes in a .hdr file, which consists of a (word, code) pair on each line, and a .code file which is a stream of 1's and 0's
    it then creates a huffman tree using the .hdr file, and then decodes the .code file with that huffman tree. 
    
  The Treenode.hpp and the utils.cpp & utils.hpp files
    were written by Professor Ali Kooshesh at Sonoma State Universtiy. The Treenode.hpp file was modified by me to fit my specific implementation. 
## Testing and Status
   I tested using the provided scripts and each one matched. so the current status is working as expected. 
    
