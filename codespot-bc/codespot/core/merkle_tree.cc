/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-14
==============================================================================*/


#include <algorithm>
#include <iostream>

#include "codespot/core/merkle_tree.h"

namespace codespot {

TreeNode::TreeNode() : left(nullptr), right(nullptr) {}

TreeNode::TreeNode(std::string& data) : TreeNode() {
    this->data = data;
    this->hash = SHA_256(data);
    this->name = "[Node: " + data + "]";
}

TreeNode::~TreeNode() {}

void TreeNode::setName(std::string& name) {
    this->name = name;
}
std::string TreeNode::getName() {
    return this->name;
}

void TreeNode::setHash(std::string& hash) {
    this->hash = hash;
}

std::string TreeNode::getHash() {
    return this->hash;
}

void TreeNode::setData(std::string& data) {
    this->data = data;
}

std::string TreeNode::getData() {
    return this->data;
}
void TreeNode::setLeft(TreeNode* left) {
    this->left = left;
}

TreeNode* TreeNode::getLeft() {
    return this->left;
}

void TreeNode::setRight(TreeNode* right) {
    this->right = right;
}

TreeNode* TreeNode::getRight() {
    return this->right;
}

MerkleTree::MerkleTree() {}
MerkleTree::~MerkleTree() {}

void MerkleTree::createMerkleTree(std::vector<std::string>& contents) {
    std::vector<TreeNode> leafList = createLeafList(contents);
    std::vector<TreeNode> parents = createParentList(leafList);
    list.insert(list.end(), leafList.begin(), leafList.end());
    list.insert(list.end(), parents.begin(), parents.end());
    while (parents.size() > 1) {
        std::vector<TreeNode> temp = createParentList(parents);
        list.insert(list.end(), temp.begin(), temp.end());
        parents = temp;
    }
    root = list[list.size() - 1];
}

const std::vector<TreeNode> MerkleTree::getList() {
    return this->list;
}

TreeNode MerkleTree::getRoot() {
    return this->root;
}


std::vector<TreeNode> MerkleTree::createParentList(std::vector<TreeNode>& leafList) {
    std::vector<TreeNode> parents;
    int len = leafList.size();
    for (int i = 0; i < len - 1; i += 2) {
        TreeNode node = createParentNode(&leafList[i], &leafList[i + 1]);
        parents.push_back(node);
    }
    if ((len & 0x1) == 1) {
        TreeNode* nil = new TreeNode;
        std::string name = "NIL";
        nil->setName(name);
        TreeNode parent = createParentNode(&leafList[len - 1], nil);
        parents.push_back(parent);
    }
    return parents;
}

TreeNode MerkleTree::createParentNode(TreeNode* left, TreeNode* right) {
    TreeNode* parent = new TreeNode;
    std::cout << left << std::endl;
    parent->setLeft(left);
    parent->setRight(right);
    std::string hash = left->getHash();
    if (!right->getHash().empty()) {
        std::string h = left->getHash() + right->getHash();
        hash = SHA_256(h);
    }
    parent->setData(hash);
    parent->setHash(hash);
    std::string name = "[Parent of " + left->getName() + " and " + right->getName() + "]";
    parent->setName(name);
    return *parent;
}

std::vector<TreeNode> MerkleTree::createLeafList(std::vector<std::string>& contents) {
    std::vector<TreeNode> leafList;
    for (std::string content : contents) {
        TreeNode *node = new TreeNode(content);
        leafList.push_back(*node);
    }
    return leafList;
}



} // end namespace codespot