// Binary Search Tree: create, insert, traversals, delete, search
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node *newNode(int x) {
    struct node *n = malloc(sizeof(struct node));
    n->data = x;
    n->left = n->right = NULL;
    return n;
}

// b) Insertion: smaller goes left, bigger goes right
struct node *insert(struct node *root, int x) {
    if (root == NULL) return newNode(x);
    if (x < root->data) root->left = insert(root->left, x);
    else if (x > root->data) root->right = insert(root->right, x);
    else printf("%d already exists\n", x);
    return root;
}

// a) Create: build a tree by inserting n keys
struct node *create() {
    struct node *root = NULL;
    int n, x;
    printf("How many keys? ");
    scanf("%d", &n);
    printf("Enter %d keys: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
    }
    return root;
}

// c) Traversals
void inorder(struct node *r) {
    if (r) { inorder(r->left); printf("%d ", r->data); inorder(r->right); }
}
void preorder(struct node *r) {
    if (r) { printf("%d ", r->data); preorder(r->left); preorder(r->right); }
}
void postorder(struct node *r) {
    if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->data); }
}

// e) Searching
struct node *search(struct node *r, int x) {
    if (r == NULL || r->data == x) return r;
    if (x < r->data) return search(r->left, x);
    return search(r->right, x);
}

// d) Deletion
struct node *minNode(struct node *r) {
    while (r->left) r = r->left;
    return r;
}

struct node *delete(struct node *root, int x) {
    if (root == NULL) {
        printf("%d not found\n", x);
        return NULL;
    }
    if (x < root->data) root->left = delete(root->left, x);
    else if (x > root->data) root->right = delete(root->right, x);
    else {
        // Case 1 and 2: no child or one child
        if (root->left == NULL) {
            struct node *t = root->right;
            free(root);
            return t;
        }
        if (root->right == NULL) {
            struct node *t = root->left;
            free(root);
            return t;
        }
        // Case 3: two children, copy inorder successor, then delete it
        struct node *s = minNode(root->right);
        root->data = s->data;
        root->right = delete(root->right, s->data);
    }
    return root;
}

int main() {
    struct node *root = NULL;
    int choice, x;
    do {
        printf("\n1.Create 2.Insert 3.Inorder 4.Preorder 5.Postorder 6.Delete 7.Search 8.Exit: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: root = create(); break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;
            case 3: printf("Inorder: ");   inorder(root);   printf("\n"); break;
            case 4: printf("Preorder: ");  preorder(root);  printf("\n"); break;
            case 5: printf("Postorder: "); postorder(root); printf("\n"); break;
            case 6:
                printf("Enter key to delete: ");
                scanf("%d", &x);
                root = delete(root, x);
                break;
            case 7:
                printf("Enter key to search: ");
                scanf("%d", &x);
                if (search(root, x)) printf("%d is present\n", x);
                else printf("%d is not present\n", x);
                break;
        }
    } while (choice != 8);
    return 0;
}