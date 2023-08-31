#include<stdio.h>
#include<stdlib.h>

#define N 6
#define Infinite 9999

struct node{
    int data;
    int color; // 1 for red and 0 for black
    int distence;
    struct node* left;
    struct node*right;
    struct node* parent;
};

typedef struct node node;

node * head= NULL;

node * create_node(int vertex,int distence){
    node* temp;
    temp=(node*)malloc(sizeof(node));
    temp->color=1;
    temp->data= vertex;
    temp->distence=distence;
    temp->left=NULL;
    temp->right=NULL;
    temp->parent=NULL;
    return temp;

}





node * BST(node * trav, node* temp){
    if (trav==NULL){
    return temp;
    }

    else if( temp->data< trav->data ){
        trav->left= BST(trav->left,temp);
        trav->left->parent= trav;
    }

    else if (temp->data>trav->data)
    {
        trav->right=BST(trav->right,temp);
        trav->right->parent= trav;
    }

    return trav;
    
}

void traverse_inorder(node* temp) {
    if (temp == NULL) {
        return;
    } 
    else {
        traverse_inorder(temp->left);
        printf("%d(%c) ", temp->data, (temp->color == 0) ? 'B' : 'R');
        traverse_inorder(temp->right);
    }
}


void traverse_preorder(node * temp){
    if (temp==NULL){
        return;
    }
    else{
        printf("%d(%c)  " , temp->data,(temp->color==0)?'B':'R'  );
        traverse_preorder(temp->left);
        traverse_preorder(temp->right);

    }




}

void left_rotate(node * temp){
    node* right1= temp->right;
    temp->right=right1->left;
    if (temp->right){
        temp->right->parent=temp;

    }
    right1->parent=temp->parent;
    if(!temp->parent){
        head=right1;
    }
    else if(temp==temp->parent->left){
        temp->parent->left=right1;
    }
    else{
        temp->parent->right=right1;

    }
    right1->left=temp;
    temp->parent=right1;

}

void right_rotate(node* temp){
    node* left1= temp->left;
    temp->left=left1->right;
    if(temp->left){
        temp->left->parent=temp;

    }
    left1->parent=temp->parent;
    if(!temp->parent){
        head=left1;

    }
    else if(temp== temp->parent->left){
        temp->parent->left=left1;
    }
    else{

        temp->parent->right=left1;
    }
    left1->right=temp;
    temp->parent=left1;

}

void fixing(node* root, node * ptr){
    node* parent_ptr=NULL;
    node* grand_parent_ptr=NULL;

   // while((ptr->parent->color==1) && (ptr!=head) && (ptr->color !=0))
    while((ptr->parent != NULL && ptr->parent->color==1) && (ptr!=head) && (ptr->color !=0))

    {


        parent_ptr=ptr->parent;
        grand_parent_ptr= ptr->parent->parent;

        // parent of pointer is left chiled of their parent

        if(parent_ptr==grand_parent_ptr->left){

           node* uncle_ptr= grand_parent_ptr->right;
           
           if(uncle_ptr !=NULL && uncle_ptr->color==1){ //it means color of uncle is red
                 grand_parent_ptr->color=1;
                 parent_ptr->color=0;
                 uncle_ptr->color=0;
                 ptr=grand_parent_ptr;


           }
           else{
                if(ptr== parent_ptr->right){
                    left_rotate(parent_ptr);
                    ptr=parent_ptr;
                    parent_ptr=ptr->parent;

                }
                else{
                    right_rotate(grand_parent_ptr);
                    int temp=parent_ptr->color;
                    parent_ptr->color=  grand_parent_ptr->color;
                    grand_parent_ptr->color=temp;
                    ptr=parent_ptr;                                               

                    }


                }

        }
        else {     //parent pointer is in right of grandparent
            node* uncle_ptr= grand_parent_ptr->left;
            if (uncle_ptr!= NULL && uncle_ptr->color== 1 )
            {
                grand_parent_ptr->color=1;
                parent_ptr->color=0;
                uncle_ptr->color=0;
                ptr=grand_parent_ptr;

            }
            else{

                if(ptr==parent_ptr->left){
                    right_rotate(parent_ptr);
                    ptr=parent_ptr;
                    parent_ptr=ptr->parent;

                }

                else{
                    left_rotate(grand_parent_ptr);
                    int temp=grand_parent_ptr->color;
                    grand_parent_ptr->color=parent_ptr->color;
                    parent_ptr->color=temp;
                    ptr=parent_ptr;

                }
            }
            
        }



        }
}




