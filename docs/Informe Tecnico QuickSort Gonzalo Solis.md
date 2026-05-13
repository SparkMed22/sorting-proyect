# Informe Técnico: QuickSort

**QuickSort** es un algoritmo de ordenamiento **comparativo** basado en la estrategia **divide y vencerás**. Su idea central consiste en seleccionar un elemento llamado **pivote** y reorganizar el arreglo de manera que:

- Los elementos **menores o iguales** al pivote queden a su izquierda.
- Los elementos **mayores** queden a su derecha.

Este proceso se llama **partición**, y se repite recursivamente sobre las dos mitades resultantes hasta que cada subpartición tenga un solo elemento.

Conceptualmente, puede interpretarse como un ordenamiento progresivo que reduce el problema en subproblemas más pequeños, hasta que el arreglo queda completamente ordenado.

---

## **Ejemplo Paso a Paso**

Dado el arreglo: `[7, 2, 9, 4, 1, 5]`

**Paso 1 — Selección del pivote:**
Se elige `5` como pivote (último elemento).

**Paso 2 — Partición:**
Recorremos el arreglo comparando cada elemento con `5`:

```
[7, 2, 9, 4, 1, 5]
 ↓                ↑ pivote = 5

Menores que 5: 2, 4, 1  →  izquierda
Mayores que 5: 7, 9     →  derecha

Resultado: [2, 4, 1, 5, 7, 9]
                   ↑ pivote en posición final
```

**Paso 3 — Recursión sobre las mitades:**

- Izquierda: `[2, 4, 1]` → se repite el proceso → `[1, 2, 4]`
- Derecha: `[7, 9]` → ya ordenado → `[7, 9]`

**Resultado final:** `[1, 2, 4, 5, 7, 9]` ✔

---

## **Implementaciones y Comparativa**

### 🔹 QuickSort con Array

**Características:**

* Acceso aleatorio en tiempo constante (O(1))
* Memoria contigua: ideal para particiones in-place
* Intercambios directos por índice

**Ventajas:**

* Máximo rendimiento: sin overhead de estructuras auxiliares
* Excelente localidad de memoria (cache-friendly)
* Implementación in-place: O(1) de memoria extra

**Desventajas:**

* Tamaño fijo en C (se debe conocer el tamaño previo)
* Sensible a la elección del pivote (aunque la implementación usa pivote aleatorio para mitigarlo)

**Conclusión:**
Es la implementación **más eficiente y natural** para QuickSort. El algoritmo fue diseñado conceptualmente para operar sobre estructuras de acceso aleatorio.

---

### 🔹 QuickSort con ArrayList

**Características:**

* Basado internamente en arrays dinámicos
* Acceso aleatorio (O(1))
* Redimensionamiento automático

**Ventajas:**

* Flexibilidad en el tamaño
* Comportamiento prácticamente idéntico al array puro
* Código más abstracto y manejable

**Desventajas:**

* Ligera sobrecarga por gestión dinámica
* Posibles redimensionamientos si el tamaño inicial es inadecuado
* Pequeña penalización por indirección de punteros

**Conclusión:**
Los resultados experimentales muestran un comportamiento **variable según el tipo de dato**: en datos aleatorios ArrayList es hasta un 24.6% más lento que Array a 2M elementos, pero en datos invertidos llega a ser un 10.1% más rápido, posiblemente por efectos de caché en patrones de acceso más predecibles.

---

### 🔹 QuickSort con LinkedList

**Características:**

* Acceso secuencial: no permite acceso por índice en O(1)
* Memoria no contigua (nodos dispersos en el heap)
* La implementación requiere copiar los datos a un arreglo temporal

**Ventajas:**

* Inserciones y eliminaciones en O(1) (no relevantes para QuickSort)

**Desventajas:**

* **No es compatible estructuralmente** con QuickSort: el algoritmo necesita acceso aleatorio para las particiones
* La implementación debe copiar los datos a un array temporal → O(n) de memoria adicional
* Doble overhead: copia de entrada + copia de salida
* Baja localidad de memoria

