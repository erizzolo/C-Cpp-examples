# Data structures

## Esempi di implementazioni

| Struttura | File                                                        | Note                                                                        |
| --------- | ----------------------------------------------------------- | --------------------------------------------------------------------------- |
| Stack     | [stackFLA.cpp](../solutions/stack/stackFLA.cpp)             | statica, fixed length array                                                 |
| Stack     | [stackDA.cpp](../solutions/stack/stackDA.cpp)               | dinamica, puntatore a memoria dinamica                                      |
| Stack     | [stackSLL.cpp](../solutions/stack/stackSLL.cpp)             | dinamica, come lista semplicemente concatenata                              |
| Stack     | [stackFLAT.cpp](../solutions/stack/template/stackFLA.cpp)   | statica, fixed length array, template                                       |
| Stack     | [stackFLATI.cpp](../solutions/stack/template/stackFLATI.cpp) | statica, fixed length array, template con operazioni interne                |
| Stack     | [stackFLATC.cpp](../solutions/stack/template/stackFLATC.cpp) | statica, fixed length array, template con operazioni interne e dati private |
| Coda      | [queueFLA.cpp](../solutions/queue/queueFLA.cpp)             | statica, fixed length array                                                 |
| Coda      | [queueFLAC.cpp](../solutions/queue/queueFLAC.cpp)           | statica, fixed length circular array                                        |
| Coda      | [queueDAC.cpp](../solutions/queue/queueDAC.cpp)             | dinamica, puntatore a memoria dinamica circolare                            |
| Coda      | [queue2Stacks.cpp](../solutions/queue/queue2Stacks.cpp)     | statica, tramite due stacks                                                 |
| Coda      | [queueSLL.cpp](../solutions/queue/queueSLL.cpp)             | dinamica, come lista semplicemente concatenata                              |
| Lista     | [listSL.cpp](../ADTLista/listSL.cpp)                        | lista dinamica semplicemente concatenata, con nodi                          |
| Lista     | [listDL.cpp](../ADTLista/listDL.cpp)                        | lista dinamica doppiamente concatenata, con nodi                            |
| Lista     | [listSH.cpp](../ADTLista/listSH.cpp)                        | lista dinamica semplicemente concatenata, con array ed indici separati      |
| Lista     | [listDH.cpp](../ADTLista/listDH.cpp)                        | lista dinamica doppiamente concatenata, con array ed indici separati        |

## Alcune note sulle implementazioni

Abbiamo visto due implementazioni dello stack:

* stack statico (stackFLA):
*basato su di un array di dimensione costante*
* stack dinamico (stackDA):
*basato su di un puntatore che indirizza una zona di memoria di dimensione variabile allocata dinamicamente*

Vediamo il caso della implementazione stackFLA:
| nome          | tipo            | dimensione (B)              |
| ------------- | --------------- | --------------------------- |
| stackFLA      | struct          | 4 + CAPACITY * sizeof(item) |
| stackFLA.data | item [CAPACITY] | CAPACITY * sizeof(item)     |
| stackFLA.size | int             | 4                           |
In questo caso i dati sono parte integrante della struct, la cui dimensione totale dipende dalla capacity.

**Se si copia la struct, la copia contiene anch'essa i dati (duplicati) ed è indipendente dalla struct originale.**

Vediamo il caso della implementazione stackDA:
| nome             | tipo      | dimensione (B)     |
| ---------------- | --------- | ------------------ |
| stackDA          | struct    | 8 + sizeof(item *) |
| stackDA.data     | item\*    | sizeof(item \*)    |
| stackDA.capacity | int       | 4                  |
| stackDA.size     | int       | 4                  |
| *senza nome*     | *memoria* | *variabile*        |
dove sizeof(item *) è la dimensione (4B o 8B) di un indirizzo.

In questo caso i dati **non** sono parte integrante della struct, la cui dimensione totale **non** dipende dalla capacity, bensì sono situati altrove (allocati in memoria dinamica) all'indirizzo memorizzato nella struct.

**Se si copia la struct, la copia non contiene anch'essa i dati ma soltanto l'indirizzo dei dati, lo stesso della struct originale.**

**I dati modificati, sia tramite l'originale che tramite la copia, sono modificati per entrambe, dato che sono gli stessi!!!**

Vedere (ed eseguire) il programma [testFLADA.cpp](solutions/stack/testFLADA.cpp) includendo le due implementazioni e notare le differenze !!!
