#pragma once
#include<iostream>
#include<functional>

template<class Data>
class FoolBinaryTree
{
public:
    struct BTNode
    {
        Data data;
        BTNode* left, * right;

        BTNode()
        {
            left = nullptr;
            right = nullptr;
        };

        BTNode(Data data) :data(data)
        {
            left = nullptr;
            right = nullptr;
        }

        BTNode(Data data, BTNode* left, BTNode* right)
            :data(data), left(left), right(right)
        {

        }

        void insertLeft(const Data& data)
        {
            if (left != nullptr)
            {
                BTNode* temp = new BTNode(data, left, nullptr);
                left = temp;
            }
            else
            {
                left = new BTNode(data, nullptr, nullptr);
            }
        }

        void insertRight(const Data& data)
        {
            if (right != nullptr)
            {
                BTNode* temp = new BTNode(data, nullptr, right);
                right = temp;
            }
            else
            {
                right = new BTNode(data, nullptr, nullptr);
            }
        }
    };

    FoolBinaryTree()
    {
        root = new BTNode(Data(), nullptr, nullptr);
        endInputFlag = Data();
    }

    ~FoolBinaryTree()
    {
        destroyFunc(root);
    }

    void preOrderTraverse(const std::function<void(Data)>& visit)
    {
        preOrderTraverse(root, visit);
    }

    void inOrderTraverse(const std::function<void(Data)>& visit)
    {
        inOrderTraverse(root, visit);
    }

    void postOrderTraverse(const std::function<void(Data)>& visit)
    {
        postOrderTraverse(root, visit);
    }

    void createBinaryTreeByPreOrder(const std::function<Data()>& input)
    {
        createBinaryTreeByPreOrder(root, input);
    }

    int leafCount()
    {
        return leafCount(root);
    }

    int nodeCount()
    {
        return nodeCount(root);
    }

    int caculateDepth()
    {
        return depth(root);
    }

    void exchangeChildren()
    {
        exchangeChildren(root);
    }

    BTNode* root;
    Data endInputFlag;
private:
    void createBinaryTreeByPreOrder(BTNode*& current, const std::function<Data()>& input)
    {
        Data currentData;
        currentData = input();
        if (currentData == endInputFlag)
        {
            current = nullptr;
            return;
        }
        current = new BTNode(currentData, nullptr, nullptr);
        std::cout << "Please input left child for student: " << current->data << '\n';
        createBinaryTreeByPreOrder(current->left, input);
        std::cout << "Please input right child for student: " << current->data << '\n';
        createBinaryTreeByPreOrder(current->right, input);
    }

    int leafCount(BTNode* current)
    {
        if (!current)
            return 0;
        if (!current->left && !current->right)
            return 1;
        return (leafCount(current->left) + leafCount(current->right));
    }

    int nodeCount(BTNode* current)
    {
        if (!current)
            return 0;
        return (nodeCount(current->left) + nodeCount(current->right)+1);
    }

    void preOrderTraverse(BTNode* current, const std::function<void(Data)>& visit)
    {
        if (current != nullptr)
        {
            visit(current->data);
            preOrderTraverse(current->left, visit);
            preOrderTraverse(current->right, visit);
        }
    }

    void inOrderTraverse(BTNode* current, const std::function<void(Data)>& visit)
    {
        if (current != nullptr)
        {
            inOrderTraverse(current->left, visit);
            visit(current->data);
            inOrderTraverse(current->right, visit);
        }
    }

    void postOrderTraverse(BTNode* current, const std::function<void(Data)>& visit)
    {
        if (current != nullptr)
        {
            postOrderTraverse(current->left, visit);
            postOrderTraverse(current->right, visit);
            visit(current->data);
        }
    }

    int depth(BTNode* current)
    {
        if (!current)
            return 0;
        int h1 = depth(current->left);
        int h2 = depth(current->right);
        if (h1 > h2)
            return h1 + 1;
        else
            return h2 + 1;
    }

    void destroyFunc(BTNode* current)
    {
        if (current)
        {
            destroyFunc(current->left);
            destroyFunc(current->right);
            delete current;
        }
    }

    void exchangeChildren(BTNode* current)
    {
        if (current)
        {
            BTNode* temp;
            exchangeChildren(current->left);
            exchangeChildren(current->right);
            temp = current->left;
            current->left = current->right;
            current->right = temp;
        }
    }
};