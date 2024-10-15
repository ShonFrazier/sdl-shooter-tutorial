#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define free_nullify(x) {free(x); x = NULL;}

typedef struct Node_s *Node;

struct Node_s {
  const void *key;
  const void *value;
  Node left, right;
};

typedef struct Tree_s {
  Node root;
  comparator cmp;
  copier cpy;
} *Tree;

int clamp(int test, int lower, int upper) {
  int l = MIN(lower, upper);
  int u = MAX(upper, lower);
  if (test < l) {
    return l;
  }
  if (test > u) {
    return u;
  }
  return test;
}

int default_comparator(const void *a, const void *b) {
  return clamp((a > b) - (a < b), -1, 1);
}

// Allocates storage for a new Dictionary
Dictionary dictionary_alloc(void) {
  Dictionary new = calloc(1, sizeof (struct Tree_s));
  return new;
}

void dictionary_set_comparator(Dictionary d, comparator cmp) {
  d->cmp = cmp;
}

void dictionary_set_key_copier(Dictionary d, copier cpy) {
  d->cpy = cpy;
}

ComparatorResult compare_node_keys(Dictionary d, Node n1, Node n2) {
  comparator cmp = default_comparator;

  if (d->cmp != NULL) {
    cmp = d->cmp;
  }

  return cmp(n1->key, n2->key);
}

// Private
// Frees all left branches, then all right branches, finally the node
// setting pointers to NULL.
void dict_free_deep(Node *n) {
  if (n == NULL || *n == NULL) {
    return;
  }
  Node an = *n;
  if (an->left != NULL) {
    dict_free_deep(&(an->left));
    free_nullify(an->left);
  }
  if (an->right != NULL) {
    dict_free_deep(&(an->right));
    free_nullify(an->right);
  }
  free_nullify(n);
}

// Requires address of Dictionary pointer - will set it to NULL when done
void dictionary_free(Dictionary *d) {
  if (d == NULL || *d == NULL) {
    return;
  }

  Node dn = (*d)->root;
  dict_free_deep(&dn);
  free_nullify(d);
}

Node node_alloc(Dictionary d, const void *key, const void *value) {
  if (d == NULL) {
    fprintf(stderr, "Attempted to create a Node for a NULL Dictionary\n");
    return NULL;
  }
  if (key == NULL) {
    fprintf(stderr, "Attempted to create a Node with a NULL key\n");
    return NULL;
  }
  if (d->cpy == NULL) {
    fprintf(stderr, "Dictionary doesn't have a copy function. Refusing to create a Node with a key that cannot be copied.\n");
    return NULL;
  }

  Node new_node = calloc(1, sizeof(struct Node_s));
  new_node->key = d->cpy(key);
  new_node->value = value;

  return new_node;
}

// If a copier function is set on the Dictionary, keys are copied.
// Values are never copied.
const void *dictionary_put(Dictionary d, const void *key, const void *value) {
  if (d == NULL) {
    fprintf(stderr, "Attempted to put a key/value pair into a NULL Dictionary\n");
    return NULL;
  }
  if (key == NULL) {
    fprintf(stderr, "Attempted to put a NULL key into a dictionary\n");
    return NULL;
  }
  if (d->cpy == NULL) {
    fprintf(stderr, "Dictionary doesn't have a copy function. Refusing to add a key that cannot be copied.\n");
    return NULL;
  }

  if (d->root == NULL) {
    d->root = node_alloc(d, key, value);
    Node root = d->root;
    return root->key;
  }

  Node parent, current;
  ComparatorResult cmp_res = OrderedSame;
  for (current = d->root; current!=NULL; current = (cmp_res > 0) ? current->right : current->left) {
    cmp_res = d->cmp(key, current->key);
    if (cmp_res == OrderedSame) {
      // replace the current value
      current->value = value;
      return current->key;
    }
    parent = current;
  }

  Node new_node = node_alloc(d, key, value);
  cmp_res > 0 ? (parent->right = new_node) : (parent->left = new_node);

  return new_node->key;
}

const void *dictionary_get(Dictionary d, const void *key) {
  if (d == NULL) {
    fprintf(stderr, "Dictionary cannot be NULL\n");
    return NULL;
  }
  if (key == NULL) {
    fprintf(stderr, "Key cannot be NULL\n");
    return NULL;
  }

  ComparatorResult cmp_res = OrderedSame;
  Node current = d->root;

  while (current != NULL) {
    cmp_res = d->cmp(current->key, key);
    if (cmp_res == OrderedSame) {
      return current->value;
      break;
    }
  }

  return NULL;
}
