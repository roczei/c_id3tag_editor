#include "id3tag.h"

/*
   Feladata: Vegrehajtja a foprogramot
   Hasznalatanak elofeltetelei: nincsen
   Bemeno parameterek: argc es argv, argc int tipusu, az argv pointer
   Visszateresi ertek: nincsen
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek: MufajFelismero, KarakterKonvertalo, SzammaKonvertalo,
                      KapcsoloVizsgalo, Sugo
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. majus 5.
*/

void
foprogram(int argc, uchar **argv)
{
    long int fajlmeret;   /* Az mp3szam meretet fogja tartalmazni */
    long int hely1, hely2;   /* segedvaltozok a fajlmeret meghatarozasahoz */
    id3v1 id3record;   /* Az ID3TAG rekordja */
    uchar id3tag[128];  /* Ebbe olvasom bele a TAG-ot, es ezt szerkesztem */
    uchar tomb[3];   /* Ennek a segitsegevel ellenorzom, hogy mp3 e */
    FILE *mp3szam;   /* Fajlmutato */
    int hiany=0; /* Ez tartalmazza a hianyzo kapcsolok szamat */
    int i, j;  /* Segedvaltozok a ciklusokhoz */
    if ( argc == 1 )
        exit(0);  /* Kilep, ha nem kapott argumentumot */
    if ( argv[1][0] == '?' )   /* Megnezi, hogy a sugora vagy e kivancsi */
    {
        Sugo(0);
	Sugo(1);
      	Sugo(2);
	exit(0);
    }
      if ( argc == 2 )
	 mp3szam=fopen(argv[1], "rb");
      else
	 mp3szam=fopen(argv[1], "r+b");
      if ( mp3szam == NULL )
      {
	 fprintf(stderr, "Nem sikerult a fajl-t megnyitnom!\n");
         Sugo(1);
	 exit(-1);
      }
      i=strlen(argv[1]);   /* Megnezi, hogy milyen hosszu a fajlnev */
      tomb[0]=argv[1][ i - 3 ];
      tomb[1]=argv[1][ i - 2 ];
      tomb[2]=argv[1][ i - 1 ];
      for (i=0; i <= 2; i++) /* A kiterjesztest nagybetusre alakitja */
	 if ( tomb[i] >= 97 && tomb[i] <= 122 )
	 tomb[i] -= 32;
      if ( tomb[0] != 'M' && tomb[1] != 'P' && tomb[2] != '3' )
      {
	 fprintf(stderr, "\nEz a fajl nem mp3 szam!\n");
	 exit(-1);
      }
      fseek(mp3szam, -128, SEEK_END);
      for (i=0; i < 128; i++, *( mp3szam + 1 ))
	 id3tag[i]=fgetc(mp3szam);
      /*
         A fajl elejenek es a vegenek a tavolsagat szamolja ki bajtokban,
         ebbol kapja meg a fajl meretet.
      */
           
      fseek(mp3szam, 0, SEEK_SET);
      hely1=ftell(mp3szam);
      fseek(mp3szam, 0, SEEK_END);
      hely2=ftell(mp3szam);
      fajlmeret=hely2-hely1;   /* Kiszamolom a fajl meretet */
      if ( argc > 2 )
      {
	 if ( id3tag[0] != 'T' && id3tag[1] != 'A' && id3tag[2] != 'G' )
	 {
            fajlmeret += 128;
            id3tag[0]='T';
	    id3tag[1]='A';
	    id3tag[2]='G';
	    for (i=3; i < 127; i++)    /* Feltolti \0-val az ures reszeket */
	       id3tag[i]='\0';
	    id3tag[i]=255;   /* Beallitja a mufajt 255-re, ami ismeretlen */
	    for (i=2; i != argc; i++)
	       if ( argv[i][0] == '-' )
	       {    /* Most ellenorzom, hogy van e hianyzo kapcsolo */
                  if  ( ( hiany != strlen(argv[ i - hiany - 1 ]) - 1 && hiany != 0 ) ||
                      ( i - hiany - 1 == 1 && i != 2 ) )                                    
                  {
                      printf("\nHianyzik egy, vagy tobb kapcsolo!\n");
                      exit (-1);
                  }
                  hiany=0;   
                  KapcsoloVizsgalo(argc, argv, i, id3tag, fajlmeret);
	       }
               else
               {
                   hiany++;
                   if ( argc - 1 == i && hiany != strlen(argv[ i - hiany ]) - 1 )
                   {
                      printf("\nHianyzik egy, vagy tobb kapcsolo!\n");
                      exit (-1);
                   }
               }
	    fseek(mp3szam, 0, SEEK_END);
               /* Beirja a fajlba az uj TAG-ot */
               
	    for (i=0; i < 128; i++, *( mp3szam + 1 ))
	       fputc(id3tag[i], mp3szam);
               /* Ez hozza letre az ID3TAG-ot, ha nem letezik. */
               
	 }
	 else
	 {
	    for (i=2; i != argc; i++)
	       if ( argv[i][0] == '-' )
	       {    /* Most ellenorzom, hogy van e hianyzo kapcsolo */
                  if ( ( hiany != strlen(argv[ i - hiany - 1 ]) - 1 && hiany != 0 ) ||
                      ( i - hiany - 1 == 1 && i != 2 ) )                     
                  {
                      printf("\nHianyzik egy, vagy tobb kapcsolo!\n");
                      exit (-1);
                  }
                  hiany=0;                  
                  KapcsoloVizsgalo(argc, argv, i, id3tag, fajlmeret);
	       }
               else
               {
                   hiany++;
                   if ( argc - 1 == i && hiany != strlen(argv[ i - hiany ]) - 1 )
                   {
                      printf("\nHianyzik egy, vagy tobb kapcsolo!\n");
                      exit (-1);
                   }
               }
	    fseek(mp3szam, -128, SEEK_END);
	    for (i=0; i < 128; i++, *( mp3szam + 1 ))
	       fputc(id3tag[i], mp3szam);
            /* Ez a resz modositja az ID3TAG-ot, ha mar letezik. */
	 }
      }
      if ( id3tag[0] == 'T' && id3tag[1] == 'A' && id3tag[2] == 'G' )     
           Megjelenito(id3tag, argv);
      else
	 printf("\n\nEz az mp3 szam nem tartalmaz ID3v1-es tagot!\n\n");
      fflush(mp3szam);
      fclose(mp3szam);
}
