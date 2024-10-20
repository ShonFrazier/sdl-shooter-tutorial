#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

typedef void (^free_and_clear_block)(void **);
extern free_and_clear_block free_and_clear;

#define DeclFreeBlkType(Type) \
  typedef void (^ Type ## FreeBlk)(Type **); \
  extern Type ## FreeBlk Type ## Free;

#define ImplFreeBlkType(Type, PreFree, PostFree) \
  Type ## FreeBlk Type ## Free = ^(Type **pp) { PreFree; free_and_clear((void **)pp); PostFree; };
