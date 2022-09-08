#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <limits.h>
#include <string.h>
using namespace std;

#define FALSE -1
#define OK 1
#define N 3000

typedef int status;
int FLAG;
int ans_var[N];
int n;//字句数
int cnfsave[30000][4000];
int num;//变元数
int imvalue_var[10000];

typedef struct datanode1
{ 
	int data;
	datanode1 *next;
}datanode1;

typedef struct Hnode
{
	datanode1 *headdata;
	Hnode *next; 
}Hnode;


bool scancnf(char *filename){
	char ch;
	int i,j,flag = 0,sum = 0;
	n=0;
	num=0;
	FILE *file;
	file = fopen(filename,"r");
	if(file==NULL) return  false;
	do{
		fscanf(file,"%c",&ch);
		if(flag == 0&&ch=='p') break;
		flag = 1; 
		if(ch=='\n'){
			fscanf(file,"%c",&ch);
			if(ch=='p') break;
		}
	}while(1);
	do{
		fscanf(file,"%c",&ch);
	}while(ch>'9'||ch<'1');
	ungetc(ch,file);
	fscanf(file,"%d",&num);
	fscanf(file,"%d",&n);
	for(i = 0;i < n;i++){
		for(j = 0;;j++){
            fscanf(file,"%d",&cnfsave[i][j]);		
			if(cnfsave[i][j]==0) break;
		}
	}
	fclose(file);
	return true; 
}

Hnode* deletHnode(Hnode *list,Hnode *root)
{
	datanode1 *p,*p1; 
	Hnode *T = root,*T1;
	p = list->headdata;
	list->headdata = NULL; 
	while(p!=NULL)
	{ 
		p1 = p;
		p = p->next;
		free(p1);
	}
	while(T)
	{
		if(T->next==list){
			T->next = T->next->next; 
			free(list);
			return T;
		}
		T = T->next;
	}
}

void deletclause(Hnode *root,int data){
	Hnode *T,*T1;
	datanode1 *p,*p1;
	T = root->next;
	while(T!=NULL)
	{
		p = T->headdata;
		while(T->headdata&&T->headdata->data == -1 * data)
		{
			p1 = T->headdata;
			T->headdata = T->headdata->next;
			free(p1);
			p = T->headdata;
		}
		while(p!=NULL)
		{
			if(p->data == data)
			{
				T = deletHnode(T,root);
				break;
			}
			if(p->next&&p->next->data == -1 * data)
			{
				p1 = p->next;
				p->next = p->next->next;
				free(p1);
			}
			p = p->next;
		}
		T = T->next;
	}
	return;
}

int search_single_clause(Hnode *root)  
{
    Hnode *p;
    p=root->next;
    while(p)
    {
        if(p->headdata->next==NULL) return (p->headdata->data);
        p=p->next;
    }
    return 0;
}

int isempty(Hnode *root)
{
    Hnode *p;
    p=root->next;
    while(p)
    {
        if(!p->headdata) return 1;
        p=p->next;
    }
    return 0;
}
Hnode *copy(Hnode *root)
{
	Hnode *newroot,*p,*q,*Tail;
    datanode1 *pp,*qq,*tail;
    newroot = (Hnode *)malloc(sizeof(Hnode)*1);
    q = (Hnode *)malloc(sizeof(Hnode)*1);
    p=root->next;
    newroot->next=q;
    while(p)
    {
        pp=p->headdata;
		qq=(datanode1 *)malloc(sizeof(datanode1));
		q->headdata=NULL;
		while(pp)
		{
			qq->data=pp->data;
			qq->next = q->headdata;
			q->headdata = qq;
			qq =(datanode1 *)malloc(sizeof(datanode1));
			pp=pp->next;
		}
		p=p->next;
		q -> next = (Hnode *)malloc(sizeof(Hnode)*1);
		Tail = q;
		q=q->next;
    }
	Tail->next = NULL;
	return newroot;
}

Hnode *createclause(Hnode *root, int data)
{
	Hnode *p;
	p=(Hnode *)malloc(sizeof(Hnode));
	datanode1 *q;
	q=(datanode1 *)malloc(sizeof(datanode1));
	p->next=root->next;
	p->headdata=q;
	p->headdata->data=data;
	p->headdata->next=NULL;
	root->next=p;
	return root;
}

void cnf_to_lb(Hnode **root)
{
	int j=0;
	Hnode *p, *pp;
	datanode1 *q,*qq;
	(*root) = (Hnode *)malloc(sizeof(Hnode));
	(*root)->next = (Hnode *)malloc(sizeof(Hnode));
	p=(*root)->next;
	for(int i=0;i<n;i++)
	{
		q = (datanode1 *)malloc(sizeof(datanode1));
		p->headdata = q;
		while(cnfsave[i][j]!=0)
		{
			q->data=cnfsave[i][j];
			q->next = (datanode1 *)malloc(sizeof(datanode1));
			qq = q;
			q=q->next;
			j++;
		}
		qq->next = NULL;
		p->next = (Hnode *)malloc(sizeof(Hnode));
		pp = p;
		p=p->next;
		j=0;
	}
	pp->next = NULL;
	cout << "读取的文字数为：" << num << "   " << "子句数为： " << n << endl;
	return ;
}

int imvalue_varde(Hnode *root)
{
	int max=0,maxi=0;
	Hnode *p;
	datanode1 *q;
	p=root->next;
	while(p)
	{
		q=p->headdata;
		while(q)
		{
			if(q->data>0) imvalue_var[q->data]++;
			else imvalue_var[num-q->data]++;
			q=q->next;
		}
		p=p->next;
	}
	for(int i=1;i<=num*2;i++)
	{
		if(imvalue_var[i]>max) {max=imvalue_var[i],maxi=i;}
	}
	if(maxi > num) maxi = -(maxi - num);
	return maxi;
}

int imvalue_varer(Hnode *root)
{
	int max=0,maxi=0;
	Hnode *p;
	datanode1 *q;
	p=root->next;
	while(p)
	{
		if(p->headdata!=NULL&&p->headdata->next!=NULL&&p->headdata->next->next==NULL)
		{
			q=p->headdata;
			while(q)
			{
				if(q->data>0) imvalue_var[q->data]++;
				else imvalue_var[num-q->data]++;
				q=q->next;
			}
			p=p->next;
		}
		else p=p->next;
	}
	for(int i=1;i<=num*2;i++)
	{
		if(imvalue_var[i]>max) {max=imvalue_var[i],maxi=i;}
	}
	if(maxi > num) maxi = -(maxi - num);
	return maxi;
}
int zdpll (Hnode *root, int flag)
{ 
	int data;
	while(data = search_single_clause(root))
	{
		if(data > 0) ans_var[data] = 1;
		else ans_var[-data] = -1;
		deletclause(root,data);
		if(root->next==NULL) return 1;
		else if(isempty(root)){
			return 0;
		}
	}
    if (flag == 4)
	{memset(imvalue_var,0,sizeof(int)*(2*num+1));
	data = imvalue_varer(root);
	if(data == 0) data = root->next->headdata->data;}
    else data = root->next->headdata->data;
	Hnode *rootfu = copy(root); 
	if(zdpll(createclause(root,data),flag)) 
	{
		return 1;
	}
	else 
	{
		return zdpll(createclause(rootfu,-data),flag);
	}
}