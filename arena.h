#include <stdlib.h>

typedef struct arena
{
  char *base;           // start of the reservation
  size_t reserved_size; // size currently being used
  size_t pos;           // bump pointer

} arena_t;

#define PUSH_STRUCT(a, T) ((T *)arena_push(a, sizeof(T)))
#define PUSH_ARRAY(a, T, n) ((T *)arena_push(a, sizeof(T) * (n)))
#define PUSH_ARRAY_NZ(a, T, n) ((T *)arena_push_nz(a, sizeof(T) * (n)))

arena_t *arena_create(size_t);
void *arena_push(arena_t *, size_t);
void arena_clear(arena_t *);
void arena_destroy(arena_t **);
arena_t *arena_scratch_get(arena_t *);
void arena_scratch_release(arena_t *);