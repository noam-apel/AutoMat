//
// Created by Noam Apelfeld on 12/09/2026.
//

#ifndef AUTOMAT_NFA_H
#define AUTOMAT_NFA_H

#include <memory>
#include <utility>
#include <vector>
#include <set>

struct State {
    int id;
    std::vector<std::pair<char, State *>> transitions;
    std::vector<State *> epsilon_transitions;

    explicit State(int id) : id(id) {}
};

struct State_Pair {
    State *start = nullptr;
    State *end = nullptr;

    State_Pair() = default;

    State_Pair(State *s, State *e) : start(s), end(e) {}
};

class NFA {
private:
    std::vector<std::unique_ptr<State>> all_states;
    int next_id = 0;
    std::vector<State *> epsilon_closure(std::vector<State *> states) const;
    std::set<char> alphabet;

public:
    State *start_state = nullptr;
    State *end_state = nullptr;
    State *create_state();
    bool match(const std::string &input) const;

    void add_to_alphabet(char c) {
        alphabet.insert(c);
    }

    const std::set<char> &get_alphabet() const {
        return alphabet;
    }
};

class NFABuilder {
private:
    NFA instance;

public:
    State_Pair create_literal(char c);
    State_Pair create_concat(State_Pair left, State_Pair right);
    State_Pair create_union(State_Pair left, State_Pair right);
    State_Pair create_star(State_Pair p);

    NFA build(State_Pair final_pair);
};

#endif // AUTOMAT_NFA_H