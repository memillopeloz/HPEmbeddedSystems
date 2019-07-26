En memcheck/lib esta definida la libreria dinamica que ha de interceptar malloc y free.
	la estoy compilando con  gcc -shared -fPIC -o caquita.so libmemcheck.c -ldl

En memcheck/src esta memcheck.c, quien se encarga de recibir el ejecutable que quiere 
uno analizar.
	correr ./memcheck -h para el help
	
	estoy utilizando memcheck/src/test para probar (compilado de test.c)

	Utilizo mc.c como un approach que le di para linkear tanto mc.c como el 
	binario especificado contra la libreria dinamica caquita.so, en un intento
	vano para tener acceso a las variables globales de la libreria dinamica

	en memcheck.c se setea la variable de ambiente LD_PRELOAD para ubicar la 	 libreria dinamica libmemcheck.c como primer opcion al resolver simbolos

OBJETIVO
	poder acceder al conteo de mallocs y frees para reportarlos, yo intente
	reportarlos en mc.c

PD:
	existe una estructura de makefiles incompleta que utilizare para compilar con
	autotools
