```ad-seealso
title: Conceptos
collapse: open
- Proceso Pesado: es un programa compuesto por un codigo, datos, pila y registros
![[Pasted image 20221204160308.png]]
- Proceso livianos: es virtual, se usa para fererise a los hilos.
- Preemptive: el SO puede quitarle la cpu al proceso en cualquier momento
- Non-Preemptive: el proceso decide cuando devuelve la cpu al sistema
```

```ad-note
title: Clasificacion de procesos
collapse: open

|          Tipo          |    Pesados    |  Livianos  |
|:----------------------:|:-------------:|:----------:|
|         Jerga          | Procesos UNIX |  Threads   |
| Espacio de direcciones |    Propio     | Compartido |
|   Procesador Virtual   |    Propio     |   Propio   |
|   Requiere Hardware    |      Sí       |     NO     |

Puede verse tambien de esta manera:
![[Pasted image 20221204161507.png]]

```
```ad-question 
title: ¿Porque se llaman pesados?
Esto va ligado al costo de implementarlos tiempo/memoria en cpu el cual es mas elevado que "lanzar" hilos, ademas se es requerido hardware fisico para el manejo de la memoria mismo