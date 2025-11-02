// name: Edison Kuo
// cruzID: edkuo
// assignment: pa4

// List.c
// Implementation file for List ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// private structs, functions, and constants

// initialSize for elements array
// Might not need at all because linked lists are dynamic anyways
// static const int initialSize = 10;

// Node 
typedef struct Node {
    ListElement data;
    struct Node* prev;
    struct Node* next;
} Node;

// ListObj
typedef struct ListObj {
    Node* front;
    Node* back;
    Node* cursor;
    int length; // length of linked list
    int position; // the cursor position
} ListObj;

// !! doubleItemArray 
// Doubles the physical size of the array 
// Might need to implement for a dynamically growing array
// Implementation in Queue.c example in Queue linkedlist
// Might not need at all because linked lists are dynamic anyways

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Creates a new Node that can be inserted anywhere in the list.
// NOTE: pass in NULL to prev or next if inserting at the front or back respectively
Node* newNode(ListElement data, Node* prev, Node* next)  {
    Node *N;
    N = malloc(sizeof(Node));
    assert(N != NULL);
    N->data = data;
    N->prev = prev;
    N->next = next;
    return N;
}

// newList()
// Creates a new empty list.
List newList() {
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = NULL;
    L->cursor = NULL; 
    L->length = 0;
    L->position = -1; // position returns -1 when the cursor is undefined 
    return L;
}

// freeList()
// Frees heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (!isEmptyList(*pL)) {
            deleteFront(*pL); 
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: length(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    return (L->length);
}

// position()
// If cursor is defined, returns the position of the cursor element, otherwise
// returns -1.
int position(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: position(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL) {
        return (L->position);
    } else {
        return -1;
    }
}

