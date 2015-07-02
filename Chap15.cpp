#include <vector>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

/*
int Prob14_13(const vector<int> &v)
{
	int max=0;
	vector<int> s=v;
	sort(s.begin(),s.end());

	for (vector<int>::size_type i=0;i<s.size();++i)
	{
		if(s[i]<=max+1)
			max=max+s[i];
		else
			break;
	}
	return (max+1);
}
void Prob14_13D()
{
	vector<int> v;
	v.push_back(1);v.push_back(2);v.push_back(5);v.push_back(10);v.push_back(4);
	cout<<Prob14_13(v);
}
*/

template<typename T>
struct treeNode{
    T data;
    struct treeNode<T> *left;
    struct treeNode<T> *right;
};

template<typename T>
treeNode<T>* newTreeNode(T data)
{
  treeNode<T>* node = (treeNode<T>*) malloc(sizeof(treeNode<T>));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}

template<typename T>
void KillTheTree(treeNode<T> *root)
{
	if (root)
	{
		treeNode<T> *nextL=root->left;
		treeNode<T> *nextR=root->right;
		free(root);
		KillTheTree(nextL);
		KillTheTree(nextR);
	}
}

template<typename T>
bool CheckBST( treeNode<T> *root, T min, T max)
{
	if (root == NULL)
		return true;
	if(root->data<min || root->data>max)
		return false;
	else
		return (CheckBST(root->left,min,root->data) && CheckBST(root->right,root->data, max));
}

void Prob15_1D()
{
	treeNode<int> *root = newTreeNode(19);
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
	cout<<CheckBST(root,INT_MIN,INT_MAX);
	KillTheTree(root);
}
template<typename T>
treeNode<T>*  FindNodeByKey(treeNode<T>* root, T elem)
{
	while(root){
		if(root->data>elem)
			root=root->left;
		else if(root->data<elem)
			root=root->right;
		else
			break;
	}
	return root;
}
template<typename T>
treeNode<T>* FindLeftest(treeNode<T>* root)
{
	while(root->left)
		root=root->left;
	return root;
}

template<typename T>
treeNode<T>*  GetNextElem(treeNode<T>* root, T elem)
{
	bool found=false;
	treeNode<T>* oldAnc=NULL;
	while(root)
	{
		if(root->data>elem)
		{
			oldAnc=root;
			root=root->left;
		}
		else if(root->data<elem)
		{
			root=root->right;
		}
		else if(root->data==elem)
		{
			found=true;
			root=root->right;
		}
	}
	return (found?oldAnc:NULL);
}
void Prob15_3D()
{
	treeNode<int> *root = newTreeNode(19);
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

	treeNode<int> *res=GetNextElem(root,23);
	cout<<"After 23:"<<res->data<<endl;
	res=GetNextElem(root,32);
	cout<<"After 32:"<<(!res?"NULL":"NOT NULL")<<endl;
	res=GetNextElem(root,41);
	cout<<"After 41:"<<res->data<<endl;
	res=GetNextElem(root,31);
	cout<<"After 31:"<<res->data<<endl;
	KillTheTree(root);
}

template<typename T>
void Prob15_4(treeNode<T>* root, queue<T> &q,int k)
{
	/*
	if (!root)
		return;
	Prob15_4(root->left,q,k);
	if(q.size()==k)
		q.pop();
	q.push(root->data);	
	Prob15_4(root->right,q,k);
	*/
	if(!root)
		return;
	if(q.size()<k)
	{
		Prob15_4(root->right,q,k);
		if(q.size()<k)
		{
			q.push(root->data);	
		}
		Prob15_4(root->left,q,k);
	}
}

void Prob15_4D()
{
	treeNode<int> *root = newTreeNode(19);
	root->left        = newTreeNode(7);
	root->right       = newTreeNode(43);
	root->left->left  = newTreeNode(3);
	root->left->left->left  = newTreeNode(2);
	root->left->left->right  = newTreeNode(5);
	root->left->right = newTreeNode(11); 
	root->left->right->right = newTreeNode(17); 
	root->left->right->right->left = newTreeNode(13); 
	root->right->left  = newTreeNode(23);
	root->right->left->right  = newTreeNode(37);
	root->right->left->right->left  = newTreeNode(29);
	root->right->left->right->left->right  = newTreeNode(31);
	root->right->left->right->right  = newTreeNode(41);
	root->right->right = newTreeNode(47); 
	root->right->right->right = newTreeNode(53); 
	queue<int> q;
	Prob15_4(root,q,5);

	while(!q.empty())
	{
		cout<<q.front()<<",";
		q.pop();
	}
	KillTheTree(root);
}

template<typename T>
int FindLCA(treeNode<T>* root,treeNode<T>* s,treeNode<T>* b)
{
	while(root)
	{
		if(root->data>s->data && root->data<b->data)
		{
			return root->data;
		}
		else if(root->data<s->data)
			root=root->right;
		else
			root=root->left;
	}
}
void Prob15_5D()
{
	treeNode<int> *root = newTreeNode(19);
	root->left        = newTreeNode(7);
	root->right       = newTreeNode(43);
	root->left->left  = newTreeNode(3);
	root->left->left->left  = newTreeNode(2);
	root->left->left->right  = newTreeNode(5);
	root->left->right = newTreeNode(11); 
	root->left->right->right = newTreeNode(17); 
	root->left->right->right->left = newTreeNode(13); 
	root->right->left  = newTreeNode(23);
	root->right->left->right  = newTreeNode(37);
	root->right->left->right->left  = newTreeNode(29);
	root->right->left->right->left->right  = newTreeNode(31);
	root->right->left->right->right  = newTreeNode(41);
	root->right->right = newTreeNode(47); 
	root->right->right->right = newTreeNode(53); 

	int LCA=FindLCA(root,root->left->left,root->left->right->right);
	cout<<"LCA of "<<root->left->left->data<<" and "<<root->left->right->right->data<<" is "<<LCA<<endl;
	LCA=FindLCA(root,root->right->left->right->right,root->right->right->right);
	cout<<"LCA of "<<root->right->right->right->data<<" and "<<root->right->left->right->right->data<<" is "<<LCA<<endl;
	KillTheTree(root);
}

template<typename T>
void IOT(treeNode<T>* root)
{
	if (root==NULL)
		return;
	IOT(root->left);
	cout<<root->data<<",";
	IOT(root->right);
}
template<typename T>
treeNode<T>*  BuildBSTFromPreOrder(const vector<T> &v, int &i,int min, int max)
{
	if(i>=v.size() || v[i]>max || v[i]<min)
		return NULL;
	treeNode<T>* r=newTreeNode(v[i++]);
	r->left=BuildBSTFromPreOrder(v,i,min,v[i-1]);
	r->right=BuildBSTFromPreOrder(v,i,v[i-1],max);
	return r;
}

void Prob15_6D()
{
	vector<int> v;
	v.push_back(3);v.push_back(1);v.push_back(2);v.push_back(6);v.push_back(4);v.push_back(9);
	int i=0;
	treeNode<int>* r=BuildBSTFromPreOrder(v,i,INT_MIN,INT_MAX);
	IOT(r);
}
int main(int argc,char**argv)
{
	Prob15_6D();
	getchar();

	return 0;
}
