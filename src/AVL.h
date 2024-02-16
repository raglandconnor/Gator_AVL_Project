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

    int height = 1;  // One-based height

    TreeNode* left;
    TreeNode* right;
    TreeNode(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    TreeNode* root;
    int nodeHeight(TreeNode* node);
    int getHeight(TreeNode* node);
    int compareID(string ufid1, string ufid2);
    string removeQuotations(string name);
    bool validName(string name);
    bool validID(string ufid);  // 1: valid
    bool containsID(TreeNode* node, string ufid);  // T: ufid present in tree
    int calculateBalance(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeftRight(TreeNode* node);
    TreeNode* rotateRightLeft(TreeNode* node);

    TreeNode* helperInsert(TreeNode* node, string name, string ufid);
    TreeNode* helperRemoveID(TreeNode* node, string ufid);
    void helperSearchID(TreeNode* node, string ufid);
//    void helperSearchName(TreeNode* node, string name);
    void helperInorder(TreeNode* node);
    void helperPreorder(TreeNode* node);
    void helperPostorder(TreeNode* node);
//    void helperRemoveInorder(TreeNode* node, int &n);

public:
    void insert(string name, string ufid);
    void removeID(string ufid);
    void searchID(string ufid);
//    void searchName(string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);

    AVLTree() : root() {}



};


#endif //GATOR_AVL_PROJECT_AVL_H
