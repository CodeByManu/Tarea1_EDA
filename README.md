# Tarea 1

## Introducción
Este README da instrucciones para configurar y correr el código de la Tarea 1. Para compilar y ejecutar el código de manera correcta, se tienen que sesguir las siguientes instrucciones.

## Estructura de Directorios

Asegurarse de tener los siguientes directorios al mismo nivel:

- `datos`: Contiene todos los archivos `.txt` con la lista de RUTs.
- `src` (u otro nombre): Contiene el código fuente y un sub-directorio llamado `build` para la compilación.

## Instrucciones

1. Ubicarse en el directorio `build`.

2. Correr el siguiente comando de linea para generar los archivos necesarios para compilar con CMake:
```bash
$ cmake .. 
```

3. Compilar el código usando `make`:
```bash
$ make
```

4. Ejecutar el código con el siguiente comando:
```bash
$ ./main [nombre_archivo].txt [algoritmo]
```

Reemplazar `[nombre_archivo].txt` con el nombre del archivo de entrada, y `[algoritmo]` con el algoritmo que se quiera aplicar. Por ejemplo:
```bash
$ ./main ruts_100.txt I
```