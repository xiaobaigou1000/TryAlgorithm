#pragma once
#include<functional>
#include<ostream>
#include<initializer_list>
#include<iomanip>

template<class Data>
class FoolBST
{
public:
    using value_type = typename Data;

    struct Node
    {
        Data data;
        int height;
        Node* parent;
        Node* left;
        Node* right;

        Node(Data data = Data(), int height = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            :data(data), height(height), parent(parent), left(left), right(right)
        {

        }
    };

    Node* root = nullptr;

    Data min()
    {
        Node* current = root;
        while (current->left)
        {
            current = current->left;
        }
        return current->data;
    }

    Data max()
    {
        Node* current = root;
        while (current->right)
        {
            current = current->right;
        }
        return current->data;
    }

    Node* insert(Data data)
    {
        if (!root)
        {
            root = new Node(data, 0, nullptr);
            return root;
        }
        Node* insertPoint = insertWithoutHeightCorrection(data);
        Node* current = insertPoint->parent;
        while (current)
        {
            current->height = caculateAVLHeight(current);
            current = current->parent;
        }
        return insertPoint;
    }

    void insert(const std::initializer_list<Data>& initList)
    {
        for (auto& i : initList)
        {
            insert(i);
        }
    }

    void inOrderTraverse(const std::function<void(Data)>& visit)
    {
        inOrderTraverse(root, visit);
    }

    friend std::ostream& operator<<(std::ostream& out, FoolBST<Data>& toPrint)
    {
        int count = 0;

        toPrint.inOrderTraverse(toPrint.root, [&count, &out](Data data)
            {
                out << std::setw(13) << data;
                ++count;
                if (count % 10 == 0)
                {
                    out << '\n';
                }
            });
        return out;
    }

    //~FoolBST()
    //{
    //    clear(root);
    //    delete root;
    //}
    void clear(Node* current)
    {
        if (current->left)
        {
            clear(current->left);
        }
        if (current->right)
        {
            clear(current->right);
        }
        delete current;
    }
protected:
    inline Node* insertWithoutHeightCorrection(Data data)
    {
        Node* current = root;
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
                    current->left = new Node(data, 0, current);
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
                    current->right = new Node(data, 0, current);
                    insertPoint = current->right;
                    break;
                }
            }
        }
        return insertPoint;
    }

    inline static int nodeHeight(Node* current)
    {
        if (!current)
            return -1;
        else
            return current->height;
    }

    inline static int caculateAVLHeight(Node* current)
    {
        int height = nodeHeight(current->left) > nodeHeight(current->right) ? nodeHeight(current->left) : nodeHeight(current->right);
        ++height;
        return height;
    }

    void inOrderTraverse(Node* current, const std::function<void(Data)>& visit)
    {
        if (!current)
            return;
        inOrderTraverse(current->left, visit);
        visit(current->data);
        inOrderTraverse(current->right, visit);
    }
};
