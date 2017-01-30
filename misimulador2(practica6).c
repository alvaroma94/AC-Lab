#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

typedef struct {

  int tag;

  int DB;

} bloque;

bloque cache[128]; // cache de 128 bloques con dirty bit

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */

void init_cache ()
{
  /* Escriu aqui el teu codi */

  int i;

  for (i = 0; i < 128; ++i) {

    cache[i].tag = -1;

    cache[i].DB = 0;

  }

}

/* La rutina reference es cridada per cada referencia a simular */

void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */

	unsigned int a = address;

	byte = a & 31;

	a = a/32;

	bloque_m = a & 134217727;

	linea_mc = a & 127;
	
	a = a/128;
	
	tag = a & 1048575;
	
	tag_out = -1;

	if (!LE) { // lectura

	  if (cache[linea_mc].tag == -1) { // miss de lectura sin reemplazo

	    cache[linea_mc].tag = tag;
	    
	    miss = 1;
	    
	    replacement = 0;
	    
	    lec_mp = 1;
	    
	    mida_lec_mp = 32; // bloques de 32 bytes

	    esc_mp = 0;

	    mida_esc_mp = 0;

	  }

	  else if (cache[linea_mc].tag != tag) { // miss de lectura con reemplazo

	    tag_out = cache[linea_mc].tag;

	    cache[linea_mc].tag = tag;

	    miss = 1;

	    replacement = 1;

	    lec_mp = 1;

	    mida_lec_mp = 32; // bloques de 32 bytes


	    if (cache[linea_mc].DB == 0) {

	      esc_mp = 0;

	      mida_esc_mp = 0;

	    }

	    else { // DB = 1

	      cache[linea_mc].DB = 0;  

	      esc_mp = 1;

	      mida_esc_mp = 32; // bloques de 32 bytes

	    }

	  }

	  else { // hit de lectura

	    miss = 0;

	    replacement = 0;
	    
	    lec_mp = 0;
	    
	    mida_lec_mp = 0;

	    esc_mp = 0;

	    mida_esc_mp = 0;

	  }

	}

	else { // escritura

	  if (cache[linea_mc].tag == -1) { // miss de escritura sin reemplazo

	    cache[linea_mc].tag = tag;

	    cache[linea_mc].DB = 1;
	    
	    miss = 1;
	    
	    replacement = 0;
	    
	    lec_mp = 1;
	    
	    mida_lec_mp = 32; // bloques de 32 bytes

	    esc_mp = 0;

	    mida_esc_mp = 0;

	  }

	  else if (cache[linea_mc].tag != tag) { // miss de escritura con reemplazo

	    tag_out = cache[linea_mc].tag;

	    cache[linea_mc].tag = tag;

	    miss = 1;

	    replacement = 1;
	    
	    lec_mp = 1;
	    
	    mida_lec_mp = 32; // bloques de 32 bytes

	    
	     if (cache[linea_mc].DB == 0) {

	       cache[linea_mc].DB = 1;

	       esc_mp = 0;

	       mida_esc_mp = 0;

	     }

	     else { // DB = 1

	       // cache[linea_mc].DB = 1;

	       esc_mp = 1;

	       mida_esc_mp = 32; // bloques de 32 bytes

	     }

	  }

	  else { // hit de escritura

	    miss = 0;

	    replacement = 0;
	    
	    lec_mp = 0;
	    
	    mida_lec_mp = 0;

	    esc_mp = 0;

	    mida_esc_mp = 0;

	    if (cache[linea_mc].DB == 0) cache[linea_mc].DB = 1;

	    // else cache[linea_mc].DB = 1;

	  }

	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */

	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */

void final ()
{
 	/* Escriu aqui el teu codi */   
}

/*
alumne@linuxFIB:~/AC/Fibernalia> gcc CacheSimCB.o MiSimulador2.c -o sim2
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 v 0
10f92150 L -> l MP:  87c90a l MC:     a TAG:10f92 byte:10 MISS L:32
10f92151 E -> l MP:  87c90a l MC:     a TAG:10f92 byte:11 HIT 
10f8a192 E -> l MP:  87c50c l MC:     c TAG:10f8a byte:12 MISS L:32
10f92153 L -> l MP:  87c90a l MC:     a TAG:10f92 byte:13 HIT 
10f8b195 L -> l MP:  87c58c l MC:     c TAG:10f8b byte:15 MISS L:32 E:32 -> 10f8a
10f8b195 L -> l MP:  87c58c l MC:     c TAG:10f8b byte:15 HIT 
10f93156 L -> l MP:  87c98a l MC:     a TAG:10f93 byte:16 MISS L:32 E:32 -> 10f92
10f92157 E -> l MP:  87c90a l MC:     a TAG:10f92 byte:17 MISS L:32 -> 10f93
10f8a198 L -> l MP:  87c50c l MC:     c TAG:10f8a byte:18 MISS L:32 -> 10f8b
10f93159 E -> l MP:  87c98a l MC:     a TAG:10f93 byte:19 MISS L:32 E:32 -> 10f92
12f92250 L -> l MP:  97c912 l MC:    12 TAG:12f92 byte:10 MISS L:32
10f92151 E -> l MP:  87c90a l MC:     a TAG:10f92 byte:11 MISS L:32 E:32 -> 10f93
10f8a192 L -> l MP:  87c50c l MC:     c TAG:10f8a byte:12 HIT 
12f92253 E -> l MP:  97c912 l MC:    12 TAG:12f92 byte:13 HIT 
10f8b195 E -> l MP:  87c58c l MC:     c TAG:10f8b byte:15 MISS L:32 -> 10f8a
10f8b195 L -> l MP:  87c58c l MC:     c TAG:10f8b byte:15 HIT 
10f93156 L -> l MP:  87c98a l MC:     a TAG:10f93 byte:16 MISS L:32 E:32 -> 10f92
12f92257 L -> l MP:  97c912 l MC:    12 TAG:12f92 byte:17 HIT 
10f8a298 L -> l MP:  87c514 l MC:    14 TAG:10f8a byte:18 MISS L:32
10f93159 L -> l MP:  87c98a l MC:     a TAG:10f93 byte:19 HIT 
Test 0 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 1
Test 1 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim2 2
Test 2 PASS :-)
*/