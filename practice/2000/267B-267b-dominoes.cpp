#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;      // Destination vertex
    int id;      // Domino index
};

struct Domino {
    int left, right;
};

vector<Edge> graph[7];          // Vertices are only 0..6
vector<Domino> dominoes;
vector<bool> used;
vector<pair<int, char>> answer;

void dfs(int u) {

    while (!graph[u].empty()) {

        Edge e = graph[u].back();
        graph[u].pop_back();

        // Skip if this domino has already been used
        if (used[e.id])
            continue;

        used[e.id] = true;

        dfs(e.to);

        // Determine whether this domino was flipped
        if (dominoes[e.id].left == u)
            answer.push_back({e.id + 1, '+'});
        else
            answer.push_back({e.id + 1, '-'});
    }
}

int main() {

    int n;
    cin >> n;

    dominoes.resize(n);
    used.assign(n, false);

    vector<int> degree(7, 0);

    // Read dominoes
    for (int i = 0; i < n; i++) {

        int a, b;
        cin >> a >> b;

        dominoes[i] = {a, b};

        graph[a].push_back({b, i});
        graph[b].push_back({a, i});

        degree[a]++;
        degree[b]++;
    }

    // Count odd-degree vertices
    int odd = 0;
    int start = -1;

    for (int i = 0; i < 7; i++) {

        if (degree[i] % 2 == 1) {
            odd++;
            start = i;
        }

        if (start == -1 && degree[i] > 0)
            start = i;
    }

    // Euler path impossible
    if (!(odd == 0 || odd == 2)) {
        cout << "No solution\n";
        return 0;
    }

    // Run Hierholzer
    dfs(start);

    // Did we use every domino?
    if ((int)answer.size() != n) {
        cout << "No solution\n";
        return 0;
    }

    reverse(answer.begin(), answer.end());

    for (auto p : answer)
        cout << p.first << " " << p.second << "\n";

    return 0;
}