-Una SORTa di Utility-

Programma et IMPERA!

Si desidera implementare una utility per l’ordinamento di una lista bidirezionale, i cui elementi vengono generati randomicamente ad inizio programma.

Ciascun elemento generato viene definito con i seguenti attributi:
-Indice = long unsigned randomico
-Label = stringa di dimensione 10 caratteri generati randomicamente (si veda la tabella ASCII per la generazione dei caratteri)
-Puntatore next,prev

Una volta generata la lista (di dimensione variabile tra 300 e 900 nodi), si chiede di:
-Verificare il riordino della lista in base all’indice e (in caso di uguaglianza) in base alla label
-Indicare il tempo impiegato per il riordino

Obiettivo Platino: 
Affidare i test di riordino ad appositi client che ricevono in ingresso la struttura. Ciascun client stampa nella propria shell il tempo impiegato e salva in un file la struttura ricevuta.

Obiettivo Diamante: 
I client sono in competizione tra loro: il server riceve da ciascun client il tempo impiegato e ne determina il vincitore facendo un confronto con i tempi di ciascuno. Il messaggio di vittoria/sconfitta è inviato ai client.
