Úvod
----

Váš strýček Pat Vás požádal o pomoc s řešením svého problému. Jako
pošťák vstává brzy ráno a i se svým kocourem vyráží rozvážet poštu.
Dokud byl ještě mladý a plný sil, příliš se netrápil s plánováním své
trasy. Nyní, těsně před důchodem, si Vás jednoho dne zavolal s
následující prosbou:

„Poslyš, ty rozumíš těm počítačům, nemohl/a bys mi nějak pomoct s
plánováním trasy tak, abych projel každou ulicí ve městě, kde mám
rozvést poštu právě jednou a nemusel se neustále někam vracet?“

Díky znalostem nabytým během svého studia jste se rozhodl/a problém
řešit pomocí převodu na problém splnitelnosti ve výrokové logice s
použitím SAT solveru.

Zadání
------

*Instance* problému se skládá z čísla 
<span class="math inline">*K*</span>, 
<span class="math inline">*K* &gt; 0</span>, značícího počet křižovatek a seznamu 
<span class="math inline">*S*</span> ulic délky 
<span class="math inline">*U*</span>, 
<span class="math inline">*U* &gt; 0</span>. Čísla 
<span class="math inline">0, 1, …, *K* − 1</span> reprezentují křižovatky.
Ulice je reprezentována dvojicí čísel 
<span class="math inline">(*z*, *k*)</span>, kde 
<span class="math inline">*z*</span> je její začátek a 
<span class="math inline">*k*</span> je její konec (platí tedy 
<span class="math inline">0 ≤ *z* &lt; *K*</span> a 
<span class="math inline">0 ≤ *k* &lt; *K*</span>). Zadaný seznam ulic je tedy formy 
<span class="math inline">*S* = (*z*<sub>0</sub>, *k*<sub>0</sub>), …, (*z*<sub>*U* − 1</sub>, *k*<sub>*U* − 1</sub>)</span>.
Pro jednoduchost je ulice vždy průjezdná pouze jedním směrem, je tedy
identifikována svou počáteční a koncovou křižovatkou; mezi dvěmi
křižovatkami dále existuje v jednom směru nejvýše jedna ulice.  
*Řešením* problému je cesta, která prochází přes každou zadanou ulici
právě jednou (začínat může kdekoliv).

