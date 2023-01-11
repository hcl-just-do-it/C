#include<stdio.h>//https://segmentfault.com/a/1190000038283791
#include<stdlib.h>
#include<string.h>
typedef struct RBTreeNode {
    int data; //数据域
    int color; //0黑色 1红色
    struct RBTreeNode *parent;//父亲结点
    struct RBTreeNode *left;  //左子结点
    struct RBTreeNode *right; //右子结点
} RBTreeNode;
RBTreeNode *RBTreeEndNode;
void search(RBTreeNode *root,int target){
    if (root == NULL)
        return ;
    if(target == root->data){
    	printf("找到%d了，color:%d\n",root->data,root->color);
    	return;
	}
    if(target < root->data)
    	search(root->left,target);
    if(target > root->data)
    	search(root->right,target);
    return ;
}
void preOrderTraverse(RBTreeNode *root){
    if (root == NULL)
        return ;
    if (root->parent != NULL)
        printf("%d color: %d parent:%d\n", root->data, root->color, root->parent->data);
    else
    	printf("%d color: %d\n", root->data, root->color);     
    preOrderTraverse(root->left);
    preOrderTraverse(root->right);
}
RBTreeNode *left_rotation(RBTreeNode *root){
	//处理新根节点
    RBTreeNode *new_root = root->right;
    //处理新根父母
	new_root->parent = root->parent;
    if (root->parent != NULL){
        //判断父亲左右
        if (new_root->parent->left == root)
        	new_root->parent->left = new_root;
        else
        	new_root->parent->right = new_root;
    }
    //移走新根左节点
    root->right = new_root->left;
	if (new_root->left != NULL)new_root->left->parent = root;
    //新加新根左节点
    new_root->left = root;
    root->parent = new_root;

    return new_root;
}
RBTreeNode *right_rotation(RBTreeNode *root){
	//处理新根节点
    RBTreeNode *new_root = root->left;
    //处理新根父母
	new_root->parent = root->parent;
    if (root->parent != NULL){
        //判断父亲左右
        if (new_root->parent->left == root)
        {
            new_root->parent->left = new_root;
        }else{
            new_root->parent->right = new_root;
        }
    }
    //移走新根右节点
    root->left = new_root->right;
	if (new_root->right != NULL)new_root->right->parent = root;
    //新加新根右节点
    new_root->right   = root;
    root->parent = new_root;
    return new_root;
}
RBTreeNode *insert(RBTreeNode *root, int data, RBTreeNode *parent){
    if (NULL == root){
        RBTreeNode *node = (RBTreeNode *)malloc(sizeof(RBTreeNode));
	    if (node == NULL){
	        printf("malloc error \n");
	        return NULL;
	    }
	    node->data  = data;
	    node->parent= parent;
	    node->color = 1;
	    node->right = NULL;
	    node->left  = NULL;
	    RBTreeEndNode = node;
	    return node;
    }
    if (data > root->data)
        root->right  = insert(root->right, data, root);
    else
        root->left   = insert(root->left, data, root);
    return root;
}
RBTreeNode *rebalance3(RBTreeNode *root, RBTreeNode *rootNode){//要放在insertRB之前
    //1 新节点在根节点
    if (root->parent == NULL){
    	root->color = 0;
    	return root;
	}
    //2 有父节点  
    //2.1 父节点是黑色，啥也不用干
    if (root->parent->color != 0){
    //2.2 父节点是红色,祖父一定是黑色啦，看叔叔是啥颜色
        RBTreeNode *parent, *gparent, *uncle;
        parent = root->parent;
        gparent = root->parent->parent;
        //先判断父节点是祖父节点的左节点还是右节点，即叔叔节点是啥
        //2.2.1 父节点是祖父节点的左节点
        if (parent == gparent->left){
            uncle = gparent->right;
            //2.2.1.1如果叔叔也是红色
            if (uncle != NULL && uncle->color == 1){
                parent->color = 0;
                uncle->color = 0;
                gparent->color = 1;
                
                return rebalance3(gparent, rootNode);
            }else{
            //2.2.1.2如果叔叔黑色 或不存在
                //2.2.1.2.1 root是左节点
                if (root == parent->left){
                    parent->color = 0;
                    gparent->color = 1;
                    gparent = right_rotation(gparent);
                }else{
                //2.2.1.2.2 root是右节点
                    //1.root与父节点交换 并把父节点设为新root的左节点,即转化为2.2.1.2.1
                    gparent->left = root;                       
                    root->parent = gparent;
                    root->left = parent;
                    parent->parent = root;
                    parent->right = NULL;
                    return rebalance3(parent, rootNode);
                }
            }
        }else{
        //2.2.2 父节点是祖父节点的右节点
            uncle = gparent->left;
            //2.2.2.1如果叔叔也是红色
            if (uncle != NULL && uncle->color == 1){
                parent->color = 0;
                uncle->color = 0;
                gparent->color = 1;
                return rebalance3(gparent, rootNode);
            }else{
            //2.2.2.2如果叔叔黑色 或不存在
                //2.2.2.2.1 root是左节点
                if (root == parent->left){
                    //1.root与父节点交换 并把父节点设为新root的左节点,即转化为2.2.2.2.2
                    gparent->right = root;
                    root->parent = gparent;
                    root->right = parent;
                    parent->parent = root;   
                    parent->left = NULL;
                    return rebalance3(parent, rootNode);
                }else{
                //2.2.2.2.2 root是右节点                        
                    parent->color = 0;
                    gparent->color = 1;
                    gparent = left_rotation(gparent);
                }
            }
        }
    }
    return rootNode;
}
RBTreeNode *inserRB(RBTreeNode *root, int data, RBTreeNode *parent){
    root = insert(root,data,parent);
    return rebalance3(RBTreeEndNode,root);
} 
RBTreeNode *FindMin(RBTreeNode *root)
{
    if (root == NULL||root->left ==NULL)
        return root;
    return FindMin(root->left);
}
RBTreeNode *Delete(RBTreeNode *root, int target, RBTreeNode *rootNode)
{
    if (root == NULL)
        return NULL;
    if (target > root->data)
        rootNode = Delete(root->right, target, rootNode);
    else if(target < root->data)
        rootNode  = Delete(root->left, target, rootNode);
    else if(target == root->data){  
		printf("%d删除成功！",target);      
        //删除根节点
        if (root->parent == NULL){
        	free(root);
        	root = NULL;
        	return root;
        }
        RBTreeNode *parent, *brother;
        parent = root->parent;
        //1.没有左右节点
        if (root->left == NULL && root->right == NULL){
            //1.1被删除节点是红色，直接删除即可
            if (root->color == 1){
                if (root == parent->left){
                    parent->left = NULL;
                }else{
                    parent->right = NULL;
                }
                free(root);
                root = NULL;//删除自身
            }else{
            //1.2被删除节点是黑色，一定有兄弟节点 破坏了平衡性 需要重新平衡
                //1.2.1被删除节点在父节点的左数上
                if (root == parent->left){
                	free(root);
                    root = NULL;
                    parent->left = NULL;//删除自身
                    brother = parent->right;
                    //1.2.1.1兄弟节点是黑色
                    if (brother->color == 0){
                        //1.2.1.1.1 兄弟节点是黑色,且有一个右节点，右节点必然是红色
                        if (brother->right != NULL && brother->left == NULL){
                            brother->right->color = parent->color;
                            parent = left_rotation(parent);
                        }else if (brother->right == NULL && brother->left != NULL){
                            //1.2.1.1.2 兄弟节点是黑色,且有一个左节点，左节点必然是红色
                            brother->color = parent->color;
                            parent->right  = brother->left;

                            brother->parent = brother->left;
                            
                            brother->left->parent = parent;
                            brother->left->right  = brother;
                            brother->left   = NULL;

                            parent = left_rotation(parent);
                        }else if (brother->right != NULL && brother->left != NULL){
                        //1.2.1.1.3 兄弟节点是黑色,且有俩节点，必然都是红色
                            brother->color = parent->color;
                            brother->right->color = 0;
                            parent->color = 0;

                            parent = left_rotation(parent);
                        }else{
                        //1.2.1.1.4 兄弟节点是黑色,且没有节点 黑色路径必然要-1了 递归
                            parent->right->color = 1;
                            return rebalance3(parent->right,rootNode);
                        }
                    }else{
                    //1.2.1.2兄弟节点是红色，父节点一定是黑色，它一定有俩黑色子节点
                        //兄弟节点置黑,兄弟左节点置红
                        brother->color = 0;
                        brother->left->color  = 1;
                        parent = left_rotation(parent);
                    }
                }else{
                //1.2.2被删除节点在父节点的右数上
                	free(root);
                    root = NULL;
                    parent->right = NULL;//删除自身
                    brother = parent->left;
                    //1.2.2.1 兄弟节点是黑色
                    if (brother->color == 0){
                        //1.2.2.1.1 兄弟节点是黑色,且有一个左节点，左节点必然是红色 跟1.2.1.1.1是镜像关系
                        if (brother->right == NULL && brother->left != NULL){
                            //把父亲颜色赋值给兄弟节点的左节点
                            brother->left->color = parent->color;
                            parent = right_rotation(parent);
                        
                        }else if(brother->right != NULL && brother->left == NULL){
                            //1.2.2.1.2 兄弟节点是黑色,且有一个右节点，右节点必然是红色 跟1.2.1.1.2是镜像关系
                            parent->left = brother->right;                          
                            brother->color = parent->color;
                            brother->parent = brother->right;

                            brother->right->parent = parent;
                            brother->right->left   = brother;
                            brother->right  = NULL;
                            parent = right_rotation(parent);
                        }else if(brother->right != NULL && brother->left != NULL){
                            //1.2.2.1.3 兄弟节点是黑色,且有俩节点，必然都是红色 跟1.2.1.1.3是镜像关系
                            brother->left->color = 0;                          
                            brother->color = parent->color;
                            parent = right_rotation(parent);
                        }else{
                            //1.2.2.1.4 兄弟节点是黑色,且没有节点 黑色路径必然要-1了 递归
                            parent->left->color = 1;
                            return rebalance3(parent->left,rootNode);
                        }  
                    }else{
                        //1.2.2.2兄弟节点是红色，父节点一定是黑色，它一定有俩黑色子节点
                        //兄弟节点置黑,兄弟右节点置红
                        brother->color = 0;
                        brother->right->color  = 1;
                        parent = right_rotation(parent);
                    }
                }
            }
        }else if (root->left != NULL && root->right == NULL){
            //2.只有左节点 该左节点必然是红色，那root一定是黑色,root值替换为左节点的值，删除左节点
            root->data = root->left->data;
            free(root->left);
            root->left  = NULL;
        }else if (root->right != NULL && root->left == NULL){
            //3.只有右节点 该右节点必然是红色，那root一定是黑色,root值替换为右节点的值，删除右节点
            root->data = root->right->data;
            free(root->right);
            root->right  = NULL;
        }else{
        //4.左右都有的情况，选取后继节点
            RBTreeNode *min = FindMin(root->right);
            root->data = min->data;
            rootNode  = Delete(min, min->data, rootNode);
        }
    }
    
    return rootNode;
}

int main(){ 
    struct RBTreeNode *node = NULL;
    node = inserRB(node, 8, NULL);
    node = inserRB(node, 4, NULL);
    node = inserRB(node, 12, NULL);
    node = inserRB(node, 2, NULL);
    node = inserRB(node, 1, NULL);
    node = inserRB(node, 1, NULL);
    while(1){
    	char operation[10000];
		int data;
    	scanf("%s",operation);
    	if(strcmp(operation, "quit") == 0)
    		return 0;
    	else if(strcmp(operation, "foreach") == 0)
    		preOrderTraverse(node);
    	else if(strcmp(operation, "search") == 0){
    		scanf("%d",&data);
    		search(node,data);
		}	
    	else if(strcmp(operation, "add") == 0){
			scanf("%d",&data);
			node = inserRB(node, data, NULL);
		}
    	else if(strcmp(operation, "del") == 0){
    		scanf("%d",&data);
    		node = Delete(node, data, node);
		}else{
			printf("你输入的格式有误，请重新输入。参考如下：\nadd 1\ndel 1\n foreach\nsearch 1\n quit\n");
		}
	}
    
    preOrderTraverse(node);
}