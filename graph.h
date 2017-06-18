#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <mutex>
#include <vector>
#include <atomic>
#include <string>

class graph { 

	private:
		std::unique_ptr<std::vector<std::vector<int>>> nodes;
		std :: unique_ptr<std::atomic<int>[]> visited;
		int size_graph;

		void generateGraph(int number_nodes);
		void readGraph(std :: string path);
	public:
		graph(int number_nodes);
		graph(std :: string path);
		~graph();
		graph(graph&& moved_graph);
		graph& operator=(graph&& moved_graph);

		void printGraph();
		bool exchangeValue(int& expected, int val, int node_index);
		int size();
		std :: vector<int>* get_children(int node);
};

#endif
