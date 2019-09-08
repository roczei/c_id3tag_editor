#include "id3tag.h"

/*
   Feladata: Felismeri az egesz szamhoz hozzarendelt mufajt, es ezt bemasolja
   a mufaj valtozoba.
   Hasznalatanak elofeltetelei: nincsen
   Bemeno parameterek: unsigned char sorszam, usigned char mufaj
   A sorszam valtozo tartalmazza azt az egesz szamot, amihez hozzarendeli
   a mufajt, E.T.-je: 0-255. A mufaj valtozoba helyezi el a mufajt.
   Visszateresi ertek: A fuggveny megvaltoztathatja a mufaj valtozo
   sztring erteket.
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek: nincsen
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. majus 5.
*/

void
MufajFelismero(uchar sorszam, uchar *mufaj)
{    
    int szam=sorszam;   /* A tombelem sorszamat tartalmazza */
    uchar *mufajtomb[]={"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge",
                          "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B",
                          "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska",
                          "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient",
                          "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical",
                          "Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel",
                          "Noise", "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative",
                          "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
                          "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream",
                          "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap",
                          "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave", "Psychadelic",
                          "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz",
                          "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk-Rock",
                          "Natinonal Folk", "Swing", "Fast Fusion", "Bebob", "Latin", "Revival",
                          "Celtic", "Bluegrass", "Avantgarde", "Gothic Rock", "Progressive Rock",
                          "Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band", "Chorus",
                          "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera",
                          "Chamber Music", "Sonata", "Symphony", "Booty Brass", "Primus",
                          "Porn Groove", "Satire", "Slow Jam", "Club", "Tango", "Samba", "Folklore",
                          "Ballad", "Poweer Ballad", "Rhytmic", "Freestyle", "Duet", "Punk Rock",
                          "Drum Solo", "A Capela", "Euro-House", "Dance Hall"};
    if ( szam >= 0 && szam <= 125 )
        strcpy(mufaj, mufajtomb[sorszam]);
    else
        strcpy(mufaj, "Ismeretlen");
}

/*
   Feladata: Kiirja magat az ID3TAG-ot
   Hasznalatanak elofeltetelei: nincsen
   Bemeno parameterek: id3tag tomb, argv tomb
   Visszateresi ertek: nincsen
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek: Mufaj_Felismero
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. majus 7.
*/

void
Megjelenito(uchar *id3tag, uchar **argv)
{
   int i,j;   /* Segedvaltozok a ciklushoz */
   id3v1 id3record;   /* Az ID3TAG kiirasahoz hasznalt tomb */
   for (j=0, i=3; i < 33; i++, j++)
       id3record.cim[j]=id3tag[i];
       id3record.cim[30]='\0';
   for (j=0, i=33; i < 63; i++, j++)
       id3record.eloado[j]=id3tag[i];
       id3record.eloado[30]='\0';
   for (j=0, i=63; i < 93; i++, j++)
       id3record.album[j]=id3tag[i];
       id3record.album[30]='\0';
   for (j=0, i=93; i < 97; i++, j++)
       id3record.ev[j]=id3tag[i];
       id3record.ev[4]='\0';
   MufajFelismero(id3tag[127], id3record.mufaj);
   if ( id3tag[126]!=0  && id3tag[125]==0 )
   {
       for (j=0, i=97; i < 125; i++, j++)
          id3record.megjegyzes[j]=id3tag[i];
          id3record.megjegyzes[28]='\0';
       /* 
            A megjegyzes csak 28 karakter lehet, ha meg van adva a
            track szama.
       */
               
       id3record.track=id3tag[126];
   }
   else
   {
       for (j=0, i=97; i < 127; i++, j++)
           id3record.megjegyzes[j]=id3tag[i];
       id3record.megjegyzes[30]='\0';
       id3record.track=0;
   }
   printf("\n\nFajl: %s\n", argv[1]);
   printf("\n\tAlbum: %s\n", id3record.album);
   printf("\tCim: %s\n", id3record.cim);
   printf("\tEloado: %s\n", id3record.eloado);
   printf("\tKiadas eve: %s\n", id3record.ev);
   printf("\tMegjegyzes: %s\n", id3record.megjegyzes);
   printf("\tMufaj: %s\n", id3record.mufaj);
   if (id3record.track)
       printf("\tTrack: %d\n\n", id3record.track);
   else
       printf("\tTrack:\n\n");
}



