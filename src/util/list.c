#include "list.h"

typedef enum {
  ListTypeSinglyLinkedList,
  ListTypeDoublyLinkedList,
  ListTypeBalancedTree,
} ListType;

struct List {
  ListType type;
  ListNode *head;
  ListNode *tail;
};
struct ListNode {
  void *value;
  ListNode *previous;
  ListNode *next;
};

bool ListAlloc(List **);
bool ListFree(List **);

bool ListStart(List *, ListNode **);
bool ListEnd(List *, ListNode **);

bool ListNodeParent(ListNode *, List **);

bool ListNodeNext(ListNode *, ListNode **);
bool ListNodePrevious(ListNode *, ListNode **);

bool ListAddItem(List*, void *);

