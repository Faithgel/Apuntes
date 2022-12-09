# Introduccion
```ad-info
title: Curiosidades
collapse: open
- C fue creado por Dennis Ritchie en el '72 en un computador DEC PDP-11, con sistema operativo UNIX
- C es sucesor del antiguo lenguaje B (Sì, bastante gracioso)
- La primera versión de C fue el  
estándar utilizado para la  
construcción del verdadero  
UNIX actual “UNIX System V”.
- Su rápido éxito ocasiona la  
aparición de muchas variantes  
y problemas de compatibilidad.

```
 ```ad-important
title: Caracteristicas
 **C es un lenguaje estructurado que permite trabajar a alto y bajo nivel,  
esto permite mayor potencia y flexibilidad a cambio de menos  
abstracción.**    
- No es un lenguaje fuertemente tipado, lo que significa que se permite  
casi cualquier conversión de tipos.  
- No se llevan a cabo comprobaciones de errores en tiempo de  
ejecución. (Ej: no se comprueban los índices de los arreglos).  
- Tiene un reducido número de palabras clave: 32 en C89 y 37 en C99.  
- Los compiladores de C, en general, producen programas ejecutables  
muy eficientes y portables.  
- cc: más eficiente en compilación | gcc: menos eficiente en compilación  
 menos eficiente en ejecución | más eficiente en ejecución

- La optimización depende de la arquitectura de la CPU, por ejemplo:
- el código generado en un procesador RISC es aproximadamente  
un 30% del generado en un CISC.
- C dispone de una biblioteca estándar de funciones
```
```ad-attention
title: En resumen
- Es un lenguaje flexible, pero no te salva de tus pendejadas y errores; si compilo y se cae culpa tuya lo más probable, asi que ojo con tu codigo >:3

```
## Lenguaje C
### Sintaxis y Ejecucion
```ad-success 
title: Metodo de compilación
collapse: open
Existen muchos copiladores pero principalmente se usa gcc.
![[Pasted image 20221203200226.png]]
```Shell
gcc main.c -o "nombre del ejecutable"
```
```ad-success
title: Sintaxis
collapse: open
```C
#include <stdio.h> /* comandos del preporcesador o header files*/
typedef float balance; //definiciones de tipos
void imprime(); /* Prototype function o prototipos de funciones*/
int cont = 3; balance b; /*variables globales*/
int main(void){ /*funcion principal*/
	b = 1000;
	imprime();
	return 0;
}

void imprime(){
	printf("cont = %d\nbalance = %f",cont ,b);
}

```
### Sentencias
```ad-done
title: Sentencias
collapse: open
En el lenguaje c cualquier expresion que termina en punto y coma ( ; ): 
- Pueden ser asignaciones, operaciones, llamadas a funciones o  
combinaciones de ellas.
```
```ad-done
title: Bloques de codigo
collapse: open
Es llamado al conjunto de sentencias simples que son contenidas o encerradas entre llaves ( { } ), tambien son llamadas sentencias compuestas

Caracteristicas: 
- Puede aparecer en cualquier lugar donde podría ir una sentencia  
simple.

- Pueden contener declaraciones de nuevas variables (la declaración  
existe sólo dentro del bloque).
```c
{
	int c = 2:
	int b = 3;
}

```

```ad-hint
title: Sentencias if-else
collapse: open
- Si la expresion es verdadera (mayor que cero) se ejecuta una sentencia 

```
```ad-hint
title: Sentencia for (1/3)
collapse: open

- La primera expresion: es la inicializacion del iterador
- La segunda expresion: corresponde a una condicion para ejecutar la sentencia
- la tercera expresion: se utiliza para modificar el valor usado en la condicion (aka la segunda expresion)
```c 
int i;
for (i = 0; i > 5 ; i ++) {
	printf("Esta es la iteracion %d", i + 1);
}
```


```ad-hint
title: Sentencia for (2/3)
collapse: open

- la primera y tercera expresion se puede omitir
```c
int i;
for (; i > 5 ;) {
	printf("Esta es la iteracion %d", i + 1);
	i++;
}
```

```ad-hint
title: Sentencia for (3/3)
collapse: open

- Si se omiten la segunda expresion o todas, la condicion quedaria con un valor verdadero de manera permanente dejando el bulce iterando de manera infinita
```c
for (;;) {
	printf("Esta es la iteracion");
}
```

```ad-hint
title: Sentencia while
collapse: open
- Esta sentencia al igual que el for itera mientras se cumpla una condicion (no posee parametros extra como iterador o modificadores)
- esta condicion siempre se evaluara primero antes de realizar un bucle dentro del bloque de codigo

- Esta sentencia tambien presenta una variante llamada do-while, donde se ejecutara el bloque de codigo una vez y luego se evaluara la condicion 

```c
int = 10;
while(i>0){
	printf("Hola, estoy en un bucle");
	i++;
}

