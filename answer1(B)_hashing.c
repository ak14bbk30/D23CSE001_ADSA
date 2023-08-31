#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20011

struct HashNode {
    int value;
    int occupied; // Flag to indicate if the slot is occupied
};

struct HashTable {
    struct HashNode table[SIZE];
};

// Initialize the hash table
void initialize(struct HashTable* ht) {
    for (int i = 0; i < SIZE; ++i) {
        ht->table[i].occupied = 0;
    }
}

// Hash function (simple modulo operation)
int hash(int value) {
    return value % SIZE;
}

// Insert a value into the hash table
void insert(struct HashTable* ht, int value) {
    int index = hash(value);
    while (ht->table[index].occupied) {
        index = (index + 1) % SIZE; // Linear probing
    }
    ht->table[index].value = value;
    ht->table[index].occupied = 1;
}

// Search for a value in the hash table
int search(struct HashTable* ht, int value) {
    int index = hash(value);
    while (ht->table[index].occupied) {
        if (ht->table[index].value == value) {
            return index; // Return index where value is found
        }
        index = (index + 1) % SIZE; // Linear probing
    }
    return -1; // Value not found
}

// Delete a value from the hash table
void delete(struct HashTable* ht, int value) {
    int index = search(ht, value);
    if (index != -1) {
        ht->table[index].occupied = 0;
        printf("Deleted value %d at index %d\n", value, index);
    } else {
        printf("Value %d not found in the hash table\n", value);
    }
}

int main() {
    struct HashTable ht;
    initialize(&ht);

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
    for(int i=0;i<10000;i++){
        insert(&ht,integerArray[i]);

    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)); 
    printf("Time taken for inserting 10000 keys: %lf seconds\n", cpu_time_used);

    // printf("Hash Table:\n");
    // for (int i = 0; i < SIZE; ++i) {
    //     if (ht.table[i].occupied) {
    //         printf("Slot %d: %d\n", i, ht.table[i].value);
    //     } else {
    //         printf("Slot %d: Empty\n", i);
    //     }
    // }

    clock_t start2 = clock();
    int insert_elemet[5]={99957, 71164, 53575, 26164, 600};
    for(int i=0; i<5; i++){
        insert(&ht, insert_elemet[i]);
        printf("Value %d inserted\n", insert_elemet[i]);
    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end2 = clock();
    double cpu_time_used2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
    printf("Time taken for inserting given Five keys: %lf seconds\n", cpu_time_used2);

// searching

    clock_t start3 = clock();
    int searchValue[5] = {18, 7791, 13000, 99824, 51375};
    for(int i=0; i<5;i++){
        int index = search(&ht, searchValue[i]);
        if (index != -1) {
            printf("Value %d found at index %d\n", searchValue[i], index);
        }
     
        else {
            printf("Value %d not found in the hash table\n", searchValue[i]);
    }
    }
    for(int i=0 ;i<5000000;i++){} //Inserting a temporary for loop for better results of Time
    clock_t end3 = clock();
    double cpu_time_used3 = ((double)(end3 - start3)) / CLOCKS_PER_SEC;
    printf("Time taken for searching given five keys: %f seconds\n", cpu_time_used3);


    clock_t start4 = clock();
    int deletevalue[5]={51, 24168, 51164, 72145, 93160};
    for(int i=0; i<5;i++){
        delete(&ht, deletevalue[i]);

    for(int i=0 ;i<5000000;i++){}  //Inserting a temporary for loop for better results of Time
    }
    clock_t end4 =  clock();
    double cpu_time_used4 = ((double)(end4 - start4)) / CLOCKS_PER_SEC;
    printf("Time taken for deleting given five keys: %f seconds\n", cpu_time_used4);


}
