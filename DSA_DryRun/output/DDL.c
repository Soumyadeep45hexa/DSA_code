#include <stdio.h>
#include <stdlib.h>

/* Each node stores data, a pointer to the previous node and a pointer to the next node */
struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;   /* head points to the first node of the list */

/* ---------- Helper: make a new node ---------- */
struct node *makeNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->data = value;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/* ---------- Count the number of elements ---------- */
int countNodes() {
    int count = 0;
    struct node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* ---------- Print the list ---------- */
void printList() {
    struct node *temp = head;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* ---------- INSERTION ---------- */

void insertFirst(int value) {
    struct node *n = makeNode(value);
    if (head != NULL) {
        n->next = head;
        head->prev = n;
    }
    head = n;
    printf("%d inserted at the first position.\n", value);
}

void insertLast(int value) {
    struct node *n = makeNode(value);
    struct node *temp = head;
    if (head == NULL) {
        head = n;
    } else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        n->prev = temp;
    }
    printf("%d inserted at the last position.\n", value);
}

void insertAtPosition(int value, int pos) {
    int total = countNodes();
    int i;
    struct node *temp = head;
    struct node *n;

    if (pos < 1 || pos > total + 1) {
        printf("Invalid position! Valid range is 1 to %d.\n", total + 1);
        return;
    }
    if (pos == 1) {
        insertFirst(value);
        return;
    }
    /* go to the node just before the given position */
    for (i = 1; i < pos - 1; i++)
        temp = temp->next;

    n = makeNode(value);
    n->next = temp->next;
    n->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = n;
    temp->next = n;
    printf("%d inserted at position %d.\n", value, pos);
}

void insertAfterData(int value, int key) {
    struct node *temp = head;
    struct node *n;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("%d not found in the list.\n", key);
        return;
    }
    n = makeNode(value);
    n->next = temp->next;
    n->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = n;
    temp->next = n;
    printf("%d inserted after %d.\n", value, key);
}

/* ---------- DELETION ---------- */

void deleteFirst() {
    struct node *temp;
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    printf("%d deleted from the first position.\n", temp->data);
    free(temp);
}

void deleteLast() {
    struct node *temp = head;
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev == NULL)      /* only one node in the list */
        head = NULL;
    else
        temp->prev->next = NULL;

    printf("%d deleted from the last position.\n", temp->data);
    free(temp);
}

void deleteAtPosition(int pos) {
    int total = countNodes();
    int i;
    struct node *temp = head;

    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (pos < 1 || pos > total) {
        printf("Invalid position! Valid range is 1 to %d.\n", total);
        return;
    }
    if (pos == 1) {
        deleteFirst();
        return;
    }
    for (i = 1; i < pos; i++)
        temp = temp->next;

    temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    printf("%d deleted from position %d.\n", temp->data, pos);
    free(temp);
}

void deleteData(int key) {
    struct node *temp = head;

    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("%d not found in the list.\n", key);
        return;
    }
    if (temp->prev == NULL)      /* it is the first node */
        head = temp->next;
    else
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    printf("%d deleted from the list.\n", key);
    free(temp);
}

/* ---------- SEARCHING ---------- */

void searchPresence(int key) {
    struct node *temp = head;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d is present in the list.\n", key);
            return;
        }
        temp = temp->next;
    }
    printf("%d is NOT present in the list.\n", key);
}

void searchPosition(int key) {
    struct node *temp = head;
    int pos = 1;
    int found = 0;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d found at position %d.\n", key, pos);
            found = 1;
        }
        temp = temp->next;
        pos++;
    }
    if (found == 0)
        printf("%d is NOT present in the list.\n", key);
}

void searchCount(int key) {
    struct node *temp = head;
    int count = 0;
    while (temp != NULL) {
        if (temp->data == key)
            count++;
        temp = temp->next;
    }
    printf("%d is present %d time(s) in the list.\n", key, count);
}

/* ---------- SORTING (ascending, bubble sort on data) ---------- */

void sortList() {
    struct node *i, *j;
    int temp;

    if (head == NULL || head->next == NULL) {
        printf("Nothing to sort.\n");
        return;
    }
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("List sorted in ascending order.\n");
}

/* ---------- REVERSING (swap prev and next of every node) ---------- */

void reverseList() {
    struct node *temp = NULL;
    struct node *current = head;

    if (head == NULL || head->next == NULL) {
        printf("Nothing to reverse.\n");
        return;
    }
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;     /* prev now holds the old next */
    }
    head = temp->prev;               /* temp is at the old second-last node */
    printf("List reversed.\n");
}

/* ---------- CREATE a new list ---------- */

void createList() {
    int n, i, value;
    struct node *temp;

    /* remove the old list (if any) before creating a new one */
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    printf("How many nodes do you want to create? ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &value);
        insertLast(value);
    }
}

/* ---------- MAIN MENU ---------- */

int main() {
    int choice, sub, value, pos, key;

    while (1) {
        printf("\n===== DOUBLY LINKED LIST MENU =====\n");
        printf("1. Create a new list\n");
        printf("2. Print the list\n");
        printf("3. Insert new data\n");
        printf("4. Delete a data from the list\n");
        printf("5. Count the number of elements\n");
        printf("6. Search for a data\n");
        printf("7. Sort the list\n");
        printf("8. Reverse the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createList();
            break;

        case 2:
            printList();
            break;

        case 3:
            printf("\n  a) Insert at the first node  -> enter 1\n");
            printf("  b) Insert at the last node   -> enter 2\n");
            printf("  c) Insert into a given position -> enter 3\n");
            printf("  d) Insert after a given data -> enter 4\n");
            printf("Enter your choice: ");
            scanf("%d", &sub);
            printf("Enter the data to insert: ");
            scanf("%d", &value);
            if (sub == 1)
                insertFirst(value);
            else if (sub == 2)
                insertLast(value);
            else if (sub == 3) {
                printf("Enter the position: ");
                scanf("%d", &pos);
                insertAtPosition(value, pos);
            } else if (sub == 4) {
                printf("Insert after which data? ");
                scanf("%d", &key);
                insertAfterData(value, key);
            } else
                printf("Invalid choice!\n");
            break;

        case 4:
            printf("\n  a) Delete the first node  -> enter 1\n");
            printf("  b) Delete the last node   -> enter 2\n");
            printf("  c) Delete from a given position -> enter 3\n");
            printf("  d) Delete a given data    -> enter 4\n");
            printf("Enter your choice: ");
            scanf("%d", &sub);
            if (sub == 1)
                deleteFirst();
            else if (sub == 2)
                deleteLast();
            else if (sub == 3) {
                printf("Enter the position: ");
                scanf("%d", &pos);
                deleteAtPosition(pos);
            } else if (sub == 4) {
                printf("Enter the data to delete: ");
                scanf("%d", &key);
                deleteData(key);
            } else
                printf("Invalid choice!\n");
            break;

        case 5:
            printf("Number of elements in the list = %d\n", countNodes());
            break;

        case 6:
            printf("\n  a) Detect presence of a data   -> enter 1\n");
            printf("  b) Find position of a data     -> enter 2\n");
            printf("  c) Count occurrences of a data -> enter 3\n");
            printf("Enter your choice: ");
            scanf("%d", &sub);
            printf("Enter the data to search: ");
            scanf("%d", &key);
            if (sub == 1)
                searchPresence(key);
            else if (sub == 2)
                searchPosition(key);
            else if (sub == 3)
                searchCount(key);
            else
                printf("Invalid choice!\n");
            break;

        case 7:
            sortList();
            break;

        case 8:
            reverseList();
            break;

        case 9:
            printf("Program ended.\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}