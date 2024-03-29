#pragma once

enum Error{
  OK,
  WARN,
  BAD
};

#define LOG(...) fprintf(stderr, "[LOG] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__)

#define WARNING(...) fprintf(stderr, "\033[93,40m[WARNING] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__);\
                        fprintf(stderr, "\033[0m")

#define ERROR(...)   fprintf(stderr, "\033[91,40m[ERROR] %s:%s:%d: ", __FILE__, __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__);\
                        fprintf(stderr, "\033[0m")

#define MALLOC_ERROR ERROR("Out memory (malloc)")
