# API de nSystem - Nivel Usuario

```ad-check
title: nEmitTask
Este emite o lanza una tarea(Hilo) que ejecutara una funcion o procedimiento
- Este retorna un descriptor de una tarea (nTask)
![[Pasted image 20221204175236.png]]
```
```ad-check
title: nExitTask
Termina le ejecucion de la tarea que la invoca, y retorna un codigo 
![[Pasted image 20221204175722.png]]
```
```ad-check
title: nWaitTask
Espera que termine una tarea y luego libera los recursos usada por esta, ademas de entregar el codigo de retorno devuelto en nExitTask

![[Pasted image 20221204175928.png]]
```
## Metodos de sincronizacion
### Locks
#### Definicion
```ad-check
title: Locks/Semaforos Binarios
- Sirven para garantizar exclusion mutua, y es un mecanismo de sincronizacion muy primitivo
![[Pasted image 20221204180505.png]]
```
#### Uso
```ad-info
title: Metodos
- makeLock: Crea un candado que inicialmente esta abierto
- lock: solicita cerrar el candado
- unlock: abre el candado
```
```ad-faq
title: Ejemplo: Diccionario concurrente
```c
#define MAX 100  
char *keys[MAX]; /*asumimos que se inicializó en NULL*/  
char *defs[MAX]; /*asumimos que se inicializó en NULL*/ 
Lock l;

int getSlot() {  
	int i;  
	for(i=0; i<MAX; i++)  
		if (keys[i]==NULL)  
			return i;  
	error(); /*asumimos que no retorna*/  
	return 0;  
}  
void newDef(char *k, char *d) {
	lock(l);
	int i = getSlot();  
	keys[i]= k;  
	defs[i]= d;
	unlock(l);
}
int getIdx(char *k) {  
	int i;  
		for(i=0; i<MAX; i++)  
			if (keys[i]!=NULL && strcmp(k, keys[i]) == 0)  
				return i;  
	return -1;  
}

char *query(char *k) {  
	char *d;  
	lock(l);  
	int i= getIdx(k);  
	if (i==-1)  
		d= NULL;  
	else  
		d= defs[i];  
	unlock(l);  
	return d;
}

