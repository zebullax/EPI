#include <memory>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>

struct treeNode
{
    int data;
    struct treeNode* left;
    struct treeNode* right;
};

struct treeNode* newTreeNode(int data)
{
  struct treeNode* node = (struct treeNode*) malloc(sizeof(struct treeNode));
  node->data = data;
  node->left = NULL;
  node->right = NULL; 
  return(node);
}

int getHeight(treeNode* root, bool &unbalanced)
{	
	if(unbalanced || !root)
		return -1;
	int heightL=0,heightR=0;
	heightL=getHeight(root->left,unbalanced);
	heightR=getHeight(root->right,unbalanced);	
	if(abs(heightL-heightR)>1)
	{
		unbalanced=true;
		return -1;
	}
	else
		return (1+std::max(heightL,heightR));	
}
void Prob10(treeNode* root)
{
	bool unbalanced=false;
	getHeight(root,unbalanced);
	if(unbalanced)
		std::cout<<"Unbalanced tree";
	else
		std::cout<<"Balanced tree";
}

void Prob10_1D()
{
	struct treeNode *root = newTreeNode(19);
	root->left        = newTreeNode(7);
	root->right       = newTreeNode(43);
	root->left->left  = newTreeNode(3);
	root->left->right = newTreeNode(11); 
	root->right->left  = newTreeNode(23);
	root->right->left->right  = newTreeNode(37);
	root->right->left->right->left  = newTreeNode(29);
	root->right->left->right->left->right  = newTreeNode(31);
	root->right->left->right->right  = newTreeNode(41);
	root->right->right = newTreeNode(47); 
	root->right->right->right = newTreeNode(53);
	Prob10(root);

	struct treeNode *broot = newTreeNode(19);
	broot->left        = newTreeNode(7);
	broot->right       = newTreeNode(43);
	broot->left->left  = newTreeNode(3);
	broot->left->right = newTreeNode(11); 
	broot->right->left  = newTreeNode(23);
	broot->right->right = newTreeNode(47); 
	broot->right->right->right = newTreeNode(53);
	Prob10(broot);
}

bool IsSymm(treeNode *rootl, treeNode *rootr)
{
	if(!rootl)
	{
		if(!rootr)
			return true;
		else
			return false;
	}

	if(rootl->data!=rootr->data)
		return false;
	return (IsSymm(rootl->left,rootr->right)&&IsSymm(rootl->right,rootr->left));	
}

void Prob10_3D()
{	
	struct treeNode *symmroot = newTreeNode(314);
	symmroot->left        = newTreeNode(6);
	symmroot->right       = newTreeNode(6);
	symmroot->left->right = newTreeNode(2); 
	symmroot->left->right->right = newTreeNode(3);
	symmroot->right->left  = newTreeNode(2);	
	symmroot->right->left->left  = newTreeNode(3);
	if(IsSymm(symmroot,symmroot))
		std::cout<<"symmetric\n";
	else
		std::cout<<"assymmetric\n";

	struct treeNode *asymmroot = newTreeNode(314);
	asymmroot->left        = newTreeNode(6);
	asymmroot->right       = newTreeNode(6);
	asymmroot->left->right = newTreeNode(2); 
	asymmroot->left->right->right = newTreeNode(9);
	asymmroot->right->left  = newTreeNode(2);	
	asymmroot->right->left->left  = newTreeNode(8);
	if(IsSymm(asymmroot,asymmroot))
		std::cout<<"symmetric\n";
	else
		std::cout<<"assymmetric\n";
}

