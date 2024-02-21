#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xgerge01
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1) jenom ulice, ktere existuji, mohou byt pouzity
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    for (unsigned i = 0; i < num_of_streets; ++i) {
        Clause* cl = create_new_clause(formula);
        for (unsigned j = 0; j < num_of_streets; ++j) {
            add_literal_to_clause(cl, true, i, streets[j].crossroad_from, streets[j].crossroad_to);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2) v každém kroku je nejvýše jedna ulice
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (unsigned i = 0; i < num_of_streets; ++i) {
        for (unsigned z = 0; z < num_of_crossroads; ++z) {
            for (unsigned k = 0; k < num_of_crossroads; ++k) {     
                unsigned k1_start = k + 1;   
                for (unsigned z1 = z; z1 < num_of_crossroads; ++z1) {
                    for (unsigned k1 = k1_start; k1 < num_of_crossroads; ++k1) {
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, i, z1, k1);
                    }
                    k1_start = 0;
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3) všechny ulice jsou navštíveny
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (unsigned i = 0; i < num_of_streets-1; ++i) {
        for (unsigned z = 0; z < num_of_crossroads; ++z) {
            for (unsigned k = 0; k < num_of_crossroads; ++k) {
                Clause *cl = create_new_clause(formula);
                add_literal_to_clause(cl, false, i, z, k);
                for (unsigned k1 = 0; k1 < num_of_crossroads; ++k1) {
                    add_literal_to_clause(cl, true, i + 1, k, k1);
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4) ulice sa nesmí opakovat
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
    for (unsigned i = 0; i < num_of_streets; ++i) {
        for (unsigned z = 0; z < num_of_crossroads; ++z) {
            for (unsigned k = 0; k < num_of_crossroads; ++k) {
                for (unsigned j = i + 1; j < num_of_streets; ++j) {
                    Clause* cl = create_new_clause(formula);
                    add_literal_to_clause(cl, false, i, z, k);
                    add_literal_to_clause(cl, false, j, z, k);
                }
            }
        }
    }
}
