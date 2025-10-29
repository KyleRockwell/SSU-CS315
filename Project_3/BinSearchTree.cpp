#include "BinSearchTree.hpp"
//BinSearchTree::BinSearchTree(): root_{nullptr} {}

bool BinSearchTree::contains(std::string_view word) const noexcept{


	if (findNode(root_, word) == nullptr) { 
		return false;
	}
	return true;
}
void BinSearchTree::bulkInsert(const std::vector<std::string>& words){
   // std::cout<<"hello \n";
	std::string curr;
	

	
	for (size_t i = 0; i < words.size(); i++){
		curr = words.at(i);
		insert(curr);
	}

	
}
void BinSearchTree::insert(const std::string& word){
	
    //std::cout<<word << std::endl;
		root_ = insertHelper(root_, word); 

	
}

TreeNode* BinSearchTree::insertHelper(TreeNode *node, const std::string &word){
	if( node== nullptr){
		TreeNode* n = new TreeNode(word);
		return n;
	}
	if(node->value() == word){
		//node->count = node->count + 1;
		node->countUp();
		return node;
	}

	if(node->value()< word){
		node->rightSubtree(insertHelper(node->rightSubtree(),word));
		
	}
	else
		node->leftSubtree(insertHelper(node->leftSubtree(),word));	
	return node;
}
const TreeNode* BinSearchTree::findNode(const TreeNode* node, std::string_view word)noexcept{

	if(node== nullptr){
		return nullptr;
	}
	if(node->value() == word){
		return node;
	}
	if(node->value()>word)
		return findNode(node->leftSubtree(),word);

	return findNode(node->rightSubtree(), word);

		
}
std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept{
	const TreeNode* node = findNode(root_, word);
	if (node == nullptr)
		return 0;
	return node->freq();
}
std::size_t BinSearchTree::size()const noexcept{
	return sizeHelper(root_);

}
std::size_t BinSearchTree::sizeHelper(const TreeNode* node)const noexcept{
	if (node == nullptr){
		return 0;
	}
	return 1+ sizeHelper(node->leftSubtree())+sizeHelper(node->rightSubtree());
}
unsigned BinSearchTree::height() const noexcept{
	return heightHelper(root_);

}
unsigned BinSearchTree::heightHelper(const TreeNode* node) const noexcept{
	if(node == nullptr)
		return 0;
	return 1 + std::max(heightHelper(node->leftSubtree()), heightHelper(node->rightSubtree()));
}

void BinSearchTree::inorderCollect( std::vector<std::pair<std::string, int>>& out)const{
	inorderHelper(root_, out);
	
}
void BinSearchTree::inorderHelper(const TreeNode* node, std::vector<std::pair<std::string, int>>& out)const{
	if(node == nullptr)
		return;
	auto p1 = std::make_pair(node->value(), node->freq());

	inorderHelper(node->leftSubtree(), out);
	out.push_back(p1);
	inorderHelper(node->rightSubtree(), out);
	return;
}

BinSearchTree::~BinSearchTree(){
	//destroy(root_->leftSubtree());
	//destroy(root_->rightSubtree());
	if(root_ != nullptr){
		delete root_->leftSubtree();
		delete root_->rightSubtree();
		delete root_;
	}
}
