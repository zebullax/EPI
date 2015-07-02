#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct node
{
    int data;
    struct node* next;
};
struct node* newNode(int data)
{
  struct node* node = (struct node*) malloc(sizeof(struct node));
  node->data = data;
  node->next = NULL; 
  return(node);
}
void deleteList(node* h)
{
	node* next;
	while (h)
	{
		next=h->next;
		free(h);
		h=next;
	}
}
void printList(node* h)
{
	while(h)
	{
		cout<<h->data<<",";
		h=h->next;
	}
}
node* findMiddle(node* L)
{
	node *S=L,*F=L;
	while(F&&F->next)
	{
		S=S->next;
		F=F->next->next;
	}
	if(F)
		return S->next;
	else
		return S;
}
node* findCycle(node* h)
{
	if (!h)
		return NULL;
	node *s=h,*f=h;

	do{
		s=s->next;
		f=f->next->next;
	}while(s&&f && s!=f);

	if(!s || !f)
		return NULL;//no cycle
	s=h;
	while(s!=f)
	{
		s=s->next;
		f=f->next;
	}
	return s;
}
node* reverseList(node *h)
{
	node *c,*p,*n;
	if(!h)
		return NULL;
	if(!h->next)
		return h;
	p=h;c=h->next;p->next=NULL;
	while(c)
	{
		n=c->next;
		c->next=p;
		p=c;
		c=n;
	}
	return p;
}

void Test8_1D()
{
	node* L=newNode(2);
	L->next=newNode(3);
	L->next->next=newNode(7);
	node* F=newNode(4);
	F->next=newNode(11);
	
	node*h=newNode(0),*retH=h,*tmp=NULL;

	while(L!=NULL && F!=0)
	{
		if(L->data<=F->data)
		{
			tmp=L->next;
			h->next=L;
			L=tmp;
		} 
		else
		{
			tmp=F->next;
			h->next=F;
			F=tmp;
		}
		h=h->next;
	}
	if(L==NULL)
		h->next=F;
	else if(F==NULL)
	{
		h->next=L;
	}
	retH=retH->next;
	while(retH!=NULL)
	{
		cout<<retH->data<<",";
		retH=retH->next;
	}
}



void Test8_2D()
{
	node* L;
	L=newNode(2);
	L->next=newNode(3);
	L->next->next=newNode(7);
	L->next->next->next=newNode(9);
	L->next->next->next->next=newNode(10);
	L->next->next->next->next->next=newNode(11);
	L->next->next->next->next->next->next=L->next->next->next;
	node *c=findCycle(L);
	if(c)
		cout<<"First node in the cycle is "<<c->data<<endl;
	else
		cout<<"No cycle\n";	
}

void Test8_5D()
{
	node* L=newNode(2);
	L->next=newNode(3);
	L->next->next=newNode(7);
	L->next->next->next=newNode(9);
	L->next->next->next->next=newNode(10);
	L->next->next->next->next->next=newNode(11);
	L->next->next->next->next->next->next=newNode(12);
	L->next->next->next->next->next->next->next=L->next->next;
	
	node*s=L,*f=L;
	do{
		s=s->next;
		f=f->next->next;
	}while((s!=NULL && f!=NULL)&&(s!=f));

	 if(f!=s)
	 {
		 cout<<"No cycle\n";
		 return;
	 }
	 else
		 s=L;
	while(f!=s)
	{
		s=s->next;
		f=f->next;
	}
	cout<<s->data<<" is the beginning of the cycle";
}
void Test8_4(node* _L, node* _R)
{
	node* L=_L;
	node* R=_R;
	while(R!=NULL)
	{
		L=_L;
		while(L!=NULL && L!=R)
			L=L->next;
		if(L==R)
		{
			cout<<L->data;
			return;
		}
		else
			R=R->next;
	}
	cout<<"No overlap\n";
}
void Test8_4D()
{
	node* L=newNode(2);
	node *R=newNode(3);
	L->next=newNode(3);
	L->next->next=newNode(7);
	L->next->next->next=newNode(9);
	L->next->next->next->next=newNode(10);
	L->next->next->next->next->next=newNode(11);
	R->next=newNode(7);
	R->next->next=newNode(8);
	R->next->next->next=L->next;
	Test8_4(L,R);
}
node* Test8_6(node* L)
{
	if(!L)
		return NULL;
	
	node *oH=L,*eH=L->next;
	node *odd=oH,*even=eH;

	while(odd && even)
	{
		odd->next=(even->next==0?eH:even->next);
		even->next=(even->next==0?0:odd->next->next);
		if(odd->next!=eH)
		{
			odd=odd->next;
			even=even->next;
		}
		else
			return oH;
	}
	odd->next=eH;
	return oH;
}
void Test8_6D()
{
	node* L=newNode(1);	
	L->next=newNode(2);
	L->next->next=newNode(3);
	L->next->next->next=newNode(4);
	L->next->next->next->next=newNode(5);
	L->next->next->next->next->next=newNode(6);
	L->next->next->next->next->next->next=newNode(7);
	L=Test8_6(L);
	while(L)
	{
		cout<<L->data<<" ";
		L=L->next;
	}
}

void Test8_9D()
{
	node* L=newNode(2);
	L->next=newNode(3);
	L->next->next=newNode(7);
	L->next->next->next=newNode(9);
	L->next->next->next->next=newNode(10);
	L->next->next->next->next->next=newNode(11);
	L=reverseList(L);
	printList(L);
}

void Test8_10D()
{
	node* L=newNode(2);
	L->next=newNode(3);
	L->next->next=newNode(4);
	L->next->next->next=newNode(5);
	L->next->next->next->next=newNode(4);
	L->next->next->next->next->next=newNode(3);
	L->next->next->next->next->next->next=newNode(2);
	//find the middle 
	node* M=findMiddle(L);
	M=reverseList(M);
	node *Mh=M,*Lh=L;
	while(M)
	{
		if(M->data!=L->data)
		{
			cout<<"No palindrome\n";
			return;
		}	
		M=M->next;
		L=L->next;
	}
	cout<<"Palindrome\n";
}

int main(int argc, char** argv)
{
	Test8_2D();
	getchar();
}