//
// Created by fokus on 10.12.2021.
//

#ifndef GRAPH_UNDIRECTEDGRAPH_H
#define GRAPH_UNDIRECTEDGRAPH_H
#include "ListSequence.h"
#include "vector"
#include "random"
#include "ctime"
#include "ISorter.h"

std::random_device rd;
std::mt19937 eng(time(0));
std::uniform_int_distribution<int> dist(0, 15);

string RandomHEXColor(){
    string hex="0123456789ABCDEF";
    string color ="#";
    for(int i = 0 ; i < 6; i++ ) {
        color += hex[ dist(eng) ];
    }
    return color;
}

//#include "Graph.h"
template <class T, class K>
class Edge;

template <class T, class K>
class Vertex {
private:
    T name;
    string color;
    Sequence<Edge<T,K>*>* incidents;

public:
    Vertex(T name) {
        this->name = name;
        incidents = new ArraySequence<Edge<T,K>*>();
    }

    T GetName() {
        return this->name;
    }
    string GetColor() {
        return this->color;
    }
    void SetColor(string clr) {
        this->color = clr;
    }
    Sequence<Edge<T,K>*>* GetEdges() {
        return incidents;
    }

    void AddEdge(Edge<T,K>* edge) {
        incidents->Append(edge);
    }
    int GetDegree(){
        return incidents->GetSize();
    }


};

template <class T, class K>
class Edge {
private:
    Vertex<T,K>* from;
    Vertex<T,K>* to;
public:
    Edge(T first, T second) {
        K weight;
        this->from = new Vertex<T,K>(first);
        this->to = new Vertex<T,K>(second);
    }


    pair<Vertex<T,K>*, Vertex<T,K>*> getVertex() {
        return make_pair(from, to);
    }

};

template <class T, class K>
int compare_v(Vertex<T,K>* v1, Vertex<T,K>* v2) {
    return v1->GetDegree()<v2->GetDegree() ? 1 : 0;
}


template <class T, class K>
class UndirectedGraph {

public:
	UndirectedGraph() {
		this->vertexList = new ArraySequence<Vertex<T,K>*>();
	}

	void addVertex(T name) {

		Vertex<T,K>* toAdd = new Vertex<T,K>(name);

		if (containsVertex(name) == -1) {
			vertexList->Append(toAdd);
		}

	}

	void addEdge(T first, T second) {

		if (containsEdge(first,second) == false) {
            Edge<T, K>* edgeToAdd = new Edge<T, K>(first, second);

            if (containsVertex(first) == -1) {
                Vertex<T,K>* firstToAdd = new Vertex<T,K>(first);
                firstToAdd->AddEdge(edgeToAdd);
                vertexList->Append(firstToAdd);
            }
            else {
                this->vertexList->Get(containsVertex(first))->AddEdge(edgeToAdd);
            }

            if (containsVertex(second) == -1) {
                Vertex<T,K>* secondToAdd = new Vertex<T,K>(second);
                secondToAdd->AddEdge(edgeToAdd);
                vertexList->Append(secondToAdd);
            }
            else {
                this->vertexList->Get(containsVertex(second))->AddEdge(edgeToAdd);
            }
        }
	}

	int containsVertex(T name) {
		for (int i = 0; i < this->getVertexCount(); ++i) {
			if (this->vertexList->Get(i)->GetName() == name) {
				return i;
			}
		}
		return -1;
	}

	bool containsEdge(T first, T second) {
		if (containsVertex(first) != -1 && containsVertex(second) != -1 ) {
            bool flag;
            Vertex<T,K>* first_v = this->vertexList->Get(containsVertex(first));
            Vertex<T,K>* second_v = this->vertexList->Get(containsVertex(second));
            for (int i =0; i<first_v->GetDegree(); i++) {
                if (first_v->GetEdges()->Get(i)->getVertex().second->GetName() == second || first_v->GetEdges()->Get(i)->getVertex().first->GetName() == second ) {
                    flag = true;
                    return flag;
                }
            }
            for (int i =0; i<second_v->GetDegree(); i++) {
                if (second_v->GetEdges()->Get(i)->getVertex().second->GetName() == first || second_v->GetEdges()->Get(i)->getVertex().first->GetName() == first ) {
                    flag = true;
                    return flag;
                }
            }
            return false;
        }
        else {
            return false;
        }
	}

	void removeEdge(T first, T second) {
		if (containsEdge(first, second) == true) {
            Vertex<T,K>* first_v = this->vertexList->Get(containsVertex(first));
            Vertex<T,K>* second_v = this->vertexList->Get(containsVertex(second));
            for (int i =0; i<first_v->GetEdges()->GetSize(); i++) {
                if (first_v->GetEdges()->Get(i)->getVertex().second->GetName() == second || first_v->GetEdges()->Get(i)->getVertex().first->GetName() == second) {
                    first_v->GetEdges()->RemoveAt(i);
                }
            }
            for (int i =0; i<second_v->GetEdges()->GetSize(); i++) {
                if (second_v->GetEdges()->Get(i)->getVertex().second->GetName() == first || second_v->GetEdges()->Get(i)->getVertex().first->GetName() == first) {
                    second_v->GetEdges()->RemoveAt(i);
                }
            }
		}
	}


	// temp. unavailable
	void removeVertex(T name) {
		if (containsVertex(name) != -1) {
            Vertex<T,K>* vert = this->vertexList->Get(containsVertex(name));
            for (int i=0; i<vert->GetDegree(); i++) {
                Edge<T,K>* edge = vert->GetEdges()->Get(i);
                this->removeEdge(edge->getVertex().first->GetName(),edge->getVertex().second->GetName());
                i--;
            }
            this->getVertexes()->RemoveAt(containsVertex(name));
		}
	}

    static void OneColor(Sequence<Vertex<T,K>*>* seq, Sequence<Vertex<T,K>*>* un_inc, UndirectedGraph<T,K> graph, string color){
        if (un_inc->GetSize()==0) {
            return;
        }
        un_inc->Get(0)->SetColor(color);
        Vertex<T,K>* vert = un_inc->Get(0);
        for (int i=0; i<seq->GetSize(); i++) {
            if (seq->Get(i)->GetName()==vert->GetName()){
                seq->RemoveAt(i);
                i--;
            }
        }
        un_inc->RemoveAt(0);


        for (int i =0; i<un_inc->GetSize(); i++) {
            if (graph.containsEdge(vert->GetName(),un_inc->Get(i)->GetName())) {
                un_inc->RemoveAt(i);

                i--;
            }
        }
        OneColor(seq, un_inc,graph,color);

    }
     void Coloring(){

        ISorter<Vertex<T,K>*>* sorter = new QuickSorter<Vertex<T,K>*>;
        Sequence<Vertex<T,K>*>* seq = this->getVertexes();
        Sequence<Vertex<T,K>*>* sorted_seq = sorter->Sort(seq,compare_v);

        while (sorted_seq->GetSize()>0) {
            string color = RandomHEXColor();
            Sequence<Vertex<T,K>*>* un_inc = sorted_seq->Clone();
            OneColor(sorted_seq,un_inc,*this,color);

        }
    }




	ArraySequence<Vertex<T,K>*>* getVertexes() {
		return this->vertexList;
	}

	int getVertexCount() {
		return this->vertexList->GetSize();
	}

private:


	ArraySequence<Vertex<T,K>*>* vertexList;

};





#endif //GRAPH_UNDIRECTEDGRAPH_H
