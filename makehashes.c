	/*****************************************************************************
 *
 *  Distributed File Repair Utilities v0.1.5 beta
 *  makehashes.c - produces hashlist of a (probably) corrupt infile
 *
 *  Copyright (C) 2005 Loki TroubleMind <loki1985@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * $loki 2005-04-05
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "md5.h"

#define CHUNKSIZE 1024 * 32

void processnextchunk(void);

char infilename[255] = "";
char outfilename[255] = "hashlist";

FILE *ifp;
FILE *ofp;

long ifoffset = 0;
long ifsize = 0;
long curchunklen = 0;
int eof_reached = 0;

md5_state_t state;
md5_byte_t digest[16];

unsigned char chunkdata[CHUNKSIZE] = {0};

int main(int argc, char *argv[]) {

    if (argc < 2) {printf("usage: %s infile\n", argv[0]); return -1;}

    strcpy(infilename, argv[1]);

    if(NULL != (ofp = fopen(outfilename, "r"))) {printf("ERROR: '%s' already exists\n", outfilename); return -1;}

    if(NULL == (ifp = fopen(infilename, "rb"))) {printf("ERROR: cannot open '%s'\n", infilename); return -1;}
    if(NULL == (ofp = fopen(outfilename, "ab"))) {printf("ERROR: cannot write to '%s'\n", outfilename); return -1;}

    fseek(ifp, 0, SEEK_END);
    ifsize = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);

    while(eof_reached != 1) {

      processnextchunk();

      printf("\rdone: %d / %d", ifoffset -1, ifsize);
    }

    fclose (ifp);
    fclose (ofp);

    return 0;
}


void processnextchunk() {

    int bytetemp = 0;
    int bytecount = 0;
    int i;

    curchunklen = 0;

    while((bytecount < CHUNKSIZE) && (eof_reached != 1)) {

      if((bytetemp = fgetc(ifp)) == EOF) {eof_reached = 1;}
      else {
        chunkdata[bytecount] = (unsigned char)bytetemp;
        bytecount++;
        curchunklen++;
      }

      ifoffset++;
    }

	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)chunkdata, curchunklen);
	md5_finish(&state, digest);

    for(i=0;i<16;i++) {fputc(digest[i], ofp);}

    return;
}
