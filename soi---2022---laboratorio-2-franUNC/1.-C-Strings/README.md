# Soluciones del punto 1 C-Strings

## Archivos: getprocinfo.h, getprocinfo.c, ProcInformation.c

### Al momento de compilar hay que compilar los dos archivos .c

### gcc ProcInformation.c getprocinfo.c

## getprocinfo.h
En el archivo de cabecera se encuentran las declaraciones de dos funciones que nos permitirán obtener datos de los archivos de procesos correspondientes a cpuinfo y meminfo. La implementación de estas funciones están en el archivo getprocinfo.c

## getprocinfo.c

  #### void getCpuInfo(char* description, char* value);
  
  Esta función recibe la descripción de la información deseada para encontrar la línea correspondiente. También se le pasa un puntero a char (value) que será la dirección en la que se almacene la información obtenida.
  
  #### static void filter(char* value);
  
  Esta función es llamada localmente por la anterior, por lo tanto no está definida en el .h y es del tipo estática. A la cadena recibida le quita toda la descripción y deja únicamente el valor de la información correspondiente.
  

  #### void getMemoryInfo(char* description);
  
  Esta función recibe la descripción de la información a buscar y aprovecha la estructura regular del archivo de texto (string int string) para comparar la descripción con la línea que está leyendo, una vez que encuentra una coincidencia ya tiene el valor almacenado en una variable.
  
  #### static void mbConverter(int* value);
  
  Esta función es llamada localmente por la anterior, por lo tanto no está definida en el .h y es del tipo estátca. Al llamarla le pasan por referencia la información obtenida. Cómo resultado de esta función, la variable entera de información se escala para convertirla de Kb a Mb.
  

## ProcInformation.c

  Por último, este archivo contiene tres funciones que realizan las llamadas a las funciones get(), para esto, en cada caso se crean arreglos que contienen las descripciones de la información a buscar y luego se realizan las llamadas correspondientes usando como parámentros estas descripciones. Como salída obtenemos una serie de impresiones de pantalla que nos muestran la información solicitada en la consigna punto por punto.

  Ejemplo de salida:

  Información de memoria RAM solicitada en el punto i:
  
  MemTotal: 5843 MB
  
  MemFree: 2476 MB
  
  MemAvailable: 3851 MB
  
  Información de memoria SWAP solicitada en el punto ii: 
  
  Swap Busy: 0 MB 
  
  Información de CPU solicitada en el punto iii: 
  
  model name : Intel(R) Core(TM) i3-2350M CPU @ 2.30GHz
  
  cpu cores : 2
  
  siblings : 4

