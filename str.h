#ifndef _LIBPACKET_STR_H_
#define _LIBPACKET_STR_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "endianess.h"

typedef struct str_t {
	char *buf;
	int size;
	int used;
	int pos;
} str_t;

str_t *str_get(uint32_t size);
void str_put(str_t *s);
int str_add_data(str_t *s, const void *data, uint32_t len);
int str_get_data(str_t *s, void *data, uint32_t len);

static inline int str_get_size(str_t *s)
{
	if (!s)
		return -1;

	return s->size;
}

static inline char *str_get_buf(str_t *s)
{
	if (!s)
		return NULL;

	return s->buf;
}

/* Add */
static inline int str_add_uint8(str_t *s, uint8_t val)
{
	if (str_add_data(s, &val, sizeof(uint8_t)) < 0)
		return -1;

	return 0;
}

static inline int str_add_int8(str_t *s, int8_t val)
{
	return str_add_uint8(s, val);
}

static inline int str_add_uint16(str_t *s, uint16_t val)
{
	uint16_t val2 = htobe16(val);

	if (str_add_data(s, &val2, sizeof(val2)) < 0)
		return -1;

	return 0;
}

static inline int str_add_int16(str_t *s, int16_t val)
{
	return str_add_uint16(s, val);
}

static inline int str_add_uint32(str_t *s, uint32_t val)
{
	uint32_t val2 = htobe32(val);

	if (str_add_data(s, &val2, sizeof(val2)) < 0)
		return -1;

	return 0;
}

static inline int str_add_int32(str_t *s, int32_t val)
{
	return str_add_uint32(s, val);
}

static inline int str_add_uint64(str_t *s, uint64_t val)
{
	uint64_t val2 = htobe64(val);

	if (str_add_data(s, &val2, sizeof(val2)) < 0)
		return -1;

	return 0;
}

static inline int str_add_int64(str_t *s, int64_t val)
{
	return str_add_uint64(s, val);
}

/* Get */
static inline int str_get_uchar(str_t *s, unsigned char *val)
{
	return str_get_data(s, val, sizeof(unsigned char));
}

static inline int str_get_char(str_t *s, char *val)
{
	return str_get_data(s, val, sizeof(char));
}

static inline int str_get_uint8(str_t *s, uint8_t *val)
{
	return str_get_data(s, val, sizeof(uint8_t));
}

static inline int str_get_int8(str_t *s, int8_t *val)
{
	return str_get_data(s, val, sizeof(int8_t));
}

static inline int str_get_uint16(str_t *s, uint16_t *val)
{
	uint16_t val2;
	int ret;

	ret = str_get_data(s, &val2, sizeof(val2));
	*val = be16toh(val2);

	return ret;
}

static inline int str_get_int16(str_t *s, int16_t *val)
{
	return str_get_uint16(s, (uint16_t *)val);
}

static inline int str_get_uint32(str_t *s, uint32_t *val)
{
	uint32_t val2;
	int ret;

	ret = str_get_data(s, &val2, sizeof(val2));
	*val = be32toh(val2);

	return ret;
}

static inline int str_get_int32(str_t *s, int32_t *val)
{
	return str_get_uint32(s, (uint32_t *)val);
}

static inline int str_get_uint64(str_t *s, uint64_t *val)
{
	uint64_t val2;
	int ret;

	ret = str_get_data(s, &val2, sizeof(val2));
	*val = be64toh(val2);

	return ret;
}

static inline int str_get_int64(str_t *s, int64_t *val)
{
	return str_get_uint64(s, (uint64_t *)val);
}

#endif /* _LIBPACKET_STR_H_ */

