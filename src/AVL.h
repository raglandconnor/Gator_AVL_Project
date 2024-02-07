//
// Created by Connor Ragland on 2/7/24.
//

#include <iostream>
#include <string>
using namespace std;

#ifndef GATOR_AVL_PROJECT_AVL_H
#define GATOR_AVL_PROJECT_AVL_H

/*
 * Part of my TreeNode struct and AVL Tree class was referenced from the given wrapped BST example:
 * https://www.onlinegdb.com/vWp_hhaQlC
 */

struct TreeNode {
    string name;
    string ufid;

    int height = 0;

    TreeNode* left;
    TreeNode* right;
    TreeNode(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    int max(int a, int b);
    int getHeight(TreeNode* node);
    int compareID(string ufid1, string ufid2);
//    string validName(string name);

    TreeNode* helperInsert(TreeNode* node, string name, string ufid);
    void helperInorder(TreeNode* node);

public:
    TreeNode* root;
    void insert(string name, string ufid);
    AVLTree() : root() {}
    void inorder();

};


#endif //GATOR_AVL_PROJECT_AVL_H