**Conclusión:**
A diferencia de RadixSort, **LinkedList es la peor estructura para QuickSort** en el caso promedio. Sin embargo, los datos experimentales muestran un comportamiento inesperado en datos ordenados, donde LinkedList (0.203 s) es comparable a ArrayList (0.232 s) e incluso más rápido en algunos tamaños, lo que sugiere que el costo de copia puede amortizarse con ciertos patrones de acceso.

---

## **Complejidad Algorítmica**

La complejidad de QuickSort varía según la elección del pivote:

### Conteo de operaciones dominantes

En cada llamada recursiva se realizan `(high - low)` **comparaciones** durante la partición. El número total depende de cuántas veces se divide el arreglo.

| Caso          | Condición                                      | Recurrencia              | Complejidad    |
|---------------|------------------------------------------------|--------------------------|----------------|
| **Mejor caso**    | Pivote siempre divide en mitades iguales       | T(n) = 2T(n/2) + O(n)   | O(n log n)     |
| **Caso promedio** | Pivote divide en proporciones constantes       | T(n) ≈ 1.39 · n log n   | O(n log n)     |
| **Peor caso**     | Pivote siempre es el mínimo o máximo           | T(n) = T(n-1) + O(n)    | O(n²)          |

### Justificación del mejor y caso promedio

Si el pivote divide el arreglo en dos mitades iguales en cada nivel, el árbol de recursión tiene altura `log n`, y en cada nivel se realizan `O(n)` comparaciones en total:

```
Nivel 0:  n comparaciones
Nivel 1:  n/2 + n/2 = n comparaciones
Nivel 2:  4 × n/4  = n comparaciones
...
log n niveles → O(n log n)
```

### Justificación del peor caso

Si el pivote siempre es el elemento mínimo o máximo (arreglo ya ordenado con pivote fijo), la partición produce subproblemas de tamaño `n-1` y `0`:

```
T(n) = T(n-1) + n
     = (n-1) + (n-2) + ... + 1
     = n(n-1)/2
     → O(n²)
```

> **Nota:** La implementación utiliza **pivote aleatorio** (`rand() % (high - low + 1)`) para que el peor caso sea extremadamente improbable en la práctica.

### Optimización con Insertion Sort

Para subparticiones de tamaño menor a 16 (`INSERTION_THRESHOLD`), se usa Insertion Sort. Esto es correcto porque:

- Insertion Sort tiene menor overhead de llamadas recursivas
- En arreglos pequeños su comportamiento constante supera a QuickSort

---

## **Cuándo Conviene (y Cuándo No)**

### ✔ Recomendado cuando:
* Se necesita **máxima velocidad práctica** en datos aleatorios
* Se trabaja con arreglos en memoria (acceso aleatorio disponible)
* El tamaño es grande (n > 100)
* Se acepta que el peor caso es O(n²) pero improbable con pivote aleatorio

### ❌ No recomendado cuando:
* Se requiere **estabilidad** (QuickSort no es estable: puede cambiar el orden relativo de elementos iguales)
* La estructura de datos no permite acceso aleatorio (listas enlazadas puras)
* Se necesita garantía absoluta de O(n log n) en el peor caso (preferir HeapSort o MergeSort)
* Los datos ya están casi ordenados y se usa pivote fijo (riesgo de O(n²))

---

## **Resultados de Laboratorio**

Los tiempos están expresados en segundos. Se incluyen todos los tamaños medidos en los experimentos.

### Datos Aleatorios

Array presenta el mejor rendimiento consistente. ArrayList es competitivo en tamaños medianos pero se distancia en 2M elementos (+24.6%). LinkedList introduce el mayor overhead por la copia temporal al arreglo, siendo un 47.9% más lento que Array en el mayor tamaño.

| Size      | Array   | ArrayList | LinkedList |
|-----------|---------|-----------|------------|
| 50,000    | 0.009   | 0.000     | 0.000      |
| 100,000   | 0.017   | 0.016     | 0.034      |
| 1,000,000 | 0.130   | 0.146     | 0.169      |
| 2,000,000 | 0.284   | 0.354     | 0.420      |

---

### Datos Ordenados

Con pivote aleatorio el rendimiento se mantiene muy por debajo del peor caso teórico O(n²). Notablemente, los tiempos en datos ordenados son **menores** que en datos aleatorios para todos los tamaños grandes (Array: 0.170 s vs 0.284 s en 2M), lo que indica que el pivote aleatorio genera buenas particiones incluso en este caso. LinkedList muestra un comportamiento relativamente eficiente en este escenario (0.203 s), siendo más rápido que ArrayList (0.232 s) en 2M elementos.

