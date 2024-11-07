## Explanation of Functions Used in the Linear Calculator

This project is an advanced calculator developed in C++ that solves complex mathematical expressions, such as [5*{7+(8/9)^4}]^2. The calculator uses a series of functions to validate syntax, break down the operation into numbers and operators, and solve operations in the correct order, considering powers, multiplications, divisions, additions, and subtractions. It also handles grouping symbols such as parentheses, brackets, and braces, breaking down and resolving internal operations before continuing with the rest of the expression.

### 1. `bool isErrorSintaxis(string)`
- **Description:** Takes the operation as a string and returns `true` if a syntax error is detected. If there is an error, it displays it on the screen.

### 2. `char getCharRightNumber(string, int)`
- **Description:** Receives the operation and the reference position of a character '.', and returns the character after the number to the right. This function is used in `isErrorSintaxis()` to validate the placement of decimal points.

### 3. `char getCharLeftNumber(string, int)`
- **Description:** Similar to `getCharRightNumber`, but returns the character before the number to the left of the reference position.

### 4. `float resolverOperaciones(string)`
- **Description:** This is the main function responsible for receiving the complete operation and returning the final result. It coordinates the execution of other functions to solve the operation.

### 5. `string limpiarEspacios(string)`
- **Description:** Receives the operation as a string and returns the same operation without spaces, if any are present.

### 6. `void descomponerOperacion(vector<char>*, vector<float>*, string)`
- **Description:** Takes the operation and references to two vectors: one for operators and another for numbers. It breaks down the operation and assigns the numbers and operators to the respective vectors.

### 7. `string desarrollarSignosAgrupacion(string)`
- **Description:** Receives the operation and, if there are grouping symbols like "()", "[]", or "{}", it resolves them by calling `resolverOperaciones()` for the sub-operation within the symbols. It replaces the sub-operation with its result and repeats until all groupings are resolved.

### 8. `float isOperacionPotencia(string, int*, float)`
- **Description:** Used in `desarrollarSignosAgrupacion()` to solve powers with complex bases that include grouping symbols, such as `(6*9+3)^3`.

### 9. `int findCierreAgrupacion(string, char, int)`
- **Description:** Receives the operation, an opening symbol "([{" and the position of that symbol. Searches and returns the position of the corresponding closing symbol.

### 10. `int findFirstChar(string, char)`
- **Description:** Receives the operation and a character. Returns the position of the first character in the string that matches the given character.

### 11. `void realizarPotencias(vector<char>*, vector<float>*)`
- **Description:** Receives the operator vector and the number vector, resolving all powers with a simple base (example: `4^10`). Returns the modified vectors.

### 12. `void realizarMultiplicacionesDiviciones(vector<char>*, vector<float>*)`
- **Description:** Resolves all multiplications and divisions in the operator and number vectors, and returns the modified vectors.

### 13. `void realizarSumasRestas(vector<char>*, vector<float>*)`
- **Description:** Similar to the previous functions but focuses on solving additions and subtractions, returning the modified vectors.

### 14. `void eliminarOperador(vector<char>*, int)`
- **Description:** Receives the reference of the operator vector and the position of an operator that should be removed after the corresponding operation has been performed.

### 15. `void eliminarNumero(vector<float>*, int)`
- **Description:** Receives the reference of the number vector and the position of a number that should be removed after it has been used in an operation.

## Technologies Used

- **Programming Language:** C++
- **Standard Libraries:** `<iostream>`, `<vector>`, `<string>`, `<math.h>`, `<stdlib.h>`, `<ctype.h>`

**Author:** Eder Said Martinez Ramirez
