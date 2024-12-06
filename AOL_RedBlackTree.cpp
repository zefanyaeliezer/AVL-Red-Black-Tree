#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Note:
// P: Parent
// R: Right
// L: Left


struct Node
{
	int number; 
	char color[1212];
	Node *P;
	Node *R;
	Node *L;
};

struct llNode
{
	int number;
	llNode *next;
}*head=NULL, *tail=NULL;

void push_linked_list(int number){
	llNode *newllNode = (llNode*)malloc(sizeof(llNode));
	newllNode->number = number;
	newllNode->next = NULL;
	if(!head)
	{
		head = tail = newllNode;
	}
	else
	{
		tail->next = newllNode;
		tail = newllNode;
	}
}

Node *Root=NULL;

Node *createNode(int number)
{
	Node *newNode=(Node *)malloc(sizeof(Node));
	newNode->number=number;
	strcpy(newNode->color,"RED");
	newNode->R=newNode->L=newNode->P=NULL;
	return newNode;
}

Node *insert(Node *currNode,Node *newNode) 
{
	if (!currNode)
	{
		return newNode;
	}
	else if (newNode->number<currNode->number)
	{
		currNode->L=insert(currNode->L,newNode);
		currNode->L->P=currNode;
	}
	
	else if(newNode->number>currNode->number)
	{
		currNode->R=insert(currNode->R,newNode);
		currNode->R->P=currNode;
	}
	
	return currNode;
}


void R_Rotate(Node *newNode)
{
	Node *L=newNode->L;
	newNode->L=L->R;
	
	if (newNode->L)
	{
		newNode->L->P=newNode;
	}
	
	L->P=newNode->P;
	
	if (newNode->P==NULL)
	{
		Root=L;
	}
	else if (newNode==newNode->P->L)
	{
		newNode->P->L=L;
	}
	else
	{
		newNode->P->R=L;
	}
	
	L->R=newNode;
	newNode->P=L;
}


void L_Rotate(Node *newNode)
{
	Node *R=newNode->R;
	newNode->R=R->L;
	
	if (newNode->R)
	{
		newNode->R->P=newNode;
	}
	
	R->P=newNode->P;
	
	if (newNode->P==NULL)
	{
		Root=R;
	}
	
	else if (newNode==newNode->P->L)
	{
		newNode->P->L=R;
	}
	
	else
	{
		newNode->P->R=R;
	}
	
	R->L=newNode;
	newNode->P=R;
}


void adjustRedBlackTree(Node *root,Node *newNode)
{
	Node *P_Node=NULL;
	Node *grandP_Node=NULL;

	while(newNode!=root&&strcmp(newNode->color,"RED")==0&&strcmp(newNode->P->color,"RED")==0)
	{
		P_Node=newNode->P;
		grandP_Node=newNode->P->P;
		
		if(P_Node==grandP_Node->L)
		{
			Node *uncle_newNode=grandP_Node->R;
			
			if (uncle_newNode&&strcmp(uncle_newNode->color,"RED")==0)
			{
				strcpy(grandP_Node->color,"RED");
				strcpy(P_Node->color,"BLACK");
				strcpy(uncle_newNode->color,"BLACK");
				newNode=grandP_Node;
			}
			else
			{
				if(newNode==P_Node->R)
				{
					L_Rotate(P_Node);
					newNode=P_Node;
					P_Node=newNode->P;
				}
				R_Rotate(grandP_Node);
				strcpy(P_Node->color,grandP_Node->color);
				strcpy(grandP_Node->color,P_Node->color);
				newNode=P_Node;
			}
			
		}
		else
		{
			Node *uncle_newNode=grandP_Node->L;
			
			if(uncle_newNode&&strcmp(uncle_newNode->color,"RED")==0)
			{
				strcpy(grandP_Node->color,"RED");
				strcpy(P_Node->color,"BLACK");
				strcpy(uncle_newNode->color,"BLACK");
				newNode=grandP_Node;
			}
			else
			{
				if (newNode==P_Node->L) 
				{
					R_Rotate(P_Node);
					newNode=P_Node;
					P_Node=newNode->P;
				}
				L_Rotate(grandP_Node);
				strcpy(P_Node->color,grandP_Node->color);
				strcpy(grandP_Node->color,P_Node->color);
				newNode=P_Node;
			}
		}
	}
}


void inorder(Node *currNode)
{
	if (currNode) 
	{
		inorder(currNode->L);
		printf("%d ",currNode->number);
		inorder(currNode->R);
	}
}


int main()
{
    // Insert the number using linkedlist
	push_linked_list(41);
	push_linked_list(22);
	push_linked_list(5);
	push_linked_list(51);
	push_linked_list(48);
	push_linked_list(29);
	push_linked_list(18);
	push_linked_list(21);
	push_linked_list(45);
	push_linked_list(3);
	
	llNode *traverse = head;
	Node *newNode;
	// traverse and insert every linkedlist->number to Red Black Tree
	while(traverse)
	{
		newNode=createNode(traverse->number);
		Root=insert(Root,newNode);
		adjustRedBlackTree(Root,newNode);
		strcpy(Root->color,"BLACK");
		traverse = traverse->next;
	}
	
	puts("Inorder Traversal of Created Tree");
	inorder(Root);
	return 0;
}

