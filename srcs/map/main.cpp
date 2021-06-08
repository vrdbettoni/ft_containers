#include "tree.hpp"
#include <iostream>

using namespace ft;

void display_tree(AvlTree<int>& tree) {
	std::cout << "--> ";
	AvlIterator<int, false> end = AvlIterator<int, false>(tree.get_max(tree._root));
	AvlIterator<int, false> it = AvlIterator<int, false>(tree.get_min(tree._root));
	++it;
	for (; it != end; ++it)
		std::cout << *it << " ";
	std::cout <<   "   (size: " << tree._size << ")" << std::endl;
}

int main()
{
	AvlTree<int> tree;

	for (int i = 1; i < 4; ++i)
		tree.add_node(i);
	// tree.add_node(1);
	// tree.add_node(2);
	// std::cout << tree._root->data << std::endl;
	// std::cout << tree._root->right->data << std::endl;

	display_tree(tree);
}