


⚠️ Detalle importante

Para LinkedList, HeapSort no es natural, porque:

No hay acceso por índice → heapify sería un infierno
Por eso hacemos el truco: lista → array → heap → lista




# Aleatorio s

Tenés tres curvas compitiendo como si fueran corredores con distintas zapatillas. La clave es **cómo crecen** más que quién gana por milésimas en un punto.

---

## 🧠 Lectura general del gráfico

1. **Eje X (size)**
   Tamaño del input.

2. **Eje Y (tiempo)**
   Cuánto tarda HeapSort en cada estructura.

3. **Las tres líneas**

   * `Array`
   * `ArrayList`
   * `LinkedList`

---

## ⚙️ Lo importante de verdad

### 1. La forma de las curvas

Si las tres suben de forma parecida (curva suave, tipo misma pendiente), entonces:

> 👉 Todas tienen **misma complejidad** (≈ O(n log n))

HeapSort debería comportarse así. Si una se dispara raro, algo anda mal en la implementación.

---

### 2. Quién está más abajo 🪶

La línea más baja = más rápida.

De tus datos:

* `ArrayList` suele estar ligeramente abajo → 🥇
* `Array` muy cerca → 🥈
* `LinkedList` a veces se queda atrás → 🥉

Pero no es una paliza, es más bien una carrera ajustada.

---

### 3. Diferencias pequeñas ≠ diferencia real

Ejemplo:

```
0.002267 vs 0.002454
```

Eso es **ruido experimental**, no una victoria clara.

En benchmarking:

* diferencias < ~10% → meh 😐
* diferencias grandes → ahí sí importa

---

### 4. El sospechoso habitual: LinkedList

Si en tamaños grandes empieza a rendir peor:

> 💡 Tiene sentido: acceso no contiguo en memoria

HeapSort necesita acceso rápido por índice →
LinkedList no es fan de eso.

---

## 📈 Lectura más fina (modo ingeniero 🧩)

* HeapSort hace muchas operaciones de acceso por índice
* En:

  * `Array` → acceso O(1) real
  * `ArrayList` → también O(1), pero con overhead mínimo
  * `LinkedList` → acceso O(n) 😬

👉 Resultado esperado:

* LinkedList debería degradarse más al crecer n

Y en tus datos… se empieza a notar en los tamaños grandes.

---

## 🧾 Conclusión clara

* Las 3 estructuras escalan parecido → algoritmo correcto ✅
* `ArrayList` y `Array` son más eficientes en práctica
* `LinkedList` penaliza por su estructura interna

---

## 🧪 Bonus (si querés subir nivel)

Podés decir en tu informe algo como:

> “Aunque la complejidad teórica de HeapSort es O(n log n) para todas las estructuras, en la práctica el rendimiento varía debido al costo de acceso a memoria. Las estructuras basadas en arrays muestran mejor desempeño que las listas enlazadas.”

---

Si querés, te ayudo a convertir esto en un párrafo formal para el informe y te queda listo para entregar sin que el profe te haga preguntas incómodas 😏




# Invertido 

Vamos por partes: código listo + lectura sin humo.

---

# 📊 Código para `heap-invertido-results.csv`

Es básicamente el mismo motor, cambiando el archivo y el nombre de salida.

```python id="heapinv1"
import csv
import matplotlib.pyplot as plt

sizes = []
array_time = []
arraylist_time = []
linkedlist_time = []

with open('heap-invertido-results.csv', newline='', encoding='utf-8-sig') as csvfile:
    reader = csv.DictReader(csvfile)
    
    # limpiar headers por si vienen con espacios raros
    reader.fieldnames = [field.strip() for field in reader.fieldnames]
    
    for row in reader:
        sizes.append(int(row['size']))
        array_time.append(float(row['array_time']))
        arraylist_time.append(float(row['arraylist_time']))
        linkedlist_time.append(float(row['linkedlist_time']))

# gráfico
plt.figure()
plt.plot(sizes, array_time, label='Array')
plt.plot(sizes, arraylist_time, label='ArrayList')
plt.plot(sizes, linkedlist_time, label='LinkedList')

plt.xlabel('Tamaño (n)')
plt.ylabel('Tiempo (segundos)')
plt.title('HeapSort - Caso Invertido')
plt.legend()
plt.grid()

# guardar PNG
plt.savefig('grafico_heap_invertido.png', dpi=300)

plt.show()
```

---

# 🧠 Interpretación (caso invertido)

Este caso suele representar un input “peor organizado posible” para muchos algoritmos…
pero HeapSort no se asusta tanto 😐

---

## 1. 📈 Forma de las curvas

Las tres curvas:

* crecen de forma suave
* no explotan
* mantienen tendencia similar

👉 Traducción directa:

> HeapSort sigue siendo **O(n log n)** incluso con datos invertidos.

✔️ Consistente con la teoría.

---

## 2. 🥇 ¿Quién gana?

Mirando tamaños grandes:

| Tamaño | Mejor     |
| ------ | --------- |
| 500k   | ArrayList |
| 1M     | Array     |
| 2M     | ArrayList |

👉 Resultado:

* **ArrayList y Array están muy parejos**
* **LinkedList queda un poco atrás** (otra vez)

Nada sorprendente.

---

## 3. 🧪 Comparación con el caso aleatorio

Aquí está lo interesante:

### 🔹 En teoría:

HeapSort debería rendir parecido en:

* datos aleatorios
* datos invertidos

### 🔹 En tus datos:

✔️ Se cumple bastante bien

Las diferencias:

* son pequeñas
* no cambian el orden general

👉 Conclusión clave:

