#pragma once
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#define InitArray(type, size) (type*)ManualInitArray(sizeof(type), (size))

typedef bool (*ArrayMatch_fn)(const void* element, va_list args);

void* ManualInitArray(size_t _typeSize, size_t size);
void DestroyArray(void* vec);

void ArrayPush(void* vec, void* data);
void ArrayPushBulk(void* arr, void* data, size_t size);
void ArrayRemove(void* vec, size_t index);
void* FilterArray(void* vec, ArrayMatch_fn lam, ...);

size_t GetArrayLen(void* vec);
