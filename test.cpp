#include <iostream>
#include <thread>
#include <functional>
#include <stack>
#include <queue>
#include "graph.h"

void singleDFS(graph& target_graph, int start, int end, int thread_id, int start_node);
void traversal(graph& target_graph, int start_node);

int main() {
	
	graph userGraph(10);
	userGraph.printGraph();
	const int start_node = 5;
	const int number_threads = 3;

	int size_graph = userGraph.size();
	int average = userGraph.size() / number_threads;
	int remainder = userGraph.size() % number_threads;
	
	std::vector<int>* children = userGraph.get_children(start_node); 
	std::vector<std::thread> threads;

	int i = 0;
	int count = 0;
	while (i < size_graph) {
		int start = i;
		int end;
		if(count < remainder) {
			end = start + average;
		} else {
			end = start + average - 1;
		}

		threads.push_back(std::thread(singleDFS, std::ref(userGraph), start, end, count + 1, start_node));
		i = end + 1;
		count++;
	}

	
	for(int i = 0; i < number_threads; i++) {
		threads[i].join();
	}
	return 0;
}

void singleDFS(graph& target_graph, int start, int end, int thread_id, int start_node) {

	std::cout << "[THREAD " << thread_id << "]" << std::endl;
	std::cout << "start: " << start << " end: " << end << std::endl;

	std::vector<int>* children = target_graph.get_children(start_node);
	std::stack<int> nodes_stack;

	for(int i = start; i <= end; i++) {
		if((*children)[i] != 0) {
			nodes_stack.push(i);
		}
	}

	int code_visited = 1;
	int expected = -2;
	std::queue<int> path;
	while(!nodes_stack.empty()) {
		int curr_node = nodes_stack.top();
		nodes_stack.pop();
		
		if(target_graph.exchangeValue(expected, code_visited, curr_node)) {
			path.push(curr_node);
			children = target_graph.get_children(curr_node);
			int size = children -> size();
			for(int i = 0; i < size; i++) {
				if((*children)[i] != 0) {
					nodes_stack.push(i);
				}
			}
		}
	}

	std::cout << "[THREAD " << thread_id << "]" << std::endl;
	if(path.empty()) {
		std::cout << "[THREAD " << thread_id << "] path is empty" << std::endl;
	}
	/*std::cout << path.front();
	path.pop();*/

	while(!path.empty()) {
		std::cout << " --> " << path.front();
		path.pop();
	}
}