Vaším úkolem je vytvořit program, který pro instanci tohoto problému
vygeneruje formuli, jejíž modely jsou právě řešeními dané instance. K
dispozici již máte kostru (níže), která se stará o zpracování vstupu a
generování formule ve formátu DIMACS 
(popis např. [zde](https://www.fit.vutbr.cz/study/courses/IZLO/public/sat/)).

V rámci kostry již máte připraveno kódování problému do výrokových proměnných. 
Pro každou trojici čísel 
<span class="math inline">*i*, *z*, *k*</span>, kde 
<span class="math inline">0 ≤ *i* &lt; *U*</span>, 
<span class="math inline">0 ≤ *z* &lt; *K*</span>, a 
<span class="math inline">0 ≤ *k* &lt; *K*</span>, máme proměnnou 
<span class="math inline">*x*<sub>*i*, *z*, *k*</sub></span> s následující sémantikou:  
  
<span class="math inline">*x*<sub>*i*, *z*, *k*</sub> = 1 ⇔ </span> V
<span class="math inline">*i*</span>-tém kroce cesty je zvolena ulice začínající v křižovatce 
<span class="math inline">*z*</span> a končící v křižovatce 
<span class="math inline">*k*</span>.  
  
Vaším úkolem je doplnit kód tří funkcí v souboru `code/add_conditions.c`, 
které se starají o generování následujících podmínek:

1.  *V každém kroku cesty je zvolena alespoň jedna* ***existující*** *ulice.* 
    Generování této formule je potřeba doplnit do funkce `at_least_one_valid_street_for_each_step(...)`.

2.  *V každém kroku cesty je zvolena maximálně jedna ulice.* 
    Generování této formule je potřeba doplnit do funkce `at_most_one_street_for_each_step(...)`.

3.  *Ulice v rámci cesty na sebe navazují.* Přesněji, pokud ulice 
    <span class="math inline">(*z*, *k*)</span> je 
    <span class="math inline">*i*</span>-tým krokem cesty, kde 
    <span class="math inline">0 ≤ *i* &lt; *U* − 1</span>, potom ulice v kroce
    <span class="math inline">*i* + 1</span> začíná v 
    <span class="math inline">*k*</span>. 
    Generování této formule doplňte do funkce `streets_connected(...)`.

4.  *Žádná ulice není navštívená vícekrát než jednou.* 
    Generování této podmínky je již implementováno ve funkci `streets_do_not_repeat(...)` jako ukázka. 
    Jinými slovy, pro každé dva různé kroky cesty 
    <span class="math inline">*i* ≠ *j*</span> a každou dvojici křižovatek 
    <span class="math inline">(*z*, *k*)</span>, ulice daná 
    <span class="math inline">(*z*, *k*)</span> může být zvolena v nejvýše jednom z kroků 
    <span class="math inline">*i*</span> a 
    <span class="math inline">*j*</span>.

Výše zmíněné funkce jsou jediné části kódu, které mají být modifikovány.

Formát vstupu
-------------

Instance problému je popsána v následujícím textovém formátu. Na první
řádce souboru se nachází hlavička obsahující přesně dvě přirozená čísla
udávající postupně celkový počet křižovatek a celkový počet ulic.
Následuje seznam ulic, kde se na každém řádku nachází jedna ulice
reprezentovaná jako dvojice čísel (v rozsahu vymezeném hlavičkou):

    <pocet_krizovatek> <pocet_ulic>

    <zacatek_ulice_1> <konec_ulice_1>
    <zacatek_ulice_2> <konec_ulice_2>
    ...

Konkrétní příklad vstupu je následující soubor:

    4 4

    0 1
    1 2
    2 1
    2 3

Pro tento vstup neexistuje řešení neboť ulici 
<span class="math inline">(1, 2)</span> je potřeba projít dvakrát.

Generování formulí
------------------

Jelikož formát DIMACS pracuje s proměnnými indexovanými přirozenými čísly, proměnná 
<span class="math inline">*x*<sub>*i*, *z*, *k*</sub></span> je převedena na proměnnou s indexem 
<span class="math inline">*n*</span>, kde 
<span class="math inline">*n* = *i* ⋅ *K*<sup>2</sup> + *z* ⋅ *K* + *k* + 1</span>.
S těmito proměnnými však nebudete pracovat přímo, ale pomocí funkcí
popsaných v následujícím odstavci. Nicméně způsob reprezentace
proměnných se může hodit, pokud si budete chtít projít vygenerovaný
DIMACS soubor (ve vygenerovaném souboru jsou na řádcích začínajících
symbolem `c` komentáře, kde je kopie vstupního problému a popis mapování
čísel proměnných na kroky a ulice).

Všechny formule ze zadání je potřeba vygenerovat v konjunktivní normální
formě (CNF), která je standardním vstupem SAT solverů. Pro reprezentaci
formule jsou již v kostře projektu vytvořeny potřebné struktury. Pro
manipulaci s těmito strukturami jsou k dispozici následující funkce:

-   `Clause *create_new_clause(CNF *f)` 
    – Vytvoří novou prázdnou (disjunktivní) klauzuli ve formuli `f`. **POZOR**: prázdná klauzule je ekvivalentní 0 (`false`).

-   `void add_literal_to_clause(Clause *c, bool is_positive, unsigned i, unsigned k, unsigned z)`
    – Vloží do klauzule `c` literál 
    <span class="math inline">*x*<sub>*i*, *k*, *z*</sub></span> (pokud `is_positive = true`), nebo 
    <span class="math inline">¬*x*<sub>*i*, *k*, *z*</sub></span> (pokud`is_positive = false`).

Testování
---------

Referenčním SAT solverem je
MiniSat<sup>1</sup>.
Na linuxových systémech založených na Debianu lze tento nástroj
nainstalovat jednoduše příkazem `apt-get install minisat`, na Windows
lze použít stejný postup ve
WSL<sup>2</sup>,
na macOS lze použít `brew install minisat`. Pro vyzkoušení lze také
využít [online
rozhraní](https://www.fit.vutbr.cz/study/courses/IZLO/public/sat/) (pak
ale nelze využít automatické testy popsané níže).

K ověření základní funkčnosti vašeho řešení je možné použít dva
přiložené skripty. Tyto skripty vyžadují `python3` a nainstalovaný
MiniSat dostupný v `PATH`. Po přeložení vašeho řešení je možné využít
skript `run.sh`, který spustí vaše řešení nad vstupním souborem a
následně spustí SAT solver nad vygenerovanou formulí. V případě, že
vygenerovaná formule je splnitelná, skript vypíše model jako lidsky
čitelné řešení problému (jednotlivé kroky cesty) a zkontroluje jestli
model splňuje podmínky specifikované zadáním. V případě, že ne, je
vypsána první porušená podmínka. Příkazem `make test` je možné ověřit
základní funkcionalitu vašeho řešení na jednoduchých vstupech. Tyto
vstupy lze nalézt ve složkách `tests/sat` a `tests/unsat`.

Další pokyny a doporučení
-------------------------

-   Potřebné formule jdou vytvořit téměř přímo v CNF, nemělo by být
    potřeba aplikovat distributivní zákony pro úpravu do CNF. Před
    samotným programováním si zkuste formule nejprve napsat na papír.

-   Generování formulí není nutné optimalizovat. Vaše řešení nebude
    testováno na větších vstupech než jsou ty, které máte k dispozici.

-   Odevzdáváte pouze soubor `add_conditions.c` do IS VUT.

-   Své řešení vypracujte samostatně. Odevzdané projekty budou
    kontrolovány proti plagiátorství, za nějž se považuje i sdílení
    vlastního řešení s ostatními studenty.

-   Před odevzdáním si zkontrolujte zda váš soubor jde opravdu přeložit
    s přiloženým Makefile.

-   Případné dotazy směřujte do fóra „Fórum k látce a projektům“.

------------------------------------------------------------------------

1.  http://minisat.se/
2.  https://ubuntu.com/wsl
