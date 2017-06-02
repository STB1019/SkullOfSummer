La problematica
===============

Partire dal codice sorgente scritto in C ed arrivare ad un programma eseguibile è il processo che viene denominato **il processo di build**. Questo processo, seppur teoricamente lineare, spesso causa problemi durante la compilazione dei programmi. Questo documento ti spiegherà come avviene il **processo di building** e ti spiegherà alcuni comandi del `gcc` che gestiscono quel processo.

Fasi di compilazione
====================

Partire dal codice sorgente scritto in C ed arrivare ad un programma eseguibile è il processo che viene denominato **il processo di build**. Questo processo è suddiviso in varie fase, che elenchiamo:

1. **Preprocessing**: ogni file *.c del codice sorgente viene dato in pasto al *preprocessore* che si occupa di gestire ogni *istruzione del preprocessore* (per esempio #define);
2. **Compilazione**: il compilatore analizza il codice sorgente .c generato dal preprocessore e ne controlla errori grammaticali, sintattici e semantici e ne genera il codice assembly;
3. **Assembly**: durante questa fase viene richiamato l'*assembler*, un programma che legge l'output generato dalla compilazione e produce il codice macchina, o *object code*;
4. **Linking**: tutte le precedenti fasi riguardano **singoli** file sorgente *.c. Spesso però è molto comodo divide le varie funzioni che si scrivono in diversi file (sia per non avere file da 10000000 righe sia per poter organizzare il proprio codice meglio). Se si scrivono più file succederà sicuramente di voler richiamare una funzione di un file da un altro file: per esempio dopo aver scritto la funzione "get_maximum_of_2_numbers" nel file "utility.c" la si vorrà usare nel proprio programma "my_awesome_program.c". Questo significa che il processo di building deve sapere che l'output dell'assembly del file "my_awesome_program" utilizza una funzione chiamata "get_maximum_of_2_numbers" che però non è definita nel file (ricorda le 3 precedenti fasi vengono effettuate **singolarmente** per ogni file .c che scrivi!). Il processo di *linking* effettua questa associazione: fa in modo di inserire nell'eseguibile finale i vari pezzi di codice assembly richiesti in modo che ogni funzione utilizzata dal programma sia definita. Il processo di linking può associare al tuo eseguibile 3 tipi di file:
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
    #il compilatore ha creato il file utility.o
    
I file contenenti *object code* hanno solitamente estensione "*.o". Facciamo la stessa cosa con "my_awesome_program.c":

    gcc -c my_awesome_program.c

Ora dobbiamo effettuare il linking:

    gcc utility.o my_awesome_program.o -o my_awesome_program
    
Questo creerà un **eseguibile** chiamato my_awesome_program: fondamentalmente hai richiamato il linker che ha incollato i codici macchina di utility.o e di my_awesome_program.o insieme. In più, implicitamente, ha collegato il tuo codice applicativo con delle *shared libraries* di sistema (la funzione `printf` è definita in una libreria di sistema, la *stdio*) in modo che il tuo eseguibile potesse utilizzare il codice macchina della `printf`. Digitando in linea di comando:

    ./my_awesome_program
    
il computer eseguirà il vostro programma, ossia stamperà 4.

Alcune Flag utili
-----------------

| Flag | Descrizione | Note |
|:----:|-------------|------|
| -e   | Esegue solo fino al processo di preprocessing | Usato per controllare se la tua macro programming fa quello che pensi che debba fare |
| -s   | Esegue solo fino al processo di compilazione  | Usato di rado |
| -c   | Esegue solo fino al processo di assembly      | Una delle flag più usata per modularizzare il tuo codice |
| -o   | Definisce il nome che l'output di `gcc` dovrà avere | |
| -L   | Cartelle in cui cercare shared libraries addizionali | |
| -l   | il *linker name* della shared library che vuoi linkare al tuo codice | Per un comportamento corretto, inserisci questi flag alla fine del comando di compilazione. L'ordine dei comandi è importante |
| -I   | Cartella in cui sono presenti *header* files addizionali | |
| -D   | Durante il processo di compilazione la costante di preprocessore specificata sarà definita | |
| -U   | Durante il processo di compilazione la costante di preprocessore specificata non sarà definita | |
| -g   | Flag usato per gestire il livello di informazioni di debug da aggiungere al tuo *machine code* | |
| -O   | Flag usato per gestire il livello di ottimizzazione del compilatore | |
| -W   | Flag usato per gestire il trattamento di alcuni warning lanciati dal compilatore | |

Esempi di come usare le flag
----------------------------

Per gestire le fasi di compilazione e l'output, esempi possono essere:

    gcc -e my_awesome_program.c
    gcc -s my_awesome_program.c
    gcc -c my_awesome_program.c
    gcc -c my_awesome_program.c -o my_awesome_program.o

Se devi utilizzare una libreria dinamica, imposta il suo percorso tramite `-L` e poi usa il suo nome con `-l`. Ricardati di mettere il `-l` alla fine del comando.

    gcc -L/home/piero/my_shared_libraries/ my_awesome_program.o -lmylib
    
Se devi usare header file esterni, usa `-I`:

    gcc -I/home/piero/my_headers/ -c my_awesoe_program.c
    
Se il gcc esegue la fase di processing (ovvero sempre tranne quando esegui il linking con i file *machine code*), puoi usare `-D` e `-U` per definire/non definire alcune macro. Per esempio possiamo definire in fase di compilazione un macro "DEBUG" che attiva dei `printf` che aiutano a debuggare il programma:

    int main(int argc, const char* args[]) {
        int a = 5 + 4;
        #ifdef DEBUG
        printf("a is %d\n", a);
        #endif
        return 0;
    }

Per definire "DEBUG" puoi fare:

    gcc -DDEBUG -c my_awesome_program.c
    #ora sarà definita la macro "DEBUG"
    
Per fare in modo di rimuovere la definizione di una macro, puoi fare:

    gcc -UDEBUG -c my_awesome_program.c
    #la macro DEBUG non è definita
    
Di default tutte le macro devono essere definite esplicitamente.
    
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
