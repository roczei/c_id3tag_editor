#ifndef __ID3TAG_H__
   #define __ID3TAG_H__
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include <unistd.h>
   typedef unsigned char uchar;
   typedef struct
   {
      uchar cim[31];    /* Az mp3 szam cime */
      uchar eloado[31];    /* Az mp3 szam eloadoja */
      uchar album[31];    /* Az mp3 szam album cime */
      uchar ev[5];    /* A kiadas eve */
      uchar megjegyzes[31];    /* Az mp3 szam megjegyzesrovata */
      uchar track;   /* Az mp3 szam track szama */
      uchar mufaj[25];    /* Az mp3 szam mufaja */
   } id3v1;
   void
   MufajFelismero(uchar sorszam, uchar *mufaj);
   int
   SzammaKonvertalo(int *szam, uchar **argv, int j);
   void
   KapcsoloVizsgalo(int argc, uchar **argv, int i, uchar *id3tag, long fajlmeret);
   void
   Sugo(int fejezet);
   void
   foprogram(int argc, uchar **argv);
   void
   Megjelenito(uchar *id3tag, uchar **argv);
#endif
