Introduzione
============

Partire dal codice sorgente scritto in C ed arrivare ad un programma eseguibile è il processo che viene denominato **il processo di build**. Questo processo è suddiviso in varie fase, che elenchiamo:

1. Preprocessing: ogni file *.c del codice sorgente viene dato in pasto al *preprocessore* che si occupa di gestire ogni *istruzione del preprocessore* (per esempio #define);
2. Compilazione: il compilatore analizza il codice sorgente .c generato dal preprocessore e ne controlla errori grammaticali, sintattici e semantici e ne genera il codice assembly;
3. Assembly: durante questa fase viene richiamato l'*assembler*, un programma che legge l'output generato dalla compilazione e produce il codice macchina, o *object code*;
4. Linking: tutte le precedenti fasi riguardano **singoli** file sorgente *.c. Spesso però è molto comodo divide le varie funzioni che si scrivono in diversi file (sia per non avere file da 10000000 righe sia per poter organizzare il proprio codice meglio). Se si scrivono
    
    
Link Utili
==========

* https://www.calleerlandsson.com/the-four-stages-of-compiling-a-c-program/
