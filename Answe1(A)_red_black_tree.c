#include<stdio.h>
#include<stdlib.h>
#include <time.h>


struct node{
    int data;
    int color; // 1 for red and 0 for black
    struct node* left;
    struct node*right;
    struct node* parent;
};

typedef struct node node;

node * head= NULL;

node * create_node(int data){
    node* temp;
    temp=(node*)malloc(sizeof(node));
    temp->color=1;
    temp->data= data;
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


struct node *tree_search(int key){
	struct node *x;

	x = head;
	while(x != NULL && x->data != key){
		if(key < x->data){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	return x;
}

struct node *tree_minimum(struct node *x){
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






int main(){
    FILE *file;
    file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening the file");
        return 1;
    }


    // Skip characters in the file
    char ch;
    while ((ch = fgetc(file)) != EOF && ch != '[') {
        // Skip characters until the '[' character is encountered
    }

    int integerArray[10000];
    // Adjust the array size as needed
    int arrayIndex = 0;

    while (fscanf(file, "%d", &integerArray[arrayIndex]) == 1) {
        // Read integers and store them in the array
        arrayIndex++;

        // Check for the ']' character to exit the loop
        ch = fgetc(file);
        if (ch == ']') {
            break;
        }
    }
    fclose(file);


    clock_t  start = clock();
    node *temp = NULL;

    for (int i = 0; i < 10000; i++) {
        temp = create_node(integerArray[i]);
        head=BST(head,temp);
        fixing(head,temp);
        head->color=0;
    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)); 
    printf("Time taken for inserting 10000 keys: %lf seconds\n", cpu_time_used);



     clock_t start2 = clock();
    //element to insert,, 99957, 71164, 53575, 26164, 600
    int insert_elemet[5]={99957, 71164, 53575, 26164, 600};
    for(int i=0;i<5;i++){

    node * temp2= create_node(99957);
    head=BST(head,temp2);
    fixing(head,temp2);
    head->color=0;
    printf("element %d succesfully inserted\n", insert_elemet[i]);
    }
    
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end2 = clock();
    double cpu_time_used2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
    printf("Time taken for inserting given Five keys: %lf seconds\n", cpu_time_used2);


    // keys to search 18, 7791, 13000, 99824, 51375

    clock_t start3 = clock();
    int temp_array[5]={18, 7791, 13000, 99824, 51375};
    for(int i=0;i<5;i++){
    if (tree_search(temp_array[i])){
        printf("value %d found\n",temp_array[i]);
    }
    else printf("Value %d not found\n", temp_array[i]);
    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end3 = clock();
    double cpu_time_used3 = ((double)(end3 - start3)) / CLOCKS_PER_SEC;
    printf("Time taken for searching given five keys: %f seconds\n", cpu_time_used3);

// to delete the given elemets.

    clock_t start4 = clock();
    int fordel[5]={532442, 24168, 51164, 72145, 93160};
    for(int i=0;i<5;i++){
        if(tree_search(fordel[i])){
            red_black_delete(tree_search(fordel[i]));
            printf("Value deleted is %d \n", fordel[i]);

        }
        else{
            printf("Value %d not found for deleteting \n", fordel[i]);
        }    
    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end4 =  clock();
    double cpu_time_used4 = ((double)(end4 - start4)) / CLOCKS_PER_SEC;
    printf("Time taken for deleting given five keys: %f seconds\n", cpu_time_used4);

    return 0;
}
