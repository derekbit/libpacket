#include <string.h>
#include "packet.h"

static inline int get_field_info(packet_t *p, uint8_t *type, uint32_t *size)
{
	if (str_get_uint8(p->s, type))
		return -1;

	if (*type == QRPC_NULL || *type == QRPC_TRUE || *type == QRPC_FALSE)
		return 0;

	if (str_get_uint32(p->s, size))
		return -1;

	return 0;
}

static inline int add_field_info(packet_t *p, uint8_t type, uint32_t size)
{
	if (str_add_uint8(p->s, type) ||
	    str_add_uint32(p->s, size))
		return -1;

	return 0;
}

static void update_header(packet_t *p, int size)
{
	char *buf = str_get_buf(p->s);
	char *ptr;
	int val;

	p->size += size;
	p->num_fields += 1;

	val = htobe32(p->size);
	ptr = buf + PACKET_OFFSET_LEN;
	memcpy(ptr, &val, sizeof(int));

	ptr = buf + PACKET_OFFSET_NUM_FIELDS;
	memcpy(ptr, &(p->num_fields), sizeof(uint8_t));
}

/* Add */
int packet_add_null(packet_t *p)
{
	int ret;

	ret = str_add_uint8(p->s, QRPC_NULL);
	update_header(p, 1);

	return ret;
}

int packet_add_bool(packet_t *p, bool val)
{
	int ret;
	uint8_t type = (val ? QRPC_TRUE : QRPC_FALSE);

	ret = str_add_uint8(p->s, type);
	update_header(p, 1);

	return ret;
}

int packet_add_uchar(packet_t *p, unsigned char val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_UCHAR, sizeof(unsigned char)) ||
	    str_add_uint8(p->s, val))
		return -1;

	update_header(p, 6);

	return 0;
}

int packet_add_char(packet_t *p, char val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_CHAR, sizeof(char)) ||
	    str_add_int8(p->s, val))
		return -1;

	update_header(p, 6);

	return 0;
}

int packet_add_uint8(packet_t *p, uint8_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_UINT8, sizeof(uint8_t)) ||
	    str_add_uint8(p->s, val))
		return -1;

	update_header(p, 6);

	return 0;
}

int packet_add_int8(packet_t *p, int8_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_INT8, sizeof(int8_t)) ||
	    str_add_int8(p->s, val))
		return -1;

	update_header(p, 6);

	return 0;
}

int packet_add_uint16(packet_t *p, uint16_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_UINT16, sizeof(uint16_t)) ||
	    str_add_uint16(p->s, val))
		return -1;

	update_header(p, 7);

	return 0;
}

int packet_add_int16(packet_t *p, int16_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_INT16, sizeof(int16_t)) ||
	    str_add_int16(p->s, val))
		return -1;

	update_header(p, 7);

	return 0;
}

int packet_add_uint32(packet_t *p, uint32_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_UINT32, sizeof(uint32_t)) ||
	    str_add_uint32(p->s, val))
		return -1;

	update_header(p, 9);

	return 0;
}

int packet_add_int32(packet_t *p, int32_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_INT32, sizeof(int32_t)) ||
	    str_add_int32(p->s, val))
		return -1;

	update_header(p, 9);

	return 0;
}

int packet_add_uint64(packet_t *p, uint64_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_UINT64, sizeof(uint64_t)) ||
	    str_add_uint64(p->s, val))
		return -1;

	update_header(p, 13);

	return 0;
}

int packet_add_int64(packet_t *p, int64_t val)
{
	if (!p)
		return -1;

	if (add_field_info(p, QRPC_INT64, sizeof(int64_t)) ||
	    str_add_int64(p->s, val))
		return -1;

	update_header(p, 13);

	return 0;
}

int packet_add_string(packet_t *p, const char *data)
{
	int size = 0;

	if (!p || !data)
		return -1;

	size = strlen(data) + 1;

	if (add_field_info(p, QRPC_STRING, size) ||
	    str_add_data(p->s, data, size))
		return -1;

	update_header(p, 5 + size);

	return 0;
}

int packet_add_void(packet_t *p, void *data, int size)
{
	if (!p || !data)
		return -1;

	if (add_field_info(p, QRPC_VOID, size) ||
	    str_add_data(p->s, data, size))
		return -1;

	update_header(p, 5 + size);

	return 0;
}

/* Get */
static inline int packet_get_uint8(packet_t *p, uint8_t *val)
{
	if (!p)
		return -1;

	return str_get_uint8(p->s, val);
}

static inline int packet_get_int8(packet_t *p, int8_t *val)
{
	if (!p)
		return -1;

	return str_get_int8(p->s, val);
}

static inline int packet_get_uint16(packet_t *p, uint16_t *val)
{
	if (!p)
		return -1;

	return str_get_uint16(p->s, val);
}

static inline int packet_get_int16(packet_t *p, int16_t *val)
{
	if (!p)
		return -1;

	return str_get_int16(p->s, val);
}

static inline int packet_get_uint32(packet_t *p, uint32_t *val)
{
	if (!p)
		return -1;

	return str_get_uint32(p->s, val);
}

