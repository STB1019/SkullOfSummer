# Funny FES!

![https://docparser.com/img/parsing-engine.png](https://docparser.com/img/parsing-engine.png)

_Muhahaha, se pensi che sia facile, ti sbagli di grosso. Mai sottovalutare il progetto del Branch._

Dovrai produrre una utility composta da tre moduli, ciascuno dedicato al parsing del file con una particolare sintassi.
* CSV, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules
.csv
* JSON, https://en.wikipedia.org/wiki/JSON#Example
.json
* XML, https://en.wikipedia.org/wiki/XML#Applications_of_XML
.xml

Il programma dell’utente invoca la tua utility che recupera dal file passato in ingresso, tutte le informazioni necessarie per realizzare una lista contenente i suddetti valori. 
È possibile che vi siano dei nodi innestati all’interno di altri nodi.

Il file è dotato di un’estensione, che definisce la tipologia di parsing necessario per recuperare le informazioni (non è necessario alcuna ulteriore verifica in merito alla corrispondenza tra contenuto ed estensione).

Il programma deve salvare la struttura dati in un file, al fine di recuperare più velocemente la struttura dati. Si suppone valida l’univocità tra nome del file e struttura salvata.

**Obiettivo Platino**: riconoscimento “automatico” del parsing necessario da implementare
**Obiettivo Diamante**: L’utility permette di convertire il contenuto di un file in ingresso, in una delle altre due sintassi, ricevendo in ingresso al programma il file di origine ed il file di destinazione.
