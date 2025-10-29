#ifndef BST_HPP
#define BST_HPP

#include <vector>
#include <string>
#include <iostream>
#include "TreeNode.hpp"
#include <optional>
class BinSearchTree{
public:
	BinSearchTree() = default;
	~BinSearchTree();

	//insert word, if present increment count
	void insert(const std::string &word);

	//for convienience, loop over insert(word) for each token
	void bulkInsert(const std::vector<std::string>& words);
	
	//Queries
	[[nodiscard]] bool contains(std::string_view word) const noexcept;
	[[nodiscard]] std::optional<int> countOf(std::string_view word) const noexcept;

	//in order traversel (word-lex order)	
	void inorderCollect(std::vector<std::pair<std::string, int>>& out) const;

	//Metrics
	[[nodiscard]] std::size_t size() const noexcept; //distinct words
	[[nodiscard]] unsigned height() const noexcept;

private:
	TreeNode *root_ = nullptr;

	//Helpers
	void destroy(TreeNode* node) noexcept;
	static TreeNode* insertHelper(TreeNode* node, const std::string& word);
	static const TreeNode* findNode(const TreeNode* node, std::string_view word) noexcept;
	void inorderHelper(const TreeNode* node,
				  std::vector<std::pair<std::string, int>>& out)const;
	std::size_t sizeHelper (const TreeNode* node) const noexcept;
	unsigned heightHelper(const TreeNode* node) const noexcept;
};
#endif
