# Informe Técnico: Análisis Comparativo de Algoritmos de Ordenamiento

**Integrantes:** 
- Francisco David Medina
- Franco Gabriel Ayala Diaz
- Gonzalo Enrique Solís Montiel

**Fecha:** 12 de mayo de 2026

**Materia:** Algoritmo y Estructura de Datos

---

## 1. Introducción

El presente documento expone los resultados obtenidos tras evaluar experimentalmente tres de los algoritmos de ordenamiento más representativos en ciencias de la computación: **QuickSort**, **HeapSort** y **RadixSort**. El objetivo es contrastar su eficiencia computacional en términos de tiempo de ejecución, considerando variables como el tamaño del conjunto de datos ($N$), el estado inicial de los elementos y la estructura de datos subyacente.


## 2. Metodología Experimental

Para garantizar la integridad del análisis, se realizaron pruebas bajo un entorno controlado con las siguientes variables:

* **Rango de Datos ($N$):** Desde $100$ hasta $2,000,000$ de elementos.
* **Naturaleza de los Datos:**
* *Aleatorios:* Distribución uniforme para evaluar el caso promedio.
* *Ordenados:* Para observar el comportamiento en escenarios ideales o patológicos.
* *Invertidos:* Para evaluar la resistencia del algoritmo ante el peor escenario teórico.


* **Estructuras de Almacenamiento:** Implementaciones sobre `Array` (estático), `ArrayList` (dinámico) y `LinkedList` (nodos enlazados).

---

## 3. Análisis Individual de Algoritmos

### 3.1 QuickSort (Divide y Vencerás)

Es un algoritmo basado en la partición recursiva mediante un elemento pivote.

* **Complejidad Teórica:** Promedio $\Theta(n \log n)$, Peor Caso $O(n^2)$.
* **Observación de Laboratorio:** Presenta los tiempos de ejecución más bajos en datos ya ordenados o invertidos, lo que sugiere una implementación optimizada (posiblemente con pivote aleatorio o mediana de tres), evitando el peor caso cuadrático.

### 3.2 HeapSort (Ordenación por Montículos)

Basado en la estructura de datos *Heap*, garantiza la extracción del máximo de forma sucesiva.

* **Complejidad Teórica:** $O(n \log n)$ en todos los casos.
* **Observación de Laboratorio:** Es el algoritmo más predecible. Aunque su velocidad es ligeramente inferior a QuickSort debido a la sobrecarga de reestructurar el montículo (*heapify*), su estabilidad temporal es su mayor fortaleza.

### 3.3 RadixSort (Distribución no Comparativa)

A diferencia de los anteriores, no utiliza comparaciones, sino que distribuye los elementos en "cubetas" basándose en sus dígitos.

* **Complejidad Teórica:** $O(n \cdot k)$, donde $k$ es la cantidad de dígitos.
* **Observación de Laboratorio:** Supera ampliamente a los algoritmos de comparación cuando $N \ge 1,000,000$, confirmando su eficiencia lineal en conjuntos masivos de datos numéricos.

---

## 4. Comparativa de Rendimiento (Resultados Consolidados)

A continuación, se presentan las tablas comparativas en milisegundos (ms) para las estructuras de tipo Array:

### Escenario A: Datos Aleatorios (Caso Promedio)

| Tamaño ($N$) | HeapSort (ms) | RadixSort (ms) | QuickSort (ms) |
| --- | --- | --- | --- |
| 100,000 | 0.0342 | **0.0173** | 0.0299 |
| 1,000,000 | 0.6326 | **0.1664** | 0.3387 |
| 2,000,000 | 1.4455 | **0.2661** | 0.5923 |

### Escenario B: Datos Ordenados/Invertidos

| Configuración ($N=2M$) | HeapSort (ms) | RadixSort (ms) | QuickSort (ms) |
| --- | --- | --- | --- |
| Ordenados | 0.5385 | 0.3945 | **0.2417** |
| Invertidos | 0.4855 | 0.3365 | **0.2379** |

---

## 5. Discusión Técnica y Hallazgos

1. **Influencia de la Estructura de Datos:** Se observó que las `LinkedList` penalizan el rendimiento en algoritmos como QuickSort y HeapSort debido a la falta de **acceso aleatorio** ($O(1)$) a los elementos, lo que incrementa el costo de los intercambios (*swaps*).
2. **Escalabilidad:** RadixSort demostró ser el algoritmo con mejor escalabilidad para grandes volúmenes de datos aleatorios. Sin embargo, su uso está restringido a claves que puedan ser procesadas por dígitos o caracteres.
3. **Eficiencia de Cache:** QuickSort se mantiene extremadamente competitivo gracias a su **localidad de referencia**, aprovechando mejor la jerarquía de memoria (caché de la CPU) que HeapSort, cuyos saltos en memoria al acceder a hijos/padres en el montículo son menos eficientes.

---

## 6. Conclusión

El análisis experimental ratifica que la elección del algoritmo debe estar sujeta al contexto del problema:

* Se recomienda **RadixSort** para el procesamiento masivo de datos numéricos donde el tiempo de ejecución sea crítico.
* Se recomienda **QuickSort** para propósitos generales, dada su eficiencia superior en la práctica y su excelente manejo de datos parcialmente ordenados.
* Se recomienda **HeapSort** en sistemas de tiempo real o críticos donde se requiera asegurar un tiempo de respuesta $O(n \log n)$ sin riesgo de degradación a casos cuadráticos.

---