void red_black_transplant(struct node *u, struct node *v) {
    if (u->parent == NULL) {
        head = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}



void red_black_delete_fixup(struct node *x){
	struct node *w;	

	while(x != NULL && x != head && x->color == 0){
		
		if(x == x->parent->left){
			w = x->parent->right;

			if(w->color == 1){
				w->color = 0;
				x->parent->color = 1;
				left_rotate(x->parent);
				w = x->parent->right;
			}

			if(w->left->color == 0 && w->right->color == 0){
				w->color = 1;
				x->parent->color = 0;
				x = x->parent;
			}
			else{

				if(w->right->color == 0){
					w->color = 1;
					w->left->color = 0;
					right_rotate(w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = 0;
				x->right->color = 0;
				left_rotate(x->parent);
				x = head;		

			}

		}
		else{
			w = x->parent->left;

			if(w->color == 1){
				w->color = 0;
				x->parent->color = 0;
				right_rotate(x->parent);
				w = x->parent->left;
			}

			if(w->left->color == 0 && w->right->color == 0){
				w->color = 1;
				x->parent->color = 0;
				x = x->parent;
			}
			else{

				if(w->left->color == 0){
					w->color = 1;
					w->right->color = 0;
					left_rotate(w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color =0;
				w->left->color = 0;
				right_rotate(x->parent);
				x = 0;

			}
		}

	}

	if (x != NULL) {
    x->color = 0;
}

}


node *tree_search(int key) {
    node *x = head;

    while (x != NULL && x->data != key) {
        if (key < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x; // Returns NULL if key is not found
}



node *tree_minimum(struct node *x){
	while(x->left != NULL){
		x = x->left;
	}
	return x;
}


void red_black_delete(struct node *z) {
	struct node *y, *x;
	int yOriginalColor;

	y = z;
	yOriginalColor = y->color;

    if (y==NULL){
        printf("-1");
        return;

    }
    else{

	if (z->left == NULL) {
		x = z->right;
		red_black_transplant(z, z->right);
	} else if (z->right == NULL) {
		x = z->left;
		red_black_transplant(z, z->left);
	} else {
		y = tree_minimum(z->right);
		yOriginalColor = y->color;

		if (y->parent != z) {
			red_black_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		x = y->right;
		red_black_transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	free(z); // Free the memory occupied by the deleted node

	if (yOriginalColor == 0) {
		red_black_delete_fixup(x);
	}
}
}


// Function to find the node with the minimum distance in the RB Tree
node* findMin(node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to extract the node with the minimum distance from the RB Tree
node* extractMin(node** root) {
    node* minNode = findMin(*root);
    // Delete minNode from the RB Tree
    // (You need to implement RB Tree deletion logic here)
    return minNode;
}

void dijkstra(int matrix[N][N], int source) {

    int dist[N];
    node* nodes[N];

    for (int i = 0; i < N; i++) {
        dist[i] = Infinite;
        nodes[i] = create_node(i, dist[i]);
        head = BST(head, nodes[i]);
        fixing(head, nodes[i]);
        head->color=0;  // Apply RB Tree fixing
    }

    dist[source] = 0;
    nodes[source]->distence = 0;  // Update the distance in RB Tree

    while (head != NULL) {
        node* minNode = extractMin(&head);
        int u = minNode->data;
        
        red_black_delete(tree_search(u));
        


        for (int v = 0; v < N; v++) {
            if (matrix[u][v] != 0 && dist[u] != Infinite &&
                dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
                nodes[v]->distence = dist[v];  // Update distance in RB Tree
                // Apply RB Tree fixing after updating distance
                fixing(head, nodes[v]);
                head->color=0;
            }
        }
    }

    // Print the result
    for (int i = 0; i < N; i++)
        printf("from source to node:  %d \t minimum distence:  %d\n", i, dist[i]);
}




int main(){

    int matrix[N][N] = {
        
        {0, 2, 3, 0, 0, 5},
        {2, 0, 0, 4, 0, 0},
        {3, 0, 0, 0, 0, 6},
        {0, 4, 0, 0, 7, 0},
        {0, 0, 0, 7, 0, 8},
       
    };
        
    

    int source = 0;
    dijkstra(matrix, source);
   
    

    return 0;


}
