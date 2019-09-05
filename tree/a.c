/*
            1
           / \
           2   3 
         /  
         4  
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *l_child, *r_child;
}node_t, *pnode_t;

typedef void (*visit_node_t)(node_t *node);

typedef struct tree {
    node_t *root;
    visit_node_t visit_node;
}tree_t;

//二叉树初始化
void tree_init(tree_t *tree, visit_node_t fun)
{   
    tree->root = NULL;
    tree->visit_node = fun;
}

//二叉树销毁
void tree_destory(tree_t *tree)
{   
    //释放所有的节点的内存空间
    

    if (tree->root == NULL) {
        return NULL;
    }

    tree_clear(tree, tree->root);

    tree->root = NULL;
}

//在某个父节点插入节点，原来的左孩子和右孩子变为右边子树
void tree_insert_node(tree_t *tree, node_t *node_parent, node_t *node, int is_left)
{   
    
    if (tree == NULL){
        return;
    }
    
    if (node == NULL){
        return;
    }
     
    //空树
    if (tree->root == NULL) {
        tree->root = node;
        return;
    } 

    if (node_parent == NULL){
        return;
    }
     
    //插入左子树或者右子树
    if (is_left) {
        
        //右子树存在，直接将原来节点挂载当前节点的右边字树上
        node_t *old_node = node_parent->l_child;
        
        node_parent->l_child = node ;
        printf("inster left:%x\n", node);
        if (old_node) {
            node->r_child = old_node;
        }

    } else {
           //右子树存在，直接将原来节点挂载当前节点的右边字树上
        node_t *old_node = node_parent->r_child;
        
        node_parent->r_child = node ;
         printf("inster right:%x\n", node);   
        if (old_node) {
            node->r_child = old_node;
        }
    }
}

//返回二叉树的根节点
node_t * tree_root_get(tree_t *tree)
{
    return tree->root;
}

//清空树
void tree_clear(tree_t *tree, node_t *node)
{   
   
	if (node == NULL)
	{   
        //递归出口
		return;
	}

	//递归清空左子树
	tree_clear(tree, node->l_child);

	//递归清空右子树
	tree_clear(tree, node->r_child);


	node->l_child = NULL;
	node->r_child = NULL;

	if (node == tree->root)
	{
		tree->root = NULL;
	}
    
    printf("clear node:0x%x\n", node);
	//释放当前节点内存
	free(node);
}

//根据值查找节点
int tree_find_node(tree_t *tree, node_t *node, node_t **node_find, int value)
{
    if (tree == NULL){
        return -1;
    } 
    
    //退出递归
    if (node == NULL) {
        return -1;   
    }

    if(node->value == value) {
        printf("find out1\n");
        *node_find = node;
        return 0;
    } 
    
    //递归查找左孩子
    if ( 0 == tree_find_node(tree, node->l_child, node_find, value) ) {
        printf("find out2\n");
        return 0;
    }
    
    //递归查找右孩子
    if ( 0 == tree_find_node(tree, node->r_child, node_find, value) ) {
        printf("find out3\n");
        return 0;
    }

    return -1;
}

//先序遍历
void tree_prev_order_visit(tree_t *tree, node_t *node)
{   
    //退出递归
    if (node == NULL) {
        return;
    }
    
    //中
    tree->visit_node(node);

    //左
    tree_prev_order_visit(tree, node->l_child);
    
    //右
    tree_prev_order_visit(tree, node->r_child);
}


//中序遍历
void tree_in_order_visit(tree_t *tree, node_t *node)
{   
    //退出递归
    if (node == NULL) {
        return;
    }
    
    //左
    tree_in_order_visit(tree, node->l_child);

    //中
    tree->visit_node(node);
    
    //右
    tree_in_order_visit(tree, node->r_child);
}

//后序遍历
void tree_post_order_visit(tree_t *tree, node_t *node)
{   
    //退出递归
    if (node == NULL) {
        return;
    }
 
    //左
    tree_post_order_visit(tree, node->l_child);
    
    //右
    tree_post_order_visit(tree, node->r_child);

    //中 
    tree->visit_node(node);
}

void visit_node(int *data)
{
    printf("data: %d\n", *data);
}


#define NODE_NUM_MAX 3
#define LEFT_CHILD         1
#define RIGHT_CHILD        0

int main(int argc, char **argv)
{   
    // 初始化二叉树
    tree_t  tree;
    tree_init(&tree, visit_node); 
     
    /*
            1
           / \ 
          2   3
               \
                4 
    */
    //分配3个节点
    node_t *node1 = (node_t *) malloc(sizeof(node_t));
    node_t *node2 = (node_t *) malloc(sizeof(node_t));
    node_t *node3 = (node_t *) malloc(sizeof(node_t));
    node_t *node4 = (node_t *) malloc(sizeof(node_t));
    if (!node1) {
        goto error;
    }
    node1->l_child = NULL;
    node1->r_child = NULL;
    node1->value   = 1;

    if (!node2) {
        goto error;
    }
    node2->l_child = NULL;
    node2->r_child = NULL;
    node2->value   = 2;

    if (!node3) {
       goto error;
    }
    node3->l_child = NULL;
    node3->r_child = NULL;
    node3->value   = 3; 

    if (!node4) {
       goto error;
    }
    node4->l_child = NULL;
    node4->r_child = NULL;
    node4->value   = 4; 
    
    node_t *node = tree.root;
    //插入根节点
    tree_insert_node(&tree, NULL, node1, LEFT_CHILD);

    //插入根节点的左孩子
    node = tree.root;
    tree_insert_node(&tree, node, node2, LEFT_CHILD);

    //插入根节点的右孩子
    node = tree.root;
    tree_insert_node(&tree, node, node3, RIGHT_CHILD);

    // //插入根节点的右孩子
    tree_insert_node(&tree, node2, node4, LEFT_CHILD);
    
    printf("prevorder\n");
    node = tree.root;
    tree_prev_order_visit(&tree, node);
    
    printf("inorder\n");
    node = tree.root;
    tree_in_order_visit(&tree, node);
    
    printf("postorder\n");
    node = tree.root;
    tree_post_order_visit(&tree, node);
   
    node_t *found = NULL;
    for (int i =1; i < 5; i++){
        node = tree.root;
        tree_find_node(&tree, node, &found, i);
        printf("find add:%x\n", found);
    }

error:
    tree_destory(&tree);

    return 0;
}
