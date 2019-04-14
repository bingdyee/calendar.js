/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-14
==============================================================================*/

#ifndef CODESPOT_CORE_MERKLETREE_H_
#define CODESPOT_CORE_MERKLETREE_H_

#include <vector>
#include <string>

#include "codespot/tools/cryptography.h"

namespace codespot {

class TreeNode {
public:
    TreeNode();
    TreeNode(std::string&);
    ~TreeNode();

    void setName(std::string&);
    std::string getName();
    void setHash(std::string&);
    std::string getHash();
    void setData(std::string&);
    std::string getData();
    void setLeft(TreeNode*);
    TreeNode* getLeft();
    void setRight(TreeNode*);
    TreeNode* getRight();

private:
    std::string name;
    std::string hash;
    std::string data;
    TreeNode* left;
    TreeNode* right;

};

class MerkleTree {
public:
    MerkleTree();
    ~MerkleTree();

    void createMerkleTree(std::vector<std::string>&);

    const std::vector<TreeNode> getList();
    TreeNode getRoot();

private:

    std::vector<TreeNode> createParentList(std::vector<TreeNode>&);
    TreeNode createParentNode(TreeNode*, TreeNode*);
    std::vector<TreeNode> createLeafList(std::vector<std::string>&);

    std::vector<TreeNode> list;
    TreeNode root;

};

} // end namespace codespot

#endif // !CODESPOT_CORE_MERKLETREE_H_
