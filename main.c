#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "packet.h"

int main()
{
	packet_t *p = packet_create(2, 3);
	char *msg = NULL;
	int size = 0;

	if (!p) {
		fprintf(stderr, "failed to create packet\n");
		return 1;
	}

	/* Create */
	packet_add_uint8(p, 10);
	packet_add_uint32(p, 1234);
	packet_add_bool(p, true);
	packet_add_bool(p, false);
	packet_add_string(p, "/usr/bin");

	size = p->size;
	msg = malloc(size * sizeof(char));
	memcpy(msg, str_get_buf(p->s), size);
	packet_destroy(p);

	/* Read */
	p = packet_parse(msg, size);

	printf("p->size = %d\n", p->size);
	printf("p->ack = %d\n", p->ack);
	printf("p->req = %d\n", p->req);
	printf("p->op = %d\n", p->op);
	printf("p->num_fields=%d\n", p->num_fields);

	printf("p->fields[0] = %d\n", p->fields[0].u8);
	printf("p->fields[1] = %d\n", p->fields[1].u32);
	printf("p->fields[2] = %d\n", p->fields[2].type);
	printf("p->fields[3] = %d\n", p->fields[3].type);
	printf("p->fields[4] = %s\n", p->fields[4].v);

	packet_destroy(p);

	return 0;
}
