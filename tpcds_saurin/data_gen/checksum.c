/**********************************************************************
 * Description: scan a file and compute CRC and various counts.       *
 * Version: 1.2 created August 29, 2006                               *
 * Usage: dcksum <fn>                                                 *
 * Output:  16-bit CRC                                                *
 *          number of LF(10) chars                                    *
 *          number of CR(13) chars                                    *
 *          number of delimiter('|') chars                            *
 *          number of chars total                                     *
 *********************************************************************/
#define _LARGEFILE64_SOURCE 1
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
 
unsigned short GetCCITT (unsigned short crc, unsigned short ch)
{
  static unsigned int i;
 
  ch <<= 8;
  for (i=8; i>0; i--) {
    if ((ch ^ crc) & 0X8000)
      crc = (crc << 1 ) ^ 0x1021;
    else
      crc <<= 1;
    ch <<= 1;
  }
  return (crc);
}
 
int main(int argc, char *argv[]) {
  FILE *fin;
  char *buffer;
  size_t i, j;
  long long int nLF=0, nCR=0, nChar=0, nDelim=0;
  unsigned short crc=0;
 
  if (argc < 2) {
    fin = stdin;
  } else {
    if (( fin = fopen (argv[1], "rb")) == NULL ) {
      fprintf (stderr, "Cannot open %s\n", argv[1]);
      return (1);
    }
  }
 
  if ((buffer = (char *)malloc(32766)) == NULL) {
    fprintf (stderr, "Out of memory\n");
    return (1);
  }
 
  for (;;) {
    i = fread(buffer, 1, 32766, fin);
    if (i == 0) {
      if (feof (fin)) {
        printf("CCITT CRC for %s is %04X; #LF/#CR is %lld/%lld; #Delim is %lld; #Chars is %lld\n",
          argv[1], crc, nLF, nCR, nDelim, nChar);
        return (0);
      }
      else
        continue;
    }
    for (j=0; j<i; j++) {
      ++nChar;
      switch (buffer[j]) {
        case 10: ++nLF; break;
        case 13: ++nCR; break;
        case '|': ++nDelim; crc = GetCCITT (crc, buffer[j]); break;
        default: crc = GetCCITT (crc, buffer[j]); break;
      }
    }
  }
}
