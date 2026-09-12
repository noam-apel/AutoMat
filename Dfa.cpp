//
// Created by Noam Apelfeld on 12/09/2026.
//

#include "Dfa.h"
#include "set"

DFA DFA::from_nfa(const NFA &nfa) {
    std::map<std::set<int>, int> dfa_state_ids;
    std::vector<std::set<int>> worklist;
    DFA dfa;
    int next_dfa_id = 0;
    std::set<char> alphabet;
    alphabet = nfa.get_alphabet();

    std::vector<State *> start_closure = nfa.epsilon_closure({nfa.start_state});
    std::set<int> start_set;
    for (State *s: start_closure) {
        start_set.insert(s->id);
    }
    dfa_state_ids[start_set] = next_dfa_id++;
    worklist.push_back(start_set);
    dfa.transitions.emplace_back();
    dfa.is_accepting.push_back(start_set.contains(nfa.end_state->id));

    while (!worklist.empty()) {
        std::set<int> current_set = worklist.back();
        worklist.pop_back();
        int curr_dfa_id = dfa_state_ids[current_set];

        std::vector<State *> current_closure;
        for (int state_id: current_set) {
            current_closure.push_back(nfa.all_states[state_id].get());
        }

        for (char c: alphabet) {
            std::vector<State *> move_targets;
            for (State *s: current_closure) {
                for (const auto &tr: s->transitions) {
                    if (tr.first == c) {
                        move_targets.push_back(tr.second);
                    }
                }
            }

            if (!move_targets.empty()) {
                auto next_closure = nfa.epsilon_closure(move_targets);
                std::set<int> next_set;
                for (State *s: next_closure) {
                    next_set.insert(s->id);
                }

                int target_dfa_id;
                auto it = dfa_state_ids.find(next_set);
                if (it == dfa_state_ids.end()) {
                    target_dfa_id = next_dfa_id++;
                    dfa_state_ids[next_set] = target_dfa_id;
                    worklist.push_back(next_set);

                    dfa.transitions.emplace_back();
                    dfa.is_accepting.push_back(next_set.contains(nfa.end_state->id));
                }
                else {
                    target_dfa_id = it->second;
                }

                dfa.transitions[curr_dfa_id][c] = target_dfa_id;
            }

        }


    }
    return dfa;

}
