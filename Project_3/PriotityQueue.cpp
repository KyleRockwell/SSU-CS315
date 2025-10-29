#include"PriorityQueue.hpp"
#include<iomanip>
#include<iostream>
PriorityQueue::PriorityQueue(std::vector<TreeNode*> nodes){
	for(size_t i = 0; i < nodes.size(); i++){
		insert(nodes[i]);
	}
}
PriorityQueue::PriorityQueue(std::vector<std::pair<std::string, int>> freq_list){
	for(size_t i = 0;i < freq_list.size(); i++){
		TreeNode *node = new TreeNode(std::get<std::string>(freq_list.at(i)),
			       	std::get<int>(freq_list.at(i)));
		insert(node);
	}
}
	
std::size_t PriorityQueue::size() const noexcept{
	return items_.size();
}
bool PriorityQueue::empty()const noexcept{
	return items_.size() == 0;
}

TreeNode* PriorityQueue::findMin()const noexcept{
	if(items_.size() > 0)
		return items_.back();
	return nullptr;
}
TreeNode* PriorityQueue::extractMin()noexcept{
	if(items_.size() > 0){
		auto end = items_.back();
		items_.pop_back();
		return end;
	}
	return nullptr;

}
void PriorityQueue::deleteMin()noexcept{
	if(items_.size() > 0)
		items_.pop_back();	
}
void PriorityQueue::insert(TreeNode* node){
	if(items_.size() == 0){
		items_.push_back(node);
	}
	else{

		int i = items_.size()-1;	
		items_.push_back(node);
		auto temp = node;
		while(i>= 0 && higherPriority(node, items_.at(i) )){
			temp = items_[i];
			items_[i] = items_[i+1];
			items_[i+1] = temp;
			i--;
		}
	}


	

}
void PriorityQueue::print(std::ostream& os )const{
	for(size_t i = 0; i< items_.size(); i++){

		os<<std::setw(10)<< items_.at(i)->freq() << " "  << items_.at(i)->value() <<"\n";
	}	
}

bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept{
		
	if(a->freq() != b->freq())
		return a->freq() > b->freq();
	return a->value() < b->value();
}

bool PriorityQueue::isSorted() const{
	for (size_t i = 0; i < items_.size() - 1; i++){
		if(higherPriority(items_.at(i+1), items_.at(i)))
					return false;
	}
	 return true;
}

