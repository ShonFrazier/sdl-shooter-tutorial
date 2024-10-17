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
  ListOptions options;
  comparator compare;
};

struct LNode {
  void *value;
  ListNode *previous;
  ListNode *next;
  List *owner;
};

// TODO: Implement logic that uses these
struct TNode {
  struct LNode;
  ListNode *left;
  ListNode *right;
};

union ListNode {
  struct LNode;
  struct TNode;
};

int pointer_compare(const void *p1, const void *p2) {
  if (p1 <  p2) { return -1; }
  if (p1 == p2) { return  0; }
  if (p1 >  p2) { return  1; }

  return ~0;
}

bool ListAlloc(List **lpp, ListOptions opts) {
  List *new = malloc(sizeof(List));
  if (new == NULL) {
    *lpp = NULL;
    return false;
  }

  new->options = opts;
  new->type = ListTypeDoublyLinkedList;

  *lpp = new;
  return true;
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
  for(ListNode *node=list->tail; node != NULL; node = node->previous) {
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

bool ListEnd(List *l, ListNode **lnpp) {
  if (l == NULL || lnpp == NULL || *lnpp == NULL) {
    return false;
  }

  *lnpp = l->tail;
  return true;
}

bool ListNodeParent(ListNode *node, List **lpp) {
  if (node == NULL || lpp == NULL) {
    return false;
  }

  *lpp = node->owner;
  return true;
}

bool ListNodeNext(ListNode *node, ListNode **lnpp) {
  if (node == NULL || lnpp == NULL) {
    return false;
  }

  *lnpp = node->next;
  return true;
}

bool ListNodePrevious(ListNode *node, ListNode **lnpp) {
  if (node == NULL || lnpp == NULL) {
    return false;
  }

  *lnpp = node->previous;
  return true;
}

bool ListAddItem(List *list, void *value) {
  if (list == NULL || value == NULL) {
    return false;
  }

  ListNode *new = NULL;
  if (!ListNodeAlloc(list, &new, value)) {
    return false;
  }
  new->next = NULL;

  ListNode *tail = list->tail;
  new->previous = tail;
  tail->next = new;
  list->tail = new;

  return true;
}

void ListTests(void) {
  List *list = NULL;
  bool result = false;

  result = ListAlloc(&list, ListOptionsDefaults);

  assert(result == true);
  assert(list != NULL);

  result = ListFree(&list);

  assert(result == true);
  assert(list == NULL);

  result = ListAlloc(NULL, ListOptionsDefaults);

  assert(result == false);

}

