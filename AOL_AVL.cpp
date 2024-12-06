#include <stdio.h>
#include <stdlib.h>

// Note:
// L=Left
// R=RigHt
// H=HeigHt
	

struct Node{
    int number;
    Node *L; 
	Node *R; 
    int H; 
};



Node *Root=NULL;


Node *createNode(int number)
{
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->number=number;
    newNode->H=1;
    newNode->L=newNode->R=NULL;
    return newNode;
}


int getMax_H(int L, int R)
{
	if(L>R)
	{
		return L;
	}
	
	else
	{
		return R;
	}
}


int get_H(Node *currNode)
{
	if(!currNode)
	{
		return 0;
	}
	
	else
	{
		return currNode->H;
	}
}


int getbalanceFactor(Node *currNode)
{
	if(!currNode)
	{
		return 0;
	}
	
	else
	{
		return get_H(currNode->L) - get_H(currNode->R);
	}
}


Node *R_rotate(Node *currNode)
{
    Node *temP_Node=currNode->L;
    Node *temp=temP_Node->R;
    temP_Node->R=currNode;
    currNode->L=temp;
    currNode->H=1+getMax_H(get_H(currNode->L), get_H(currNode->R));
    temP_Node->H=1+getMax_H(get_H(temP_Node->L), get_H(temP_Node->R));
    return temP_Node;
}


Node *L_rotate(Node *currNode)
{
    Node *temP_Node=currNode->R;
    Node *temp=temP_Node->L;
    temP_Node->L=currNode;
    currNode->R=temp;
    currNode->H=1+getMax_H(get_H(currNode->L),get_H(currNode->R));
    temP_Node->H=1+getMax_H(get_H(temP_Node->L), get_H(temP_Node->R));
    return temP_Node;
}


Node *balancing(Node *currNode)
{
	int left_H=get_H(currNode->L);
	int right_H=get_H(currNode->R);
	
    currNode->H=1+getMax_H(left_H, right_H);
   
    int balance=getbalanceFactor(currNode);
    
    if(balance>1&&getbalanceFactor(currNode->L)>= 0)
	{
    	return R_rotate(currNode);
	}
    if(balance>1&&getbalanceFactor(currNode->L)<0)
	{
        currNode->L=L_rotate(currNode->L);
        return R_rotate(currNode);
    }
    
    if(balance<-1&&getbalanceFactor(currNode->R)<=0)
	{
    	return L_rotate(currNode);
	}
	
    if(balance<-1&&getbalanceFactor(currNode->R)>0)
	{
        currNode->R=R_rotate(currNode->R);
        return L_rotate(currNode);
    }  
    return currNode;
}


Node *insert(Node *currNode, int number)
{
	if(!currNode){
		currNode=createNode(number);
	}
	
    else if(number<currNode->number)
	{
    	currNode->L=insert(currNode->L, number); 
	}
	
    else if(number>currNode->number)
	{
    	currNode->R=insert(currNode->R, number);
	} 
	
    else
	{
    	return currNode;
	} 
    return balancing(currNode); 
}	


Node *delNode(Node *currNode, int number)
{
	if(!currNode)
	{
		printf("Data not found!\n");
		printf("Press enter to continue...");getchar();
		return currNode;
	}
	
	else if(number<currNode->number)
	{
		currNode->L=delNode(currNode->L, number);
	}
	
	else if(number>currNode->number)
	{
		currNode->R=delNode(currNode->R, number);
	}
	
	else
	{
		if(!currNode->L||!currNode->R)
		{
			Node *child;
			if(!currNode->L)
			{
				child=currNode->R;
			}
			
			else
			{
				child=currNode->L;
			}
			free(currNode);
			return child;
		}
		
		else
		{
			Node *successor=currNode->R;
			while(successor->L)
			{
				successor=successor->L;
			}
			currNode->number=successor->number;
			currNode->R=delNode(currNode->R, successor->number);
			return balancing(currNode);
		}
	}
	return balancing(currNode);
}


void inorder(Node *currNode)
{
	if(currNode)
	{
	inorder(currNode->L);
	printf("%d ",currNode->number);
	inorder(currNode->R);
	}
}


void preorder(Node *currNode)
{
	if(currNode)
	{
	printf("%d ",currNode->number);
	preorder(currNode->L);
	preorder(currNode->R);
	}
}


void postorder(Node *currNode)
{
	if(currNode)
	{
	postorder(currNode->L);
	postorder(currNode->R);
	printf("%d ",currNode->number);
	}
}


int main()
{
	
	bool ExitMenu=false;
	
	while(!ExitMenu)
	{
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		while(!ExitMenu)
		{
			printf("Choose: ");
			int userInput=0;
			scanf("%d",&userInput);getchar();
			if(userInput==1)
			{
				printf("Insert: ");
				int number;
				scanf("%d",&number);getchar();
				Root=insert(Root, number);
				system("cls");
				break;
			}
			else if(userInput==2)
			{
				printf("delete: ");
				int number;
				scanf("%d",&number);getchar();
				Root=delNode(Root,number);
				system("cls");
				break;
			}
			else if(userInput==3)
			{
				printf("inorder: ");
				inorder(Root);
				puts("");
				
				printf("preorder: ");
				preorder(Root);
				puts("");
				
				printf("postorder: ");
				postorder(Root);
				puts("");
				
				printf("Press enter to continue...");
				getchar();
				system("cls");
				break;
			}
			else if(userInput==4)
			{
				ExitMenu=true;
			}
		}
	}
	
	puts("Thank you!");
	puts("Press enter to exit");
	getchar();
	
	return 0;
}
