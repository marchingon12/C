<h1> Programmieren I - Assignment 05 </h1>
<div style="float: left">August Ho, Benjamin von Behren</div>
<div style="float: right">18.10.2020</div>
<br>

## Aufgabe 1: Rabatt auf Schokoriegel

siehe `total.c`

<br>

## Aufgabe 2: Guess my number

siehe `guess_my_number.c`

<br>

## Aufgabe 3: Formatierung von Quelltext

a)

```c
int f(int i){
	printf ("called f\n");
	if (i < 0){
		return -i;
	}else{
		return 3 * i;
	}
}
```

b)

Die Funktion `f` nimmt einen Input-Wert `i` als Integer und gibt den Wert `i` entweder als positiver Zahl züruck falls es vorher negativ war, oder mit 3 multipliziert wenn es vorher positiv war. Dazu wird eine Benachrichtigung `called f` mit eine Zeilenumbruch `\n` im Compiler ausgegeben.

c)

siehe `fib.c`

<br>

## Aufgabe 4: Compiler Fehlermeldungen

siehe `primes.c` und unten für Fehlermeldungen.

```bash
Fehlermeldung 1:
primes.c:7:10: fatal error: Bas.eh: No such file or directory
    7 | #include "Bas.eh" //include prog1lib
      |          ^~~~~~~~
compilation terminated.
make: *** [primes] Error 1

Es wurde versucht eine Bas.eh Datei und nicht die Base.h Datei einzufügen. Außerdem
sollte es klein geschrieben werden (base.h), wobei es groß geschrieben auf manchen
Systemen auch funktioniert.
```

```bash
Fehlermeldung 2:
primes.c: In function 'print_primes_in_intervall':
primes.c:19:16: error: 'prime' undeclared (first use in this function)
   19 |         while (prime < upper){
      |                ^~~~~
compilation terminated due to -Wfatal-errors.
make: *** [primes] Error 1

Wenn zuvor die if-Schleife nicht durchgeführt wurde, wurde prime nicht deklariert.
Eigentlicher Fehler ist eine fehlende Klammer in Zeile 15:
if(prime < 2)
zu
if(prime < 2) {
```

```bash
Fehlermeldung 3:
In file included from ../prog1lib/lib/Base.h:140,
                 from primes.c:7:
primes.c: In function 'print_primes_in_intervall':
primes.c:21:13: error: expected ',' or ';' before '_Bool'
   21 |             bool is_a_prime = true;
      |             ^~~~
compilation terminated due to -Wfatal-errors.
make: *** [primes] Error 1

In der vorherigen Zeile fehlt ein Semikolon.
```

```bash
Fehlermeldung 4:
primes.c: In function 'print_primes_in_intervall':
primes.c:23:35: error: lvalue required as left operand of assignment
   23 |                     if( prime % i = 0 ){
      |                                   ^
compilation terminated due to -Wfatal-errors.
make: *** [primes] Error 1

"prime % i" ist keine Variable und kann daher kann man ihm nicht den Wert 0 zuordnen,
der eigentliche Fehler ist, dass hier ein Vergleich (==) stehen sollte.
```

<br>
<br>
<br>

```bash
Fehlermeldung 5:
primes.c: In function 'print_primes_in_intervall':
primes.c:29:13: warning: this 'if' clause does not guard... [-Wmisleading-indentation]
   29 |             if(is_a_prime)
      |             ^~
primes.c:31:17: note: ...this statement, but the latter is misleadingly indented as if
it were guarded by the 'if'
   31 |                 printf("Die %2d. Primzahl im Intervall:
   [%d,%d)] ist: %2d\n", count, lower, upper, prime);
      |                 ^~~~~~
primes.c:36:1: warning: control reaches end of non-void function [-Wreturn-type]
   36 | }

Der Compiler weißt daraufhin, dass das printf nicht zur if-Schleife gehört,
die Einrückung dies jedoch vermuten lässt (es fehlen also Klammern,
da printf zur if-Schleife gehört). Außerdem wird in Zeile 36 das Ende der Funktion
erreicht, wobei es nicht zwingend eine Rückgabe gibt, obwohl die Funktion eine
Rückgabe haben sollte. Es fehlt also eine Rückgabe, wenn die if-Bedingung falsch ist:
else {
    return 0;
}
```
