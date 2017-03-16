/*****************************************************************************
 *
 *  Distributed File Repair Utilities v0.1.5 beta
 *  insertchunks.c - inserts .fix-chunks a copy of the damaged file...
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

#define CHUNKSIZE 1024 * 32

char infilename[255] = "";
char outfilename[255] = "";
char fixfilename[255] = "";

FILE *ifp;
FILE *ofp;
FILE *ffp;

long currentoffset = 0;
long currentchunkoffset = 0;
unsigned int currentbyte = 0;
long ifsize = 0;
int chunknum = 0;
int eof_reached = 0;

unsigned char chunkdata[CHUNKSIZE] = {0};

int main(int argc, char *argv[]) {

    int bytetemp = 0;
    int bytecount = 0;
    long outbytecount;

    if (argc < 2) {printf("usage: %s brokenfile\n", argv[0]); return -1;}

    strcpy(infilename, argv[1]);
    sprintf(outfilename, "%s_fixed", infilename);

    if(NULL != (ofp = fopen(outfilename, "r"))) {printf("ERROR: '%s' already exists\n", outfilename); return -1;}

    if(NULL == (ifp = fopen(infilename, "rb"))) {printf("ERROR: cannot open '%s'\n", infilename); return -1;}
    if(NULL == (ofp = fopen(outfilename, "ab"))) {printf("ERROR: cannot open '%s'\n", infilename); return -1;}

    fseek(ifp, 0, SEEK_END);
    ifsize = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);

    while (currentoffset < ifsize) {

      bytetemp = 0;
      bytecount = 0;

      sprintf(fixfilename, "%08d.fix", chunknum);

      while(bytecount <= (CHUNKSIZE - 1) && eof_reached != 1) {

        if((bytetemp = fgetc(ifp)) == EOF) {eof_reached = 1;}
        else {
          chunkdata[bytecount] = (unsigned short)bytetemp;
          bytecount++;
        }

        currentoffset++;
      }

      if(NULL != (ffp = fopen(fixfilename, "rb"))) {

        bytetemp = 0;
        bytecount = 0;

        eof_reached = 0;

        while(bytecount <= (CHUNKSIZE - 1) && eof_reached != 1) {

          if((bytetemp = fgetc(ffp)) == EOF) {eof_reached = 1;}
          else {
            chunkdata[bytecount] = (unsigned short)bytetemp;
            bytecount++;
          }
        }

        fclose(ffp);
      }

      outbytecount = 0;

      while(outbytecount < CHUNKSIZE && outbytecount < bytecount) {
        fputc(chunkdata[outbytecount], ofp);
        outbytecount++;
      }

      printf("\rdone: %d / %d", currentoffset - 1, ifsize);

      chunknum++;
    }

    fclose (ifp);
    fclose (ofp);

    return 0;
}

