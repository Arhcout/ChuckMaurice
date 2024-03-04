#pragma once

enum CM_Error{
  CM_OK,
  CM_WARN,
  CM_BAD
};

#define CM_LOG(...) fprintf(stderr, "[LOG] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__)

#define CM_WARNING(...) fprintf(stderr, "\033[93,40m[WARNING] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__);\
                        fprintf(stderr, "\033[0m")

#define CM_ERROR(...)   fprintf(stderr, "\033[91,40m[ERROR] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__);\
                        fprintf(stderr, "\033[0m")

#define CM_MALLOC_ERROR CM_ERROR("Out memory (malloc)")
