# May The Force Be With You

![](http://blog.roadtripnation.com/wp-content/uploads/2013/05/MayTheForce-Banner.jpg)

Realizzare una libreria (sia shared che static library) per la gestione di strutture comuni come la lista (uni e bidirezionale), Heap e Grafiasddsa

La lista è una concatenazione di nodi, in cui ciascun nodo segue il precedente,  ad eccezione del primo nodo (la testa) che non è preceduto da nessuno, mentre per l’ultimo nodo (la coda) non esiste alcun successore.

Una lista, normalmente, viene definiti unidirezionale (è possibile scorrere in un sol senso). Talvolta è definita come bidirezionale, pertanto da ciascun nodo è possibile risalire a chi lo precede o recuperare il nodo successivo.

L’HEAP è una struttura ad albero, ove ciascun nodo è dotato di una propria chiave ( genericamente numerica, ma non è necessariamente), in cui è valida la “proprietà dell’heap”: in cui le chiavi sono vincolate da un ordine preciso. Ne consegue che, generalmente, esistono alberi di max/min heap in cui il nodo padre possiede sempre la chiave max/min rispetto ai nodi figli.

Il Grafo è concettualmente una lista in in cui ciascun elemento possiede più di un collegamento con altri pari. Un set definito di nodi collegati tra loro, costituiscono un grafo se e solo se è possibile partire da uno qualsiasi e raggiungerne un altro, in un numero finito di passi.

La liberia deve poter gestire le note operazioni di add/remove/get dei nodi, a seconda delle scelte fatte dal programmatore.

**Obiettivo Platino**: implementazione metodo di ricerca dipendente dal “payload” del nodo.
