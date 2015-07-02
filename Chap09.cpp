#include <cstdlib>
#include <memory>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <string>

struct pair{
	int val;
	int max;
} ;

class MaxStack{
public:
	MaxStack(int _capacity):capacity(_capacity)
	{
		if (capacity>0)
			stak=new pair[capacity];
		else
			stak=NULL;
		nbElem=0;
	}
	
	~MaxStack()
	{
		delete[] stak;
	}

	MaxStack(const MaxStack &that)
	{
		if(stak)
			delete[] stak;
		stak=new pair[that.capacity];
		capacity=that.capacity;
		memcpy(this->stak,that.stak,sizeof(pair)*that.capacity);
		nbElem=that.nbElem;
	}

	void operator=(const MaxStack& that)
	{
		if(this!=&that)
		{
			delete[] stak;
			stak=new struct pair[that.capacity];
			capacity=that.capacity;
			memcpy(this->stak,that.stak,sizeof(pair)*that.capacity);
			nbElem=that.nbElem;
		}
	}

	void push (int val)
	{
		stak[nbElem].val=val;
		if(nbElem>0)
			stak[nbElem].max=(val>stak[nbElem-1].max?val:stak[nbElem-1].max);
		else
			stak[nbElem].max=stak[nbElem].val;
		nbElem++;
		//resize
		if(nbElem==capacity)
		{
			capacity*=2;
			pair* tmp=new pair[capacity];
			memcpy(tmp,stak,sizeof(pair)*nbElem);
			delete []stak;
			stak=tmp;
		}
	}
	pair& top()
	{
		if(nbElem>0)
		{
			return stak[nbElem-1];
		}
		else throw;
	}

	bool empty()
	{
		return (nbElem==0);
	}

	void pop()
	{
		nbElem--;
	}

	int max()
	{
		return stak[nbElem-1].max;
	}

private:
	pair* stak;
	int nbElem;
	int capacity;
};

template<class t>
class DeQueue{
private:
    int start,end,nbElem,size;
    t* deq;
public:
    DeQueue(int _size):size(_size),deq(NULL)
    {
        if (size>0) {
            deq=new t[size];
        }
        nbElem=0;
        start=0;
        end=0;
    }
    DeQueue(const DeQueue<t> &that)
    {
        size=that.size;
        nbElem=that.nbElem;
        if(size>0)
        {
            deq=new t[size];
        }
        if(nbElem>0)
        {
            memcpy(deq,that.deq,sizeof(t)*nbElem);
        }
    }
    void operator=(const DeQueue<t> &that)
    {
        if(this!=&that)
        {
            if(deq)
                delete[] deq;
            
            size=that.size;
            nbElem=that.nbElem;
            if(size>0)
            {
                deq=new t[size];
            }
            if(nbElem>0)
            {
                memcpy(deq,that.deq,sizeof(t)*nbElem);
            }
        }
    }
    void Enqueue(t elem)
    {
        //resize ?
        if (nbElem==size)
        {
            size=(size==0?10:size*2);
            t* tmp=new t[size];
            //[.|.|2|3]
            if(end>=start)
            {
                memcpy(tmp, deq+start, sizeof(t)*nbElem);
            }
            else //[4|.|.|2|3]
            {
                memcpy(tmp, deq+start, sizeof(t)*(size/2-start));
                memcpy(tmp, deq, sizeof(t)*(nbElem-(size/2-start)) );
            }
            delete[] deq;
            deq=tmp;
        }
        deq[end]=elem;
        end=end+1%size;
        nbElem++;
    }
    t Dequeue()
    {
        if(nbElem==0)
            throw;
        end=(end-1<0?size-1:end-1);
        t tmp=deq[end];
        return tmp;
    }
    bool Empty()
    {
        return (nbElem==0);
    }
    int Size()
    {
        return nbElem;
    }
};

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

void Test9_1()
{
	MaxStack mS(10);
	mS.push(5);
	mS.push(2);
	std::cout<<mS.max();
	mS.push(2);
	mS.push(2);
	mS.pop();
	mS.push(20);
	std::cout<<mS.max();
}

void Test9_10(struct treeNode* root)
{
	std::queue<std::pair<int,struct treeNode* >> s;
	std::pair<int,struct treeNode *> popped;
	int curLevel=1;

	s.emplace(curLevel,root);
	while(!s.empty())
	{
		popped=s.front();
		s.pop();
		if(curLevel!=popped.first)
		{
			std::cout<<std::endl;
			curLevel=popped.first;
		}
		std::cout<<popped.second->data<<" ";
		if(popped.second->left)
			s.emplace(curLevel+1,popped.second->left);
		if(popped.second->right)
			s.emplace(curLevel+1,popped.second->right);
	}
}

void Test9_10D()
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
	
	Test9_10(root);
}

int Test9_2(char *s)
{
	char tok=',';
	char* found;
	std::queue<int> q;
	int i,j;
	found=strtok(s,&tok);
	while(found)
	{
		if(*found=='+')
		{
			i=q.front();q.pop();
			j=q.front();q.pop();
			q.push(i+j);
		}
		else if(*found=='*')
		{
			i=q.front();q.pop();
			j=q.front();q.pop();
			q.push(i*j);
		}
		else if(*found=='/')
		{
			i=q.front();q.pop();
			j=q.front();q.pop();
			q.push(i/j);
		}
		else if(*found=='-' && strlen(found)==1 && q.size()==1)
		{
			i=q.front();q.pop();
			q.push(-i);
		}
		else if(*found=='-' && strlen(found)==1 && q.size()==2)
		{
			i=q.front();q.pop();
			j=q.front();q.pop();
			q.push(i-j);
		}
		else if(*found=='-'&& strlen(found)>1)
		{
			i=atoi(found+1);
			q.push(-i);				
		}
		else
		{
			q.push(*found-'0');
		}
		found=strtok(NULL,&tok);
	}
	return(q.front());	
}

void Test9_2D()
{
	char s[]="3,4,*,1,2,+,+";
	std::cout<<Test9_2(s);	
}

void Test9_11()
{
    DeQueue<int> deq(0);
    deq.Enqueue(10);deq.Enqueue(20);deq.Enqueue(30);deq.Enqueue(40);
    std::cout<<deq.Dequeue()<<" ";
    std::cout<<deq.Dequeue()<<" ";
    std::cout<<deq.Dequeue()<<" ";
    std::cout<<deq.Dequeue()<<" ";
}
int main(int argc, char **argv)
{
	Test9_11();
	getchar();
}