/* { dg-do run } */
/* { dg-options "-fdump-tree-crc-details -w" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-g" "-Os" "-flto"} } */

#include <stdint.h>
#include <stdlib.h>

__attribute__ ((noinline,optimize(0)))
uint32_t _crc32_O0 (uint32_t data, uint32_t crc) {
  int i;
  for (i = 0; i < 32; i++) {
      if ((crc & 0x80000000) ^ (data & 0x80000000))
	crc = (crc << 1) ^ 0x04C11DB7;
      else
	crc = (crc << 1);
      data <<= 1;
    }
  return crc;
}

uint32_t _crc32 (uint32_t data, uint32_t crc) {
  int i;
  for (i = 0; i < 32; i++) {
      if ((crc & 0x80000000) ^ (data & 0x80000000))
	crc = (crc << 1) ^ 0x04C11DB7;
      else
	crc = (crc << 1);
      data <<= 1;
    }
  return crc;
}

int main ()
{
  uint32_t crc = 0;

  for (uint32_t i = 0; i < 0xffff; i++)
    {
      uint32_t res1 = _crc32_O0 (i, crc);
      uint32_t res2 = _crc32 (i, crc);
      if (res1 != res2)
	abort ();
      crc = res2;
    }
}

/* { dg-final { scan-tree-dump "function maybe contains CRC calculation." "crc"} } */
/* { dg-final { scan-tree-dump "Loop iteration number is 31" "crc"} } */
/* { dg-final { scan-tree-dump "Bit forward" "crc"} } */
/* { dg-final { scan-tree-dump "calculates CRC." "crc"} } */
/* { dg-final { scan-tree-dump-times "Couldn't generate faster CRC code." 0 "crc"} } */