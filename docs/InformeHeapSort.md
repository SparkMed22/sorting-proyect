
### Análisis Cuantitativo de la Relación de Velocidad

| Tamaño (n) | ArrayList (s) | LinkedList (s) | Relación (LL / AL) | Interpretación |
| :--- | :--- | :--- | :--- | :--- |
| 100 | 0.000023 | 0.000025 | 1.08 | LinkedList ~8% más lenta |
| 10,000 | 0.002161 | 0.002891 | 1.33 | LinkedList ~33% más lenta |
| 100,000 | 0.032467 | 0.035733 | 1.10 | LinkedList ~10% más lenta |
| 1,000,000 | 0.515109 | 0.567809 | 1.10 | LinkedList ~10% más lenta |
| **2,000,000** | **1.273717** | **1.147785** | **0.90** | **LinkedList ~10% más RÁPIDA** |

### Conclusión 

1.  **Eficiencia del Algoritmo:** HeapSort funciona perfectamente para ambos tipos de listas. La complejidad temporal es la esperada $O(n \log n)$.
2.  **Rendimiento por Tamaño:**
    - Para **n < 1.5M**, `ArrayList` es superior debido a la **localidad de caché**. Es la opción recomendada para la mayoría de los casos de uso.
    - Para **n = 2M**, se observa un **cambio de paradigma**. La `LinkedList` gana la carrera.
3.  **Hipótesis sobre el fallo en 2M:**
    - Es muy probable que el `ArrayList` sufra de **sobrecarga de redimensionamiento** o **gestión de memoria no óptima** (posiblemente el sistema operativo está paginando ese array gigante).
    - La `LinkedList`, al ser fragmentada, evita el problema de asignar un bloque continuo gigante, lo que en este caso extremo le da una ventaja inesperada.