> HeapSort es **insensible al orden inicial** (a diferencia de QuickSort, por ejemplo)

---

## 4. 🧱 El patrón que se repite

LinkedList vuelve a sufrir en silencio:

* Más lento en general
* Diferencia más visible cuando n crece

💡 Motivo:
HeapSort necesita acceso por índice
→ LinkedList no está hecha para eso

---

## 5. ⚖️ Diferencias reales vs ruido

Ejemplo:

```id="noise1"
0.242568 vs 0.257268
```

Eso es ≈ 6%

👉 Traducción:

* No es una ventaja estructural fuerte
* Puede ser cache, CPU, o ruido

---

# 🧾 Conclusión clara para informe

Podés decir algo así:

> En el caso de entrada invertida, HeapSort mantiene un comportamiento consistente con su complejidad O(n log n), mostrando curvas de crecimiento similares a las del caso aleatorio. Las estructuras basadas en arreglos (Array y ArrayList) presentan un rendimiento levemente superior a LinkedList, lo cual se explica por el acceso eficiente por índice requerido por el algoritmo. Además, se observa que el orden inicial de los datos no afecta significativamente el desempeño, confirmando que HeapSort es poco sensible a la disposición inicial de la entrada.

---

## 🎯 Resumen en una línea

HeapSort es como un tractor:
le da igual si el terreno está ordenado, invertido o caótico… avanza igual 🚜

---

Si querés, el siguiente nivel sería:

* juntar ambas gráficas en una sola comparación 🔥
* o hacer un análisis automático de cuál gana por porcentaje

Ahí ya estás jugando en modo “proyecto serio”, no solo tarea.








# Ordenado 


Perfecto: este es el **tercer escenario (ordenado)**, y junto con los otros dos ya tenés un análisis bastante sólido.

---

# 📊 Código para `heap-ordenado-results.csv`

```python
import csv
import matplotlib.pyplot as plt

sizes = []
array_time = []
arraylist_time = []
linkedlist_time = []

with open('heap-ordenado-results.csv', newline='', encoding='utf-8-sig') as csvfile:
    reader = csv.DictReader(csvfile)
    reader.fieldnames = [f.strip() for f in reader.fieldnames]

    for row in reader:
        sizes.append(int(row['size']))
        array_time.append(float(row['array_time']))
        arraylist_time.append(float(row['arraylist_time']))
        linkedlist_time.append(float(row['linkedlist_time']))

plt.figure()

plt.plot(sizes, array_time, label='Array')
plt.plot(sizes, arraylist_time, label='ArrayList')
plt.plot(sizes, linkedlist_time, label='LinkedList')

plt.xlabel('Tamaño (n)')
plt.ylabel('Tiempo (segundos)')
plt.title('HeapSort - Caso Ordenado')
plt.legend()
plt.grid()

plt.savefig('grafico_heap_ordenado.png', dpi=300)

plt.show()
```

---

# 🧠 Interpretación del caso ordenado

Este es el escenario “más aburrido” para muchos algoritmos… pero útil para medir estabilidad.

---

## 1. 📈 Forma general

* Curvas suaves
* Crecimiento estable
* Sin saltos raros

👉 Traducción:

> HeapSort no se beneficia ni se perjudica significativamente por estar ordenado.

---

## 2. ⚖️ Comparación entre estructuras

En tamaños grandes:

| Estructura | Rendimiento          |
| ---------- | -------------------- |
| ArrayList  | 🥇 ligeramente mejor |
| Array      | 🥈 muy cerca         |
| LinkedList | 🥉 más lento         |

Diferencias:

* pequeñas pero consistentes
* LinkedList pierde más a medida que crece n

---

## 3. 🧠 Comparación con otros casos (clave del informe)

Ahora viene lo importante de verdad:

### 🔹 Ordenado vs Invertido vs Aleatorio

HeapSort:

| Caso      | Impacto    |
| --------- | ---------- |
| Aleatorio | baseline   |
| Invertido | casi igual |
| Ordenado  | casi igual |

👉 Conclusión fuerte:

> HeapSort es prácticamente **insensible al orden de entrada**

---

## 4. 🔬 Qué está pasando realmente

HeapSort hace siempre:

* construir heap
* extraer máximo repetidamente

Eso significa:

* no “aprovecha” orden previo
* rehace estructura desde cero

---

## 5. 📉 Por qué LinkedList pierde otra vez

Se repite el patrón:

* acceso por índice lento
* heap necesita acceso constante a posiciones

👉 Resultado:

> penalización acumulada con tamaños grandes

---

# 🧾 Conclusión lista para informe

Podés usar algo así:

> En el caso de entrada ordenada, HeapSort mantiene un comportamiento estable y consistente con una complejidad O(n log n), sin mejoras significativas respecto a los casos aleatorio o invertido. Esto confirma que el algoritmo no aprovecha el orden inicial de los datos, ya que siempre reconstruye la estructura de heap desde cero. En cuanto a las estructuras de datos, Array y ArrayList presentan rendimientos similares, mientras que LinkedList muestra un desempeño inferior debido al costo de acceso por índice.

---

# 🧩 Conclusión global (los 3 casos juntos)

Si juntás todo:

* Aleatorio → baseline
* Invertido → casi igual
* Ordenado → casi igual

👉 Mensaje final:

> HeapSort es estable en rendimiento frente al orden de entrada, pero depende fuertemente del tipo de estructura utilizada.

---

Si querés, el siguiente paso interesante sería:

* hacer una **gráfica comparativa de los 3 casos en una sola figura**
* o calcular **promedios y porcentajes de diferencia automáticamente**

Ahí ya pasás de “gráficas” a “análisis de laboratorio serio”.
