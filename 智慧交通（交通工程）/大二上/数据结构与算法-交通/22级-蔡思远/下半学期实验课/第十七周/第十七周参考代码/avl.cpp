#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct AVLNode* AVLTree;
struct AVLNode{
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int GetHeight(AVLTree AT){
	int HL, HR, MaxH;
	if (AT){
		HL = GetHeight(AT->Left);
		HR = GetHeight(AT->Right);
		MaxH = HL > HR ? HL : HR;
		return (MaxH + 1);
	}
	else
		return 0;
}

int MAX(int HL, int HR){
	return HL > HR ? HL : HR;
}

AVLTree RebalanceL1(AVLTree A){
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = MAX(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = MAX(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree RebalanceR1(AVLTree A){
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = MAX(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = MAX(GetHeight(B->Right), A->Height) + 1;
	return B;
}

AVLTree RebalanceL2(AVLTree A){
	AVLTree B = A->Left;
	AVLTree C = B->Right;
	A->Left = C->Right;
	B->Right = C->Left;
	C->Right = A;
	C->Left = B;
	A->Height = MAX(GetHeight(C->Right), GetHeight(A->Right)) + 1;
	B->Height = MAX(GetHeight(B->Left), GetHeight(C->Left)) + 1;
	C->Height = MAX(A->Height, B->Height) + 1;
	return C;
}

AVLTree RebalanceR2(AVLTree A){
	AVLTree B = A->Right;
	AVLTree C = B->Left;
	A->Right = C->Left;
	B->Left = C->Right;
	C->Left = A;
	C->Right = B;
	A->Height = MAX(GetHeight(C->Left), GetHeight(A->Left)) + 1;
	B->Height = MAX(GetHeight(B->Right), GetHeight(C->Right)) + 1;
	C->Height = MAX(A->Height, B->Height) + 1;
	return C;
}

AVLTree VALTreeInsert(AVLTree AT, ElementType Data){
	if (AT == NULL){
		AT = (AVLTree)malloc(sizeof(struct AVLNode));
		AT->Data = Data;
		AT->Left = AT->Right = NULL;
		AT->Height = 1;
	}
	
	else if (Data < AT->Data){
		AT->Left = VALTreeInsert(AT->Left, Data);
		if ((GetHeight(AT->Left) - GetHeight(AT->Right))==2){
			if (Data < AT->Left->Data)
				AT = RebalanceL1(AT);
			else
				AT = RebalanceL2(AT);
		}
	}
	
	else if (Data > AT->Data){
		AT->Right = VALTreeInsert(AT->Right, Data);
		if ((GetHeight(AT->Left) - GetHeight(AT->Right))==-2){
			if (Data > AT->Right->Data)
				AT = RebalanceR1(AT);
			else
				AT = RebalanceR2(AT);
		}
	}
	AT->Height = MAX(GetHeight(AT->Left), GetHeight(AT->Right))+1;
	return AT;
}

void InorderTraversal(AVLTree AT){
	if (AT != NULL){
		InorderTraversal(AT->Left);
		printf("%d ", AT->Data);
		InorderTraversal(AT->Right);
	}
}

void PriorTraversal(AVLTree AT){
	if (AT != NULL){
		printf("%d ", AT->Data);
		PriorTraversal(AT->Left);
		PriorTraversal(AT->Right);
	}
}

int main(){
	int Data, m;
	AVLTree AT = NULL;
	scanf("%d", &m);
	for(int i=1; i<=m; i++){
		scanf("%d", &Data);
		AT = VALTreeInsert(AT, Data);
	}
	PriorTraversal(AT);
	printf("\n");
	InorderTraversal(AT);
	return 0;
}