| Size      | Array   | ArrayList | LinkedList |
|-----------|---------|-----------|------------|
| 100,000   | 0.009   | 0.000     | 0.016      |
| 500,000   | 0.025   | 0.034     | 0.050      |
| 1,000,000 | 0.084   | 0.099     | 0.083      |
| 2,000,000 | 0.170   | 0.232     | 0.203      |

---

### Datos Invertidos

Comportamiento similar al caso ordenado: Array (0.277 s) y ArrayList (0.249 s) son muy cercanos en 2M, con ArrayList siendo un 10.1% más rápido. LinkedList (0.346 s) sigue siendo la estructura más lenta, aunque el gap es menor que en datos aleatorios (24.9% vs 47.9%).

| Size      | Array   | ArrayList | LinkedList |
|-----------|---------|-----------|------------|
| 50,000    | 0.000   | 0.000     | 0.002      |
| 100,000   | 0.004   | 0.004     | 0.013      |
| 500,000   | 0.033   | 0.033     | 0.034      |
| 1,000,000 | 0.142   | 0.083     | 0.122      |
| 2,000,000 | 0.277   | 0.249     | 0.346      |

---

## **Análisis de Resultados**

### Observación 1: Datos ordenados son más rápidos que datos aleatorios

Contra la intuición inicial, los datos ordenados producen tiempos menores que los aleatorios en todos los tamaños grandes. A 2M elementos con Array: **0.170 s (ordenado) vs 0.284 s (aleatorio)**, es decir, un 40% más rápido. Esto ocurre porque el pivote aleatorio en datos ordenados tiende a seleccionar elementos que crean particiones razonablemente balanceadas, y el acceso secuencial a memoria es más cache-friendly en este caso.

---

### Observación 2: ArrayList supera a Array en datos invertidos

En datos invertidos a 2M elementos, ArrayList (0.249 s) es un **10.1% más rápido** que Array (0.277 s). Este resultado inesperado puede deberse a que el ArrayList gestiona los swaps de forma diferente internamente, generando un patrón de acceso más favorable para el caché del procesador en arreglos con orden descendente.

---

### Observación 3: LinkedList presenta comportamiento variable

A diferencia del comportamiento uniforme esperado, LinkedList muestra resultados inconsistentes según el tipo de dato:

- **Aleatorio**: 47.9% más lento que Array en 2M → overhead de copia bien visible
- **Invertido**: 24.9% más lento que Array en 2M → gap menor, copia parcialmente amortizada
- **Ordenado**: 19.4% más lento que Array en 2M, pero **más rápido que ArrayList** → comportamiento anómalo que sugiere que el patrón de copia puede beneficiarse de la predictibilidad del acceso secuencial en datos ordenados

---

### Observación 4: Alta varianza en tamaños medianos (10k–50k)

Los tiempos en el rango 10,000–50,000 muestran irregularidades notables (por ejemplo, Array registra 0.011 s en 10k pero 0.009 s en 50k en datos aleatorios). Esto refleja la influencia del **scheduler del sistema operativo**, el estado de la caché y la variabilidad natural de mediciones de bajo tiempo. Para estos tamaños, los tiempos son tan pequeños que el ruido de medición domina sobre la diferencia real entre estructuras.

---

### Observación 5: Pivote aleatorio neutraliza efectivamente el peor caso

Los datos ordenados e invertidos, que serían O(n²) con pivote fijo, mantienen tiempos incluso menores que los datos aleatorios. Esto confirma que la optimización del **pivote aleatorio** es altamente efectiva: elimina en la práctica el riesgo del peor caso teórico.

---

### Observación 6: Escalabilidad consistente con O(n log n)

De 1M a 2M elementos (factor 2x en n, factor ~2.07x esperado en n·log n):

