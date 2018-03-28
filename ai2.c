#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define val 4
int space=0;
typedef struct node{
    struct node* P;//parent
    int matrix[val][val];
    int C;//cost
    int x,y,level;
    struct node* next;

}node;
node* close;
node* head;

int r[] = {1,0,-1,0};int c[] = {0,-1,0,1};//initialising row and cloumns

int issafe_func(int x,int y);
 int cost_func(int start[val][val],int goal[val][val]);//manhattan dist
 void print_close_func(node* root);
 void print_node_func(node* root);
void print_matrix_func(int m[val][val]);
void print_path_func(node* root );
void visited_mark_func(node* root,node* P);
int check_visited_close_func(node* root);
node* MinNode_func(node* root);
node *InsertNode_func(int mat[val][val],int x,int y,int newx,int newy,int level,int goal[val][val],node* P);
void Puzzle_func(int goal[val][val]);
int getInvCount(int arr[]);
// find Position of blank from bottom
int findXPosition(int puzzle[val][val]);
_Bool isSolvable(int puzzle[val][val]);

 


int main(){
	
	
	int start[val][val];
	int x,y;
	for(int i=0;i<=val-1;i++){
		for(int j=0;j<=val-1;j++){
			scanf("%d",&start[i][j]);
		}
	}
	
	scanf("%d %d",&x,&y);
	int goal[val][val] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,0}
	};
	
 if (isSolvable(start)){
	 printf("\nsolvable\n\n");
	 head = InsertNode_func(start,x,y,x,y,0,goal,NULL);
	Puzzle_func(goal);
    printf("no of nodes %d\n",space);
 }
	else{printf("not solvable\n");}
	
	
}

int issafe_func(int x,int y){
    return (x>=0 && x<val && y>=0 && y<val);
}
 int cost_func(int start[val][val],int goal[val][val]){
    int sum = 0;
    for(int i=0;i<val;i++) {
            for(int j=0;j<val;j++) {
                for(int p=0;p<val;p++) {
                    for(int q=0;q<val;q++) {
                        if(start[i][j] == goal[p][q] && start[i][j] != 0) {
                            if(i>p) sum += i-p;
                            if(i<p) sum += p-i;
                            if(j>q) sum += j-q;
                            if(j<q) sum += q-j;
                        }
                    }
                }
            }       
        }
        
        
        
    //printf("manhattan distance is %d\n",sum);
    return sum;
    // printf("manhattan distance is %d\n",sum);
 }

void print_close_func(node* root){
    while(root!=NULL){
        for(int i=0;i<=val-1;i++){
            for(int j=0;j<=val-1;j++){
                printf("%d\t",root->matrix[i][j]);

            }
            printf("\n");
        }
        root=root->next;
    }
}


void print_node_func(node* root){
    while(root!=NULL){
        for(int i=0;i<=val-1;i++){
            for(int j=0;j<=val-1;j++){
                printf("%d\t",root->matrix[i][j]);
            }printf("\n");

        }printf("x=%d y=%d cost=%d level=%d total=%d",root->x,root->y,root->C,root->level,root->level+root->C);
        printf("\n");
        root=root->next;
    }
}

void print_matrix_func(int m[val][val]){
    for(int i=0;i<=val-1;i++){
        for(int j=0;j<=val-1;j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_path_func(node* root ){
    if(root->P!=NULL){
        print_path_func(root->P);
    }
    print_matrix_func(root->matrix);
}

void visited_mark_func(node* root,node* P){
    node* temp = (node*)malloc(sizeof(node));
    temp->P=P;
    for(int i=0;i<=val-1;i++){
        for(int j=0;j<=val-1;j++){
            temp->matrix[i][j]=root->matrix[i][j];

        }
    }
    temp->C=root->C;
    temp->x=root->x;
    temp->y=root->y;
    temp->level=root->level;
    temp->next = close;
    close=temp;
}

 
int check_visited_close_func(node* root){ 
 
 	
 	node* temp=close;
 	
 	while(temp!=NULL){
 		int count=0,i,j;
 		
 		for(i=0;i<=val-1;i++){
			for(j=0;j<=val-1;j++){
				if (temp->matrix[i][j]!=root->matrix[i][j]){
					count++;
					break;
				}
			}
			if(count)
			{
				count=0;
				break;
			}
		}
		
		if(i==val && j==val){
			
			
			return 1;
		}
		temp=temp->next;
 	}
 	
 	return 0;
 		
}

node* MinNode_func(node* root)
{   
    
    int min = INT_MAX;
    node* temp;
    node* temp1;
    temp1=root;
    int pos=0;
    int min_pos;
    if(root->next==NULL){
    	return root;
    }
    while (temp1 != NULL) {
    	
    	if(check_visited_close_func(temp1)==0){
    		
		if (min > temp1->C+temp1->level){
		    	min = temp1->C+temp1->level;
		    	
		    	temp=temp1;
		     }
	 
	    }
	    temp1 = temp1->next;
	   }
   
   return temp;      
}

node *InsertNode_func(int mat[val][val],int x,int y,int newx,int newy,int level,int goal[val][val],node* P){

	
	node* temp = (node*)malloc(sizeof(node));
	
		temp->P = P;
		
		for(int i=0;i<=val-1;i++){
			for(int j=0;j<=val-1;j++){	
				temp->matrix[i][j]=mat[i][j];
			}
		}
		int swap = temp->matrix[newx][newy];
		temp->matrix[newx][newy] = temp->matrix[x][y];
		temp->matrix[x][y] = swap;
		temp->C = cost_func(temp->matrix,goal);	
		temp->level = level;	
		temp->x = newx;
		temp->y = newy; 
		temp->next = NULL;
		return temp;
}
void Puzzle_func(int goal[val][val]){
	
	while(head!=NULL){
	
		node* temp = MinNode_func(head);
		
		if(temp->C==0){
			print_path_func(temp);
			printf("ended\n");
			break;
		}
		
		int x=temp->x;
		int y=temp->y;
		
		if(check_visited_close_func(temp)==0)
		{
						
			for(int i=0;i<4;i++){
				
				if(issafe_func(x+r[i],y+c[i])){
                    space++;
				
					node* temp1 = InsertNode_func(temp->matrix,x,y,x+r[i],y+c[i],temp->level+1,goal,temp);
				
						if(head==NULL){
							head=temp1;
						}
						else{
							temp1->next=head;
							head=temp1;
						}
					
				}
			}
		}
		visited_mark_func(temp,temp->P);
		
	}
	
	
}

int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < val * val - 1; i++)
    {
        for (int j = i + 1; j < val * val; j++)
        {
         
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}
int findXPosition(int puzzle[val][val])
{

    for (int i = val - 1; i >= 0; i--)
        for (int j = val - 1; j >= 0; j--)
            if (puzzle[i][j] == 0)
                return val - i;
}
 
 _Bool isSolvable(int puzzle[val][val])
{
 
    int invCount = getInvCount((int*)puzzle);
 
    
    if (val & 1)
        return !(invCount & 1);
 
    else     //  even
    {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}