#include "id3tag.h"

/*
   Feladata: Szringet szamma konvertaljon, ha lehetseges.
   Hasznalatanak elofeltetelei: A sztring szam legyen.
   Bemeno parameterek: Az argv j. sztringjet dolgozza fel, es ezt alakitja
   at szamma, amit a szam valtozoba helyez el. A szam valtozo erteke,
   megvaltozhat emiatt.
   Visszateresi ertek: Int tipusu szam, 1 a visszateresi ertek, ha a sztring
   szamma konvertalasa sikeres, 0 a vissz. ertek, ha nem.   
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek: nicsen
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. aprilis 26.
*/

int
SzammaKonvertalo(int *szam, uchar **argv, int j)
{
   char hiba='N';   /* Ha nincs hiba, akkor az erteke: N */
   int i;
   for(i=0; argv[j][i]; i++)
   {
       switch (argv[j][i])   
       /* 
          Megvizsgalja a stringet, hogy a szamokon kivul tartalmaz e mas
          karaktert.
       */         
	 
       {
           case '0':
           case '1':
           case '2':
           case '3':
           case '4':
           case '5':
           case '6':
           case '7':
           case '8':
           case '9':
              break;
           default:
              printf("\nHibas karakter: %c\n", argv[j][i]);
              hiba='I';    
              /* 
                  Ha mar egy rossz karaktert talal, akkor a hiba
                  erteke I lesz.
              */
                                
           break;
       }   /* Switch szerkezet vege */
   }   /* For ciklus vege */
   if ( hiba == 'N' )
   {
       *szam=atoi(argv[j]);            
           /* A szam valtozoba teszi a szamma konvertalt sztringet */
           
       return 1;
   }
   else
       return 0;
}

/*
   Feladata: A kapcsolokat egyenkent kiertekeli egy argumentumon belul
   Hasznalatanak elofeltetelei: Legyen megnyitva egy mp3 szam azert, hogy
   majd modositani tudja.
   Bemeno parameterek:A mainfuggveny parameterei, parametereinek a szama,
   az id3tag tomb, valamint az mp3szam fajlmerete, ami arra szolgal, hogy
   torolni tudja az ID3TAG-ot, ha szukseges.
   Visszateresi ertek: Nincsen. Az id3tag tomb tartalma megvaltozhat.
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek: SzammaKonvertalo, Sugo
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. aprilis 26.
*/

void
KapcsoloVizsgalo(int argc, uchar **argv, int i, uchar *id3tag, long fajlmeret)
{
    int szam;
        /* trackszam, mufajszam es a kiadas evenek az ellenorzesehez */

    int j;
        /*
            Ez tarolja azt, hogy melyik argumentumot dolgozom fel az
	    aktualis kapcsolohoz.
        */

    int k, l;    /* Segedvaltozok a ciklushoz */
    int m;
        /*
           Ez tarolja azt, hogy hanyadik kapcsolot ertekelem eppen ki
	   egy argumentumon belul.
       */

    for (m=1, j = i + 1; argv[i][m]; j++, m++)
    {
	 if ( argv[i][m] != 'r' )
	 {
	    if ( argc == j )   
                /* Megvizsgalja, hogy van e a kapcsolohoz uj ertek megadva */
            {
               printf("\nHianyzo argumentum!\n");
	       Sugo(1);
	       exit (-1);
            }
	 }
	 if ( argv[i][m] != 'r' )
	 {
	    if ( argv[j][0] == '-' )
                /* 
                   Megnezi, hogy a kapcsolohoz tartozo uj ertek veletlenul
                   nem e egy masik kapcsolo.
                */   
            {
                printf("\nHianyzo argumentum!\n");
	        Sugo(1);
	        exit (-1);
            }
	 }
	 switch (argv[i][m])   /* Kirtekeli a kapcsolokat egyenkent */
	 {
	    case 'a':    /* Albumcimet modosito resz */
	       if ( strlen(argv[j]) <= 30 )
	       {
		  for (k=63, l=0; argv[j][l]; k++, l++)
		     id3tag[k]=argv[j][l];
		  for (; l < 30; l++, k++)
		     id3tag[k]='\0';   /* Az ures cellakat feltolti \0-val */
	       }
	       else
	       {
		  printf("\nTul hosszu az albumcim!\n");
		  Sugo(2);
		  exit (-1);
	       }
	       break;
	    case 'c':   /* A szam cimet modosito resz */
	       if ( strlen(argv[j]) <= 30 )
	       {
		  for (k=3, l=0; argv[j][l]; k++, l++)
		     id3tag[k]=argv[j][l];
		  for (; l < 30; l++, k++)
		     id3tag[k]='\0';  /* Itt is feltolti az ures cellakat */
	       }
	       else
	       {
		  printf("\nTul hosszu a szam cime!\n");
		  Sugo(2);
		  exit (-1);
	       }
	       break;
	    case 'e':   /* Az eloado nevet modosito resz */
	       if ( strlen(argv[j]) <= 30 )
	       {
		  for (k=33, l=0; argv[j][l]; k++, l++)
		     id3tag[k]=argv[j][l];
		  for (; l < 30; l++, k++)
		     id3tag[k]='\0';   /* Itt is ugyancsak feltolti \0-val. */
	       }
	       else
	       {
		  printf("\nTul hosszu az eloado neve!\n");
		  Sugo(2);
		  exit (-1);
	       }
	       break;
	    case 'v': /* A kiadas evet modosito resz */
	       if (SzammaKonvertalo(&szam, argv, j))
	       {
		  if ( szam >= 1900 && szam <= 2100 )
                      /* 
                         Ha az ev szama nem megfelelo, akkor nem
                         modositja.
                      */
                      
		     for (k=93, l=0; argv[j][l]; k++, l++)
		     id3tag[k]=argv[j][l];
		  else
		  {
		     printf("\n\nA kiadas eve nem megfelelo!");
		     Sugo(2);
		     exit(-1);
		  }
	       }
	       else
	       {
		  printf("\nHibasan adta meg a kiadas evet!\n");
		  exit(-1);
	       }
	       break;
	    case 'm':   /* A szam mufajat modosito resz */
	       if (SzammaKonvertalo(&szam, argv, j))
	       {
		  if ( szam >= 0 && szam <= 255 )
                       /* Csak 0-255-ig fogadja el a szamokat */
		     id3tag[127]=szam;
		  else
		  {
		     printf("\n\nA mufaj sorszama nem jo!");
		     Sugo(2);
		     exit(-1);
		  }
	       }
	       else
	       {
		  printf("\nHibasan adta meg a mufaj sorszamat!\n");
		  exit(-1);
	       }
	       break;
	    case 't':  /* A szam track szamat modosito resz */
	       if (SzammaKonvertalo(&szam, argv, j))
	       {
		  if ( szam >= 0 && szam <= 255 )   
                     /* 
                        Itt se lehet akarmilyen szamot megadni, ezt 
                        vizsgalja
                     */
                     
		  {
		     id3tag[125]='\0';
		     id3tag[126]=szam;              
		  }
		  else
		  {
		     printf("\n\nA track szama nem jo!");
		     Sugo(2);
		     exit(-1);
		  }
	       }
	       else
	       {
		  printf("\nHibasan adta meg a mufaj sorszamat!\n");
		  exit(-1);
	       }
	       break;
	    case 'g':   /* A megjegyzes mezot megvaltoztato resz */
	       if ( strlen(argv[j]) <= 28 )
	       {
		  for (k=97, l=0; argv[j][l]; k++, l++)
		     id3tag[k]=argv[j][l];
		  for (; l < 28; l++, k++)
                      /* Az ures cellakat \0-val feltolti */
		     id3tag[k]='\0';
	       }
	       else
	       {
		  printf("\nTul hosszu a megjegyzes!\n");
		  Sugo(2);
		  exit (-1);
	       }
	       break;
            case 'r':   /* Az ID3TAG-ot torlo resz */
	       fajlmeret -= 128;   /* A fajl meretet 128-al lecsokkenti */
	       truncate(argv[1], fajlmeret);
	       exit (0);
               break;
	    default:
	       printf("\nIsmeretlen kapcsolo: -%c\n", argv[i][m]);
	       Sugo(1);
	       exit (-1);
	       break;
         }   /* Switch szerkezet vege */
    }   /*  For ciklus vege */
}

