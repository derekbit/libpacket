#define _BSD_SOURCE
#include <string.h>
#include "str.h"

str_t *str_get(uint32_t size)
{
	str_t *s;

	s = calloc(1, sizeof(str_t));
	if (!s)
		return NULL;

	s->size = size;

	if (size > 0) {
		s->buf = calloc(size, 1);
		if (!s->buf) {
			free(s);
			return NULL;
		}
	}

	return s;
}

void str_put(str_t *s)
{
	if (s) {
		free(s->buf);
		free(s);
	}
}

static int str_verify(str_t *s)
{
	if (!s)
		return -1;

	if (s->used > s->size) {
		fprintf(stderr, "str error: allocated %u, used %u",
			s->size, s->used);
		return -1;
	}

	if (s->pos > s->used) {
		fprintf(stderr, "str error : position %u, used %u",
			s->pos, s->used);
		return -1;
	}

	if (s->pos > s->size) {
		fprintf(stderr, "str error : position %u, allocated %u",
			s->pos, s->size);
		return -1;
	}

	return 0;
}

static inline int realloc_str(str_t *s, int needed)
{
	int smallest = 1;
	char *new = NULL;

	/* Find the smallest power of two which is greater or equal to needed */
	while (smallest < needed)
		smallest <<= 1;

	needed = smallest;
	new = realloc(s->buf, needed);

	if (!new)
		return -1;

	s->buf = new;
	s->size = needed;

	return str_verify(s);
}

int str_add_data(str_t *s, const void *data, uint32_t len)
{
	if (s->size < (s->used + len)) {
		if (realloc_str(s, s->used + len) < 0)
			return -1;
	}

	memcpy(s->buf + s->used, data, len);

	s->used += len;
	str_verify(s);

	return 0;
}

int str_get_data(str_t *s, void *data, uint32_t len)
{
	/*
	 * Check for a integer overflow first, then check
	 * if not enough data is in the buffer.
	 */
	if (s->pos + len < len || s->pos + len > s->used)
		return -1;

	memcpy(data, s->buf + s->pos, len);
	s->pos += len;

	return 0;
}
