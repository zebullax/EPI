#include <memory>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

struct treeNode
{
    int data;
    treeNode* left;
    treeNode* right;
};

treeNode* newTreeNode(int data)
{
  treeNode* node = static_cast<treeNode*>(malloc(sizeof(treeNode)));
  node->data = data;
  node->left = NULL;
  node->right = NULL; 
  return(node);
}
treeNode* GetBigTree()
{
	treeNode *root = newTreeNode(314);
	root->left = newTreeNode(6);
	root->right = newTreeNode(6);
	root->left->left = newTreeNode(271);
	root->left->left->left = newTreeNode(28);
	root->left->left->right = newTreeNode(0);
	root->left->right = newTreeNode(561);
	root->left->right->right = newTreeNode(3);
	root->left->right->right->left = newTreeNode(17);
	root->right->left = newTreeNode(2);
	root->right->left->right = newTreeNode(1);
	root->right->left->right->left = newTreeNode(401);
	root->right->left->right->left->right = newTreeNode(641);
	root->right->left->right->right = newTreeNode(257);
	root->right->right = newTreeNode(271);
	root->right->right->right = newTreeNode(28);
	return root;
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

void BinSum(int& sum, int val, treeNode* root)
{
	if (!root)
		return;
	val =val* 2 + (root->data);
	if (!root->left && !root->right)
	{
		sum += val;
		return;
	}	
	BinSum(sum, val, root->left);
	BinSum(sum, val, root->right);	
}
void Prob10_6D()
{
	treeNode *root = newTreeNode(1);
	root->left = newTreeNode(0);
	//root->right = newTreeNode(1);
	root->left->left = newTreeNode(0);
	root->left->right = newTreeNode(1);
	root->left->right->right = newTreeNode(1);
	root->left->right->right->left = newTreeNode(0);
	root->left->left->left = newTreeNode(0);
	root->left->left->right = newTreeNode(1);
	int sum = 0, val = 0;
	BinSum(sum, val, root);
	std::cout << "Sum = " << sum << std::endl;
}

void Prob10_1D()
{
	treeNode *root = newTreeNode(19);
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

	treeNode *broot = newTreeNode(19);
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
	treeNode *symmroot = newTreeNode(314);
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

	treeNode *asymmroot = newTreeNode(314);
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
	treeNode *root = GetBigTree();
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

bool FindWeight(int sum, treeNode* root, int weight)
{
	if (!root)
		return false;
	sum += root->data;
	if (sum == weight && (!root->left && !root->right))
		return true;
	return(FindWeight(sum, root->left, weight) || FindWeight(sum, root->right, weight));
}
void Prob10_7D()
{
	treeNode *root = GetBigTree();
	int weight = 580;
	if (FindWeight(0, root, weight))
		std::cout << weight << " has been found\n";
	else
		std::cout << weight <<" has not been found\n";

}

void GetLeftAndRightExteriors(treeNode* l, treeNode* r, std::vector<treeNode*> &l_e, std::vector<treeNode*> &r_e)
{
	if (!l && !r)
		return;
	if (l)
		l_e.push_back(l);
	if (r)
		r_e.push_back(r);
	GetLeftAndRightExteriors(l->left, r->right, l_e, r_e);
}

void GetLeaves(treeNode* root,std::vector<treeNode*> &v)
{
	if (!root)
		return;
	if (!root->left && !root->right)
		v.push_back(root);
	else
	{
		GetLeaves(root->left, v);
		GetLeaves(root->right, v);
	}	
}
std::vector<treeNode*> GetExterior(treeNode* root)
{
	std::vector<treeNode*> l_e, r_e;
	std::vector<treeNode*> leaves;
	std::vector<treeNode*> result;
	GetLeftAndRightExteriors(root->left, root->right, l_e, r_e);
	GetLeaves(root, leaves);
	result.push_back(root);
	result.insert(result.end(),l_e.begin(), l_e.end()-1);
	result.insert(result.end(), leaves.begin(), leaves.end());
	std::reverse(r_e.begin(), r_e.end());
	result.insert(result.end(), r_e.begin()+1, r_e.end());
	return result;
}
void Prob10_15D()
{
	treeNode* root = GetBigTree();
	std::vector<treeNode*> result = GetExterior(root);
	for (int i = 0; i < result.size(); ++i)
	{
		std::cout << (result[i]->data)<<",";
	}
}
void NonRecursivePreOrderTraversal(treeNode *root)
{
	if (!root)
		return;
	std::stack<treeNode*> s;
	treeNode* current;
	s.push(root);
	while (!s.empty())
	{
		current = s.top();
		s.pop();
		std::cout << current->data << ",";
		if (current->right)
			s.push(current->right);
		if (current->left)
			s.push(current->left);
	}
}
void NonRecursivePostOrderTraversal(treeNode *root)
{
	if (!root)
		return;
	std::stack<treeNode*> s;
	std::stack<treeNode*> final;
	treeNode* current;
	s.push(root);
	while (!s.empty())
	{
		current = s.top();
		s.pop();
		final.push(current);		
		if (current->left)
			s.push(current->left);
		if (current->right)
			s.push(current->right);
	}
	while (!final.empty())
	{
		current = final.top();
		final.pop();
		std::cout << current->data <<",";
	}
}
void Prob10_9D()
{
	treeNode *root = GetBigTree();
	NonRecursivePreOrderTraversal(root);
	std::cout << std::endl;
	NonRecursivePostOrderTraversal(root);
}
int main(int argc, char** argv)
{
	Prob10_15D();
	getchar();

	return 0;
}