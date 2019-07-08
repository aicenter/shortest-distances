Contraction hierarchies implementation in C++
=============================================

Projekt obsahuje implementaci techniky `Contraction Hierarchies` inspirovanou článkem "Contraction Hierarchies: Faster and Simpler Hierarchical
Routing in Road Networks" od čtveřice autorů Robert Geisberger, Peter Sanders, Dominik Schultes a Daniel Delling. Implementace umí předzpracovat
zadaný graf, tedy vytvořit samotnou 'Contraction Hierarchy' a umí jí pak i použít pro vyhodnocování dotazů (queries). Momentálně jsou funkční
dotazy na vzdálenost ('vrať nejkratší vzdálenost z bodu a do bodu b'). Teoreticky by se díky 'Contraction Hierarchies' dala vracet i samotná
nejkratší cesta (tedy kromě vzdálenosti i posloupnost vrcholů na nejkratší cestě), to ale momentálně není korektně implementováno.

Kompilace
---------
- Stáhněte si aktuální `master`
- V libovolném IDE něco jako 'build project from sources'
- Odeberte z projektu soubory `RandomGraphGenerator.cpp`, `RandomTripsGenerator.cpp` a `AlternativeRandomTripsGenerator.cpp`. Jedná se o samostatné programy, které se dají samostatně zkompilovat a generují náhodné grafy nebo náhodné dvojice source - target v určité rozsahu. Dají se použít pro debugování. Pokud je necháte v projektu, nejspíše dostanete chybovou hlášku něco ve smyslu "multiple main definitions".

Alternativně se dá program zkompilovat s využitím přiloženého `Makefile`. Ten funguje s masterem při commitu s SHA:'c20503730a7c1c3aee89c9a92ca436c52e85417b', byl ovšem vygenerován ručně, takže není zaručeno, že bude fungovat i v budoucnu. S pomocí Makefilu se dá program zkompilovat i z příkazové řádky:
- Ve složce s Makefilem stačí použít příkaz `make compile`
- Pro smazání všech vygenerovaných souborů a opětovnou čistou kompilaci programu stačí použít příkaz `make compile` následovaný opět příkazem `make compile`
- Tím se vygeneruje spustitelný soubor `chTest` v aktuálním souboru.
- Makefile implicitně používá `g++` ke kompilaci. Pro použití jiného kompilátoru (nebo jiných přepínačů) stačí v Makefilu přepsat 'CC' a 'CFLAGS' na požadované hodnoty.
 

Projekt nepouzívá žádné externí knihovny (pouze stl), takže by měl bez větších potíží fungovat. 

Použití
-------
Momentálně se při každém spuštění programu provede 'odkomentovaná' funkce v 'main.cpp'. Do budoucna by bylo vhodné implementovat nějaké user interface, alespoň na úrovni command line, ale to jsem nestíhal. Momentálně je tedy potřeba při každé změně použití program znovu překompilovat.

### Generování Contraction Hierarchy
Řeší metoda `constructDDSGCH()`. Ta dostane graf zadaný ve formátu implementační soutěže DIMACS (popsán níže) a vygeneruje z něj soubor obsahující vygenerovanou 'Contraction Hierarchy' s příponou ".ch". U velkých grafů může předzpracování trvat poměrně dlouho a být celkem náročné na paměť.

Co kde nastavit ve funkci DDSGCH():
- Na řádce kde je `Loader graphLoader = Loader("xyz");` tak na místo 'xyz' doplňte cestu k vašemu vstupnímu souboru (včetně přípony). Soubor musí být korektní soubor v daném formátu, program neprovádí kontroly validity vstupního souboru.
- Na řádce kde je `graph->flushInDdsgFormat("xyz");` tak na místo 'xyz' doplnit cestu k souboru, kam se uloží daná 'Contraction Hierarchy'. K názvu souboru je automaticky přidána přípona ".ch".

### Benchmarking
Metody `runCHBenchmark()` načte 'Contraction Hierarchy' a nechá ji vyhodnotit sadu dotazů dodanou dalším souborem. Formát souboru s dotazy je popsán níže a dá se též vygenerovat pomocí 'RandomTripsGenerator.cpp'. Funkce nechá 'Contraction Hierarchy' vyhodnotit po jednom všechny dané dotazy a vypíše celkový čas (v sekundách). Průměrný čas na query se dá snadno dopočíst vydělením vráceného času počtem dotazů. V tomto případě se posílají dotazy pouze na vzdálenost (nezajímá nás posloupost vrcholů na nejkratší cestě). 
Měří se sice pouze čas vyhodnocování dotazů, ale pro alespoň nějakou přesnost měření by bylo asi vhodné nechat test provést víckrát a ověřit, zda se časy moc neliší, plus testování provádět ideálně na větší sadě dotazů.

