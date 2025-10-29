#include "HuffmanTree.hpp"
HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string,int>>& counts){
	PriorityQueue pq(counts);	

	while (pq.size() > 1){
			
		TreeNode * a = pq.extractMin();
		TreeNode * b = pq.extractMin();
	
		
		int freq =  a->freq() + b->freq();
		std::string word = std::min(a->value(), b->value());
		TreeNode * c = new TreeNode(word, freq);
		c->leftSubtree(a);
		c->rightSubtree(b);
		pq.insert(c);

	}

	HuffmanTree  hf;
	hf.root_ = pq.extractMin();
	return hf;

	
}



void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string>>& out) const{
	std::string prefix = "";	
	//traverse Tree left to right, each node progressed, append that number (1, 0) to code
	//once reaching a leaf node->left, node-> right == nullptr; push word, code pair  to "out"
	//gotta call that helper function
	assignCodesDFS(root_, prefix, out);
}

void HuffmanTree::assignCodesDFS(const TreeNode* n, std::string& prefix, std::vector<std::pair<std::string, std::string>>& out){
	if(n == nullptr)
		return;
	if(n->leftSubtree() == nullptr && n->rightSubtree() == nullptr){
		out.push_back(std::pair(n->value(), prefix));
		return;
	}
		std::string l  = prefix;
		std::string r = prefix;
		l.push_back('0');
		r.push_back('1');
	assignCodesDFS(n->leftSubtree(),  l, out);

	assignCodesDFS(n->rightSubtree(), r, out);


}

error_type HuffmanTree::writeHeader(std::ostream& os) const{
	std::string prefix = "";
	writeHeaderPreorder(root_, os, 	prefix);
	return NO_ERROR;
}

void HuffmanTree::writeHeaderPreorder(const TreeNode* n, std::ostream& os,
                                    		std::string& prefix){

		if(n == nullptr)
			return;
		if(n->leftSubtree() == nullptr && n->rightSubtree() == nullptr){
			os  << n->value() << " " << prefix << "\n";
		}
		std::string l  = prefix;
		std::string r = prefix;
		l.push_back('0');
		r.push_back('1');

		writeHeaderPreorder(n->leftSubtree(), os,  l);
		writeHeaderPreorder(n->rightSubtree(), os, r);
}
error_type HuffmanTree::encode(const std::vector<std::string>& tokens,
                      std::ostream& os_bits,
                      int wrap_cols ) const{
	int wrapCount = 0;	
	std::vector<std::pair<std::string, std::string>> codes;
	assignCodes(codes);

	for(size_t i = 0; i < tokens.size(); i++) {
		for( size_t j = 0; j < codes.size(); j++){
			if(std::get<0>(codes.at(j)) == tokens.at(i)){
				//output std::get<1>(codes.at(j) one by one
				//increment wrapcount each time. 
				//if wrapcount == wrap_cols, add a newline, and reset wrapcount
				auto outcode =  std::get<1>(codes.at(j));
				for(size_t k = 0; k < outcode.length(); k++){
					//putc(outcode.at(k), os_bits);
					os_bits << outcode.at(k);
					wrapCount++;
					if(wrapCount == wrap_cols){
						//putchar('\n', os_bits);
						os_bits << '\n';
						wrapCount = 0;
					}
				}

			}

		}
	}
	os_bits<<'\n';
return NO_ERROR;

}

HuffmanTree::~HuffmanTree(){
	delete root_;
}
