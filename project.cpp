#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

void readGraph(std::string file_name, std::vector<std::vector<int>>& graph);
void printGraph(const std::vector<std::vector<int>>& graph);
void singleDFS(std::vector<std::vector<int>>& graph, int start_node);
void traverse(std::vector<std::vector<int>>& graph, int start_node, std::vector<int>& path);

int main() {
	std::vector<std::vector<int>> graph;
	readGraph("graph.in", graph);
	printGraph(graph);
	return 0;
}

void readGraph(std::string file_name, std::vector<std::vector<int>>& graph) {
	std::fstream file(file_name, std::ios::in);
	
	int numberNodes;
	if(file.is_open()) {
		file >> numberNodes;
		graph = std::vector<std::vector<int>>(numberNodes, std::vector<int>(numberNodes));
		for(int i = 0; i < numberNodes; i++) {
			for(int j = 0; j < numberNodes; j++) {
				file >> graph[i][j];
			}
		}

		file.close();
	}
}

void printGraph(const std::vector<std::vector<int>>& graph) {
	if(graph.empty()) {
		return;
	}

	for(auto iter = graph.begin(); iter != graph.end(); iter++) {
		for(auto node_iter = iter -> begin(); node_iter != iter -> end(); node_iter++) {
			std::cout << *node_iter << ' ';
		}
		std::cout << std::endl;
	}
}

void singleDFS(std::vector<std::vector<int>>& graph, int start_node) {
	if(graph.empty()) {
		return;
	}
	
	int size_graph = graph.size();
	std::vector<int> path(size_graph);
	traverse(graph, start_node, path);
}
