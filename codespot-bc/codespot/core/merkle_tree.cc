/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@date: 2019-04-14
@email: fetaxyu@gmail.com
==============================================================================*/


#include <algorithm>
#include <iostream>

#include "codespot/core/merkle_tree.h"

namespace codespot {

TreeNode::TreeNode() : left(nullptr), right(nullptr) {}

TreeNode::TreeNode(std::string& data) : TreeNode() {
    this->data = data;
    this->hash = SHA_256(data);
    this->name = std::string("[Node: " + data + "]");
}

MerkleTree::MerkleTree() {}
MerkleTree::~MerkleTree() {
    while (!list.empty()) {
        delete list.back(), list.pop_back();
    }
}

void MerkleTree::CreateMerkleTree(std::vector<std::string>& contents) {
    for (std::string content : contents) {
        list.push_back(new TreeNode(content));
    }
    size_t size = contents.size();
    while (size > 1) {
        int begin = list.size() - size, end = begin + size, len = 0;
        for (size_t i = begin; i < end; i += 2) {
            if (i + 1 >= size) {
                list.push_back(CreateNode(list[i], nullptr));
            } else {
                list.push_back(CreateNode(list[i], list[i + 1]));
            }
            ++len;
        }
        size = len;
    }
}

TreeNode* MerkleTree::CreateNode(TreeNode* left, TreeNode* right) {
    TreeNode* node = new TreeNode;
    std::string th = left->hash;
    if (right != nullptr) {
        th = left->hash + right->hash;
        node->name = "[Parent of " + left->name + " and " + right->name + "]";
    } else {
        node->name = "[Parent of " + left->name + " and NIL node]";
    }
    node->hash = SHA_256(th);
    node->left = left;
    node->right = right;
    return node;
}


const std::vector<TreeNode*> MerkleTree::getList() {
    return this->list;
}

TreeNode MerkleTree::getRoot() {
    return this->root;
}
 /*

std::vector<TreeNode> MerkleTree::createParentList(std::vector<TreeNode>& leafList) {
    std::vector<TreeNode> parents;
    size_t len = leafList.size();
    for (int i = 0; i < len - 1; i += 2) {
        TreeNode node = createParentNode(leafList[i], leafList[i + 1]);
        parents.push_back(node);
    }
    if ((len & 0x1) == 1) {
        TreeNode nil;
        nil.name = "NIL";
        TreeNode parent = createParentNode(leafList[len - 1], nil);
        parents.push_back(parent);
    }
    return parents;
}

TreeNode MerkleTree::createParentNode(TreeNode& left, TreeNode& right) {
    TreeNode parent;
    parent.left = &left;
    parent.right = &right;
    std::string hash = left.hash;
    if (!right.hash.empty()) {
        std::string h(left.hash + right.hash);
        hash = SHA_256(h);
    }
    parent.data = hash;
    parent.hash = hash;
    parent.name = "[Parent of " + left.name + " and " + right.name + "]";
    return parent;
}

std::vector<TreeNode> MerkleTree::createLeafList(std::vector<std::string>& contents) {
    std::vector<TreeNode> leafList(contents.size());
    for (int i = 0; i < contents.size(); ++i) {
        leafList[i] = TreeNode(contents[i]);
    }
    return leafList;
}

*/

} // end namespace codespot