Co kde nastavit ve funkci 'runCHBenchmark()':
- Na řádce kde je `Loader tripsLoader = Loader("xyz");` tak na místo 'xyz' doplňte cestu k souboru s dotazy (v korektním formátu).
- Na řádce kde je `DDSGLoader loader = DDSGLoader("xyz");` tak na místo 'xyz' doplňte cestu k souborem s 'Contraction Hierarchy' (včetně přípony).

### Porovnání 'Contraction Hierarchies' s 'Dijkstrou'
Metoda `compareCHWithDijkstra()` umožňuje porovnat 'Contraction Hierarchies' s implementací 'Dijkstrova algoritmu'. Program kromě časů obou algoritmů vrátí i speedup 'CH' oproti 'Dijkstrovi'. Pro tuto funkci musí být k dispozici jak originální vstupní graf pro 'Dijkstru', tak soubor s předzpracovanou 'Contraction Hierarchy'.
Navíc je potřeba i soubor se sadou dotazů, které budou použity pro měření (ve stejném formátu jako pro 'runCHBenchmark()'). Opět je vhodné použít soubor s větším počtem dotazů. Tato funkce může být použita i v případě, že by se upravovali 'Conntraction Hierarchies', protože na konci i porovná, jestli oba algoritmy vracely stejné vzdálenosti. Tedy pokud by v implementaci 'Contraction Hierarchies' byly nějaké chyby, pravděpodobně by se projevily zde, nebo by 'Dijkstra' vracel správné hodnoty, ale 'CH' už ne.

Co kde nastavit ve funkci 'compareCHWithDijkstra()'
- Na řádce kde je `Loader tripsLoader = Loader("xyz");` tak na místo 'xyz' doplňte cestu k souboru s dotazy (v korektním formátu).
- Na řádce kde je `DDSGLoader chLoader = DDSGLoader("xyz");` tak na místo 'xyz' doplňte cestu k souborem s 'Contraction Hierarchy' (včetně přípony).
- Na řádce kde je ` Loader dijkstraLoader = Loader("xyz);` tak na místo 'xyz' doplňte cestu k originálnímu grafu (bude použit pro Dijkstru).
 

Podobně fuguje i funkce 'compareMineWithReference()', která porovnává dvě 'Contraction Hierarchies' proti sobě. Ta se dá použít, pokud bych měl dvě 'Contraction Hierarchies' vygenerované různými algoritmy, a chtěl bych vyzkoušet, na které z nich jsou dotazy rychlejší.

### Odpovídání na dotazy
Pokud bych chtěl připravit 'Contraction Hierarchy', aby odpovídala na příchozí dotazy, potřebuji udělat pouze několik jednoduchých kroků:
- Pomocí `DDSGLoader loader = DDSGLoader("xyz");` kde na místo 'xyz' doplním cestu k souboru s 'Contraction Hierarchy' a následným zavoláním `IntegerFlagsGraph * ch = loader.loadFlagsGraph();` program načte 'Contraction Hierarchy' ze souboru a vytvoří z ní graf.
- Pomocí `IntegerCHDistanceQueryManager queryManager(*ch);` vytvořím 'queryManager', který si inicializuje všechny pomocné struktury.
- Každé následující volání `queryManager.findDistance(x, y);` kde 'x' a 'y' jsou dva vrcholy vrátí vzdálenost mezi těmito vrcholy. Je jedno, jak se tyto dva vrcholy získají, zda se načtou odněkud ze souboru, nebo třeba přijdou jako dotaz po síti. Je ovšem třeba, aby obě čísla byla validní, tedy z rozsahu 0 až n-1 kde 'n' je počet vrcholů v použitém grafu. Při hledání vzdálenosti už se toto nijak nekontroluje.

Popis vstupních formátů
-----------------------

