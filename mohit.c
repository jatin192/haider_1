#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define max(a,b) (a>b)?a:b

typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

typedef struct queue{
    int front;
    int rear;
    int capacity;
    int size;
    treeNode** array;
}queue;

typedef struct stack{
    int top;
    int capacity;
    treeNode **array;
}stack;

stack* createStack(int cap){
    stack *myStack = (stack*)malloc(sizeof(stack));
    myStack->capacity=cap;
    myStack->top=-1;
    myStack->array=(treeNode**)malloc(sizeof(treeNode*));
    return myStack;
}

void printStack(stack* myStack){
    int temp=myStack->top;
    while(temp!=-1){
        printf("%d ",myStack->array[temp--]->data);
    }
    printf("\n");
}

void push(treeNode* x, stack* myStack){
    if(myStack->top==myStack->capacity-1)return;
    myStack->array[++myStack->top]=x;
}

treeNode* pop(stack *myStack){
    if(myStack->top==-1)return NULL;
    return myStack->array[myStack->top--];
}

treeNode* root=NULL;

bool isFull(queue* myQueue){
    return myQueue->size==myQueue->capacity;
}

bool isEmpty(queue* myQueue){
    return myQueue->size==0;
}

queue* createQueue(int cap){
    queue* myQueue=(queue*)malloc(sizeof(queue));
    myQueue->array=(treeNode**)malloc(sizeof(treeNode*)*cap);
    myQueue->front=-1;
    myQueue->rear=0;
    myQueue->capacity=cap;
    myQueue->size=0;
    return myQueue;
}

void enqueue(treeNode* newNode, queue* myQueue){
    if(isFull(myQueue)){puts("FULL!");return;}
    if(myQueue->front==-1){myQueue->front++;}
    myQueue->array[myQueue->rear]=newNode;
    myQueue->rear=(myQueue->rear+1)%myQueue->capacity;
    myQueue->size++;    
}

treeNode* dequeue(queue* myQueue){
    int temp=myQueue->front;
    myQueue->front=(myQueue->front+1)%myQueue->capacity;
    myQueue->size--;
    return myQueue->array[temp];
}

void printQueue(queue* myQueue){
    int front=myQueue->front;
    int rear=myQueue->rear;
    int temp_size=myQueue->size;
    for(int i=0;i<temp_size;i++){
        treeNode* temp_node=myQueue->array[(front+i)%myQueue->capacity];
        printf("%d ",temp_node->data);
    }
    printf("\n");
}

bool isNum(char input){
    if(input>='0' && input<='9')return true;
    return false;
}

void myCustomPrintTree(treeNode* root){
    queue* myQueue=createQueue(100);
    printf("%d:",root->data);
    int left_data=(root->left!=NULL)?root->left->data:-1;
    int right_data=(root->right!=NULL)?root->right->data:-1;
    printf("L%d, ",left_data);
    printf("R%d\n",right_data);
    if(root->left!=NULL)myCustomPrintTree(root->left);
    if(root->right!=NULL)myCustomPrintTree(root->right);
}

void inOrder(treeNode* root){
    // if(root->left==NULL&&root->right==NULL){
        // printf("%d ",root->data);
    // }
    treeNode* current=root;
    stack* myStack=createStack(100);
    while(myStack->top!=-1 || current!=NULL){
        if(current==NULL && myStack->top==-1){
            break;
        }
        while(current!=NULL){
            push(current,myStack);
            current=current->left;
        }
        if(current==NULL && myStack->top!=-1){
            current=pop(myStack);
            printf("%d ",current->data);
            current=current->right;            
        }
    }
    printf("\n");
}

void inOrderRec(treeNode* root){
    if(root==NULL)return;
    inOrderRec(root->left);
    printf("%d ",root->data);
    inOrderRec(root->right);
}

void postOrder(treeNode* root){
    treeNode* current=root;
    stack* myStack=createStack(100);
    bool temp=true;
    while(temp || myStack->top!=-1){
        if(temp)temp=!temp;
        while(current!=NULL){
            if(current->right!=NULL)push(current->right,myStack);
            push(current,myStack);
            current=current->left;
        }
        current=pop(myStack);
        if(current->right!=NULL && current->right==myStack->array[myStack->top]){
            pop(myStack);
            push(current,myStack);
            current=current->right;
        }else{
            printf("%d ",current->data);
            current=NULL;
        }
    }
    printf("\n");
}

void postOrderRec(treeNode* root){
    if(root==NULL)return;
    postOrderRec(root->left);
    postOrderRec(root->right);
    printf("%d ",root->data);
}

void preOrder(treeNode* root){
    stack* myStack=createStack(100);
    push(root,myStack);
    // printf("root->element=%d\n",pop(myStack)->data);
    while(myStack->top!=-1){
        treeNode* temp=pop(myStack);
        printf("%d ",temp->data);
        if(temp->right!=NULL)push(temp->right,myStack);
        if(temp->left!=NULL)push(temp->left,myStack);
    }
    printf("\n");
}

void preOrderRec(treeNode* root){
    if(root==NULL)return;
    printf("%d ",root->data);
    preOrderRec(root->left);
    preOrderRec(root->right);
}

void insert(int data, treeNode* root){
    treeNode* newNode=(treeNode*)malloc(sizeof(treeNode));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    if(root==NULL){
        root=newNode;
        return;
    }
    treeNode* temp=root;
    if(data>temp->data){
        if(temp->right==NULL)temp->right=newNode;
        else{insert(data,temp->right);}
    }
    else{
        if(temp->left==NULL)temp->left=newNode;
        else{insert(data,temp->left);}
    }
}

