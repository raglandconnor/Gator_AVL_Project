//
// Created by Connor Ragland on 2/7/24.
//

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
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

    // Left and right children pointers
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    // Root variable and count of nodes
    TreeNode* root;
    int nodeCount = 0;

    // Helper functions
    int nodeHeight(TreeNode* node);
    int getHeight(TreeNode* node);
    int compareID(string ufid1, string ufid2);
    bool identicalName(string name1, string name2);  // T: same name
    string removeQuotations(string name);
    bool validName(string name);
    bool validID(string ufid);  // 1: valid
    bool containsID(TreeNode* node, string ufid);  // T: ufid present in tree
    bool containsName(TreeNode* node, string name);  // T: name present in tree. Could be one or more
    int calculateBalance(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeftRight(TreeNode* node);
    TreeNode* rotateRightLeft(TreeNode* node);
    TreeNode* helperInsert(TreeNode* node, string name, string ufid);
    TreeNode* helperRemoveID(TreeNode* node, string ufid);
    TreeNode* helperRemoveSuccessor(TreeNode* node, string ufid);
    void helperSearchID(TreeNode* node, string ufid);
    void helperSearchName(TreeNode* node, string name);  // Returns false if name is not found
    void helperInorder(TreeNode* node, int& count);
    void vectorInorder(TreeNode* node, vector<string> &ufidVector);
    void helperPreorder(TreeNode* node, int& count);
    void helperPostorder(TreeNode* node, int& count);

    // Helper functions for the command input/parsing
    bool helperSearchCommand(string token);
    vector<string> parseInputs(string commandLine);
    void executeCommands(vector<string> commands);

public:
    // User command input function
    void command(string commandLine);

    // Public functions accessible by the user
    void insert(string name, string ufid);
    void removeID(string ufid);
    void searchID(string ufid);
    void searchName(string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    bool removeInorder(int n);

    AVLTree() : root() {}
};


#endif //GATOR_AVL_PROJECT_AVL_H
