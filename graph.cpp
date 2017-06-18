#include "graph.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include <random>
#include <string>
#include <fstream>

graph::graph(int number_nodes) : visited(new std::atomic<int>[number_nodes]) {
	size_graph = number_nodes;
	generateGraph(number_nodes);
	for(int i = 0; i < number_nodes; i++) {
		visited[i].store(-2);
	}
}

graph :: graph(std :: string path) {
	if(path.length() == 0) {
		return;
	}

	readGraph(path);
	size_graph = nodes -> size();
	visited = std :: unique_ptr<std :: atomic<int>[]>(new std :: atomic<int>[size_graph]);
}

graph :: graph(graph&& moved_graph) : nodes(std :: move(moved_graph.nodes)), visited(std :: move(moved_graph.visited)) {
	std :: cout << "Invoking the move construc\n";
}

graph& graph :: operator=(graph&& moved_graph) {
	nodes = std :: move(moved_graph.nodes);
	visited = std :: move(moved_graph.visited);
}

graph::~graph() {	
}

bool graph::exchangeValue(int& expected, int val, int node_index) {
	if(node_index >= size_graph) {
		return false;
	}
	return visited[node_index].compare_exchange_strong(expected, val);
}

void graph::generateGraph(int number_nodes) {
	if(number_nodes == 0) {
		return;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 generator (seed);
	std::uniform_int_distribution<int> distribution(0, 1);
	
	nodes = std::unique_ptr<std::vector<std::vector<int>>>(new std::vector<std::vector<int>>(number_nodes, std::vector<int>(number_nodes)));
	for(int i = 0; i < number_nodes; i++) {
		for(int j = 0; j < number_nodes; j++) {
			(*nodes)[i][j] = distribution(generator);
		}
	}
}

void graph :: readGraph(std :: string path) {
	std :: fstream file(path, std :: ios :: in);
	if(!file.is_open()) {
		return;
	}

	int size_graph = 0;
	file >> size_graph;

	nodes = std :: unique_ptr<std :: vector<std :: vector<int>>>(new std :: vector<std :: vector<int>>(size_graph, std :: vector<int>(size_graph)));
	for(int i = 0; i < size_graph; i++) {
		for(int j = 0; j < size_graph; j++) {
			file >> (*nodes)[i][j];
		}
	}

	if(file.is_open()) {
		std :: cout << "Closing file " << path << std :: endl;
		file.close();
	}
}

void graph::printGraph() {
	for(auto iter = nodes -> begin(); iter != nodes -> end(); iter++) {
		for(auto elementIter = iter -> begin(); elementIter != iter -> end(); elementIter++) {
			std :: cout << *elementIter << " ";
		}
		std :: cout << std :: endl;
	}
}

int graph :: size() {
	return size_graph;
}

std :: vector<int>* graph :: get_children(int node_index) {	
	if(node_index >= size_graph) {
		return nullptr;
	}

	return &(*nodes)[node_index];
}
