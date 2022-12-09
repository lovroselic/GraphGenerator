// https://www.codeabbey.com/index/task_view/graph-generator
// https://www.codeabbey.com/index/task_view/linear-congruential-generator
// https://www.codeabbey.com/index/task_view/dijkstra-in-the-network

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>
#include <numeric>
#include <tuple>
#include <regex> 

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class Node {
public:
	size_t id;
	int distance;
	bool visited;
	vector<size_t> edges;
	map<size_t, int> weights;
	int prev;

	Node(size_t id) {
		this->id = id;
		this->distance = numeric_limits<int>::max();
		this->visited = false;
		this->prev = -1;
	}

	int sumWeights() {
		int sum = 0;
		for (auto e : this->edges) {
			sum += this->weights[e];
		}
		return sum;
	}
};

class Graph {
public:
	vector<Node*> nodes;
	Graph(int N) {
		for (size_t i = 0; i < N; i++) {
			this->add();
		}
	}

	void display() {
		cout << "Graph display: " << endl;
		for (auto node : this->nodes) {
			cout << "node: " << node->id + 1 << ":";
			for (auto e : node->edges) {
				cout << " " << e + 1 << " - " << node->weights[e];
			}
			cout << "\t distance: " << node->distance;
			cout << "\t visited: " << boolalpha << node->visited;
			cout << "\t prev: " << node->prev;
			cout << endl;
		}
	}

	vector<int> sumWeights() {
		vector<int> sumWeights;
		for (auto node : this->nodes) {
			sumWeights.push_back(node->sumWeights());
		}
		return sumWeights;
	}

	void add() {
		size_t next = this->nodes.size();
		Node* node = new Node(next);
		this->nodes.push_back(node);
	}

	void link(size_t source, size_t target, int weight) {
		this->nodes[source]->edges.push_back(target);
		this->nodes[target]->edges.push_back(source);
		this->nodes[source]->weights[target] = weight;
		this->nodes[target]->weights[source] = weight;
	}

	bool isLinked(size_t source, size_t target) {
		return find(this->nodes[source]->edges.begin(), this->nodes[source]->edges.end(), target) != this->nodes[source]->edges.end();
	}

	void setDistance(size_t nodeIndex, int distance) {
		nodes[nodeIndex]->distance = distance;
	}

	int getDistance(size_t nodeIndex) {
		return nodes[nodeIndex]->distance;
	}

	void setVisited(size_t nodeIndex) {
		nodes[nodeIndex]->visited = true;
	}

	int minUnvisited() {
		int min = numeric_limits<int>::max();
		int minIndex = -1;
		for (auto node : this->nodes) {
			if (!node->visited) {
				if (node->distance < min) {
					min = node->distance;
					minIndex = node->id;
				}
			}
		}
		return minIndex;
	}

	vector<size_t> getUnvisitedNeighbours(size_t nodeIndex) {
		vector<size_t> NB;
		for (auto e : this->nodes[nodeIndex]->edges) {
			Node* node = this->nodes[e];
			if (!node->visited) {
				NB.push_back(e);
			}
		}
		return NB;
	}

	int getWeight(size_t nodeIndex, size_t edge) {
		return nodes[nodeIndex]->weights[edge];
	}

	void setPrev(size_t nodeIndex, int prev) {
		this->nodes[nodeIndex]->prev = prev;
	}

	vector<int> getDistances() {
		vector<int> distances;
		for (auto node : this->nodes) {
			distances.push_back(node->distance);
		}
		return distances;
	}
};

long long int LinearCongruentialGenerator(int A, int C, int M, int seed);
void Dijkstra(Graph G, size_t root);

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Dijkstra v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	//printVector(raw_data);
	/***********************/

	vector<int> data = splitToInt(raw_data[0], " ");
	//printVector(data);
	int N = data.at(0);
	int X = data.at(1);
	size_t R = data.at(2);
	size_t V = 0;
	int D = 0;
	const int A = 445;
	const int C = 700001;
	const int M = 2097152;

	Graph G = Graph(N);

	for (size_t i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			X = LinearCongruentialGenerator(A, C, M, X);
			V = X % N + 1;
			X = LinearCongruentialGenerator(A, C, M, X);
			D = X % N + 1;
			if (i == V - 1) continue;
			if (G.isLinked(i, V - 1)) continue;
			G.link(i, V - 1, D);
		}
	}

	Dijkstra(G, R - 1);
	//G.display();

	cout << "\nSolution: " << joinVector(G.getDistances()," ") << endl;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

long long int LinearCongruentialGenerator(int A, int C, int M, int seed) {
	return ((static_cast<long long>(A) * seed) + C) % M;
}

void Dijkstra(Graph G, size_t root) {
	G.setDistance(root, 0);
	while (true) {
		int current = G.minUnvisited();
		if (current == -1) break;
		G.setVisited(current);
		int currentDistance = G.getDistance(current);
		vector<size_t> NB = G.getUnvisitedNeighbours(current);
		for (auto n : NB) {
			int sumDistance = G.getWeight(current, n) + currentDistance;
			if (sumDistance < G.getDistance(n)) {
				G.setDistance(n, sumDistance);
				G.setPrev(n, current);
			}
		}
	}
}