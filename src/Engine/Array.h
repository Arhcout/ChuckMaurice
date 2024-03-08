#pragma once
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#define InitArray(type, size) (type*)ManualInitArray(sizeof(type), (size))
#define ArrayPush(arr, data) {typeof(data) x = data; (arr) = ManualArrayPushBulk((arr), &x, 1);}(void)0
#define ArrayPushBulk(arr, data, len) arr = ManualArrayPushBulk((arr), (data), (len))

#define FilterArray(arr, condition) \
for(size_t __i = 0; __i < GetArrayLen((arr)); __i++){\
  typeof(*arr) item = arr[__i];\
  if ((condition)) {\
    ArrayRemove((arr), __i);\
    __i--;\
  }\
}(void)0

typedef bool (*ArrayMatch_fn)(const void* element, va_list args);

void* ManualInitArray(size_t _typeSize, size_t size);
void DestroyArray(void* vec);

void* ManualArrayPushBulk(void* arr, void* data, size_t len);
void ArrayRemove(void* vec, size_t index);
void* CopyArray(void* arr);

size_t GetArrayLen(void* vec);
