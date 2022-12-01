# Soluciones del punto 3 Estructuras
# Punto i
## Typedef
  Typedef es una palabra reservada en C y cuya función es asignar un nombre alternativo junto a tipos existentes, es normalmente utilizada cuando la declaración normal es complicada o confusa.  
  Para utilizarlo basta con anteponer la palabra reservada al tipo de variable, en el siguiente ejemplo se muestra cómo usarlo con estructuras y cómo varia la forma de instanciar una nueva estructura.
  
  ### Sin typedef

  struct Persona{  
    char nombre[20];  
    int edad;  
    long int DNI;  
  };
  
  Cómo no se utilizó el typedef, cada vez que querramos crear una variable del tipo persona deberémos indicar que es una struct, por ejemplo si queremos crear una variable llamada persona1 se hace lo siguiente:  
  #### struct Persona persona1;
  
  ### Con typedef
  
  typedef struct{  
    char nombre[20];  
    int edad;  
    long int DNI;  
  } Persona;  
  
  Con este modo de declaración, al momento de crear una nueva variable del tipo Persona, no debemos indicar que es una struct, si no, siguiendo el ejemplo anterior sería:  
  #### Persona persona1;
  

## Packing y Padding
Para comenzar a hablar de packing y padding, primero tenemos que definir cuál es el tamaño de una estructura. Inicialmente este es AL MENOS la suma del tamaño de todos sus elementos. Veamos en un ejemplo: 

![image](https://user-images.githubusercontent.com/101826494/185791405-fcfd7a3a-6c61-4cac-8735-73974c20dfae.png)

Si observamos las estructuras definidas, podríamos decir en primera instancia que el tamaño de struct1 es 8 (Dos enteros de 4 bytes cada uno) y que el de struct2 es 5 (un int de 4 bytes y un char de 1 byte), pero no es así. Observamos que en realidad el tamaño de la primera si es el calculado pero el de la segunda es mayor. 

Esto se debe a una alineación de memoria que se realiza para acceder a memoria más fácilmente, ya que las computadoras acceden a memoria con direcciones de 1 word.  
Dicha alineación se hace ajustandose al tamaño del mayor atributo de la estructura y se rellena los espacios vacíos con "basura" que añade el sistema. En nuestro ejemplo anterior se vería de este modo:

![image](https://user-images.githubusercontent.com/101826494/185792109-400c4788-985f-4a65-9ca7-161d47260848.png)

Por defecto se realizará esta alineación, pero como programadores podemos deshabilitarla, para ello se debemos agregar un atributo a la estructura de la siguiente forma:

![image](https://user-images.githubusercontent.com/101826494/185792244-788e2a02-6fb9-4ed4-8e62-85534576fa5f.png)

Podemos observar que al agregar __\_\_attribute\_\_((packed))__ en la declaración de la estructura, no se realiza el padding y nos muestra el valor obtenido de la suma. Esto puede ser de utilidad en caso de tener que transmitir los datos, ya que si no enviaríamos basura.

# Punto ii
## Explique a que se deben los tamaños de cada una de las estructuras.
![image](https://user-images.githubusercontent.com/101826494/186411622-c9160f15-e169-494e-8823-11bf69757ded.png)

![image](https://user-images.githubusercontent.com/101826494/185793361-5a0dc863-032e-4d21-9080-5147a0541176.png)

![image](https://user-images.githubusercontent.com/101826494/185793572-11312a1c-cd91-4578-be8b-09bed0895260.png)

![image](https://user-images.githubusercontent.com/101826494/185793701-be75401a-e42f-4eae-9a80-5cce0924ee03.png)

## Explique por que la expresion que calcula  limit y limit_aux generan el mismo resutado

![image](https://user-images.githubusercontent.com/101826494/185793763-237a7c97-36d3-401e-81ce-c203ebacb5ec.png)

![image](https://user-images.githubusercontent.com/101826494/185793815-3cce312d-a91e-4ffb-966c-e3bf4985cfe5.png)

En el caso del primer cálculo, lo que hace es al puntero char* limit asignarle la dirección de memoria de la estructura data y sumarle el sizeof de una estructura del mismo tipo, por lo tanto dicho puntero apunta al final de data.

En el segundo caso utiliza aritmética de punteros y le asigna a char* limit_aux la dirección de memoria de data + 1, pero este 1 en realidad representa 1 estructura, por lo tanto es lo mismo que sumarle el sizeof. Por lo tanto ambos resultados son iguales.

## Explique los valores que se muestran en pantalla en cada iteracion del for
![image](https://user-images.githubusercontent.com/101826494/185793986-79a7eb1a-dcd6-4e7e-b4f9-83ab9bf26baf.png)

![image](https://user-images.githubusercontent.com/101826494/185794009-023a21d0-da6d-41c7-b83e-06f1c2f6f45f.png)

![image](https://user-images.githubusercontent.com/101826494/186412245-2399b2cc-88d3-4692-b6cd-456caa4f7236.png)


# Punto iii

## Archivos: list.h, list.c, UseList.c

### Al momento de compilar hay que compilar los dos archivos .c

### gcc UseList.c list.c

## list.h
En el archivo de cabecera se encuentran las declaraciones de las estructuras y funciones necesarias para crear una lista simplemente enlazada y añadir datos al final de ella. Las implementaciones de dichas funciones se encuentran en el archivo list.c

## list.c
  #### Struct NODE
  Estructura en la cual se almacenan los datos. Tiene como campos un valor entero (data) y un puntero a otro nodo (next) para realizar el enlace.
  
  #### Struct LIST
  Estructura que almacena información de una lista, contiene su inicio, su final y su tamaño.
  
  #### void init(LIST* list, char* name);
  
  Esta función inicializa una nueva lista, inicialmente sus valores comienzan en NULL salvo su nombre que le es pasado como parámetro.
  
  #### int isEmpty(LIST* list);
  
  Esta función retorna 1 si la lista está vacía y 0 en caso contrario. 

  #### static NODE* createNode(int dataToSave);
  
  Esta función es llamada localmente al momento de crear un nodo, se creó una función debido a que si se quieren generar otras funciones push se reutilizará esta sección.
  
  #### void pushBack(LIST* list, int dataToSave);
  
  Esta función añade un nuevo nodo al final de la lista con el dato correspondiente a la lista que se le indica, a demás incrementa el size de la lista.
  
  #### void printList(LIST* list);
  Imprime la lista indicada.

## UseList.c

  Por último este archivo contiene funciones a modo de ejemplo de cómo se interactua con listas
