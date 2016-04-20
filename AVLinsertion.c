#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0

struct node{
	struct node *lchild;
	int info;
	struct node *rchild;
	int balance;
};

struct node *root=NULL;
struct node *rotatel(struct node *p);
struct node *rotater(struct node *p);
struct node *insert(struct node *root,int);
struct node *insert_lcheck(struct node *p,int *q);
struct node *insert_rcheck(struct node *p,int *q);
struct node *insert_lbal(struct node *p);
struct node *insert_rbal(struct node *p);
void inorder(struct node *root);


main()
{
	int key,choice;
	
	while(1)
	{
		printf("\nENTER\n1.to insert\n2.to display\n3.to exit\n");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				printf("\n enter the value to be inserted\n");
				scanf("%d",&key);
				root=insert(root,key);
				break;
				
			case 2:
				inorder(root);
				break;
			case 3:
				exit(1);
			default:
				printf("\nInvalid choice\n");
		}
		
	}
}

struct node *rotater(struct node *p)
{
	struct node *q;
	q=p->lchild;
	p->lchild=q->rchild;
	q->rchild=p;
	return q;
}

struct node *rotatel(struct node *p)
{
	struct node *q;
	q=p->rchild;
	p->rchild=q->lchild;
	q->lchild=p;
	return q;
}

struct node *insert(struct node *root,int k)
{
	static int taller;
	
	if(root==NULL)
	{
		root=(struct node *)malloc(sizeof(struct node));
		root->info=k;
		root->lchild=root->rchild=NULL;
		root->balance=0;
		taller=true;
	}
	else if(k<root->info)
	{
		root->lchild=insert(root->lchild,k);
		if(taller==true)
		  root=insert_lcheck(root,&taller);
		  
	}
	else if(k>root->info)
	{
		root->rchild=insert(root->rchild,k);
		 if(taller==true)
		   root=insert_rcheck(root,&taller);
	}
	else
	 {
	 	printf("\nduplicate element not allowed\n");
	 	taller=false;
	 }
	 return root;
}
 
 struct node *insert_lcheck(struct node *p,int *n)
 {
 	switch(p->balance)
 	{
 		case 0:
 			p->balance=1;
 			break;
 		case -1:
 			p->balance=0;
 			*n=false;
 			break;
 		case 1:
 			p=insert_lbal(p);
 			*n=false;
 	}
 	return p;
 }
 
 struct node *insert_lbal(struct node *p)
 {
 	struct node *a,*b;
 	  a=p->lchild;
 	  if(a->balance==1)
 	  {
 	  	p->balance=0;
 	  	a->balance=0;
 	  	p=rotater(p);
 	  	
 	  }
 	  else
 	  {
 	  	b=a->rchild;
 	  	  switch(b->balance)
 	  	  {
 	  	  	case -1:
 	  	  		p->balance=0;
 	  	  		a->balance=1;
 	  	  		break;
 	  	  	case 1:
 	  	  		p->balance=-1;
 	  	  		a->balance=0;
 	  	  		break;
 	  	  	case 0:
 	  	  		p->balance=0;
 	  	  		a->balance=0;
 	  	  }
 	  	  
 	  	  b->balance=0;
 	  	  p->lchild=rotatel(a);
 	  	  p=rotater(p);
 	  }
 	  return p;
 }
 
 struct node *insert_rcheck(struct node *p,int *n)
 {
 	switch(p->balance)
 	{
 		case 0:
 			p->balance=-1;
 			break;
 		case 1:
 			p->balance=0;
 			*n=false;
 			break;
 		case -1:
 			p=insert_rbal(p);
 			*n=false;
 	}
 	return p;
 }
 
 struct node *insert_rbal(struct node *p)
 {
 	struct node *a,*b;
 	 a=p->rchild;
 	 if(a->balance==-1)
 	 {
 	 	p->balance=0;
 	 	a->balance=0;
 	 	p=rotatel(p);
 	 	
 	 }
 	 else
 	 {
 	 	b=a->rchild;
 	 	switch(b->balance)
 	 	{
 	 		case -1:
 	 			p->balance=1;
 	 			a->balance=0;
 	 			break;
 	 		case 1:
 	 			p->balance=0;
 	 			a->balance=-1;
 	 			break;
 	 		case 0:
 	 			p->balance=0;
 	 			a->balance=0;
 	 	}
 	 	b->balance=0;
 	 	p->rchild=rotater(a);
 	 	p=rotatel(p);
 	 }
 	 return p;
 }
 
 void inorder(struct node *root)
 {
 	if(root!=NULL){
 	inorder(root->lchild);
 	printf("%d\t",root->info);
 	inorder(root->rchild);
     }
}
