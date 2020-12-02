#pragma once
#include"FoolBST.h"

template<class Data>
class FoolAVL :public FoolBST<Data>
{
public:
    using Node = FoolBST<Data>::Node;

    Node* insert(Data data)
    {
        if (!this->root)
        {
            this->root = new Node(data, 0, nullptr);
            return this->root;
        }
        Node* insertPoint = this->insertWithoutHeightCorrection(data);
        Node* current = insertPoint->parent;
        Node* fixedRoot = nullptr;
        while (current)
        {
            if (current->left)
                current->left = fixAVL(current->left);
            if (current->right)
                current->right = fixAVL(current->right);
            fixedRoot = current;
            current = current->parent;
        }
        this->root = fixAVL(fixedRoot);
        return insertPoint;
    }

    void insert(const std::initializer_list<Data>& initList)
    {
        for (auto& i : initList)
        {
            insert(i);
        }
    }
protected:
    inline static Node* fixAVL(Node* current)
    {
        if (testAVL(current) < -1)
        {
            if (testAVL(current->right) < 0)
            {
                current = leftRotate(current);
            }
            else
            {
                current->right = rightRotate(current->right);
                current = leftRotate(current);
            }
        }
        else if (testAVL(current) > 1)
        {
            if (testAVL(current->left) > 0)
            {
                current = rightRotate(current);
            }
            else
            {
                current->left = leftRotate(current->left);
                current = rightRotate(current);
            }
        }
        else
        {
            current->height = FoolBST<Data>::caculateAVLHeight(current);
        }
        return current;
    }

    inline static int testAVL(Node* current)
    {
        return FoolBST<Data>::nodeHeight(current->left) - FoolBST<Data>::nodeHeight(current->right);
    }

    inline static Node* leftRotate(Node* toRotate)
    {
        Node* right = toRotate->right;
        toRotate->right = right->left;
        right->left = toRotate;
        right->parent = toRotate->parent;
        toRotate->parent = right;
        toRotate->height = FoolBST<Data>::caculateAVLHeight(toRotate);
        right->height = FoolBST<Data>::caculateAVLHeight(right);
        return right;
    }

    inline static Node* rightRotate(Node* toRotate)
    {
        Node* left = toRotate->left;
        toRotate->left = left->right;
        left->right = toRotate;
        left->parent = toRotate->parent;
        toRotate->parent = left;
        toRotate->height = FoolBST<Data>::caculateAVLHeight(toRotate);
        left->height = FoolBST<Data>::caculateAVLHeight(left);
        return left;
    }
};