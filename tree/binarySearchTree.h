// 二分搜索树不一定是完全二叉树
#include <iostream>
#include <queue>
#include <cassert>
using namespace std;
template <typename Key, typename Value>
class BST
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *lchild;
        Node *rchild;
        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            this->lchild = NULL;
            this->rchild = NULL;
        }
        Node(Node *node)
        {
            this->key = node->key;
            this->value = node->value;
            this->lchild = node->lchild;
            this->rchild = node->rchild;
        }
    };
    Node *root;
    int count;

public:
    BST()
    {
        root = NULL;
        count = 0;
    }
    ~BST()
    {
        destroy(root);
    }
    int size()
    {
        return count;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    void insert(Key key, Value value)
    {
        root = insert(root, key, value);
    }
    // 插入的非递归实现
    void insert_v2(Key key, Value value)
    {
        Node *curNode = root;
        Node *parentNode = NULL;
        while (true)
        {
            if (curNode->key == key)
            {
                curNode->value = value;
                return;
            }
            else if (curNode->key > key)
            {
                parentNode = curNode;
                if (parentNode->lchild == NULL)
                {
                    parentNode->lchild = new Node(key, value);
                    return;
                }
                curNode = curNode->lchild;
            }
            else
            {
                parentNode = curNode;
                if (parentNode->lchild == NULL)
                {
                    parentNode->lchild = new Node(key, value);
                    return;
                }
                curNode = curNode->rchild;
            }
        }
    }

    bool contain(Key key)
    {
        return contain(root, key);
    }

    Value *search(Key key)
    {
        return search(root, key);
    }

    // 下面提到的遍历方式都是o（n）复杂度的，n是二叉搜索树节点的数量
    // 二分搜索的中序遍历可以得到从小到大的有序的数列
    // 二分搜索的后序遍历可以用来释放二分搜索树
    void preorder()
    {
        preorder(root);
    }

    // 层序遍历（广度优先遍历）用队列就行
    void levelOrder()
    {
        levelOrder(root);
    }

    // 寻找二叉搜索树中的最小节点，一直向左走就行了
    Key minimum()
    {
        assert(count > 0);
        Node *minNode = minimum(root);
        return minNode->key;
    }

    Key maximum()
    {
        assert(count > 0);
        Node *maxNode = maximum(root);
        return maxNode->key;
    }

    // 删除节点的时间复杂度是O（logn）
    // 删除最小键值所在节点，如果最小节点没有右孩子，则直接删除，如果有右孩子则把右孩子与最小节点的父亲节点连接
    void deleteMin()
    {
        if (root)
            root = deleteMin(root);
    }
    // 删除最大键值所在节点
    void deleteMax()
    {
        if (root)
            root = deleteMax(root);
    }
    // 删除只有一个孩子的节点很简单，把那个单独的孩子连接到父节点就可以了，删除有两个孩子的节点看图示,左子树的
    // 最大值，右子树的最小值代替要删除的节点
    void remove(Key key)
    {
        root = remove(root, key);
    }

private:
    Node *remove(Node *node, Key key)
    {
        if (node = NULL)
            return NULL;
        if (node->key > key)
        {
            node->lchild = remove(node->lchild, key);
        }
        else if (node->key < key)
        {
            node->rchild = remove(node->rchild, key);
        }
        else
        {
            if (node->lchild == NULL)
            {
                Node *ret = node->rchild;
                delete node;
                count--;
                return ret;
            }
            else if (node->rchild == NULL)
            {
                Node *ret = node->lchild;
                delete node;
                count--;
                return ret;
            }
            else
            {
                // 小心下面两步操作使得s失效，因此要给Node结构体另做一个构造函数
                Node *s = new Node(minimum(node->rchild));
                count++;
                s->rchild = deleteMin(node->rchild);
                s->lchild = node->lchild;
                delete node;
                count--;
                return s;
            }
        }
    }
    Node *deleteMax(Node *node)
    {
        if (node->rchild == NULL)
        {
            Node *ret = node->lchild;
            delete node;
            count--;
            return ret;
        }
        node->rchild = deleteMin(node->rchild);
        return node;
    }
    // 删除以node为根的二分搜索树的最小节点，返回新的根节点
    Node *deleteMin(Node *node)
    {
        if (node->lchild == NULL)
        {
            Node *ret = node->rchild;
            delete node;
            count--;
            return ret;
        }
        node->lchild = deleteMin(node->lchild);
        return node;
    }
    Node *maximum(Node *node)
    {
        if (node->rchild == NULL)
            return node;
        return maximum(node->rchild);
    }
    Node *minimum(Node *node)
    {
        if (node->lchild == NULL)
            return node;
        return minimum(node->lchild);
    }
    // 非递归版本
    Node *minimum_v2(Node *node)
    {
        Node *minNode = node;
        while (!minNode->lchild)
            minNode = minNode->lchild;
        return minNode;
    }
    void levelOrder(Node *node)
    {
        queue<Node *> nodeQueue;
        nodeQueue.push(node);
        while (!nodeQueue.empty())
        {
            Node *curNode = nodeQueue.front();
            cout << curNode->Key << endl;
            nodeQueue.pop();
            if (curNode->lchild)
                nodeQueue.push(curNode->lchild);
            if (curNode->rchild)
                nodeQueue.push(curNode->rchild);
        }
    }
    void destroy(Node *node)
    {
        if (node != NULL)
        {
            destroy(node->lchild);
            destroy(node->rchild);
            delete node;
            count--;
        }
    }
    void preorder(Node *node)
    {
        if (node != NULL)
        {
            // 对元素做一些操作
            cout << node->key << end;
            preorder(node->lchild);
            preorder(node->rchild);
        }
    }
    // 以node为根的二叉树中是否包含键值为key的节点
    Value *search(Node *node, Key key)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (node->key == key)
        {
            return &(node->value);
        }
        else if (node->key > key)
        {
            return search(node->lchild, key);
        }
        else
        {
            return search(node->rchild, key);
        }
    }

    // 以node为根的二叉树中是否包含键值为key的节点
    bool contain(Node *node, Key key)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->key == key)
        {
            return true;
        }
        else if (node->key > key)
        {
            return contain(node->lchild, key);
        }
        else
        {
            return insert(node->rchild, key);
        }
    }

    // 向以node为根的二叉搜索树中插入key，value，返回新的二叉搜索树的根
    Node *insert(Node *node, Key key, Value value)
    {
        if (node == NULL)
        {
            count++;
            return new Node(key, value);
        }
        if (node->key == key)
        {
            node->value = value;
        }
        else if (node->key > key)
        {
            node->lchild = insert(node->lchild, key, value);
        }
        else
        {
            node->rchild = insert(node->rchild, key, value);
        }
        return node;
    }
};
// 二分搜索树的顺序性：可以很容易的找到最大值和最小值，也可以很容易的找到一个元素的前驱predecessor和后继successor
//                   可以实现floor（<=）和ceil（>=）函数
//                   可以实现rank（58是排名第几的元素，更改现有数据结构，对每个节点多加一个属性-以该节点为根的
//                   二分搜索树一共有多少个节点，包括根节点）和select（排名第10的元素是谁）函数

// 二分搜索树的局限性:不平衡导致算法的退化
// TODO：平衡二叉树的实现：AVL树
// TODO: trie的实现
// 树形问题：使用递归的一些问题（快速排序，归并排序），搜索问题（八皇后问题）