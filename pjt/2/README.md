![](http://www.iotleague.com/wp-content/uploads/2015/11/Iot1.png)

_Complimenti, il progetto più simpatico è tuo!_

Dovrai realizzare un server ed almeno 4 clients che comunichino tra loro scambiandosi un set di messaggi particolari.
Ciascun clients è dotato di alcune funzionalità particolari di seguito elencate:

* Il clients somma
  * Esegue la somma se deve elaborare numeri
  * Esegue la somma tra char (concatenazione)
  * Esegue la somma di puntatori (shift) https://it.wikipedia.org/wiki/Aritmetica_dei_puntatori#Operatore_di_somma_di_un_puntatore_e_un_intero
* Il clients differenza
  * Esegue la differenza se deve elaborare numeri
  * Esegue la differenza tra char (sottrare la prima stringa alla seconda e ne mostra il risultato, che può essere “” ovvero nulla)
  * Esegue la differenza di puntatori (vedi sopra)
* Il clients prodotto
  * Esegue il prodotto se deve elaborare numeri
  * Esegue il prodotto tra char: ogni volta che trova l’iniziale della prima stringa, all’interno della seconda stringa, viene inserita la prima nella seconda e prosegue la lettura dalla fine del suddetto inserimento.
    * “caso”*”arciduca”=”arcasoducasoa”
  * In caso di puntatori effettua l’AND sugli indirizzi
    * 00X001101 * 00X010101 = 00x000101
* Il clients divisione
  * Esegue la divisione se deve elaborare numeri
  * Esegue la divisione tra char (split) sostituendo nella stringa 1, ogni ripetizione della stringa 2, con uno \#. Ogni qualvolta venisse trovata la combinazione \#, deve essere castata come \\##.
  * In caso di puntatori effettua l’OR sugli indirizzi
    * 00X001101 * 00X010101 = 00x011101

Il server ha il compito di eseguire un set di operazioni definite in ingresso (a.k.a dall’utente), demandando ai client il compito di svolgere il calcolo.

Ciascun client deve salvare in lista delle operazioni che ha ricevuto e salvare il tutto in un file di log (se il file esiste già proseguire con la scrittura, senza eliminare quanto precedentemente scritto).

**Obiettivo Platino**: in input viene data una espressione (solo parentesi tonde, ndr) composta da valori numerici.

**Obiettivo Diamante**
: viene fornita una espressione (anche parentesi quadrate,ndr) alfanumerica, le cui variabili sono definite in ingresso. 