printf("Hola, ahora estoy fuera del bucle");
```

```ad-hint
title: Sentencia switch
collapse: open

- Es una sentencia de seleccion multiple 
- Se ejecuta cada bloque de codigo asociado a la constante que es igual a la expresion.
- la sentencia default se ejecuta si no se ha encontrado ninguna correspondencia. (Es opcional)
- la sentencia **break** por su parte, permite salir de un bloque de codigo si se coloca dentro de un bucle permite salir del ciclo
```c
switch (c){
	case 'a': 
		printf("hola, soy el bloque de codigo %c", c);
		break;
	case 'b':
		printf("hola, soy el bloque de codigo %c", c);
		break;
	default:  
		printf("hola, soy el bloque de codigo de la senencia default y entraste gracias a este valor %c", c);
		break;
}
```
```ad-hint
title: Sentencia continue
collapse: open

- Normalmente es utilizada en un ciclo 
- Funciona similar a un break, solo que en vez de salir de terminar el ciclo fuerza una nueva iteracion sin ejecutar el codigo restante
```c
int i = 0;
for(; i <=20 ; i++){
	if(i%2 == 0) continue;
	printf("%d", i);
}
```
```ad-hint 
title: Sentencia return
collapse: open

- Se utiliza para volver de una funcion
- Retorna al punto donde se hizo la invocacion de la funcion
- Aunque es opcional depende de la naturaleza de la funcion (Tipos de valores de retorno)

```c
void hola(){
	printf("Soy la funcion hola");
	return;
}

int main(){
	hola();
	return 0;
}

```
```ad-important
title: Set de caracteres y palabras claves del lenguaje
collapse: open
- Set de caracteres: 
![[Pasted image 20221203225156.png]]
- Palabras clave
	- Estas mismas pueden ser usadas como labels
![[Pasted image 20221203225312.png]]
```

### Asignacion de memoria y punteros
```ad-summary
title: Introduccion 
collapse: open 
- La memoria ram de un procesador puede ser vista como un arreglo de bytes y dentro de la misma cada dato usa un numero determinado de estos mismos.
- Para cada uno de estos bytes, es posible acceder por su direccion y como eso es posible gracias a los punteros. 
```
```ad-check
title: Punteros
Estas estructuras son variables capaces de albergar la direccion de memoria de una variable, la declaracion de estos mismos se realiza con un * *(Asterisco)*
- Cuando se declara un puntero, este apunta a una direccion desconocida
```c
float *pf;
char *c;
void *p; /*Este es un puntero generico (No esta ligado a un tipo especifico de variable)*/
```
```ad-hint
title: Operadores de punteros
collapse: open
- Existen 2 operadores con los cuales se puede trabajar con los punteros:
	- &*(Operador de direccion)*: devuelve la direccion en memoria.
	- **(Operador de indireccion)*: devuelve el contenido de la direccion apuntada
	```c 
	void swap(int *x, int *y){
		int aux;
		aux=*x;
		*x=*y;
		y*=aux;	
	}
	
	int main(){
		int a = 100, b = 200;
		swap(&a,&b);
	}
```
```ad-warning
title: Punteros (puntos importantes 1/3)
collapse: open
- Un puntero **NO** reserva memoria
``` c
/*Esto es incorrecto no sabemos a que direccion apunta nuestra variable*/
int *p;
*p=5;
/*Esto es lo valido*/
int *p;
char letra;
p=&letra;
*p = 'b'; /* OJO letra tambien valdra b */
letra 'c' /* *p tambiem valdra c debido a que ambos apuntan a la misma direccion de memoria */
```
```ad-warning
title: Punteros (puntos importantes 2/3)
collapse: open
Los punteros soportan operaciones de aritmetica, aunque no realmente al valor que esta en la memoria que representa sino la posicion a la que este apunta. Por ejemplo tiene una puntero de enteros quieres acceder a la siguiente posicion en memoria simplemente sumas o incrementas 
```c
int *p;
p = p++;
```
```ad-warning 
title: Punteros (puntos importantes 3/3)
collapse:open
Se es posible crear un puntero que apunte a otro puntero que se encuentre apuntando a algun dato en la memoria. Esto es llamada indireccion multiple
- Se puede realizar colocando un asterico adicional frente al nombre de la variable: 
```c
float **p;
int ***i;
void (*suma)();/*Esto es un puntero a una funcion*/
```
```ad-success
title: Manejo de memoria dinamica
La asignacion de memoria dinamica es la forma en la que un programa puede obtener memoria mientras se ejecuta, principalmente dentro del lenguaje c tenemos *malloc()* para la asignacion y *free()* para la liberacion de la misma

```c
int *p;
p= (int *) malloc(50*sizeof(int));
auto *a;
a=(auto *) malloc(sizeof(auto));
free(p);
```
