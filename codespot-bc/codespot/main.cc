/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

Eigen/grpc/Crypto++

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-11
==============================================================================*/

#include <iostream>
#include <thread>

#include "codespot/core/merkle_tree.h"

using namespace std;
using namespace codespot;


int main(int args, char** argv) {
	std::string data = "I work for smarter cybersecurity with machine learning.";
    std::vector<std::string> contents = {"BlockChain", "AI", "Machine Learning", "Deep Learning"};

    MerkleTree tree;
    tree.createMerkleTree(contents);
    std::vector<TreeNode> list = tree.getList();
    for (TreeNode node : list) {
        std::cout << node.getName() << ": " << node.getHash() << std::endl;
    }
    TreeNode root = tree.getRoot();
    std::cout << "Root Name: " << root.getName() << std::endl;
    TreeNode *left = root.getLeft();
    std::cout << "Root Hash: " << left->getName() << std::endl;
	system("pause");
	return 0;
}