/*
   Feladata: Sugo feladatot lat el
   Hasznalatanak elofeltetelei: nincsen
   Bemeno parameterek: Egy darab sorszam 0,1 es 2 van ertelmezve, ezeknek
   megfelolo irja ki a megfelelo reszt.
   Visszateresi ertek: nincsen
   Egyeb parameterek: nincsen
   Hivatkozott globalis valtozok: nincsen
   Hivott fuggvenyek:nincsen
   Keszito: Roczei Gabor
   Utolso modositas datuma: 2002. aprilis 26.
*/

void
Sugo(int fejezet)
{
      switch (fejezet)
      {
	 case 0:
	    printf("\nEz a program egy ID3v1.1-es mp3 TAG editor\n");
	    printf("A programot keszitette: Roczei Gabor\n");
	    printf("Tankor: G-102i\n");
	    printf("Datum: 2002. aprilis 26.");
	    break;
	 case 1:    /* A programban hasznalhato kapcsolok */
	    printf("\nA program hasznalata:\n");
	    printf("\t\tid3tag [? | fajlnev.mp3] [-acevmgt]... [uj ertek]...\n");
	    printf("\t\tid3tag fajlnev.mp3 -r\n\n");
            printf("\t ?\tSugo\n");
	    printf("\t-a\tAlbum cime\n");
	    printf("\t-c\tZeneszam cime\n");
	    printf("\t-e\tEloado\n");
	    printf("\t-v\tKiadas eve\n");
	    printf("\t-m\tMufaj\n");
	    printf("\t-g\tMegjegyzes\n");
	    printf("\t-t\tTrack\n");
	    printf("\t-r\tID3TAG torlese\n\n");
	    break;
	 case 2:
	    printf("\nAz album cime maximum 30 karakter lehet. ");
	    printf("A zeneszam cime maximum 30 karakter lehet. ");
	    printf("Az eloado neve maximum 30 karakter lehet. ");
	    printf("A kiadas eve egesz szam, 1900-2100-ig adhato meg. ");
	    printf("A mufaj megadasakor egy egesz szamot lehet megadni, ");
	    printf("0-255-ig. A mufajok kodjait a mufajok.txt-ben talalod meg.");
	    printf("A megjegyzes maximum 28 karakter lehet. ");
	    printf("A track erteke 0-255 lehet.\n\n");
	    break;
      }    /* A Sugo switch szerkezetenek a vege */
}    /* A Sugo fuggveny vege */
