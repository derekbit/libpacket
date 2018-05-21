#ifndef _LIBPACKET_PACKET_H_
#define _LIBPACKET_PACKET_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "str.h"

/* QPRC Identifier */
#define QRPC_NULL      0
#define QRPC_TRUE      1
#define QRPC_FALSE     2

#define QRPC_UINT8     3  /* 1 byte */
#define QRPC_INT8      4  /* 1 byte */
#define QRPC_UINT16    5  /* 2 bytes */
#define QRPC_INT16     6  /* 2 bytes */
#define QRPC_UINT32    7  /* 4 bytes */
#define QRPC_INT32     8  /* 4 bytes */
#define QRPC_UINT64    9  /* 8 bytes */
#define QRPC_INT64    10  /* 8 bytes */

#define QRPC_STRING   11  /* A sequence of bytes with null terminated */
#define QRPC_VOID     12  /* A sequence of bytes */

#define QRPC_CHAR      QRPC_INT8
#define QRPC_UCHAR     QRPC_UINT8

/* Message Layout */
#define PACKET_HEADER_SIZE          8
#define PACKET_ACK                0xA

#define PACKET_OFFSET_LEN           0
#define PACKET_OFFSET_ACK           4
#define PACKET_OFFSET_REQ           5
#define PACKET_OFFSET_OP            6
#define PACKET_OFFSET_NUM_FIELDS    7

typedef struct field_t {
	uint8_t type;
	uint32_t size;

	union {
		unsigned char uc;
		char c;
		uint8_t u8;
		int8_t i8;
		uint16_t u16;
		int16_t i16;
		uint32_t u32;
		int32_t i32;
		uint64_t u64;
		int64_t i64;
		void *v;
	};

} field_t;

typedef struct packet_t {
	str_t *s;

	uint32_t size;

	uint8_t ack;
	uint8_t req;
	uint8_t op;
	uint8_t num_fields;
	field_t *fields;
} packet_t;

packet_t *packet_create(uint8_t op, uint8_t req);
void packet_destroy(packet_t *p);
packet_t *packet_parse(const char *msg, int size);

int packet_add_null(packet_t *p);
int packet_add_bool(packet_t *p, bool val);

int packet_add_char(packet_t *p, char val);
int packet_add_uchar(packet_t *p, unsigned char val);

int packet_add_uint8(packet_t *p, uint8_t val);
int packet_add_int8(packet_t *p, int8_t val);
int packet_add_uint16(packet_t *p, uint16_t val);
int packet_add_int16(packet_t *p, int16_t val);
int packet_add_uint32(packet_t *p, uint32_t val);
int packet_add_int32(packet_t *p, int32_t val);
int packet_add_uint64(packet_t *p, uint64_t val);
int packet_add_int64(packet_t *p, int64_t val);

int packet_add_string(packet_t *p, const char *data);
int packet_add_void(packet_t *p, void *data, int size);

#endif /* _LIBPACKET_PACKET_H_ */
