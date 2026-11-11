// Easiest hashing in C: linear probing, no menu
#include <stdio.h>

#define SIZE 10

int table[SIZE];   // 0 means the slot is empty (keys must be greater than 0)
void insert(int key){
    int i=key%SIZE;
    while(table[i]!=0){
        i=(i+1)%SIZE;
    }
    table[i]=key;
}
int search(int key){
    int i=key%SIZE;
    while(table[i]!=0){
        if (table[i]==key)
            return i;
        i=(i+1)%SIZE;
    }
    printf("The Key is not present\n");
    return -1;
}
int main() {
    printf("Enter the number of keys need to be entered: ");
    int n;
    int keys[n];
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
    scanf("%d",&keys[i]);
        insert(keys[i]);
    }
    for (int i = 0; i < SIZE; i++)
        printf("%d -> %d\n", i, table[i]);

    printf("25 is at index %d\n", search(25));
    return 0;
}