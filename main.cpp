#include <iostream>
#include "vector"
#include "limits"
#include "map"

class Graph {
public:
    Graph(long long n_) : n(n_){
        visited = std::vector<bool>(n, false);
        distance = std::vector<std::vector<unsigned long long>> (n, std::vector<unsigned long long>(n, std::numeric_limits<unsigned long long>::max()));
    };
    void AddEdge(long long v, long long nv, unsigned long long weight) {
        if (v != nv) {
            distance[v][nv] = std::min(weight, distance[v][nv]);
            distance[nv][v] = std::min(weight, distance[nv][v]);
        }
    }
    void floyd() {
        for (long long k = 0; k < n; ++k) {
            for (long long i = 0; i < n; ++i) {
                for (long long j = 0; j < n; ++j) {
                    if (distance[i][k] != std::numeric_limits<unsigned long long>::max() &&
                        distance[k][j] != std::numeric_limits<unsigned long long>::max()) {
                        distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            distance[i][i] = 0;
        }
    }
    void Result() {
        unsigned long long r = ULONG_LONG_MAX;
        unsigned long long d = 0;
        std::vector<unsigned long long> extrnasitet;
        std::vector<int> centers;
        for (auto i: distance) {
            unsigned long long temp_m = 0;
            for (auto j: i) {
                if (j != std::numeric_limits<unsigned long long>::max()) {
                    temp_m = std::max(temp_m, j);
                }
            }
            extrnasitet.push_back(temp_m);
        }

        for (auto i: extrnasitet) {
            r = std::min(r, i);
            d = std::max(d, i);
        }
        for (int i = 0; i < n; ++i) {
            if (extrnasitet[i] == r) {
                centers.push_back(i);
            }

        }
        std::cout << "Radius: " << r << '\n' << "Diametr: " << d << '\n' << "Centers: ";
        for (auto  i: centers) {
            std::cout << i + 1 << ' ';
        }
    }
    void PrintAll () {
        for (long long i = 0; i < n; ++i) {
            std::cout << i << ": ";
            for (long long j = 0; j < n; ++j) {
                std::cout << distance[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    long long n;
    std::vector<bool> visited;
    std::vector<std::vector<unsigned long long>> distance;
};



int main() {
    long long n,m;
    std::cin >> n >> m;
    Graph graph(n);
    for (long long i = 0; i < m; ++i) {
        long long t1, t2;
        std::cin >> t1 >> t2;
        --t1;
        --t2;
        graph.AddEdge(t1, t2, 1);
    }

    graph.floyd();
    graph.Result();
    return 0;
}
