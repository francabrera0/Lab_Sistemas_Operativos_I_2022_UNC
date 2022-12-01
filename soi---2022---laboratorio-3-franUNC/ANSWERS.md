Laboratorio N3
# GNU Toolchain y Linux Software
### SOI - FCEFyN - UNC - 2022

## Ubicación del binario
El binario del programa se encontrará en la carpeta /bin una vez que se ejecute el comando make. 
Para realizar pruebas del binario, hay un script llamado Test.sh que realiza varias ejecuciones del Main con diferentes parámetros.

## Cuestionario

## 1.- Process File Descriptors

  Según vemos en el manual de Standar I/O Streams, cada proceso al momento de iniciarse tiene minimamente tres archivos, uno referenciado a entradas, otro a salidas y otro a impresiones de errores. Cada uno de estos archivos cuenta con un identificador de tipo entero.

![image](https://user-images.githubusercontent.com/101826494/189350321-b4a25265-9bed-4ca9-bca7-21fed4076034.png)

  Lo que encontramos en `/proc/[pid]/fd` es una entrada por cada archivo que el proceso ha abierto, referenciado a su identificador, y este es un link simbólico al archivo. Como vimos anteriormente: 
  0: Standar input
  1: Standar output
  2: Standar error
  
![image](https://user-images.githubusercontent.com/101826494/189348955-d52760d8-3d5b-41d3-af7a-6a93b029e7b1.png)

>Referencia: man stdio, man proc

### Ejemplo
Ejecutando el comando 
~~~{.sh}
  ls -l /proc/16264/fd
~~~

Obtenemos la siguiente salida parcial
![image](https://user-images.githubusercontent.com/101826494/189353334-f618db4b-6624-44d7-8f44-9f65d20adb32.png)

## 2.- echo "Hello World!"
Si, es perfectamente válido. Podemos observar que si lanzamos el proceso tail, y luego desde otra consola ejecutamos el comando 
~~~{.sh}
echo "Hello World! >> /proc/[pidof tail]/fd/1
~~~
Observamos como se muestra en la primera consola el mensaje.
![image](https://user-images.githubusercontent.com/101826494/189361211-5db54a05-bf6e-4488-9440-6cf13a4f72d1.png)

## Hard and Soft limits
 Hay dos tipos de limites:
 -> El hard limit, es el máximo valor que es permitido para el soft limit. Cualquier cambio en el Hard limit requiere un nivel de root.
 -> El soft limit es el valor que el sistema operativo usa para limitar los recursos de sistema a los procesos activos. El soft limit no puede ser mayor al hard limit
  
  Podemos ver los limites de nuestro SO de la siguiente manera
  
  ![image](https://user-images.githubusercontent.com/101826494/189364319-3dd008a5-db1a-498a-8749-8aba197d46ff.png)


