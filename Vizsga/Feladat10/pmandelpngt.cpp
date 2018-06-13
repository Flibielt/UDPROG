// Mandelbrot png párhuzamosan P-szálakkal
// Programozó Páternoszter/PARP
//
// Dr. Bátfai Norbert, batfai.norbert@inf.unideb.hu, nbatfai@gmail.com
// http://progpater.blog.hu/2011/03/26/kepes_egypercesek
// http://progpater.blog.hu/2011/03/27/a_parhuzamossag_gyonyorkodtet
//
// l. még.: http://www.tankonyvtar.hu/informatika/javat-tanitok-2-2-080904-1
//
// Fordítás:
// g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -o pmandelpngt
// g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -O3 -o pmandelpngt
#include <iostream>
#include "png++/png.hpp"
#include <pthread.h>
#include <time.h>
#include <sys/times.h>

#define SZALAK_SZAMA 2
// számítás adatai
double a = -2.0, b = .7, c = -1.35, d = 1.35;
int szelesseg = 600, magassag = 600, iteraciosHatar = 32000;
// png-t készítünk a png++ csomaggal
png::image < png::rgb_pixel > kep(szelesseg, magassag);
void *
mandel_resz_szamitas(void *id) {
	int mettol = *(int *) id * (magassag / SZALAK_SZAMA);
	int meddig = mettol + (magassag / SZALAK_SZAMA);
	// a számítás
	double dx = (b - a) / szelesseg;
	double dy = (d - c) / magassag;
	double reC, imC, reZ, imZ, ujreZ, ujimZ;
	// Hány iterációt csináltunk?
	int iteracio = 0;
	std::cout << *(int *) id << ". szal szamitas indul";
	// Végigzongorázzuk a szélesség x magasság rácsot:
	for (int j = mettol; j < meddig; ++j) {
		//sor = j;
		for (int k = 0; k < szelesseg; ++k) {
			// c = (reC, imC) a rács csomópontjainak
			// megfelelő komplex szám
			reC = a + k * dx;
			imC = d - j * dy;
			// z_0 = 0 = (reZ, imZ)
			reZ = 0;
			imZ = 0;
			iteracio = 0;
			// z_{n+1} = z_n * z_n + c iterációk
			// számítása, amíg |z_n| < 2 vagy még
			// nem értük el a 255 iterációt, ha
			// viszont elértük, akkor úgy vesszük,
			// hogy a kiinduláci c komplex számra
			// az iteráció konvergens, azaz a c a
			// Mandelbrot halmaz eleme
			while (reZ * reZ + imZ * imZ < 4 && iteracio < iteraciosHatar) {
				// z_{n+1} = z_n * z_n + c
				ujreZ = reZ * reZ - imZ * imZ + reC;
				ujimZ = 2 * reZ * imZ + imC;
				reZ = ujreZ;
				imZ = ujimZ;
				++iteracio;
			}
			kep.set_pixel(k, j,
			png::rgb_pixel(255 -
			(255 * iteracio) / iteraciosHatar,
			255 -
			(255 * iteracio) / iteraciosHatar,
			255 -
			(255 * iteracio) / iteraciosHatar));
			}
			std::cout << "." << std::flush;
	}
	return id;
}
int
main(int argc, char *argv[]) {
	// Mérünk időt (PP 64)
	clock_t delta = clock();
	// Mérünk időt (PP 66)
	struct tms tmsbuf1, tmsbuf2;
	times(&tmsbuf1);
	if (argc != 2) {
		std::cout << "Hasznalat: ./mandelpng fajlnev";
		return -1;
	}
	pthread_t szal[SZALAK_SZAMA];
	int szal_arg[SZALAK_SZAMA];
	int i, *r;
	// SZALAK_SZAMA db P-szálat készítünk
	for (i = 0; i < SZALAK_SZAMA; ++i) {
		szal_arg[i] = i;
		// a párhuzamosan végrehajtandó kód a
		// mandel_resz_szamitas függvényben
		if (pthread_create(szal + i, NULL,
			mandel_resz_szamitas, (void *) (szal_arg + i)))
			exit(-1);
	}
	// Megvárjuk, hogy minden szál befejezze a melót
	for (i = 0; i < SZALAK_SZAMA; ++i) {
		pthread_join(szal[i], (void **) &r);
		std::cout << *r << ". szal kesz.";
	}
	// Ha kész vannak a szálak, kinyomjuk fájlba a képet
	kep.write(argv[1]);
	std::cout << argv[1] << " mentve" << std::endl;
	times(&tmsbuf2);
	std::cout << tmsbuf2.tms_utime - tmsbuf1.tms_utime
	+ tmsbuf2.tms_stime - tmsbuf1.tms_stime << std::endl;
	delta = clock() - delta;
	std::cout << (double) delta / CLOCKS_PER_SEC << " sec" << std::endl;
}