### Formát grafu z implementační soutěže DIMACS 
(Ukázkové grafy v tomto formátu mohou být staženy zde: http://www.dis.uniroma1.it/challenge9/download.shtml)

- Soubor začíná řádkou `p sp n e` kde místo 'n' je číslo určující počet vrcholů a místo 'e' je číslo určující počet hran.
- Následuje 'e' řádek ve tvaru `a u v w` reprezentujících jednotlivé hrany, s tím že 'u' je číslo source uzlu, 'v' je číslo target uzlu a 'w' je váha hrany (délka, čas potřebný pro její projetí...). Čísla 'u' a 'v' musí být z rozsahu 1 až n. V rámci formátu pro soutěž DIMACS se vrcholy indexovaly od jedničky. Program indexuje vrcholy od nuly, takže se každý načtený vrchol automaticky sníží o 1. Hrany se načítají orientovaně, takže pokud chci mít hranu 'u <-> v' obousměrnou, musím jí zadat jako hranu z 'u' do 'v' a znovu jako hranu z 'v' do 'u'.
- Kdekoliv v soubrou se dále mouhou vyskytovat řádky začínající znakem `c`. Tyto řádky reprezentují komentáře a program je pouze zahazuje.


### Formát souboru s dotazy
- Na první řádce bude číslo `x` reprezentující počet párů source target (tedy dotazů)
- Následuje 'x' řádek z nichž každá obsahuje dvě čísla oddělená mezerou `a b` kde 'a' je source a 'b' je target. Oba vrcholy musí být z rozsahu 0 až n-1 kde 'n' je počet vrcholů v pouužitém grafu. Zde se vrcholy indexují od nuly.
- Pro vygenerování libovolně velké sady dotazů se dá využít soubor `RandomTripsGenerator.cpp`.

### Formát 'Contraction Hierarchies'
- Pro ukládání 'Contraction Hierarchy' se používá binární formát, který je stručně popsaný na konci souboru `DDSGLoader.h`.


Kde co hledat
-------------

### Předzpracování
- V podstatě za veškerý preprocessing grafu na 'Contraction Hierarchy' je zodpovědná třída `CHPreprocessor` s malou pomocí třídy `EdgeDifferenceManager`. Při předzpracování se používá `IntegerUpdateableGraph` pro reprezentaci grafu, což je třída, která umožňuje snadné přidávání a odebírání hran. Fungování jednotlivých metod je stručně popsáno v kódu vždy nad každou metodou.

### Dotazy
- Vyhodnocování 'Contraction Hierarchy' dotazů řeší třída `IntegerCHDistanceQueryManager`. Ten dostane reprezentaci 'Contraction Hierarchy' jakožto instanci třídy `IntegerFlagsGraph` a následně se na něj dají volat dotazy pomocí funkce `findDistance`. V rámci `IntegerFlagsGraph` je každá hrana uložena pouze jednou a sice u vrcholu s menším rankem v rámci 'Contraction Hierarchies' společně s flagy v kterém směru tato hrana existuje. Navíc tato reprezentace grafu obsahuje různé pomocné informace o jednotlivých vrcholech potřebné pro vyhodnocování dotazů.
- Třídy `IntegerCHDistanceQueryManager` řeší pouze dotazy na vzdálenost, tedy dotaz typu 'vrať nejkratší vzdálenost z bodu a do bodu b'. V budoucnu by třída `IntegerCHPathQueryManager` mohla vracet i posloupnost vrcholů na nalezené nejkratší cestě. Momentálně `IntegerCHPathQueryManager` nefunguje správně (nevrací správné cesty).

### Načítání
- Načítání grafů a sad dotazů řeší třída `Loader` a načítání 'Contraction Hierarchies' řeší `DDSGLoader`. Momentálně `Loader` podporuje pouze načítání grafu ve formátu z implementační soutěže DIMACS (popsáno výše). Pokud by byla potřeba generovat 'Contraction Hierarchy' i pro grafy v jiném formátu, jedna možnost je napsat v rámci `Loader` novou funkci, která by dokázala načíst graf v jiném formátu, tedy v podstatě načíst všechny hrany do instance `IntegerUpdateableGraph` (jak to funguje teď z formátu soutěže DIMACS je možno vidět v rámci metody `loadUpdateableGraph` třídy `Loader`). Druhá možnost je napsat konvertor, který dokáže převést graf z nějakého jiného formátu do formátu soutěže DIMACS. To by sice znamenalo další mezikrok při vytváření 'Contraction Hierarchy' z daného grafu v jiném formátu, ale zase by se nemuselo v podstatě vůbec zasahovat do kódu tohoto projektu a konvertor by mohl fungovat uplně odděleně.