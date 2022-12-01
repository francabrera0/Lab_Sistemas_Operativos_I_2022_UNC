# soi---2022---laboratorio-6-franUNC

# mmap

## Planteo del problema
  Se pretende realizar el mapeo de memoria de un archivo en memoria y realizar operaciones sobre el. 

## Solución
  Previamente, se conoce la estructura de organización de los datos internos del archivo y su tamaño. Por esto inicialmente, se generó una estructura que permita almacenar dichos datos en un formato que facilite su lectura y operaciones.
  Esta estructura no tiene padding, para que todos los datos se encuentren contiguos y se respete el tamaño.
  
  Luego, se llama a una función que calcula la cantidad de instancias de lectura hay en el archivo, lo que nos va a permitir reservar el espacio justo en memoria. El cálculo de la cantidad de instancias es simplemente

$$ numero de instancias = \frac{sizeof(file)}{sizeof(dataStructure)} $$

  Una vez calculado esto, se utiliza la función mmap para mapear el archivo en memoria, con un size igual al tamaño de la estructura multiplicado por la cantidad de instancias.
  
  Por último se calcula de manera iterativa el promedio del campo "validSamples" de la cantidad de mediciones almacenadas en memoria.
