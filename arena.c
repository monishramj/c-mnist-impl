/*
 * Basic memeory arena allocator
 */

#include "arena.h"

#include <stdlib.h>

arena_t *arena_create(size_t size)
{
  if (size == 0)
    return NULL;

  arena_t *arena = malloc(sizeof(arena_t));
  arena->pos = 0;
  arena->reserved_size = size;
  arena->base = malloc(size);

  return arena;
}

void *arena_push(arena_t *arena, size_t size)
{
  if (!arena)
    return NULL;
  size_t aligned_pos = (arena->pos + 7) & ~7;
  if (aligned_pos + size > arena->reserved_size)
    return NULL;

  void *ptr = arena->base + aligned_pos;
  arena->pos = aligned_pos + size;
  return ptr;
}

void arena_clear(arena_t *arena)
{
  if (!arena)
    return;
  arena->pos = 0;
}

void arena_destroy(arena_t **arena)
{
  if (!arena || !*arena)
    return;

  free((*arena)->base);
  free(*arena);

  *arena = NULL;
}

static arena_t *_scratch[2] = {NULL, NULL};

arena_t *arena_scratch_get(arena_t *conflict)
{
  if (_scratch[0] == NULL)
  {
    _scratch[0] = arena_create(64 * 1024 * 1024);
    _scratch[1] = arena_create(64 * 1024 * 1024);
  }
  return (_scratch[0] == conflict) ? _scratch[1] : _scratch[0];
}

void arena_scratch_release(arena_t *scratch)
{
  arena_clear(scratch);
}