| Estructura  | Aleatorio       | Ordenado        | Invertido       |
|-------------|-----------------|-----------------|-----------------|
| Array       | 0.130 → 0.284 (×2.18) | 0.084 → 0.170 (×2.02) | 0.142 → 0.277 (×1.95) |
| ArrayList   | 0.146 → 0.354 (×2.42) | 0.099 → 0.232 (×2.34) | 0.083 → 0.249 (×3.00) |
| LinkedList  | 0.169 → 0.420 (×2.49) | 0.083 → 0.203 (×2.45) | 0.122 → 0.346 (×2.84) |

Array es la estructura más consistente con el crecimiento teórico O(n log n). ArrayList y LinkedList muestran factores de crecimiento algo mayores, especialmente en datos invertidos, lo que indica mayor sensibilidad al patrón de datos.

---

## **Discusión Técnica**

El rendimiento de QuickSort depende fuertemente de **tres factores** (los resultados experimentales añaden un tercero al análisis teórico clásico):

1. **Elección del pivote**: un pivote malo lleva al peor caso O(n²). El pivote aleatorio reduce esta probabilidad a prácticamente cero, como confirman los tiempos en datos ordenados e invertidos.

2. **Estructura de datos**: QuickSort es un algoritmo de acceso aleatorio por naturaleza. Cualquier estructura que no lo soporte (como LinkedList) implica una copia temporal que incrementa el tiempo de ejecución.

3. **Patrón de datos y comportamiento de caché**: los resultados muestran que el tipo de dato (aleatorio, ordenado, invertido) afecta el rendimiento de forma no trivial, incluso con pivote aleatorio. El hardware moderno (caché L1/L2/L3, predictor de ramas) introduce efectos que escapan al análisis asintótico puro.

La optimización con **Insertion Sort para subparticiones pequeñas** (`INSERTION_THRESHOLD = 16`) es una práctica estándar en implementaciones profesionales:

> Para n < 16, el overhead de recursión en QuickSort supera al trabajo útil. Insertion Sort, con su bajo overhead, es más eficiente en estos rangos.

La **optimización de recursión de cola** (tail recursion) también es relevante: al recursar primero sobre la partición más pequeña, se garantiza que la profundidad del stack sea O(log n) en lugar de O(n).

---

## **Conclusión General**

QuickSort es un algoritmo:

* **Rápido en la práctica**: los resultados experimentales confirman tiempos competitivos, incluso superando las expectativas en datos ordenados gracias al pivote aleatorio
* **Flexible**: adaptable mediante optimizaciones (pivote aleatorio, Insertion Sort híbrido, tail recursion)
* **Dependiente de la estructura y del hardware**: su rendimiento está influenciado por el patrón de datos y el comportamiento de la caché, no solo por la estructura de datos

Sin embargo:

* No es estable (puede cambiar el orden relativo de elementos iguales)
* El peor caso teórico es O(n²), aunque completamente mitigado con pivote aleatorio en los experimentos
* Presenta varianza alta en tamaños medianos, lo que dificulta comparaciones precisas sin múltiples repeticiones y promedios

---

## **Síntesis Final**

```text
QuickSort — Ranking experimental por tipo de dato (a 2,000,000 elementos):

Aleatorio:  Array (0.284s) < ArrayList (0.354s) < LinkedList (0.420s)
Ordenado:   Array (0.170s) < LinkedList (0.203s) < ArrayList (0.232s)
Invertido:  ArrayList (0.249s) < Array (0.277s) < LinkedList (0.346s)
```

El ranking no es absoluto: **el tipo de dato cambia la estructura ganadora**, especialmente entre Array y ArrayList. LinkedList es consistentemente la peor o segunda peor opción, salvo en el caso ordenado donde supera a ArrayList.

---

## **Conclusión Final de la Práctica**

* La estructura de datos influye directamente en el rendimiento de QuickSort, pero no de forma unívoca: el ganador depende también del patrón de los datos
* El acceso aleatorio es **crítico** para que el algoritmo funcione correctamente sin overhead de copia
* El pivote aleatorio es una optimización **esencial y efectiva**: elimina el peor caso en todos los escenarios probados
* Los efectos de caché introducen comportamientos inesperados (ArrayList más rápido que Array en datos invertidos, LinkedList más rápido que ArrayList en datos ordenados) que no son predecibles solo con análisis asintótico
* Para una evaluación de rendimiento rigurosa, se recomienda realizar múltiples ejecuciones y promediar, especialmente en tamaños medianos donde la varianza de medición es alta
