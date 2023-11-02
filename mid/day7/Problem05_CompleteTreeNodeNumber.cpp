/*求完全二叉树节点的个数*/
class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int date){
        this->value=date;
        this->left=nullptr;
        this->right=nullptr;
    }
};
//最左子树的深度
int mostleftLevel(Node* node,int level){
    while(node!=nullptr){
        level++;
        node=node->left;
    }
    return level-1;
}
//计算给定二叉树中从第 l 层到第 h 层的节点数量。
/*
首先，如果 l 和 h 相等，即只计算单一层的节点数量，这表示只有根节点，因此返回1。

否则，首先检查右子树的最左叶子节点所在的层数是否等于 h - 1，
如果是，说明右子树是一个高度为 h - 1 的完全二叉树，可以通过位运算 (1 << (h - l)) 计算其节点数量，
然后递归计算右子树的节点数量（起始层 l 变为 l + 1，结束层 h 保持不变）。

如果右子树的最左叶子节点所在的层数不等于 h - 1，则说明左子树是一个高度为 h - 1 的完全二叉树，
可以通过位运算 (1 << (h - l - 1)) 计算其节点数量，然后递归计算左子树的节点数量（起始层 l 变为 l + 1，结束层 h 保持不变）。
*/
/*
完全二叉树的条件是：

所有的叶子节点（最底层的节点）都集中在树的最左边。
除了最底层，其他每一层的节点都必须是满的，即每一层的节点数都达到最大值。
这意味着在完全二叉树中，从根节点到倒数第二层的节点都是满的，最后一层的节点尽量集中在最左边，但最后一层的节点数可以少于最大值。
*/
int bs(Node* node,int l,int h){
    if(l==h){
        return 1;
    }
	if (mostleftLevel(node->right, l + 1) == h) {
		return (1 << (h - l)) + bs(node->right, l + 1, h);
	} else {
		return (1 << (h - l - 1)) + bs(node->left, l + 1, h);
	}
}

int nodeNum(Node* head){
    if(head==nullptr){
        return 0;
    }
    return bs(head,1,mostleftLevel(head,1));
}
