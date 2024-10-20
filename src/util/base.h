typedef void (^VoidVoidBlock)(void);

extern VoidVoidBlock EmptyCleanup;

typedef struct {
  VoidVoidBlock cleanup;
} Base;

Base *BaseAlloc(void);
void BaseInit(Base *, VoidVoidBlock);
