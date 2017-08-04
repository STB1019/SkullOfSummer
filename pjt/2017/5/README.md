_Quando il gioco si fa duro, spegni la console e lasciala raffreddare._

![tooltip](http://www.zanongiocattoli.it/image/cache/data/Hasbro/forza%204%20hasbro12-500x500.jpg)

Seguendo le regole del forza 4, implementare un gioco con le segenti varianti:
* Ciascun giocatore vede solo i propri gettoni
* I gettoni cadono sino a quando non giacciono sul fondo o su altri gettoni
* Vi sono al più 4 giocatori (R;G;V;B)

L’esito del gioco viene valutato dal server che istante per istante ha lo stato della partita, mentre i client vedono solamente i propri gettoni.

Il server crea una waiting room per stabilire il numero di partecipanti e successivamente stabilisce con essi il socket; sempre il server decide l’ordine dei partecipanti (randomico), successivamente mantenuto per la durata della partita.

In caso di vittoria/sconfitta, i partecipanti ricevono un messaggio di sberleffo/congratulazioni.

**Obiettivo Platino**: rendere il server sufficientemente robusto, tale per cui accetti socket solo con una password. In caso di attacco DOS conservi gli indirizzi ip e ne filtri le future richieste.  

**Obiettivo Diamante**: se vi fosse un numero dispari di giocatori, viene aggiunto un giocatore virtuale dal server, che tenterà di sconfiggere gli avversari. 
