#pragma once

class Node {
    private:
        int value;
        Node* leftChild;
        Node* rightChild;
    
    public:
        Node(int v) {
            value = v;
        }
        ~Node() {
            delete leftChild;
            delete rightChild;
        }
        Node* getLeft() {
            return leftChild;
        };
        Node* getRight() {
            return rightChild;
        };
        int getValue() {
            return value;
        };
        bool setLeft(int v) {
            leftChild = new Node(v);
            return true;
        };
        bool setRight(int v) {
            rightChild = new Node(v);
            return true;
        };
};

class BinaryTree {
    private:
        Node* root;
    
    public:
        BinaryTree(int v) {
            root = new Node(v);
        };
        ~BinaryTree() {
            delete root;
        };
        Node* getRoot() {
            return root;
        };
};