treeNode* arrangeTree(int* input, int n){
    treeNode* root=(treeNode*)malloc(sizeof(treeNode));
    root->data=input[0];
    root->left=NULL;
    root->right=NULL;
    for(int i=1;i<n;i++)insert(input[i],root);
    return root;
}

int leafCount(treeNode* root){
    if(root->left==NULL && root->right==NULL)return 1;
    int ans=0;
    if(root->left!=NULL)ans+=leafCount(root->left);
    if(root->right!=NULL)ans+=leafCount(root->right);
    return ans;
}

int internalNodeCount(treeNode* root){
    if(root->left==NULL && root->right==NULL)return 0;
    int ans=1;
    if(root->left!=NULL)ans+=(internalNodeCount(root->left));
    if(root->right!=NULL)ans+=(internalNodeCount(root->right));
    return ans;
}

int findTreeHeight(treeNode* root){
    if(root->left==NULL && root->right==NULL)return 1;
    int shortAns=0,leftAns=0,rightAns=0;
    if(root->left!=NULL)leftAns=findTreeHeight(root->left);
    if(root->right!=NULL)rightAns=findTreeHeight(root->right);
    shortAns=max(leftAns,rightAns);
    return shortAns+1;
}

void deleteTree(treeNode* root){
    if(root==NULL)return;
    if(root->left==NULL&&root->right==NULL){free(root);return;}
    if(root->left!=NULL)deleteTree(root->left);
    if(root->right!=NULL)deleteTree(root->right);
    free(root);
    root=NULL;
}

treeNode* findNodeParent(int data, treeNode* root){
    if((root->left&&root->left->data==data)||(root->right&&root->right->data==data))return root;
    else if(data>root->data)return findNodeParent(data,root->right);
    else if(data<root->data)return findNodeParent(data,root->left);
    else if(data==root->data)return NULL;
    else{
        printf("No Tree Node with data %d exists!\n",data);
        return NULL;
    }
}

bool checkNode(int data, treeNode* root){
    if(root==NULL)return false;
    else if(data==root->data)return true;
    bool a=checkNode(data,root->left);
    bool b=checkNode(data,root->right);
    return (a||b);
}

treeNode* findNode(int data, treeNode* root){
    if(root==NULL){return NULL;}
    if(data>root->data)return findNode(data,root->right);
    else if(data<root->data)return findNode(data,root->left);
    else if(data==root->data)return root;
    else{puts("error");return NULL;}
}


treeNode* findMax(treeNode* root){
    treeNode* ans=root;
    while(root!=NULL){
        if(root->data>ans->data)ans=root;
        root=root->right;
    }
    return ans;
}

treeNode* deleteTreeNode(int data, treeNode* root){
    if(root->data==data&&(root->left==NULL^root->right==NULL)){
        treeNode* temp=(root->right)?root->right:root->left;
        // printf("temp=%d\n",temp->data);
        root=temp;
        return temp;
    }
    if(root==NULL)return root;
    if(data<root->data)root->left=deleteTreeNode(data,root->left);
    else if(data>root->data)root->right=deleteTreeNode(data,root->right);
    else{
        // printf("Hello");
        if (root->left==NULL){
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right==NULL){
            treeNode* temp=root->left;
            free(root);
            return temp;
        }
        treeNode* temp=findMax(root->left);
        root->data=temp->data;
        root->left=deleteTreeNode(temp->data,root->left);
        // myCustomPrintTree(root);
    }
    return root;
}

treeNode* menuOption1(){
    int n;
    scanf("%d",&n);
    int *myArray=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)scanf("%d",&myArray[i]);
    treeNode* root=arrangeTree(myArray,n);
    // myCustomPrintTree(root);
    free(myArray);
    return root;
}

treeNode* menuOption2(treeNode* root){
    int data;
    printf("Enter Node's data to be deleted : ");
    scanf("%d",&data);
    treeNode* ans;
    // printf("root exists=%d\n",(checkNode(data,root))?1:0);
    if(checkNode(data,root))ans=deleteTreeNode(data,root);
    else{puts("error");return NULL;}
    printf("\n");
    return ans;
}

void menuOption3(treeNode* root){
    if(root==NULL){puts("There is no valid input tree to count leaves of... Please Input tree first!");return ;}
    printf("Number of Leaf Nodes = %d\n",leafCount(root));
    printf("Number of Internal Nodes = %d\n",internalNodeCount(root));
    printf("Height of Tree = %d\n",findTreeHeight(root)-1);
}

void openMenu(){
    int option=0;
    while(option!=7){
        printf("1. Insert Nodes\n2. Delete Node\n3. Details of Tree (leaves, internal node count, tree height\n4. In-order Traversal\n5. Pre-Order Traversal\n6. Post-Order Traversal\n7. Exit\n");
        // printf("8. myCustomTreeInput\n9. preorder Rec Traversal\n10. In Order Traversal Rec\n11. Post Order Traversal\n");
        scanf("%d",&option);
        switch(option){
            case 1:
                root=menuOption1();
                break;
            case 2:
                root=menuOption2(root);
                break;
            case 3:
                menuOption3(root);
                break;        
            case 4:
                inOrder(root);
                break;
            case 5:
                preOrder(root);
                break;
            case 6:
                postOrder(root);
                break;
            case 7:
                break;
            //delete following till default
            // case 8:
            //     myCustomPrintTree(root);
            //     break;
            // case 9:
            //     preOrderRec(root);puts("");
            //     break;
            // case 10:
            //     inOrderRec(root);puts("");
            //     break;
            // case 11:
            //     postOrderRec(root);puts("");
            //     break;
            default:
                puts("Invalid Input. Try Again!");
                break;
        }
    }
    deleteTree(root);
}

int main(){
    openMenu();
}