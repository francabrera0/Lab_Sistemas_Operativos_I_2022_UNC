# Soluciones del punto 2 Arreglos

## Archivos: getversioninfo.h, getversioninfo.c, VersionInformation.c

### Al momento de compilar hay que compilar los dos archivos .c

### gcc VersionInformation.c getversioninfo.c

## getversioninfo.h
En el archivo de cabecera se encuentran las declaraciones de las funciones que nos permitirán obtener datos del archivo /proc/version. La implementación de estas funciones están en el archivo getversioninfo.c

## getversioninfo.c

  #### int getSizeFile(FILE* file);
  
  Esta funcion recibe el puntero al archivo abierto y cuenta la cantidad de caracteres, retorna su valor y rebobina el archivo para colocar el cursor nuevamente en la posición inicial.
  
  #### void toUppercase(char* str, int size);
  
  Esta función recibe la cadena obtenida del archivo y cambia las letras minúsculas por mayúsculas.

  #### static void removeChar(char* str);
  
  Esta función es llamada localmente por la función siguiente, por lo tanto no se encuentra definida en el archivo.h. Es usada para remover los caracteres "(", ")" y "," que impiden la correcta impresión del listado. Función recursiva.
  
  #### void printList(char* str, int size);
  
  Función para imprimir una por una las palabras de la cadena. No destruye la cadena original ya que trabaja con una copia.
  

## VersionInformation.c

  Por último, este archivo realiza las llamadas a las funciones nombradas anteriormente, para obtener la información del archivo, pasarla a mayúsculas e imprimirla en forma de lista. La información es almacenada en un arreglo dinámico que luego es liberado.

  Ejemplo de salida:  
LINUX  
VERSION  
5.15.0-46-GENERIC  
BUILDD@LCY02-AMD64-007  
GCC  
UBUNTU  
9.4.0-1UBUNTU1-20.04.1  
9.4.0  
GNU  
LD  
GNU  
BINUTILS  
FOR  
UBUNTU  
2.34  
#49-20.04.1-UBUNTU  
SMP  
THU  
AUG  
4  
19:15:44  
UTC  
2022  
