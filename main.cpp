#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Node {
	string name;
	vector<string> children;
public:
	Node(string name) : name(name) {}
	void addChild(string child) { children.push_back(child); }
	string getname() { return name; }
	bool haschild(string child) {
		for (auto c : children)
			if (child == c)
				return true;
		return false;
	}
};
class Graph {
	vector<Node> elements;
public:
	vector<Node>* get_elements() { return &elements; }
	void fill() {
		int i = 0, curr, parent;
		string s;
		cin >> s;
		while (s[0] != '!') {
			curr = find_node(s);
			if (curr == elements.size())// if it's a new child/parent
				elements.push_back(s);
			if (i++ % 2 != 0)// if it's a child
				elements[parent].addChild(s);
			else
				parent = curr;
			cin >> s;
		}
	}
	void output(string str = "") {
		cout << str;
		for (auto i : elements)
			cout << i.getname() << ", ";
		cout << "\b\b " << endl;
	}
	int find_node(string a) {//returns the parent/child index or the graph's size
		for (auto c = elements.begin(); c != elements.end(); c++)
			if (a == c->getname())
				return (c - elements.begin());
		return elements.size();
	}
	bool is_beginning(string s) {//check if it's a source
		for (auto x : elements)
			if (x.haschild(s))
				return false;
		return true;
	}
};
void fulckerson_sort(Graph*);

int main() {
	Graph* graph = new Graph;

	graph->fill();
	graph->output("Unsorted:\t");
	fulckerson_sort(graph);
	graph->output("Sorted:\t\t");
	delete graph;
	return 0;
}
void fulckerson_sort(Graph* graph) {
	vector<string> deathlist;
	vector<Node>* elements = graph->get_elements(), new_e;
	for (;!elements->empty();) {
		deathlist.clear();
		for (auto x = elements->begin(); x < elements->end(); x++)
			if (graph->is_beginning(x->getname()))
				deathlist.push_back(x->getname());
		for (auto node_name : deathlist) {
			new_e.push_back(*(elements->begin() + graph->find_node(node_name)));
			elements->erase(elements->begin() + graph->find_node(node_name));
		}
	}
	for (auto i : new_e)	
		elements->push_back(i);
}