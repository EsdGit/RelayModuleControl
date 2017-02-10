#include "crc8.h"

uint8_t crc8(uint8_t uint8_ts[MESSAGE_LENGTH], int len)
{
	uint8_t crc = 0xFF;
	int i;
	for (i = 0; i < len; i++)
          crc = crc8_table[crc ^ uint8_ts[i]];
	return crc;
}

