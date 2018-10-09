/**
 * 若要把二叉搜索树转换为排序的双向链表，只需中序遍历树中的每个结点，
 * 遍历的过程中始终保存已生成链表的最右端结点，当遍历父亲结点的时候
 * 将父亲结点加入到左子树生成的链表的最右端结点的后面，接着再遍历父亲结点的右
 * 子树，整个遍历完成后的最右端结点即是链表的最右端结点
 * */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(nullptr), right(nullptr) {
    }
};
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode *pLastNodeInList = nullptr;
        Convert(pRootOfTree, &pLastNodeInList);

        while(pLastNodeInList && pLastNodeInList->left)
            pLastNodeInList = pLastNodeInList->left;
        return pLastNodeInList;
    }
    void Convert(TreeNode *pNode, TreeNode **pLastNodeInList) {
        if(!pNode)
            return;

        if(pNode->left)
            Convert(pNode->left, pLastNodeInList);

        pNode->left = *pLastNodeInList;
        if(*pLastNodeInList) //可能为NULL
            (*pLastNodeInList)->right = pNode;
        *pLastNodeInList = pNode;

        if(pNode->right)
            Convert(pNode->right, pLastNodeInList);
    }
};
/**若要把一般二叉树转换为单链表结构，只需后序遍历每个结
 * 点，在遍历父亲结点的时候将左子树形成的链表插入到父亲结点和右子树形成的链表中间
 * */
class SolutionSingalList {
public:
    void flatten(TreeNode* root) {
        if(!root) return;

        flatten(root->left);
        flatten(root->right);

        if(!root->left) return;

        TreeNode *pNode = root->left; //将左子树生成的链表插入到root与root->right中间
        while(!pNode->right) //得到左子树生成的链表的最右端结点
            pNode = pNode->right;
        pNode->right = root->right;
        root->right = root->left;
        root->left = nullptr; //NULL root root->left pNode->right root->right
    }
};