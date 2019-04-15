/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@date: 2019-04-14
@email: fetaxyu@gmail.com
==============================================================================*/

#ifndef CODESPOT_CORE_MERKLETREE_H_
#define CODESPOT_CORE_MERKLETREE_H_

#include <vector>
#include <string>

#include "codespot/tools/cryptography.h"

namespace codespot {


typedef struct TreeNode {
    std::string name;
    std::string hash;
    std::string data;
    struct TreeNode* left, * right;

    TreeNode();
    TreeNode(std::string&);

}TreeNode;



class MerkleTree {
public:
    MerkleTree();
    ~MerkleTree();

    void CreateMerkleTree(std::vector<std::string>&);

    const std::vector<TreeNode*> getList();
    TreeNode getRoot();

private:

    TreeNode* CreateNode(TreeNode*, TreeNode*);

    std::vector<TreeNode*> list;
    TreeNode root;

};

} // end namespace codespot

#endif // !CODESPOT_CORE_MERKLETREE_H_