static inline int packet_get_int32(packet_t *p, int32_t *val)
{
	if (!p)
		return -1;

	return str_get_int32(p->s, val);
}

static inline int packet_get_uint64(packet_t *p, uint64_t *val)
{
	if (!p)
		return -1;

	return str_get_uint64(p->s, val);
}

static inline int packet_get_int64(packet_t *p, int64_t *val)
{
	if (!p)
		return -1;

	return str_get_int64(p->s, val);
}

static inline int packet_get_data(packet_t *p, void *data, uint32_t len)
{
	if (!p)
		return -1;

	return str_get_data(p->s, data, len);
}

static int add_header(packet_t *p, uint8_t op, uint8_t req, uint8_t ack)
{
	if (!p)
		return -1;

	if (str_add_uint32(p->s, 0) ||
	    str_add_uint8(p->s, ack) ||
	    str_add_uint8(p->s, req) ||
	    str_add_uint8(p->s, op) ||
	    str_add_uint8(p->s, 0))
		return -1;

	p->size = PACKET_HEADER_SIZE;

	return 0;
}

static int get_header(packet_t *p)
{
	if (packet_get_uint32(p, &p->size) ||
	    packet_get_uint8(p, &p->ack) ||
	    packet_get_uint8(p, &p->req) ||
	    packet_get_uint8(p, &p->op) ||
	    packet_get_uint8(p, &p->num_fields))
		return -1;

	return 0;
}

static void fields_destroy(field_t *fields, int num_fields)
{
	if (!fields)
		return;

	for (int i = 0; i < num_fields; i++) {
		if (fields[i].type == QRPC_VOID ||
		    fields[i].type == QRPC_STRING)
			free(fields[i].v);
	}

	free(fields);
}

static field_t *fields_create(packet_t *p)
{
	field_t *fields;
	int retval = 0;

	fields = calloc(p->num_fields, sizeof(field_t));
	if (!fields)
		return NULL;

	for (int i = 0; i < p->num_fields; i++) {
		if (get_field_info(p, &(fields[i].type), &(fields[i].size))) {
			fields_destroy(fields, p->num_fields);
			return NULL;
		}

		switch (fields[i].type) {
		case QRPC_NULL:
			break;
		case QRPC_TRUE:
			break;
		case QRPC_FALSE:
			break;
		case QRPC_UINT8:
			retval = packet_get_uint8(p, &(fields[i].u8));
			break;
		case QRPC_INT8:
			retval = packet_get_int8(p, &(fields[i].i8));
			break;
		case QRPC_UINT16:
			retval = packet_get_uint16(p, &(fields[i].u16));
			break;
		case QRPC_INT16:
			retval = packet_get_int16(p, &(fields[i].i16));
			break;
		case QRPC_UINT32:
			retval = packet_get_uint32(p, &(fields[i].u32));
			break;
		case QRPC_INT32:
			retval = packet_get_int32(p, &(fields[i].i32));
			break;
		case QRPC_UINT64:
			retval = packet_get_uint64(p, &(fields[i].u64));
			break;
		case QRPC_INT64:
			retval = packet_get_int64(p, &(fields[i].i64));
			break;
		case QRPC_STRING:
		case QRPC_VOID:
			fields[i].v = calloc(fields[i].size, sizeof(char));
			if (!fields[i].v) {
				retval = -1;
				break;
			}

			retval = packet_get_data(p, fields[i].v, fields[i].size);
			break;
		default:
			fprintf(stderr, "unknow data type (%d)\n", fields[i].type);
					return NULL;
		}

		if (retval) {
			fields_destroy(fields, p->num_fields);
			return NULL;
		}
	}

	return fields;
}

void packet_destroy(packet_t *p)
{
	if (p) {
		fields_destroy(p->fields, p->num_fields);
		str_put(p->s);
		free(p);
	}
}

packet_t *packet_create(uint8_t op, uint8_t req)
{
	packet_t *p;

	p = calloc(1, sizeof(packet_t));
	if (!p)
		return NULL;

	p->s = str_get(0);
	if (!p->s) {
		packet_destroy(p);
		return NULL;
	}

	if (add_header(p, op, req, PACKET_ACK)) {
		packet_destroy(p);
		return NULL;
	}

	p->ack = PACKET_ACK;
	p->req = req;
	p->op = op;
	
	return p;
}

packet_t *packet_parse(const char *msg, int size)
{
	packet_t *p = NULL;

	if (!msg)
		return NULL;

	p = calloc(1, sizeof(packet_t));
	if (!p)
		return NULL;

	p->s = str_get(0);
	if (!p->s)
		return NULL;

	if (str_add_data(p->s, msg, size)) {
		packet_destroy(p);
		return NULL;
	}

	/* Read header */
	if (get_header(p)) {
		packet_destroy(p);
		return NULL;
	}

	/* Check ACK */
	if (p->ack != PACKET_ACK) {
		fprintf(stderr, "invalid packet\n");
		packet_destroy(p);
		return NULL;
	}

	/* Read fields */
	p->fields = fields_create(p);
	if (!p->fields) {
		packet_destroy(p);
		return NULL;
	}
		
	return p;
}
