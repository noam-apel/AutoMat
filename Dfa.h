//
// Created by Noam Apelfeld on 12/09/2026.
//

#ifndef AUTOMAT_DFA_H
#define AUTOMAT_DFA_H


#include <vector>
#include <map>
#include <string>
#include "Nfa.h"

struct DFA {
    int start_state = 0;
    std::vector<bool> is_accepting;
    std::vector<std::map<char, int>> transitions;

    bool match(const std::string &input) const;

    static DFA from_nfa(const NFA &nfa);

};


#endif //AUTOMAT_DFA_H
