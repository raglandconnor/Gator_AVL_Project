//
// Created by Connor Ragland on 2/7/24.
//

#include "AVL.h"

int AVLTree::max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int AVLTree::getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::compareID(string ufid1, string ufid2) {
    // < 0 : ufid1 < ufid2
    // = 0 : ufid1 = ufid2
    // > 0 : ufid1 > ufid2
    return ufid1.compare(ufid2);
}

TreeNode* AVLTree::helperInsert(TreeNode* node, string name, string ufid) {
    //TODO: Check if name is valid?
    //TODO: Check if ufid is unique (name too?)
//    if (ufid.length() != 8) {
//        cout << "Unsuccessful" << endl;
//    }
//    else { //TODO: Check if letters and remove quotations
//
//    }

    if (node == nullptr) {
        return new TreeNode(name, ufid);
    }
    else if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
        node->left = helperInsert(node->left, name, ufid);
    }
//    else if (compareID(ufid, node->ufid) == 0) {  // = 0 : ufid1 = ufid2
//        cout << "Unsuccessful" << endl;
//    }
    else {  // > 0 : ufid1 > ufid2
        node->right = helperInsert(node->right, name, ufid);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));  // Referenced from lecture slides

    //TODO: balance

    cout << "Successful" << endl;
    return node;
}

void AVLTree::helperInorder(TreeNode *node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperInorder(node->left);
        cout << node->name << " ";
        helperInorder(node->right);
    }
}

void AVLTree::insert(string name, string ufid) {
    this->root = helperInsert(this->root, name, ufid);
}

void AVLTree::inorder() {
    helperInorder(this->root);
}