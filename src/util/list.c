#include <stdlib.h>
#include "list.h"

// Implementation should change depending on needs. E.g. a sorted list would perform better as a tree.
typedef enum {
  ListTypeSinglyLinkedList, // NOTE: do we even need this?
  ListTypeDoublyLinkedList,
  ListTypeBalancedTree, // TODO: Implement tree
} ListType;

struct List {
  ListType type;
  ListNode *head;
  ListNode *tail;
  size_t item_count;
  ListOptions options;
  comparator compare;
};

struct ListNode {
  void *value;
  ListNode *previous;
  ListNode *next;
  List *owner;
};

/*
// TODO: Implement logic that uses these
struct TreeNode {
  struct ListNode;
  ListNode *left;
  ListNode *right;
};

// NOTE: Can we union these to get some interchangability?
union uListNode {
  struct ListNode;
  struct TreeNode;
};
*/

int pointer_compare(const void *p1, const void *p2) {
  if (p1 <  p2) { return -1; }
  if (p1 == p2) { return  0; }
  if (p1  > p2) { return  1; }

  return ~0;
}

bool ListAlloc(List **lpp, ListOptions opts) {
  if (lpp == NULL) {
    return false;
  }

  List *new = malloc(sizeof(List));
  if (new == NULL) {
    *lpp = NULL;
    return false;
  }

  new->options = opts;
  new->type = ListTypeDoublyLinkedList;
  new->item_count = 0;

  *lpp = new;
  return true;
}

bool ListAllocDefault(List **lpp) {
  return ListAlloc(lpp, ListOptionsDefaults);
}

List *ItrListAlloc(ListOptions opts) {
  List *lp = NULL;
  if (ListAlloc(&lp, opts)) {
    return lp;
  }
  return NULL;
}
List *ItrListAllocDefault(void) {
  List *lp = NULL;
  if (ListAllocDefault(&lp)) {
    return lp;
  }
  return NULL;
}

bool ListSetComparator(List *list, comparator c) {
  if (list == NULL) {
    return false;
  }

  if (c == NULL) {
    list->compare = &pointer_compare;
  } else {
    list->compare = c;
  }

  return true;
}

bool ListNodeAlloc(List *list, ListNode **lnpp, void *value) {
  if (list == NULL || lnpp == NULL) {
    return false;
  }

  ListNode *new = malloc(sizeof(ListNode));
  if (new == NULL) {
    return false;
  }

  new->owner = list;
  new->value = value;

  *lnpp = new;
  return true;
}

// Outputs the previous values in `value`, `previous`, and `next`
bool ListNodeFree(ListNode **lnpp, void **value, ListNode **previous, ListNode **next) {
  if (lnpp == NULL || *lnpp == NULL) {
    return false;
  }

  ListNode *node = *lnpp;
  List *list = node->owner;

  if (!(previous == NULL || *previous == NULL)) {
    *previous = node->previous;
  }
  if (!(next == NULL || *next == NULL)) {
    *next = node->next;
  }
  if (!(value == NULL || *value == NULL)) {
    *value = node->value;
  }

  if (list->options & ListOptionsTakeOwnership) {
    free(*value);
    *value = NULL;
  }

  free(node);
  *lnpp = NULL;

  return true;
}

bool ListFree(List **lpp) {
  if (lpp == NULL || *lpp == NULL) {
    return false;
  }

  List *list = *lpp;
  ListNode *previous;

  // Dealloc in reverse in case that's good for memory management
  for(ListNode *node=list->tail; node != NULL; node = previous) {
    if (!ListNodeFree(&node, NULL, &previous, NULL)) {
      return false;
    }
  }

  free(*lpp);
  *lpp = NULL;

  return true;
}

bool ListStart(List *l, ListNode **lnpp) {
  if (l == NULL || lnpp == NULL || *lnpp == NULL) {
    return false;
  }

  *lnpp = l->head;
  return true;
}

ListNode *ItrListStartNode(List *list) {
  ListNode *np = NULL;
  if (ListStart(list, &np)) {
    return np;
  }
  return NULL;
}

void *ItrListStartItem(List *list) {
  ListNode *np = ItrListStartNode(list);
  if (np != NULL) {
    return np->value;
  }
  return NULL;
}

bool ListEnd(List *l, ListNode **lnpp) {
  if (l == NULL || lnpp == NULL || *lnpp == NULL) {
    return false;
  }

  *lnpp = l->tail;
  return true;
}

ListNode *ItrListEndNode(List *list) {
  ListNode *np = NULL;
  if (ListEnd(list, &np)) {
    return np;
  }
  return NULL;
}

