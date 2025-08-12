#include <bits/stdc++.h>
using namespace std;

struct State {
    int jug1, jug2;   
    vector<string> path; 
};

void waterJugBFS(int cap1, int cap2, int target) {
    set<pair<int, int>> visited; 
    queue<State> q;

    State start = {0, 0, {}}; 
    q.push(start);
    visited.insert({0, 0});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        int x = cur.jug1, y = cur.jug2;

        if (x == target || y == target) {
            cout << "Solution found in " << cur.path.size() << " steps:\n";
            for (auto &step : cur.path) {
                cout << step << "\n";
            }
            cout << "Final State: (" << x << ", " << y << ")\n";
            return;
        }

        vector<State> nextStates;

        nextStates.push_back({cap1, y, cur.path});
        nextStates.back().path.push_back("Fill Jug1");

        nextStates.push_back({x, cap2, cur.path});
        nextStates.back().path.push_back("Fill Jug2");

        nextStates.push_back({0, y, cur.path});
        nextStates.back().path.push_back("Empty Jug1");

        nextStates.push_back({x, 0, cur.path});
        nextStates.back().path.push_back("Empty Jug2");

        {
            int pour = min(x, cap2 - y);
            nextStates.push_back({x - pour, y + pour, cur.path});
            nextStates.back().path.push_back("Pour Jug1 → Jug2");
        }

        {
            int pour = min(y, cap1 - x);
            nextStates.push_back({x + pour, y - pour, cur.path});
            nextStates.back().path.push_back("Pour Jug2 → Jug1");
        }

        for (auto &state : nextStates) {
            if (!visited.count({state.jug1, state.jug2})) {
                visited.insert({state.jug1, state.jug2});
                q.push(state);
            }
        }
    }

    cout << "No solution possible.\n";
}

int main() {
    int cap1, cap2, target;
    cout << "Enter capacity of Jug1: ";
    cin >> cap1;
    cout << "Enter capacity of Jug2: ";
    cin >> cap2;
    cout << "Enter target amount of water: ";
    cin >> target;

    if (target > max(cap1, cap2)) {
        cout << "Target can't be greater than both jug capacities.\n";
        return 0;
    }

    waterJugBFS(cap1, cap2, target);

    return 0;
}
