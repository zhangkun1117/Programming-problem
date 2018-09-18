/**
 * 二叉树的层次遍历，分为bfs和dfs
 * /
 **/


#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct BinaryTree {
    int val;
    BinaryTree *left;
    BinaryTree *right;
    BinaryTree(int value)
        : val(value), left(nullptr), right(nullptr) { }
};

//广度优先遍历
void levelOrder(BinaryTree *root) {
    if (root == nullptr)
        return;

    queue<BinaryTree*> que;
    que.push(root);
    while (!que.empty()) {
        BinaryTree *front = que.front();
        cout << front->val << " ";
        que.pop();
        if (front->left != nullptr)
            que.push(front->left);
        if (front->right != nullptr)
            que.push(front->right);
    }
}
//深度优先遍历
// 用堆实现
void depthFirstSearch(BinaryTree* root){
    stack<BinaryTree*> nodeStack;  //使用C++的STL标准模板库
    nodeStack.push(root);
    BinaryTree* node;
    while(!nodeStack.empty()){
	    node = nodeStack.top();
		cout<<node->val;//遍历根结点
        nodeStack.pop();
        if(node->right){
            nodeStack.push(node->right);  //先将右子树压栈
        }
        if(node->left){
            nodeStack.push(node->left);  //再将左子树压栈
        }
    }
}
//求二叉树的深度
int treeDepth(BinaryTree* root) {
    if (root == nullptr) return 0;

    int depth = 0;
    queue<BinaryTree*> que;
    que.push(root);
    while (!que.empty()) {
        depth++;
        int count = 0;
        int size = que.size();

        while (count < size) { //弹出当前层的所有节点
            BinaryTree *front = que.front();
            que.pop();
            count++;
            if (front->left)
                que.push(front->left);
            if (front->right)
                que.push(front->right);
        }
    }

    return depth;
}
/**
 * 二叉树前序遍历 中序遍历  后序遍历 
 * */
//递归实现 
void preorder_recursion(BinaryTree* t){
    if(t){
        printf("%c ",t->val);
        preorder_recursion(t->left);
        preorder_recursion(t->right);
    }
}
//前序非递归
void PreOrderDev(BinaryTree *root)
{
    if(root == nullptr)
    {
        cout <<"The tree is NULL..." <<endl;
        return ;
    }
    stack<BinaryTree *> nstack;
    BinaryTree *node = root;

    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty( ) != true)
    {
        //  输出当前子树的根节点，然后递归直至最左
        while(node != NULL)
        {
            cout <<node->val;
            nstack.push(node);
            node = node->left;
        }
        //  此时循环结束时，当前栈顶节点已经是最左节点
        //  此时递归开始返回，开始出栈，并输出节点的右节点
        if(!nstack.empty())
        {
            node = nstack.top( );
            nstack.pop( );
            node = node->right;
        }
    }
}
//中序非递归
void InOrderDev(BinaryTree *root)
{
    if(root == nullptr)
    {
        cout <<"The tree is NULL..." <<endl;
        return ;
    }
    stack<BinaryTree *> nstack;
    BinaryTree *node = root;
    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty() != true)
    {
        // 不输出当前根节点，但是递归直至当前根节点node的最左端
        while(node != NULL)
        {
            nstack.push(node);
            node = node->left;
        }
        //  此时栈顶的元素是当前最左元素
        //  它应该被输出
        if(!nstack.empty())
        {
            node = nstack.top();
            cout <<node->val;
            nstack.pop( );
            node = node->right;
        }
    }
}
//后序非递归
struct BinaryTree {
    int val;
    int isFirst;
    BinaryTree *left;
    BinaryTree *right;
    BinaryTree(int value)
        : val(value), left(nullptr), right(nullptr) { }
};
void PostOrderDev(BinaryTree *root)
{
    if(root == NULL)
    {
       cout <<"The tree is NULL..." <<endl;
       return ;
    }
    stack<BinaryTree *> nstack;
    BinaryTree *node = root;
    while(node != NULL || nstack.empty( ) != true)
    {
        //  遍历直至最左节点
        while(node != NULL)
        {
            node->isFirst = 1;       // 当前节点首次被访问
            nstack.push(node);
            node = node->left;
        }
        if(nstack.empty() != true)
        {
            node = nstack.top( );
            nstack.pop( );
            if(node->isFirst == 1)   // 第一次出现在栈顶
            {

                node->isFirst++;
                nstack.push(node);

                node = node->right;
            }
            else if(node->isFirst == 2)
            {
                cout <<node->val;
                node = NULL;
            }
        }
    }
}