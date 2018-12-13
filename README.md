# VP tree 
A veces el algoritmo de indexación falla porque los puntos escogidos no son óptimos, pero la probabilidad es muy poca por el límite que se le puso a SAMPLE_SIZE. Si llega a fallar se puede volver a ejecutar.

Escoge un punto aleatorio del vector de puntos y retorna por defecto los 6 vecinos más cercanos, estos se guardan un un archivo llamado 'knn.txt', para conocer cuáles son los puntos, así mismo la consola imprime las distancias entre el punto query y los vecinos hallados.