void delDef(char *k) {  
	lock(l);  
	int i= getIdx(k);  
	if (i!=-1) {  
		keys[i]= NULL;  
		defs[i]= NULL;  
	}  
	unlock(l);  
}
```
### Semaforos
#### Definicion
```ad-check
title: Semaforos
Se puede imaginar un semaforo como un distribuidor de tickets(Si no hay ningun ticket se debe esperar)
![[Pasted image 20221204182403.png]]
```
#### Uso
```ad-info
title: Metodos
- makeSem: crea un semaforo con n tickets
- wait: saca un ticket y espera si no hay disponibles(nunca hay cantidad negativa)
- signal: aporta un ticket al semaforo
```
```ad-faq
title: Problema del productor consumidor
```c
#define N 100  
Item buff[N];  
int e=0, f=0;  
...  
Sem full= makeSem(0);  
Sem empty= makeSem(N);  
...  
void put(Item it) {  
	wait(empty);  
	buff[e]= it;  
	e= (e+1)%N;  
	signal(full);  
}  
Item get() {  
	Item it;  
	wait(full);  
	it= buff[f];  
	f= (f+1)%N;  
	signal(empty);  
	return it;  
}
```
```ad-faq
title: Problema de productores consumidores
```c
#define N 100  
Item buff[N];  
int e=0, f=0, c=0;  
...  
Sem full= makeSem(0);  
Sem empty= makeSem(N);  
Sem semP= makeSem(1);  
Sem semC= makeSem(1);  
...
Sem full= makeSem(0);  
Sem empty= makeSem(N);  
...  
void put(Item it) {  
	wait(empty);  
	wait(semP);  
	buff[e]= it;  
	e= (e+1)%N;  
	signal(semP);  
	signal(full);  
}
Item get() {  
	Item it;  
	wait(full);  
	wait(semC);  
	it= buff[f];  
	f= (f+1)%N;  
	signal(semC);  
	signal(empty);  
	return it;  
}
```
### Mensajes
#### Definicion
```ad-check
title: Mensajes
Se crearon como metodo de sincronizacion, para efectos de sistemas distribuidos en red problema que los semaforos no pueden resolver, se ideo este sistema que permite enviar mensajes hacia diferentes sistemas para mantener la sincronizacion incluso en ese nivel
![[Pasted image 20221204183611.png]]
```
#### Uso
```ad-info
title: Metodos
- nSend: envia un mensaje a una tarea y se queda bloqueado hasta que la tarea reciba el mensaje
- nReceive: Espera y recibe un mensajee durante un tiempo especificado o de manera ilimitada hasta que llegue el mensaje
- nReply: responde al mensaje enviado por una tarea, Desde ese instante, el receptor no puede accesar la información contenida  
en el mensaje que había sido enviado, ya que el emisor podría destruirlo
```
```ad-faq
title: Ejemplo - Multiplicador Concurrente
```c
#include <nSystem.h>  

#define MULT 1  
#define DEST 2  

typedef struct {  
	nTask serv;  
} *Mult;

typedef struct {  
	int code;  
	double f, p;  
} Req;  

Mult makeMult() {  
	Mult m = (Mult) nMalloc(sizeof *m);  
	m->serv = nEmitTask(multProc);  
	return m;  
}
double mult(Mult m, double f) {  
	Req rq;  
	rq.code = MULT;  
	rq.f= f;  
	nSend(m->serv, &rq);  
	return(rq.p);  
}  
void destroyMult(Mult m) {  
	Req rq;  
	rq.code = DEST;  
	nSend(m->serv, &rq);  
	nWaitTask(m->serv);  
	nFree(m);  
}

int multProc() {  
	double p = 1.0;  
	for(;;) {  
		Req *prq;  
		nTask t;  
		prq = (Req *) nReceive(&t, -1);  
		if (prq->code == MULT) {  
			p = p * prq->f;  
			prq->p = p;  
			nReply(t, 0);  
		} else { /*DEST*/  
			nReply(t, 0);  
			nExitTask(0);  
		}  
	}
}

```
### Monitores Estilo Hansen
#### Definicion
```ad-check
title: Monitor Hansen
Los monitores son una herramienta de sincronización más estructurada que  
encapsula variables compartidas junto con los procedimientos para acceder a  ellas.
- Para modificar las estructuras de datos internas del monitor es preciso utilizar  
los procedimientos definidos en él, no hay acceso directo a estas estructuras desde fuera del monitor.
```
#### Uso
```ad-info
title: Metodos
- nMakeMonitor: Construye un monitor  
- nDestroyMonitor: Destruye un monitor  
- nEnterMonitor: Ingreso al monitor  
- nExitMonitor: Salida del monitor
```
```ad-faq
title: Ejemplo - Problema del productor consumidor
```c
Item buf[N];
int next_empty = 0, next_full=0;
int count=0;

nMonitor m;

Item get(){
	Item x;
	nEnter(m);
	while(count==0)nWait(m);
	x = buff[next_full];
	next_full = (next_full + 1) % N;
	count--;
	nNotifyAll(m);
	nExit(m);
}
void put(Item X){
	nEnter(m);
	while(count==N) nWait(m);
	buff[next_empty]= x;
	next_empty = (next_empty + 1) % N;
	count++;
	nNotifyAll(m);
	nExit(m);
}
```
### Monitores Estilo Hoare
#### Definicion
```ad-check
title: Monitor Hoare
Es una nueva implementacion que añade un nuevo tipo de datos que son las condiciones, que aseguran la exclusion mutua dentro del monitor
![[Pasted image 20221204193507.png]]
```
```ad-info
title: Metodos
- nMakeCondition: Crea una condicion nueva para un monitor
- nDestroyCondition: Destruye la condicion
- nWaitCondition: Espera que la condicion sea triguereada
- nSignalCondition: Trigerea la condicion deseada
```
```ad-faq
title: Ejemplo - Problema Productor consumidor
```c
Item buf[N];
int next_empty = 0, next_full=0;
int count=0;

nMonitor m;
nCondition no_empty;
nCondition no_full;

Item get(){
	Item x;
	nEnter(m);
	while(count==0) nWaitCondition(no_empty);
	x = buff[next_full];
	next_full = (next_full + 1) % N;
	count--;
	nSignalCondition(no_full);
	nExit(m);
}
void put(Item X){
	nEnter(m);
	while(count==0) nWaitCondition(no_full);
	x = buff[next_full];
	next_empty = (next_empty + 1) % N;
	count++;
	nSignalCondition(no_empty);
	nExit(m);
```

```ad-attention
title: Patron de uso de monitores
La mayoria de los problemas de sinconizacion se resuelven con el siguiente patron:
```c
nEnter(m);
while(...) nWait(m);
.....Aqui consulta o actualizacion......
nNotifyAll(m);
nExit(m);
```