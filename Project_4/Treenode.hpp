//
// Created by Ali Kooshesh on 10/1/25.
// modified to fit Huffman Tree Project by Kyle Rockwell

#ifndef BINSEARCHTREESTUDENTFILES_TREENODE_HPP
#define BINSEARCHTREESTUDENTFILES_TREENODE_HPP
#include <string>
class TreeNode {
public:
    TreeNode(std::string n): left(nullptr), right(nullptr), word(n), count(1) {}
    TreeNode(std::string str, int freq): left(nullptr), right(nullptr), word(str), count(freq) {}
    ~TreeNode() {
        leftSubtree(nullptr);
        rightSubtree(nullptr);
    }

    TreeNode *leftSubtree() const { return left; }
    TreeNode *rightSubtree() const { return right; }
    std::string value()const {return word;}
    void value(std::string value) {word = value;}
    void leftSubtree( TreeNode *newLeft ) { left = newLeft; }
    void rightSubtree(TreeNode *newRight) { right = newRight; }
    void countUp() {this->count+= 1;}
    int freq()const{ return count; }
    
private:
    TreeNode *left, *right;
    
    std::string word;
    int count;
};

#endif //BINSEARCHTREESTUDENTFILES_TREENODE_HPP

