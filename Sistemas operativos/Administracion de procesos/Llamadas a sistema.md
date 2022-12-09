```ad-question
title:¿Que son las llamadas al sistema? (*System Call*)
Es una interfaz de programacion para usar los servivios proveidos por el sistema operativo
- Se utilizan para trasferir el control entre el sistema y el usuario.
``` 
```ad-question
title: ¿Como se realiza la ejecucion?
![[Pasted image 20221204162738.png]]
```
```ad-hint
title: Tipos de llamadas
- Control de procesos
- Manipulacion de archivos
- Manipulacion de dispositivos
- Mantenimiento de informacion
- Comunicaciones.
```

## Control de procesos
```ad-check
title: Control de procesos - **fork()** - **getdid()**
- fork:
 Es utilizado para creado para crear nuevos procesos, a partir de uno ya existente
	- Este mismo crea un procesos nuevo que llamaremos hijo y retorna 0 cero al hijo y el id de proceso al padre
	- PID = id del proceso (*Este es asignado por el nucleo del sistema*)	
	 ![[Pasted image 20221204164615.png]]
- getpid:
Es utilizado para si un proceso desea saber su pid
![[Pasted image 20221204165216.png]]

```
## Comunicacion
```ad-check
title: Pipe
collapse: open
Es un canal de comunicacion entre procesos emparentados, que referenciado por un descriptor de archivo 
- Solo existen mientras se use y desaparece cuando se cierra
```
```ad-check
title: Sockets
collapse: open
Es una interfaz de IO de datos que permite la comunicacion entre procesos que pueden estar en el mismo local o unidos por una red
- Hay variados tipos de sockets
	- Stream (TDP)
	- Datagram (UDP)
	- Raw
```
