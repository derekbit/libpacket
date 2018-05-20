#ifndef _LIBPACKET_STR_H_
#define _LIBPACKET_STR_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct str_t {
	char *buf;
	int size;
	int used;
	int pos;
} str_t;

str_t *get_str(uint32_t size);
void put_str(str_t *s);
int str_add_data(str_t *str, const void *data, uint32_t len);
int str_get_data(str_t *str, void *data, uint32_t len);

int str_jump(str_t *str, uint32_t offset)
{
	if (!str)
		return -1;

	if (offset > str->size)
		return -1;

	str->used = offset;

	return 0;
}

static inline int str_get_size(str_t *str)
{
	if (!str)
		return -1;

	return str->size;
}

static inline char *str_get_buf(str_t *str)
{
	if (!str)
		return NULL;

	return str->buf;
}


static inline int str_add_u8(str_t *str, uint8_t data)
{
	if (str_add_data(str, &data, sizeof(uint8_t)) < 0)
		return -1;

	return 0;
}

static inline int str_add_u16(str_t *str, uint16_t data)
{
	if (str_add_data(str, &data, sizeof(data)) < 0)
		return -1;

	return 0;
}

static inline int str_add_u32(str_t *str, uint32_t data)
{
	if (str_add_data(str, &data, sizeof(data)) < 0)
		return -1;

	return 0;
}

static inline int str_add_u64(str_t *str, uint64_t data)
{
	if (str_add_data(str, &data, sizeof(data)) < 0)
		return -1;

	return 0;
}

static inline int str_get_u8(str_t *str, uint8_t *data)
{
	return str_get_data(str, data, sizeof(uint8_t));
}

static inline int str_get_u32(str_t *str, uint32_t *data)
{
	return str_get_data(str, data, sizeof(uint32_t));
}

static inline int str_get_u64(str_t *str, uint64_t *data)
{
	return str_get_data(str, data, sizeof(uint64_t));
}

static inline int str_get_be32toh(str_t *str, uint32_t *data)
{
	int ret;
	uint32_t data2;

	ret = str_get_data(str, &data2, sizeof(uint32_t));
	*data = be32toh(data2);

	return ret;
}

static inline int str_get_be64toh(str_t *str, uint64_t *data)
{
	int ret;
	uint64_t data2;

	ret = str_get_data(str, &data2, sizeof(uint64_t));
	*data = be64toh(data2);

	return ret;
}

#endif /* _LIBPACKET_STR_H_ */

