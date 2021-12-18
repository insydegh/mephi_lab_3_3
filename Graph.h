//
// Created by fokus on 09.12.2021.
//

#include "ListSequence.h"
#include "vector"
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
template <class T, class K>
class D_Edge;

template <class T, class K>
class D_Vertex {
private:
    T name;
    Sequence<D_Edge<T,K>*>* out_incidents;
public:
    D_Vertex(T name) {
        this->name = name;
        out_incidents = new ArraySequence<D_Edge<T,K>*>();
    }

    T GetName() {
        return this->name;
    }
    Sequence<D_Edge<T,K>*>* GetEdges() {
        return out_incidents;
    }

    void AddEdge(D_Edge<T,K>* edge) {
        out_incidents->Append(edge);
    }
    int GetDegree(){
        return out_incidents->GetSize();
    }
};

template <class T, class K>
class D_Edge {
private:
    K weight;
    D_Vertex<T,K>* from;
    D_Vertex<T,K>* to;
public:
    D_Edge(T first, T second) {
        this->from = new D_Vertex<T,K>(first);
        this->to = new D_Vertex<T,K>(second);
    }



    pair<D_Vertex<T,K>*, D_Vertex<T,K>*> getVertex() {
        return make_pair(from, to);
    }

};



template <class T, class K>
class Graph {

public:
    Graph() {
        this->vertexList = new ArraySequence<D_Vertex<T,K>*>();
    }

    void addVertex(T name) {

        D_Vertex<T,K>* toAdd = new D_Vertex<T,K>(name);

        if (containsVertex(name) == -1) {
                vertexList->Append(toAdd);
        }
    }

    void addEdge(T first, T second) {

        if (containsEdge(first,second) == false) {
            D_Edge<T, K>* edgeToAdd = new D_Edge<T, K>(first, second);

            if (containsVertex(first) == -1) {
                D_Vertex<T,K>* firstToAdd = new D_Vertex<T,K>(first);
                firstToAdd->AddEdge(edgeToAdd);
                vertexList->Append(firstToAdd);
            }
            else {
                this->vertexList->Get(containsVertex(first))->AddEdge(edgeToAdd);
            }

            if (containsVertex(second) == -1) {
                D_Vertex<T,K>* secondToAdd = new D_Vertex<T,K>(second);
                vertexList->Append(secondToAdd);
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
            D_Vertex<T,K>* first_v = this->vertexList->Get(containsVertex(first));
            for (int i =0; i<first_v->GetDegree(); i++) {
                if (first_v->GetEdges()->Get(i)->getVertex().second->GetName() == second) {
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
            D_Vertex<T,K>* first_v = this->vertexList->Get(containsVertex(first));

            for (int i =0; i<first_v->GetEdges()->GetSize(); i++) {
                if (first_v->GetEdges()->Get(i)->getVertex().second->GetName() == second || first_v->GetEdges()->Get(i)->getVertex().first->GetName() == second) {
                    first_v->GetEdges()->RemoveAt(i);
                }
            }
        }
    }


    // temp. unavailable
    void removeVertex(T name) {
        if (containsVertex(name) != -1) {
            D_Vertex<T,K>* vert = this->vertexList->Get(containsVertex(name));
            for (int i=0; i<vert->GetDegree(); i++) {
                D_Edge<T,K>* edge = vert->GetEdges()->Get(i);
                this->removeEdge(edge->getVertex().first->GetName(),edge->getVertex().second->GetName());
                i--;
            }
            for (int i =0; i<this->getVertexes()->GetSize(); i++) {
                if (this->getVertexes()->Get(i)->GetName()==name) {
                    continue;
                }
                else {
                    D_Vertex<T,K>* vert = getVertexes()->Get(i);
                    for (int j =0; j<vert->GetDegree(); j++) {
                        D_Edge<T,K>* edge = vert->GetEdges()->Get(j);
                        if (edge->getVertex().second->GetName()==name) {
                            this->removeEdge(vert->GetName(), name);
                            j--;
                        }
                    }
                }
            }
            this->getVertexes()->RemoveAt(containsVertex(name));
        }
    }




    ArraySequence<D_Vertex<T,K>*>* getVertexes() {
        return this->vertexList;
    }

    int getVertexCount() {
        return this->vertexList->GetSize();
    }


private:

    ArraySequence<D_Vertex<T,K>*>* vertexList;


};
















#endif //GRAPH_GRAPH_H
