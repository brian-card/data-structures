////////////////////////////////////////////////////////////////////////////////
//
//                       Copyright (c) 2026 Brian Card
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//                                 Brian Card
//                       https://github.com/brian-card
//
////////////////////////////////////////////////////////////////////////////////

/// @file LinkedList.c
///
/// @brief Library implementation of the LinkedList.

// Standard C includes
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

// ListNode functions need to come first

/// @fn ListNode* listNodeCreate(void *value, int size)
///
/// @brief Allocate and initialize a ListNode.
///
/// @param value A pointer to the value to be assigned to the ListNode.  This
///   value will be copied into the ListNode.
/// @param size The number of bytes the value takes up.
///
/// @return Returns a pointer to an allocated and initialized ListNode on
/// success, NULL on failure.
ListNode* listNodeCreate(void *value, int size) {
    // Both prev and next of the new node need to be initialized to
    // NULL and we need to test its value against NULL, so use calloc.
    ListNode *node = (ListNode*) calloc(1, sizeof(ListNode));
    if (node == NULL) {
        // Out of memory
        return NULL;
    }

    // Copy the value to the new node
    node->value = malloc(size);
    if (node->value == NULL) {
        free(node); node = NULL;
        return NULL;
    }
    memcpy(node->value, value, size);

    return node;
}

/// @fn ListNode* listNodeDestroy(ListNode *node)
///
/// @brief Release all the memory allocated to hold a ListNode and its value.
///
/// @param node A pointer to a previously-allocated ListNode.
///
/// @return This function always succeeds and always returns NULL.
ListNode* listNodeDestroy(ListNode *node) {
    // Deallocate the ListNode in the reverse order it was created
    free(node->value); node->value = NULL;
    free(node); node = NULL;
    return NULL;
}

// LinkedList functions follow

/// @fn LinkedList* linkedListCreate(int (*compare)(const void*, const void*))
///
/// @brief Allocate and initialize a linked list.
///
/// @return Returns a pointer to an allocated and initialized LinkedList on
/// success, NULL on failure.
LinkedList* linkedListCreate(int (*compare)(const void*, const void*)) {
    if (compare == NULL) {
        // We can't create a list like this
        return NULL;
    }

    LinkedList *linkedList = (LinkedList*) calloc(1, sizeof(LinkedList));
    if (linkedList == NULL) {
        // Out of memory
        return NULL;
    }

    linkedList->compare = compare;
    // All other values are initialized to 0 by calloc

    return linkedList;
}

/// @fn int linkedListInsertFront(LinkedList *linkedList, void *value, int size)
///
/// @brief Insert a new value at the front of a linked list.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
/// @param value A pointer to the value to copy to the front of the list.
/// @param size The number of bytes the value takes up.
///
/// @return Returns 0 on success, -1 on failure.
int linkedListInsertFront(LinkedList *linkedList, void *value, int size) {
    if (linkedList == NULL) {
        // Nothing we can do
        return -1;
    }

    // Create the new node and copy the value
    ListNode *node = listNodeCreate(value, size);
    if (node == NULL) {
        return -1;
    }

    // Insert the node at the front of the list
    if (linkedList->head != NULL) {
        linkedList->head->prev = node;
    }
    node->next = linkedList->head
    // No need to set node->prev since node was created with calloc
    linkedList->head = node;
    if (linkedList->tail == NULL) {
        // List was empty
        linkedList->tail = node;
    }
    linkedList->size++;

    return 0;
}

/// @fn int linkedListInsertBack(LinkedList *linkedList, void *value, int size)
///
/// @brief Insert a new value at the back of a linked list.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
/// @param value A pointer to the value to copy to the back of the list.
/// @param size The number of bytes the value takes up.
///
/// @return Returns 0 on success, -1 on failure.
int linkedListInsertBack(LinkedList *linkedList, void *value, int size) {
    if (linkedList == NULL) {
        // Nothing we can do
        return -1;
    }

    // Create the new node and copy the value
    ListNode *node = listNodeCreate(value, size);
    if (node == NULL) {
        return -1;
    }

    // Insert the node at the back of the list
    if (linkedList->tail != NULL) {
        linkedList->tail->next = node;
    }
    node->prev = linkedList->tail;
    // No need to set node->next since node was created with calloc
    linkedList->tail = node;
    if (linkedList->head == NULL) {
        // List was empty
        linkedList->head = node;
    }
    linkedList->size++;

    return 0;
}

