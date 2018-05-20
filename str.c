#define _BSD_SOURCE
#include "endianess.h"
#include <string.h>
#include "str.h"

str_t *get_str(uint32_t size)
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

void put_str(str_t *s)
{
	if (!s)
		return;

	free(s->buf);
	free(s);
}

static int str_verify(str_t *str)
{
	if (!str)
		return -1;

	if (str->used > str->size) {
		fprintf(stderr, "str error: allocated %u, used %u",
			str->size, str->used);
		return -1;
	}

	if (str->pos > str->used) {
		fprintf(stderr, "str error : position %u, used %u",
			str->pos, str->used);
		return -1;
	}

	if (str->pos > str->size) {
		fprintf(stderr, "str error : position %u, allocated %u",
			str->pos, str->size);
		return -1;
	}

	return 0;
}

static inline int realloc_str(str_t *str, int needed)
{
	int smallest = 1;
	char *new = NULL;

	/* Find the smallest power of two which is greater or equal to needed */
	while (smallest < needed)
		smallest <<= 1;

	needed = smallest;
	new = realloc(str->buf, needed);

	if (!new)
		return -1;

	str->buf = new;
	str->size = needed;

	return str_verify(str);
}

int str_add_data(str_t *str, const void *data, uint32_t len)
{
	if (str_verify(str))
		return -1;

	if (str->size < (str->used + len)) {
		if (realloc_str(str, str->used + len) < 0)
			return -1;
	}

	memcpy(str->buf + str->used, data, len);

	str->used += len;
	str_verify(str);

	return 0;
}


int str_get_data(str_t *str, void *data, uint32_t len)
{
	/*
	 * Check for a integer overflow first, then check
	 * if not enough data is in the buffer.
	 */
	if (str->pos + len < len || str->pos + len > str->used)
		return 0;

	memcpy(data, str->buf + str->pos, len);
	str->pos += len;

	return len;
}
