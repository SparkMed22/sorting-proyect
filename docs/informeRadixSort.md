1. Objetivo

El objetivo de esta practica fue comparar el rendimiento de RadixSort al trabajar con 3 estructuras de datos distintas: Array, ArrayList y LinkedList.
Se buscó analizar como influye la organización de memoria, el acceso a los elementos y el costo de insercción sobre el tiempo de ejecucion del algoritmo

Se ejecutó RadixSort sobre un conjunto de datos aleatorios con tamaños crecientes.
Para cada tamaño n, se midió el tiempo de ordenamiento en:
- Array
- ArrayList
- LinkedList

Es importante que, para que la comparación sea válida, las tres estructuras trabajen sobre la misma secuencia base de datos o, al menos, sobre datos generados con el mismo criterio y distribución.

Resultados
size, 		array_time, arraylist_time,	linkedlist_time
100, 		0.000066, 	0.000054, 		0.000031
500, 		0.000275, 	0.000266, 		0.000105
1000, 		0.000506, 	0.000486, 		0.000194
2000, 		0.000987, 	0.000958, 		0.000369
5000, 		0.001811, 	0.001328, 		0.000496
10000, 		0.002487, 	0.002564, 		0.000961
20000, 		0.005077, 	0.005207, 		0.002337
50000, 		0.013078, 	0.012768, 		0.005305
100000, 	0.025557, 	0.026514, 		0.010729
200000, 	0.052892, 	0.051181, 		0.021386
500000, 	0.132109, 	0.128786, 		0.053921
1000000,	0.252031, 	0.265034, 		0.106050
2000000,	0.515687, 	0.508282, 		0.212911


Los datos muestran un comportamiento muy claro: LinkedList fue la estructura más rápida en todos los tamaños medidos.
Además, la diferencia entre Array y ArrayList se vuelve más marcada conforme crece n.

Algunas observaciones
1. Array y ArrayList presentan tiempos similares
  - Esto es esperable ya que ambas estructuras manejan memoria contigua o casi contigua y tienen accesso 
2. LinkedList tiene mejores tiempos en radixSort
  - Esto sugiere que la implementación de RadixSort utilizada favorece operaciones de inserción
3- El crecimiento del tiempo es aproximadamente lineal
  - Esto es coherente con RadixSort, cuya complejidad práctica suele aproximarse a:
    O(n⋅k)
    donde k es la cantidad de dígitos del número mayor. 


Conclusión
Los resultados experimentales indican que, para esta implementación de Radix Sort, el LinkedList fur la estructura más eficiente en todos los tamaños analizados.
Array y ArrayList obtuvieron tiempos muy parecidos entre sí, pero consientemente mayores que LinkedList