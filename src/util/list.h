#pragma once

#include <stdbool.h>

typedef struct List List;
typedef struct ListNode ListNode;

typedef enum {
  // The default is no options.
  ListOptionsDefaults = 0,

  // If this is set, the list will free items when the related node is freed. If a list takes ownership of an item, then
  // that item's pointer cannot be added to the list again to prevent double-free mistakes. Items that compare as the
  // same but do not have the same pointer *will* be added, unless `ListOptionUniqueItems` is set.
  ListOptionsTakeOwnership = 0x01 << 0,

  // By default, the list will not allow
  // These options require a comparator. The default comparison is a straight pointer address comparison. If you want
  // a custom comparator, specify one with `ListSetComparator()`.
  // Verify that added items are unique.
  ListOptionUniqueItems = 0x01 << 1,
  ListOptionSortOnAppend = 0x01 << 2,
} ListOptions;

typedef int (^comparator)(const void *, const void *);

// The underlying struct is opaque to callers. These functions allow this API to maintain ownership of the underlying
// memory. Pass a pointer-pointer. (e.g. create a pointer variable `List *l;` and call these methods with `&l` as the
// parameter. These methods will change the pointer as needed - your pointer will be `NULL` after the list is freed.
// Returns `false` and sets the pointer to `NULL` if allocation fails. Returns `false` if there as problem freeing any
// part of the list, but only sets the pointer to `NULL` if deallocation succeeds.
bool ListAlloc(List **, ListOptions);
bool ListAllocDefault(List **);
bool ListFree(List **);

List *ItrListAlloc(ListOptions);
List *ItrListAllocDefault(void);

// Set the comparator used to sort items into the list.
bool ListSetComparator(List *, comparator);

// Get the `ListNode` at the head of the list. Returns `false` if the list pointer is NULL, if the `ListNode`
// pointer-pointer is NULL, or if the head of the list is NULL.
bool ListStart(List *, ListNode **);
ListNode *ItrListStartNode(List *);
void *ItrListStartItem(List *);

// Get the `ListNode` at the tail of the list. Returns `false` if the list pointer is NULL, if the `ListNode`
// pointer-pointer is NULL, or if the tail of the list is NULL. Note: the tail should only be `NULL` if the head is also
// `NULL`.
bool ListEnd(List *, ListNode **);
ListNode *ItrListEndNode(List *);
void *ItrListEndItem(List *);

// Get the current number of items in the list. Returns `false` if either parameter is `NULL`.
bool ListItemCount(List *, int *);
int ItrListItemCount(List *);

// Get the `List` to which this node belongs. Returns `false` and sets the `List` pointer-pointer to `NULL` if the
// supplied node is an orphan.
bool ListNodeParent(ListNode *, List **);
List *ItrListNodeParent(ListNode *);

// Get the node after this node. Returns `false` and sets the ListNode pointer-pointer to NULL if the first parameter
// is the tail of the list.
bool ListNodeNext(ListNode *, ListNode **);
ListNode *ItrListNodeNext(ListNode *);

// Get the node before this node. Returns `false` and sets the ListNode pointer-pointer to NULL if the first parameter
// is the head of the list.
bool ListNodePrevious(ListNode *, ListNode **);
ListNode *ItrListNodePrevious(ListNode *);

// Get the item / value that this node wraps.
bool ListNodeGetItem(ListNode *, void **);
void *ItrListNodeGetItem(ListNode *);

// Adds the supplied pointer to the list. If `ListOptionsTakeOwnership`, this pointer will be deallocated when the
// containing node is deallocated, typically when the `List` is deallocated. Returns `false` if the item is `NULL`
// or if there was some other issue.
bool ListAddItem(List *, void *);
bool ListRemoveNode(ListNode *);

typedef void (^ListEachFn)(void *item);
typedef bool (^ListFilterFn)(void *item);
typedef void* (^ListMapFn)(void *item);
typedef void* (^ListReduceFn)(void *currentResult, void *item);

bool ListForEach(List *, ListEachFn);
List *ListFilter(List *, ListFilterFn);
List *ListMap(List *, ListMapFn);
void *ListReduce(List *, void *initial, ListReduceFn);
