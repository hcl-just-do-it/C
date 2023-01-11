#include<bits/stdc++.h>
using namespace std;
int N,ans;
class TreeNode{
	public:
	TreeNode *left,*right;
	int val;
	TreeNode(){
		val = INT_MAX;
		left = nullptr;
		right = nullptr;
	};
	TreeNode(int _val):val(_val){
		val = _val;
		left = nullptr;
		right = nullptr;
	};
};
TreeNode *build(TreeNode *root,int val){
	if(root == nullptr){
		root = new TreeNode(val);
		return root;
	}
	if(val<=root->val)
		root->left = build(root->left,val);
	else
		root->right = build(root->right,val);
	return root;
}
void display(TreeNode* root){
	if(root == nullptr)
		return ;
	display(root->left);
	cout<<root->val<<" ";
	if(root->val>N){
		ans+=root->val;
	}
	display(root->right);
}
int main(){
	TreeNode *root = nullptr;
	cin>>N;
	int x;
	for(int i=0;i<5;i++){
		cin>>x;
		root = build(root,x);
	}
	display(root);
	cout<<endl<<ans<<endl;
}