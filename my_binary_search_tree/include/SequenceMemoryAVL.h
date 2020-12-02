#pragma once
#include<vector>
#include<array>
#include"FoolAVL.h"
template<class Data>
class SequenceMemoryAVL : public FoolAVL<Data>
{
public:
    using Node = FoolBST<Data>::Node;

    Node* insert(Data data)
    {
        if (!this->root)
        {
            this->root = createNode(data);
            return this->root;
        }

        Node* current = this->root;
        Node* insertPoint = nullptr;
        while (true)
        {
            if (data < current->data)
            {
                if (current->left)
                {
                    current = current->left;
                }
                else
                {
                    current->left = createNode(data, 0, current);
                    insertPoint = current->left;
                    break;
                }
            }
            else
            {
                if (current->right)
                {
                    current = current->right;
                }
                else
                {
                    current->right = createNode(data, 0, current);
                    insertPoint = current->right;
                    break;
                }
            }
        }

        current = insertPoint->parent;
        Node* fixedRoot = nullptr;
        while (current)
        {
            if (current->left)
                current->left = this->fixAVL(current->left);
            if (current->right)
                current->right = this->fixAVL(current->right);
            fixedRoot = current;
            current = current->parent;
        }
        this->root = this->fixAVL(fixedRoot);
        return insertPoint;
    }

    void insert(const std::initializer_list<Data>& initList)
    {
        for (auto& i : initList)
        {
            insert(i);
        }
    }

    ~SequenceMemoryAVL()
    {
        for (auto i : nodesList)
        {
            delete[]i;
        }
    }
private:
    std::vector<Node*> nodesList;
    Node* arrayBegin = nullptr;
    Node* arrayEnd = nullptr;
    Node* currentPos = nullptr;
    std::vector<Node*> emptyLocation;

    Node* createNode(Data data = Data(), int height = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
    {
        if (!emptyLocation.empty())
        {
            Node* location = emptyLocation.back();
            emptyLocation.pop_back();
            location->data = data;
            location->height = height;
            location->parent = parent;
            location->left = left;
            location->right = right;
            return location;
        }
        if (currentPos == arrayEnd)
        {
            auto currentArray = new Node[2048000];
            nodesList.push_back(currentArray);
            arrayBegin = &currentArray[0];
            arrayEnd = &currentArray[2048000 - 1];
            currentPos = arrayBegin + 1;
            arrayBegin->data = data;
            arrayBegin->height = height;
            arrayBegin->parent = parent;
            arrayBegin->left = left;
            arrayBegin->right = right;
            return arrayBegin;
        }
        Node* location = currentPos;
        ++currentPos;
        location->data = data;
        location->height = height;
        location->parent = parent;
        location->left = left;
        location->right = right;
        return location;
    }
};