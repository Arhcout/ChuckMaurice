#pragma once

typedef enum CM_Error_e{
  CM_OK,
  CM_WARN,
  CM_BAD
}CM_Error;

#define CM_LOG(message) fprintf(stderr, "[LOG] %s:%s:%d: %s\n", __FILE__, __func__, __LINE__, message)
#define CM_WARNING(message) fprintf(stderr, "[WARNING] %s:%s:%d: %s\n", __FILE__, __func__, __LINE__, message)
#define CM_ERROR(message) fprintf(stderr, "[ERROR] %s:%s:%d: %s\n", __FILE__, __func__, __LINE__, message)

#define CM_MALLOC_ERROR CM_ERROR("Out memory (malloc)")
