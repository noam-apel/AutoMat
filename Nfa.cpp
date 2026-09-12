//
// Created by Noam Apelfeld on 12/09/2026.
//

#include <queue>
#include "NFA.h"

State *NFA::create_state() {
    all_states.push_back(std::make_unique<State>(next_id++));
    return all_states.back().get();
}

State_Pair NFABuilder::create_literal(char c) {
    State *start = instance.create_state();
    State *end = instance.create_state();
    start->transitions.push_back({c, end});
    instance.add_to_alphabet(c);
    return State_Pair(start, end);
}

State_Pair NFABuilder::create_concat(State_Pair left, State_Pair right) {
    left.end->epsilon_transitions.push_back(right.start);
    return State_Pair(left.start, right.end);
}

State_Pair NFABuilder::create_union(State_Pair left, State_Pair right) {
    State *new_start = instance.create_state();
    State *new_end = instance.create_state();

    new_start->epsilon_transitions.push_back(left.start);
    new_start->epsilon_transitions.push_back(right.start);
    left.end->epsilon_transitions.push_back(new_end);
    right.end->epsilon_transitions.push_back(new_end);

    return State_Pair(new_start, new_end);
}

State_Pair NFABuilder::create_star(State_Pair p) {
    State *new_start = instance.create_state();
    State *new_end = instance.create_state();

    new_start->epsilon_transitions.push_back(new_end);
    new_start->epsilon_transitions.push_back(p.start);
    p.end->epsilon_transitions.push_back(p.start);
    p.end->epsilon_transitions.push_back(new_end);

    return State_Pair(new_start, new_end);
}

NFA NFABuilder::build(State_Pair final_pair) {
    instance.start_state = final_pair.start;
    instance.end_state = final_pair.end;
    return std::move(instance);
}

std::vector<State *> NFA::epsilon_closure(std::vector<State *> states) const {
    std::vector<bool> visited(all_states.size(), false);
    std::vector<State *> res;
    for (State *s: states) {
        if (s && !visited[s->id]) {
            visited[s->id] = true;
            res.push_back(s);
        }
    }

    while (!states.empty()) {
        State *curr = states.back();
        states.pop_back();
        for (State *nxt: curr->epsilon_transitions) {
            if (!visited[nxt->id]) {
                visited[nxt->id] = true;
                states.push_back(nxt);
                res.push_back(nxt);
            }
        }
    }


    return res;
}

bool NFA::match(const std::string &input) const {
    std::vector<State *> current_states = epsilon_closure({this->start_state});
    for (char c: input) {
        std::vector<State *> next_states;
        for (State *s: current_states) {
            for (const auto &tr: s->transitions) {
                if (tr.first == c) {
                    next_states.push_back(tr.second);
                }
            }
        }
        current_states = epsilon_closure(next_states);
        if (current_states.empty()) {
            return false;
        }
    }

    for (State *s: current_states) {
        if (s == end_state) {
            return true;
        }
    }
    return false;
}