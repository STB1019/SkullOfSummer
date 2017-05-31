La problematica
===============

Partire dal codice sorgente scritto in C ed arrivare ad un programma eseguibile è il processo che viene denominato **il processo di build**. Questo processo, seppur teoricamente lineare, spesso causa problemi durante la compilazione di 

Fasi di c
============

Partire dal codice sorgente scritto in C ed arrivare ad un programma eseguibile è il processo che viene denominato **il processo di build**. Questo processo è suddiviso in varie fase, che elenchiamo:

1. Preprocessing: ogni file *.c del codice sorgente viene dato in pasto al *preprocessore* che si occupa di gestire ogni *istruzione del preprocessore* (per esempio #define);
2. Compilazione: il compilatore analizza il codice sorgente .c generato dal preprocessore e ne controlla errori grammaticali, sintattici e semantici e ne genera il codice assembly;
3. Assembly: durante questa fase viene richiamato l'*assembler*, un programma che legge l'output generato dalla compilazione e produce il codice macchina, o *object code*;
4. Linking: tutte le precedenti fasi riguardano **singoli** file sorgente *.c. Spesso però è molto comodo divide le varie funzioni che si scrivono in diversi file (sia per non avere file da 10000000 righe sia per poter organizzare il proprio codice meglio). Se si scrivono più file succederà sicuramente di voler richiamare una funzione di un file da un altro file: per esempio dopo aver scritto la funzione "get_maximum_of_2_numbers" nel file "utility.c" la si vorrà usare nel proprio programma "my_awesome_program.c". Questo significa che il processo di building deve sapere che l'output dell'assembly del file "my_awesome_program" utilizza una funzione chiamata "get_maximum_of_2_numbers" che però non è definita nel file (ricorda le 3 precedenti fasi vengono effettuate **singolarmente** per ogni file .c che scrivi!). Il processo di *linking* effettua questa associazione: fa in modo di inserire nell'eseguibile finale i vari pezzi di codice assembly richiesti in modo che ogni funzione utilizzata dal programma sia definita. Il processo di linking può associare al tuo eseguibile 3 tipi di file:
 * machine code;
 * static libraries;
 * dynamic libraries;

Le fasi dalla 1 alla 3 vanno fatte singolarmente per ogni file sorgente mentre la quarta deve essere fatta una volta sola collegante tutti i tuoi file contenenti *object code*.

Esempio
=======

Supponiamo di avere il file "utility.c":

    int get_maximimum_of_2_numbers(int a, int b) {
        return a >= b ? a : b;
    }
    
ed il file "my_awesome_program.c":

    #include <stdio.h>
    #include <stdlib.h>
    //prototipo solo per dire al compilatore che la funzione esiste ma è definita da qualche altro file.
    //se non lo metti non ti fa compilare
    int get_maximimum_of_2_numbers(int a, int b);
    
    int main(int argc, const char* args[]) {
        printf("the maximum number is %d\n", get_maximum_of_2_numbers(3, 4));
        return 0;
    }
    
Ora, eseguiamo le prime 3 fasi per il file "utility.c". Da linea di comando:

    gcc -c utility.c
    #il compilatore ha creato il fiel utility.o
    
I file contenenti *object code* hanno solitamente estensione "*.o". Facciamo la stessa cosa con "my_awesome_program.c":

    gcc -c my_awesome_program.c

Ora dobbiamo effettuare il linking:

    gcc utility.o my_awesome_program.o -o my_awesome_program
    
Questo creerà un **eseguibile** chiamato my_awesome_program: fondamentalmente hai richiamato il linker che ha incollato i codici macchina di utility.o e di my_awesome_program.o insieme. In più, implicitamente, ha collegato il tuo codice applicativo con delle *shared libraries* di sistema (la funzione `printf` è definita in una libreria di sistema, la *stdio*) in modo che il tuo eseguibile potesse utilizzare il codice macchina della `printf`. Digitando in linea di comando:

    ./my_awesome_program
    
il computer eseguirà il vostro programma, ossia stamperà 4.

    
Link Utili
==========

* Capire le fasi di compilazione: https://www.calleerlandsson.com/the-four-stages-of-compiling-a-c-program/;
* Alcune flag molto utili in ambiente di produzione: http://blog.httrack.com/blog/2014/03/09/what-are-your-gcc-flags/;


Curiosità
=========

Immagina di esserti dimenticato di collegare `utility.o` a `my_awesome_program.o`. Ossia:

    gcc -c my_awesome_program.c
    gcc -c utility.c
    gcc my_awesome_program.c -o my_awesome_program
    
In questo caso il linker si lamenterà con:

    koldar@koldar:~/Desktop/Skull$ gcc my_awesome_program.c -o my_awesome_program
    /tmp/ccMJof6N.o: In function `my_awesome_program':
    my_awesome_program.c:(.text+0x1a): undefined reference to `get_maximum_of_2_numbers'
    collect2: error: ld returned 1 exit status
    
Questo è un classico errore da linker: esso si sta lamentando che non trova il codice macchina della funzione "get_maximum_of_2_numbers". Tra parentesi `ld` è il linker vero e proprio.
