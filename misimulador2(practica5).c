#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

typedef struct {

  int via0;

  int via1;

  int LRU;

} conj;


conj cache[64]; // 64 conjuntos

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */

void init_cache ()
{
    totaltime=0.0;

    /* Escriu aqui el teu codi */

    int i;

    for (i = 0; i < 64; ++i) {

      cache[i].via0 = -1;

      cache[i].via1 = -1;

      cache[i].LRU = -1;

    }

}

/* La rutina reference es cridada per cada referencia a simular */ 

void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		   // Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();

	/* Escriu aqui el teu codi */

	unsigned int a = address;

	byte = a & 31;

	a = a/32;

	bloque_m = a & 134217727;

	conj_mc = a & 63;

	a = a/64;

	tag = a & 2097151;

	tag_out = -1;

	if (cache[conj_mc].via0 == -1) { // via0 vacia

	  miss = 1;

	  cache[conj_mc].via0 = tag;

	  via_mc = 0;

	  replacement = 0;

	  cache[conj_mc].LRU = 1;

	}

	else if (cache[conj_mc].via0 != tag) { // via0 != tag


	  if (cache[conj_mc].via1 == -1) { // via0 != tag y via1 vacia
	    
	    miss = 1;
	    
	    cache[conj_mc].via1 = tag;
	    
	    via_mc = 1;
	    
	    replacement = 0;

	    cache[conj_mc].LRU = 0;
	    
	  }

	  else if (cache[conj_mc].via1 != tag) { // via0 y via1 != tag

	    miss = 1;

	    replacement = 1;

	    if (cache[conj_mc].LRU == 0) {

	      tag_out = cache[conj_mc].via0;

	      cache[conj_mc].via0 = tag;

	      via_mc = 0;

	      cache[conj_mc].LRU = 1;

	    }

	    else { // LRU = 1

	      tag_out = cache[conj_mc].via1;

	      cache[conj_mc].via1 = tag;

	      via_mc = 1;

	      cache[conj_mc].LRU = 0;
	      
	    }

	  }

	  else { // via1 = tag

	    miss = 0;

	    replacement = 0;

	    via_mc = 1;

	    cache[conj_mc].LRU = 0;

	  }

	}

	else { // via0 = tag

	   miss = 0;

	   replacement = 0;

	   via_mc = 0;

	   cache[conj_mc].LRU = 1;

	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */

	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
 
void final ()
{
 	/* Escriu aqui el teu codi */ 
}

/*
alumne@linuxFIB:~/AC/Fibernalia> gcc CacheSim2.o MiSimulador2.c tiempo.c -o sim2
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 0
Test 0 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 1
Test 1 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 2
Test 2 PASS :-)
*/