void *ItrListEndItem(List *list) {
  ListNode *np = ItrListEndNode(list);
  if (np != NULL) {
    return np->value;
  }
  return NULL;
}

bool ListItemCount(List *list, int *p) {
  if (list == NULL || p == NULL) {
    *p = -1;
    return false;
  }
  *p = list->item_count;
  return true;
}

int ItrListItemCount(List *list) {
  int c = 0;
  if (ListItemCount(list, &c)) {
    return c;
  }
  return -1;
}

bool ListNodeParent(ListNode *node, List **lpp) {
  if (node == NULL || lpp == NULL) {
    return false;
  }

  *lpp = node->owner;
  return true;
}

List *ItrListNodeParent(ListNode *node) {
  List *lp = NULL;
  if (ListNodeParent(node, &lp)) {
    return lp;
  }
  return NULL;
}

bool ListNodeNext(ListNode *node, ListNode **lnpp) {
  if (node == NULL || lnpp == NULL) {
    return false;
  }

  *lnpp = node->next;
  return true;
}

ListNode *ItrListNodeNext(ListNode *node) {
  ListNode *np = NULL;
  if (ListNodeNext(node, &np)) {
    return np;
  }
  return NULL;
}

bool ListNodePrevious(ListNode *node, ListNode **lnpp) {
  if (node == NULL || lnpp == NULL) {
    return false;
  }

  *lnpp = node->previous;
  return true;
}

ListNode *ItrListNodePrevious(ListNode *node) {
  ListNode *np = NULL;
  if (ListNodePrevious(node, &np)) {
    return np;
  }
  return NULL;
}

bool ListNodeGetItem(ListNode *node, void **pItem) {
  if (node == NULL) {
    return false;
  }

  *pItem = node->value;

  return true;
}

void *ItrListNodeGetItem(ListNode *node) {
  void *item = NULL;
  if (ListNodeGetItem(node, &item)) {
    return item;
  }
  return NULL;
}

bool ListContainsPointerOrValue(List *list, void *value) {
  for (ListNode *node=list->head; node != NULL; node = node->next) {
    if (pointer_compare(value, node->value) == 0) {
      return true;
    }

    if ( // If the list requires unique items, and we have a comparator function that's not the default...
      list->options & ListOptionUniqueItems &&
      list->compare != NULL &&
      list->compare != pointer_compare
    ) {
      // ... then call the comparator
      if (list->compare(value, node->value) == 0) {
        return true;
      }
    }
  }

  return false;
}

bool ListAddItem(List *list, void *value) {
  if (list == NULL || value == NULL) {
    return false;
  }

  if (ListContainsPointerOrValue(list, value)) {
    return false;
  }

  ListNode *new = NULL;
  if (!ListNodeAlloc(list, &new, value)) {
    return false;
  }
  new->next = NULL;

  ListNode *head = list->head;
  ListNode *tail = list->tail;
  if (head == NULL) {
    list->head = new;
    list->tail = new;
  } else {
    if (head == tail) {
      new->previous = head;
      list->tail = new;
      head->next = new;
    } else {
      new->previous = tail;
      tail->next = new;
      list->tail = new;
    }
  }

  list->item_count += 1;

  return true;
}

bool ListRemoveNode(ListNode *node) {
  ListNode *prev = node->previous;
  ListNode *next = node->next;

  next->previous = prev;
  prev->next = next;

  return ListNodeFree(&node, NULL, NULL, NULL);
}

bool ListForEach(List *list, ListEachFn each) {
  if (list == NULL || each == NULL) {
    return false;
  }

  for(ListNode *node = list->head; node != NULL; node = node->next) {
    each(node->value);
  }

  return true;
}

List *ListFilter(List *list, ListFilterFn filter) {
  if (list == NULL || filter == NULL) {
    return NULL;
  }

  List *filtered = ItrListAlloc(list->options);

  for(ListNode *node = list->head; node != NULL; node = node->next) {
    if (filter(node->value)) {
      ListAddItem(filtered, node->value);
    }
  }

  return filtered;
}

List *ListMap(List *list, ListMapFn map) {
  if (list == NULL || map == NULL) {
    return NULL;
  }

  List *mapped = ItrListAlloc(list->options);

  for(ListNode *node = list->head; node != NULL; node = node->next) {
    ListAddItem(mapped, map(node->value));
  }

  return mapped;
}

void *ListReduce(List *list, void *initial, ListReduceFn reduce) {
  if (list == NULL || reduce == NULL) {
    return NULL;
  }

  void *result = initial;

  for(ListNode *node = list->head; node != NULL; node = node->next) {
    result = reduce(result, node->value);
  }

  return result;
}
