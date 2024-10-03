#pragma once

typedef struct T *T;
typedef _Bool err_t;

struct THandle {
  void (*free)(void *actual_handle);
  void *actual_handle;
};
typedef struct THandle *(*TOn)(T context, const char *event_name, void *args);
typedef err_t (*TPlugin)(T context, TOn on);

typedef T (*tInit)();
typedef err_t (*tRegisterPlugin)(T self, TPlugin plugin);
typedef err_t (*tStart)(T self);
