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
	vector<size_t> edges;
	map<size_t, int> weights;

	Node(size_t id) {
		this->id = id;
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
		cout << "graph display: " << endl;
		for (auto node : this->nodes) {
			cout << "node: " << node->id + 1 << ":";
			for (auto e : node->edges) {
				cout << " " << e + 1 << " - " << node->weights[e];
			}
			cout << endl;
		}
	}

	vector<int> sumWeights() {
		vector<int> sumWeights;
		for (auto node : this->nodes) {
			sumWeights.push_back( node->sumWeights());
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
};

long long int LinearCongruentialGenerator(int A, int C, int M, int seed);

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Graph Generator v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	//printVector(raw_data);
	/***********************/

	vector<int> data = splitToInt(raw_data[0], " ");
	//printVector(data);
	int N = data.at(0);
	int X = data.at(1);
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
			if (G.isLinked(i, V-1)) continue;
			G.link(i, V - 1, D);
		}
	}

	G.display();
	cout << "\nSolution: "<< joinVector(G.sumWeights(), " ") << endl;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

long long int LinearCongruentialGenerator(int A, int C, int M, int seed) {
	return ((static_cast<long long>(A) * seed) + C) % M;
}
