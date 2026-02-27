# Maquina de Ejecucion

## Descripcion
Maquina virtual que busca ejecutar instrucciones de un lenguaje de bajo nivel assembly-like. Contiene distintos modulos encargados 
de realizar distintas tareas, como la decodificacion y ejecucion de instrucciones, asi como la gestion de memoria.

## CPU
Se simulo una CPU con un conjunto variable de registros de 4 bytes cada uno, siendo el tamaño base 8; los cuales pueden ser 
utilizados para almacenar datos temporales durante la ejecucion de un programa. El ultimo registro se utiliza para el contador 
de las instrucciones, permitiendo mantener un orden de ejecución.


### RAM
Se simulo una memoria RAM de tamaño variable, siendo el tamaño por defecto 256 registros de 4 bytes cada uno. Se agregaron 
operaciones para poder manipular los datos dentro de ella como lo son la lectura y escritura de datos. Se cuenta con un control
interno para evitar que se escriba o lea fuera de los limites de la memoria, lo cual podria causar errores o corrupcion de datos.

### Instrucciones
Se creo un objeto para poder contener de forma ordenada las caracteristicas de cada instruccion escrita del lenguaje como el nombre,
operando y registros a manipular.
Se cuenta con un conjunto de 17 instrcciones: 
- HALT: Detiene la ejecucion del programa
- IN: Lee un valor de la entrada estandar y lo guarda en un registro
- OUT: Escribe el valor de un registro a la salida estandar
- ADD: Suma el valor de dos registros y guarda el resultado en un tercer registro
- SUB: Resta el valor de dos registros y guarda el resultado en un tercer registro
- MUL: Multiplica el valor de dos registros y guarda el resultado en un tercer registro
- DIV: Divide el valor de dos registros y guarda el resultado en un tercer registro
- LD: Carga un valor de la memoria a un registro
- LDA: Carga la direccion de un valor en la memoria a un registro
- LDC: Carga en un registro un valor constante
- ST: Almacena el valor de un registro en la memoria
- JLT: Salta a una instruccion si el valor de un registro es menor que el valor de otro registro
- JLE: Salta a una instruccion si el valor de un registro es menor o igual que el valor de otro registro
- JGE: Salta a una instruccion si el valor de un registro es mayor o igual que el valor de otro registro
- JGT: Salta a una instruccion si el valor de un registro es mayor que el valor de otro registro
- JEQ: Salta a una instruccion si el valor de un registro es igual al valor de otro registro
- JNE: Salta a una instruccion si el valor de un registro es diferente al valor de otro registro

## Inicializacion 
Se invoca el programa y se pasa el archivo a analizar como parametro (se pasa la ruta donde se encuentra). En caso de no pasar un 
parametro se pueden escribir las soluciones deseadas en el archivo 'instrucciones.txt' dentro de la carpeta del programa.

## Limitaciones
La memoria RAM y los registros solo manejan enteros, por lo que usar un tipo de dato diferente a este podria causar errores o resultados 
inesperados. Se recomienda usar solo enteros para evitar problemas de este tipo.