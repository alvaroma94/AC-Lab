#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

int cache[128]; // cache de 128 bloques

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */

void init_cache ()
{
    totaltime=0.0;

    /* Escriu aqui el teu codi */

    int i;

    for (i = 0; i < 128; ++i) cache[i] = -1;

}

/* La rutina reference es cridada per cada referencia a simular */

void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
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

	linea_mc = a & 127;

	a = a/128;

	tag = a & 1048575;

	tag_out = -1;

	if (cache[linea_mc] == -1) { // miss de lectura sin reemplazo

	  miss = 1;

	  cache[linea_mc] = tag;

	  replacement = 0;

	}

	else if (cache[linea_mc] != tag) { // miss de lectura con reemplazo

	  miss = 1;

	  tag_out = cache[linea_mc];

	  cache[linea_mc] = tag;

	  replacement = 1;

	}

	else { // hit de lectura

	  miss = 0;

	  replacement = 0;

	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */

	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */

void final ()
{
 	/* Escriu aqui el teu codi */ 
}

/*
alumne@linuxFIB:~/AC/Fibernalia> gcc CacheSim.o MiSimulador.c tiempo.c -o sim
alumne@linuxFIB:~/AC/Fibernalia> ./sim 0
Test 0 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim 1
Test 1 PASS :-)
alumne@linuxFIB:~/AC/Fibernalia> ./sim 2
Test 2 PASS :-)
*/