int FindInSubrange(const std::vector<int> &v, int s,int e,int elem)
{
	int i=s;
	while(i<=e && v[i]!=elem)
		++i;
	if(v[i]!=elem)
		return -1;
	else
		return i;
}
treeNode* buildSubtreeFromPreIn(const std::vector<int> &pre,const std::vector<int> &in, int in_s, int in_e,int &pre_idx)
{
	if(in_s>in_e || in_s<0 || in_e>in.size()-1||pre_idx>pre.size()-1)
		return NULL;
	treeNode *root=newTreeNode(pre[pre_idx]);
	int root_idx=FindInSubrange(in,in_s,in_e,pre[pre_idx++]);
	root->left=buildSubtreeFromPreIn(pre,in,in_s,root_idx-1,pre_idx);
	root->right=buildSubtreeFromPreIn(pre,in,root_idx+1,in_e,pre_idx);
	return root;
}
treeNode* buildSubtreeFromPreIn(std::string pre,std::string in,int &start)
{
	treeNode* root=newTreeNode(pre[start]-'0');
	int idx=in.find(pre[start],0);
	start++;
	root->left=(idx>0?buildSubtreeFromPreIn(pre,in.substr(0,idx),start):NULL);
	root->right=(idx<in.size()-1?buildSubtreeFromPreIn(pre,in.substr(idx+1,std::string::npos),start):NULL);
	return root;
}

void IOT(treeNode* root)
{
	if (root==NULL)
		return;
	IOT(root->left);
	std::cout<<root->data<<",";
	IOT(root->right);
}

void Prob10_12D()
{
	std::string in="621583497";
	std::string pre="826513479";
	int idx=0;
	treeNode *root=buildSubtreeFromPreIn(pre,in,idx);
	IOT(root);
	std::vector<int> inV;std::vector<int> preV;
	inV.push_back(6);inV.push_back(2);inV.push_back(1);inV.push_back(5);inV.push_back(8);inV.push_back(3);inV.push_back(4);inV.push_back(9);inV.push_back(7);
	preV.push_back(8);preV.push_back(2);preV.push_back(6);preV.push_back(5);preV.push_back(1);preV.push_back(3);preV.push_back(4);preV.push_back(7);preV.push_back(9);
	idx=0;
	root=buildSubtreeFromPreIn(preV,inV,0,in.size()-1,idx);
	std::cout<<"\n";
	IOT(root);
}

void Prob10_10(treeNode* root)
{
	std::stack<treeNode* > s;
	s.push(root);
	treeNode* t;
	while(!s.empty())
	{
		t=s.top();s.pop();
		std::cout<<t->data<<",";
		if(t->right)
			s.push(t->right);
		if(t->left)
			s.push(t->left);
	}
}
void Prob10_10D()
{
	struct treeNode *root = newTreeNode(314);
	root->left        = newTreeNode(6);
	root->right       = newTreeNode(6);
	root->left->left  = newTreeNode(271);
	root->left->left->left  = newTreeNode(28);
	root->left->left->right  = newTreeNode(0);
	root->left->right = newTreeNode(561); 
	root->left->right->right = newTreeNode(3); 
	root->left->right->right->left = newTreeNode(17);
	root->right->left  = newTreeNode(2);
	root->right->left->right  = newTreeNode(1);
	root->right->left->right->left  = newTreeNode(401);
	root->right->left->right->left->right  = newTreeNode(641);
	root->right->left->right->right  = newTreeNode(257);
	root->right->right = newTreeNode(271); 
	root->right->right->right = newTreeNode(28);
	Prob10_10(root);
}

treeNode* Prob10_13(const std::vector<int> &v)
{
	std::stack<treeNode*> s;
	for(int i=v.size()-1;i>=0;--i)
	{
		if(v[i]!=-1)
		{
			treeNode* r=newTreeNode(v[i]);
			r->left=s.top();s.pop();
			r->right=s.top();s.pop();
			s.push(r);
		}
		else
			s.push(NULL);
	}
	return s.top();
}

void Prob10_13D()
{
	std::vector<int> preV;
	preV.push_back(8);preV.push_back(2);preV.push_back(6);preV.push_back(-1);preV.push_back(-1);preV.push_back(5);preV.push_back(1);preV.push_back(-1);preV.push_back(-1);preV.push_back(-1);
	preV.push_back(3);preV.push_back(-1);preV.push_back(4);preV.push_back(-1);preV.push_back(7);preV.push_back(9);preV.push_back(-1);preV.push_back(-1);preV.push_back(-1);
	treeNode* r=Prob10_13(preV);
	IOT(r);
}

int main(int argc, char** argv)
{
	Prob10_13D();
	getchar();

	return 0;
}