# WOLF SHELL

## Instalación

Pasos para instalar:

- Clonar el repositorio
  
  - En el directorio deseado ejecutar el comando desde la terminal
    

```bash
git clone https://github.com/ICOMP-UNC/soi---2022---laboratorio-4-franUNC            
```

    *NOTA*: También se puede descargar el .zip directamente desde github

- Dentro del proyecto, abrir una terminal y ejecutar
  
  ```makefile
  make
  ```
  
- Una vez realizado esto se habrá instalado la shell
  

## Ejecución

El binario de la bash se encuentra en el directorio `/bin`, para ejecutarlo podemos hacerlo directamente desde este directorio o desde la raiz ejecutar el archivo `launcher.sh`

Primera opción:

```bash
./bin/main
```

Segunda opcion:

```bash
sh ./launcher.sh
```

## Comandos internos admitidos

`clr`

    Limpia la salida de consola

`echo <message/env>`

    Impresión en consola del mensaje ingresado, en caso de que se añada un "$" delante del mensaje se lo interpretará como una variable de entorno y se imprimirá su valor (si es que existe).

`cd <DirectoryTarget>`

    Cambia del directorio actual al indicado, y actualiza las variables de entorno PWD y OLDPWD.

    En caso de que no se explicite un directorio, cambiará al directorio /home/username

    En caso de ingresar ".." cambiará al directorio anterior (OLDPWD)

`quit`

    Finaliza la ejecución de la bash

## Ejecución de programas externos

    En caso de ingresar un comando que no sea reconocido como interno, la shell interpretará que es un programa interno e intentará encontrarlo y ejecutarlo. Acepta path relativos y absolutos. En caso de no ingresar el path buscará en /usr/bin.

### Ejecución en background

    Si al final del nombre del programa se añade el símbolo "&" la ejecución se realizará en background.

    Se imprime un mensaje indicando el PID del proceso en background y continúa la ejecución de la shel normalmente. Cuando el proceso secundario finalice, se imprimirá un mensaje indicando que el proceso termino, volviendo a mostrar su PID.

## BUGS

- Al ejecutar más de un proceso en background sólo da aviso de finalización del primero. NO deja procesos zombies
- No ejecuta los comandos internos de la shell en background, solo programas externos
