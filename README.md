## Explicación de Funciones Empleadas en la Calculadora Lineal

### 1. `bool isErrorSintaxis(string)`
- **Descripción:** Recibe la operación como un string y devuelve `true` si se detecta un error de sintaxis. Si hay un error, lo muestra por pantalla.

### 2. `char getCharRightNumber(string, int)`
- **Descripción:** Recibe la operación y la posición de referencia de un carácter '.', y devuelve el carácter que se encuentra después del número a la derecha. Esta función se utiliza en `isErrorSintaxis()` para validar la ubicación de los puntos decimales.

### 3. `char getCharLeftNumber(string, int)`
- **Descripción:** Similar a `getCharRightNumber`, pero devuelve el carácter que se encuentra antes del número a la izquierda de la posición de referencia.

### 4. `float resolverOperaciones(string)`
- **Descripción:** Es la función principal que se encarga de recibir la operación completa y devolver el resultado final. Coordina la ejecución de otras funciones para resolver la operación.

### 5. `string limpiarEspacios(string)`
- **Descripción:** Recibe la operación como un string y devuelve la misma operación sin espacios, en caso de que los tenga.

### 6. `void descomponerOperacion(vector<char>*, vector<float>*, string)`
- **Descripción:** Recibe la operación y referencias a dos vectores: uno para los operadores y otro para los números. Descompone la operación y asigna los números y operadores a los vectores correspondientes.

### 7. `string desarrollarSignosAgrupacion(string)`
- **Descripción:** Recibe la operación y, si hay signos de agrupación como "()", "[]", o "{}", los resuelve llamando a `resolverOperaciones()` para la sub-operación dentro de los signos. Reemplaza la sub-operación con su resultado y repite hasta que todas las agrupaciones estén resueltas.

### 8. `float isOperacionPotencia(string, int*, float)`
- **Descripción:** Utilizada en `desarrollarSignosAgrupacion()` para resolver potencias con bases complejas que incluyen signos de agrupación, como en `(6*9+3)^3`.

### 9. `int findCierreAgrupacion(string, char, int)`
- **Descripción:** Recibe la operación, un signo de apertura "([{" y la posición de dicho signo. Busca y devuelve la posición del signo de cierre correspondiente.

### 10. `int findFirstChar(string, char)`
- **Descripción:** Recibe la operación y un carácter. Devuelve la posición del primer carácter en la cadena que coincida con el recibido.

### 11. `void realizarPotencias(vector<char>*, vector<float>*)`
- **Descripción:** Recibe el vector de operadores y el de números, resolviendo todas las potencias con base simple (ejemplo: `4^10`). Devuelve los vectores con las modificaciones correspondientes.

### 12. `void realizarMultiplicacionesDiviciones(vector<char>*, vector<float>*)`
- **Descripción:** Resuelve todas las multiplicaciones y divisiones en los vectores de operadores y números, y devuelve los vectores modificados.

### 13. `void realizarSumasRestas(vector<char>*, vector<float>*)`
- **Descripción:** Similar a las funciones anteriores, pero se enfoca en resolver sumas y restas, devolviendo los vectores modificados.

### 14. `void eliminarOperador(vector<char>*, int)`
- **Descripción:** Recibe la referencia del vector de operadores y la posición de un operador que debe ser eliminado después de que la operación correspondiente ha sido realizada.

### 15. `void eliminarNumero(vector<float>*, int)`
- **Descripción:** Recibe la referencia del vector de números y la posición de un número que debe ser eliminado después de haber sido utilizado en una operación.

## Tecnologías Utilizadas

- **Lenguaje de Programación:** C++
- **Bibliotecas Estándar:** `<iostream>`, `<vector>`, `<string>`, `<math.h>`, `<stdlib.h> `, ` <ctype.h>`

**Autor:** Eder Said Martinez Ramirez