/// @fn ListNode* linkedListSearch(LinkedList *linkedList, const void *value)
///
/// @brief Search a linked list for a specific value.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
/// @param value A pointer to the value to search for.
///
/// @return Returns a pointer to the ListNode that contains the value on
/// success, NULL on failure.
ListNode* linkedListSearch(LinkedList *linkedList, const void *value) {
    if (linkedList == NULL) {
        // Nothing we can do
        return NULL;
    }

    // Get the comparison function from the list
    int (*compare)(const void*, const void*) = linkedList->compare;

    for (ListNode *cur = linkedList->head; cur != NULL; cur = cur->next) {
        if (compare(cur->value, value) == 0) {
            return cur;
        }
    }

    return NULL;
}

/// @fn int linkedListRemoveValue(LinkedList *linkedList, const void *value)
///
/// @brief Remove a value from a linked list.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
/// @param value A pointer to the value to remove.
///
/// @return Returns 0 on success, -1 on failure.
int linkedListRemoveValue(LinkedList *linkedList, const void *value) {
    ListNode *found = linkedListSearch(linkedList, value);
    if (found == NULL) {
        // Can't remove a value we didn't find
        return -1;
    }

    // Splice out the found node from its neighbors
    if (found->prev != NULL) {
        found->prev->next = found->next;
    }
    if (found->next != NULL) {
        found->next->prev = found->prev;
    }

    // Update head and tail if we're the beginning or end of the list
    if (found == linkedList->head) {
        linkedList->head = found->next;
    }
    if (found == linkedList->tail) {
        linkedList->tail = found->prev;
    }

    found = listNodeDestroy(found);
    linkedList->size--;

    return 0;
}

/// @fn void* linkedListPeekFront(LinkedList *linkedList)
///
/// @brief Get the value from the front of the list if there is one.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
///
/// @return Returns the value at the front of the list on success, NULL on
/// failure.
void* linkedListPeekFront(LinkedList *linkedList) {
    void *front = NULL;

    if ((linkedList != NULL) && (linkedList->head != NULL)) {
        front = linkedList->head->value;
    }

    return front;
}

/// @fn void* linkedListPeekBack(LinkedList *linkedList)
///
/// @brief Get the value from the back of the list if there is one.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
///
/// @return Returns the value at the back of the list on success, NULL on
/// failure.
void* linkedListPeekBack(LinkedList *linkedList) {
    void *back = NULL;

    if ((linkedList != NULL) && (linkedList->tail != NULL)) {
        back = linkedList->tail->value;
    }

    return back;
}

/// @fn void* linkedListPopFront(LinkedList *linkedList)
///
/// @brief Get the value from the front of the list if there is one and destroy
/// the ListNode.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
///
/// @return Returns the value at the front of the list on success, NULL on
/// failure.
void* linkedListPopFront(LinkedList *linkedList) {
    if ((linkedList == NULL) || (linkedList->head == NULL)) {
        return NULL;
    }

    ListNode *node = linkedList->head;
    void *front = node->value;

    linkedList->head = node->next;
    if (linkedList->size == 1) {
        linkedList->tail = NULL;
    }
    free(node); node = NULL;
    linkedList->size--;

    return front;
}

/// @fn void* linkedListPopBack(LinkedList *linkedList)
///
/// @brief Get the value from the back of the list if there is one and destroy
/// the ListNode.
///
/// @param linkedList A pointer to a previously-initialized LinkedList.
///
/// @return Returns the value at the back of the list on success, NULL on
/// failure.
void* linkedListPopBack(LinkedList *linkedList) {
    if ((linkedList == NULL) || (linkedList->head == NULL)) {
        return NULL;
    }

    ListNode *node = linkedList->tail;
    void *back = node->value;

    linkedList->tail = node->prev;
    if (linkedList->size == 1) {
        linkedList->head = NULL;
    }
    free(node); node = NULL;
    linkedList->size--;

    return back;
}