// front()
// Returns front element. Pre: length()>0
ListElement front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: front(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: front(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    return (L->front->data);
}

// back()
// Returns back element. Pre: length()>0
ListElement back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: back(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: back(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    return (L->back->data);
}

// get()
// Returns cursor element. Pre: length()>0, position()>=0
ListElement get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: get(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: get(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: get(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    return (L->cursor->data);
}


// isEmptyList()
// Returns true if L is empty, otherwise returns false.
bool isEmptyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: isEmptyList(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    return(L->length == 0);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: clear(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    while (!isEmptyList(L)) {
        deleteFront(L);
    }

    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->position = -1;
}

// set()
// Overwrites the cursor element’s data with x. Pre: length()>0, position()>=0
void set(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: set(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: set(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: set(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}
// moveFront()
// If L is non-empty, places the cursor under the front element, otherwise does
// nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveFront(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (!isEmptyList(L)) {
        L->cursor = L->front;
        L->position = 0;
    }
}

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise
// does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveBack(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (!isEmptyList(L)) {
        L->cursor = L->back;
        L->position = (L->length - 1);
    }
}


// movePrev()
// If cursor is defined and not at front, moves cursor one step toward front of
// L, if cursor is defined and at front, cursor becomes undefined, if cursor is
// undefined does nothing.
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: movePrev(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL) {
        if (L->cursor != L->front) {
            L->cursor = L->cursor->prev;
            L->position -= 1;
        } else {
            L->cursor = NULL;
            L->position = -1;
        }
    }
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward back of
// L, if cursor is defined and at back, cursor becomes undefined, if cursor is
// undefined does nothing.
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveNext(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL) {
        if (L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->position += 1;
        } else {
            L->cursor = NULL;
            L->position = -1;
        }
    }
}

// prepend()
// Insert new element into L. If List is non-empty, insertion takes place
// before front element.
// Node* newNode(ListElement data, Node* prev, Node* next);
void prepend(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: prepend(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    Node* N = newNode(data, NULL, L->front);

    if (!isEmptyList(L)) {
        L->front->prev = N;
        L->front = N;
    } else {
        L->front = L->back = N;
    }     
    
    if (L->cursor != NULL) {
        L->position++;
    }

    L->length++;
}

// append()
// Insert new element into L. If List is non-empty, insertion takes place
// after back element.
void append(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: append(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    Node* N = newNode(data, L->back, NULL);

    if (!isEmptyList(L)) {
        L->back->next = N;
        L->back = N;
    } else {
        L->front = L->back = N;
    }     

    L->length++;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, position()>=0
// Node* newNode(ListElement data, Node* prev, Node* next);
void insertBefore(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertBefore(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: insertBefore(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: insertBefore(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    Node *N = newNode(data, L->cursor->prev, L->cursor);

    if (L->cursor->prev != NULL) {
        L->cursor->prev->next = N;
    } else {
        L->front = N;
    }

    L->cursor->prev = N;
    L->length++;
    L->position++;
}

// insertAfter() 
// Inserts new element after cursor. Pre: length()>0, position()>=0
// Node* newNode(ListElement data, Node* prev, Node* next);
void insertAfter(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertAfter(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: insertAfter(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: insertAfter(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    Node *N = newNode(data, L->cursor, L->cursor->next);

    if (L->cursor->next != NULL) {
        L->cursor->next->prev = N;
    } else {
        L->back = N;
    }

    L->cursor->next = N;
    L->length++;
}

// deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
    Node *N= NULL;

    if (L == NULL) {
        fprintf(stderr, "List Error: deleteFront(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: deleteFront(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    N = L->front;

    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->position = -1;
    } else if (L->cursor != NULL) { 
        L->position--; 
    }

    if (L->length >= 2) {
        L->front->next->prev = NULL;
        L->front = L->front->next;
    } else {
        L->front = L->back = NULL;
    }

    L->length--;
    free(N);
}

// deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L) {
    Node *N= NULL;

    if (L == NULL) {
        fprintf(stderr, "List Error: deleteBack(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: deleteBack(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    N = L->back;

    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->position = -1;
    }

    if (L->length >= 2) {
        L->back->prev->next = NULL;
        L->back = L->back->prev;
    } else {
        L->front = L->back = NULL;
    }

    L->length--;
    free(N);
}

// delete()
// Deletes cursor element, making cursor undefined. Pre: length()>0, position()>=0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: delete(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: delete(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: delete(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    Node *N = L->cursor;

    if (N->prev != NULL) {
        N->prev->next = N->next;
    } else {
        L->front = N->next;
    }

    if (N->next != NULL) {
        N->next->prev = N->prev;
    } else {
        L->back = N->prev;
    }

    free(N);

    L->cursor = NULL;
    L->position = -1;
    L->length--;
}

// Other operations -----------------------------------------------------------

// join()
// Returns the concatenation of A followed by B. The cursor in the new List is
// undefined, regardless of the states of the cursors A in and B. The states of
// A and B are unchanged.
List join(List A, List B) {
    if (A == NULL) {
        fprintf(stderr, "List Error: join(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "List Error: join(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List C = newList();
    
    Node *N = NULL; // Node for iteration through list
    for (N = A->front; N != NULL; N = N->next) {
        append(C, N->data);
    }

    for (N = B->front; N != NULL; N = N->next) {
        append(C, N->data);
    }

    return C;
}

// split()
// Removes all elements before (in front of but not equal to) the cursor element
// in L. The cursor element in L is unchanged. Returns a new List consisting of
// all the removed elements. The cursor in the returned list is undefined.
// Pre: length(L)>0, position(L)>=0
List split(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: split(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        fprintf(stderr, "List Error: split(): length of list must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    if (L->position < 0) {
        fprintf(stderr, "List Error: split(): cursor element does not exist\n");
        exit(EXIT_FAILURE);
    }

    List L_split = newList();

    while (L->front != L->cursor) {
        append(L_split, L->front->data);
        deleteFront(L);
    }

    L->position = 0;
    return L_split;
}