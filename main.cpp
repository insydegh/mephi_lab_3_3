#include <iostream>
#include "Graph.h"
#include <fstream>
#include "gvc.h"
#include "UndirectedGraph.h"
#include "ISorter.h"
#include "random"
#include <ctime>
/*
template<typename T,typename K>
void read_graph(const char * fname, Graph<T,K> g)
{
    ListSequence<Vertex<T>*>* vertexList = g.getVertexes();
    ListSequence<Edge<T, K>*>* edgeList = g.getEdges();
    fstream f;
    f.open("../graph/input.txt", std::ios::out | ios::trunc);
    int n = vertexList->GetSize();
    int m = edgeList->GetSize();
    f << n <<" "<< m;
    f<<endl;
    for (int i = 0; i < m; ++i) {
        T from, to;
        from = edgeList->Get(i)->getVertex().first->GetName();
        to = edgeList->Get(i)->getVertex().second->GetName();
        f << from <<" "<< to;
        f<<endl;

    }
    f.close();
}
*/
template<typename T,typename K>
void write_directed_graph_dot(const char * fname, Graph<T,K> g)
{
    ArraySequence<D_Vertex<T,K>*>* vertexList = g.getVertexes();
    //ListSequence<Edge<T, K>*>* edgeList = g.getEdges();
    fstream f;
    f.open("g.dot", std::ios::out | ios::trunc);
    f << "digraph {\n";
    f <<"node [shape=circle, width=0.4]\n";
    for (int i = 0; i < vertexList->GetSize(); ++i) {
        f << vertexList->Get(i)->GetName() << ";\n";
    }
    f<<"edge [len=5];";
    for (int i =0; i<g.getVertexes()->GetSize(); i++) {
        D_Vertex<T,K>* vert = g.getVertexes()->Get(i);
        for (int j=0; j<vert->GetDegree(); j++) {
            D_Edge<T,K>* edge = vert->GetEdges()->Get(j);
            f<<edge->getVertex().first->GetName()<<" -> "<<edge->getVertex().second->GetName()<<endl;
        }
        f<<endl;
    }
    f << "}\n";
    f.close();
}

template<typename T,typename K>
void write_undirected_graph_dot(const char * fname, UndirectedGraph<T,K> g)
{
    ArraySequence<Vertex<T,K>*>* vertexList = g.getVertexes();
    //ListSequence<Edge<T, K>*>* edgeList = g.getEdges();
    fstream f;
    f.open("g.dot", std::ios::out | ios::trunc);
    f << "strict graph {\n";
    f<<"graph[size=\"20,20\"]\n";
    f <<"node [shape=circle, width=0.2]\n";
    f<<"node [nodesep=2]\n";

    //f << "nodesep = 2\n";


    for (int i = 0; i < vertexList->GetSize(); ++i) {
        f << vertexList->Get(i)->GetName()<< ";\n";
    }


    for (int i =0; i<g.getVertexes()->GetSize(); i++) {
        Vertex<T,K>* vert = g.getVertexes()->Get(i);
        for (int j=0; j<vert->GetDegree(); j++) {
            Edge<T,K>* edge = vert->GetEdges()->Get(j);
            f<<edge->getVertex().first->GetName()<<"--"<<edge->getVertex().second->GetName()<< endl;
        }
        f<<endl;
    }
    f << "}\n";
    f.close();
}


template<typename T,typename K>
void colored_write_undirected_graph_dot(const char * fname, UndirectedGraph<T,K> g)
{
    ArraySequence<Vertex<T,K>*>* vertexList = g.getVertexes();
    //ListSequence<Edge<T, K>*>* edgeList = g.getEdges();
    fstream f;
    f.open("g.dot", std::ios::out | ios::trunc);
    f << "strict graph {\n";
    f <<"node [shape=circle, width=0.1]\n";
    for (int i = 0; i < vertexList->GetSize(); ++i) {
        f << vertexList->Get(i)->GetName()<< "[color=\""<<vertexList->Get(i)->GetColor()<<"\" , style=filled]"<< ";\n";
        cout<<vertexList->Get(i)->GetColor()<<endl;
    }
    for (int i =0; i<g.getVertexes()->GetSize(); i++) {
        Vertex<T,K>* vert = g.getVertexes()->Get(i);
        for (int j=0; j<vert->GetDegree(); j++) {
            Edge<T,K>* edge = vert->GetEdges()->Get(j);
            f<<edge->getVertex().first->GetName()<<"--"<<edge->getVertex().second->GetName()<<endl;
        }
    }
    f << "}\n";
    f.close();
}

template<typename T, typename K>
void Undirected_UI() {
    UndirectedGraph<T, K> graph = UndirectedGraph<T, K>();
    while (true) {
        //----------------------------------------------------------
        {
            cout << "Commands:\n";
            cout << "	s - Show graph\n";
            cout << "	c - Show colored graph\n";
            cout << "	1 - Add edge\n";
            cout << "	2 - Add vertex\n";
            cout << "	3 - Remove Edge\n";
            cout << "	4 - Remove Vertex\n";
            cout << "	q - quit\n";
        }
        //----------------------------------------------------------
        char command;
        std::cin >> command;
        if (command == 'q') {
            return;
        }
        if (command == 's' || command == 'S') {
            write_undirected_graph_dot("g.dot", graph);
            system("dot g.dot -Tpng -og.png");

        }
        if (command == 'c' || command == 'C') {
            graph.Coloring();
            colored_write_undirected_graph_dot("g.dot", graph);
            system("dot g.dot -Tpng -og.png");
        }
        if (command == '1') {
            int count;
            cout << "How many edges do you want to add?: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                T from, to;
                std::cout << "input keys: ";
                std::cin >> from >> to;
                graph.addEdge(from, to);
            }
        }
        if (command == '2') {
            int count;
            cout << "How many vertexes do you want to add?: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                T v;
                std::cout << "input keys: ";
                std::cin >> v;
                graph.addVertex(v);
            }
            if (command == '3') {
                T from, to;
                std::cout << "input keys: ";
                std::cin >> from >> to;
                graph.removeEdge(from, to);
            }

            if (command == '4') {
                T v;
                std::cout << "input keys: ";
                std::cin >> v;
                graph.removeVertex(v);
            }
        }
    }
}


template <typename T, typename K>
void Directed_UI() {
    Graph<T,K> graph = Graph<T,K>();
    while (true) {
        //----------------------------------------------------------
        {
            cout << "Commands:\n";
            cout << "	s - Show graph\n";
            cout << "	1 - Add edge\n";
            cout << "	2 - Add vertex\n";
            cout << "	3 - Remove Edge\n";
            cout << "	4 - Remove Vertex\n";
            cout << "	q - quit\n";
        }
        //----------------------------------------------------------
        char command;
        std::cin >> command;
        if (command == 'q') {
            return;
        }
        if (command == 's' || command == 'S') {
            write_directed_graph_dot("g.dot", graph);
            system("dot g.dot -Tpng -og.png");

        }

        if (command == '1') {
            int count;
            cout << "How many edges do you want to add?: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                T from, to;
                std::cout << "input keys: ";
                std::cin >> from >> to;
                graph.addEdge(from, to);
            }
        }
        if (command == '2') {
            int count;
            cout << "How many vertexes do you want to add?: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                T v;
                std::cout << "input keys: ";
                std::cin >> v;
                graph.addVertex(v);
            }
        }
        if (command == '3') {
            T from, to;
            std::cout << "input keys: ";
            std::cin >> from >> to;
            graph.removeEdge(from, to);
        }

        if (command == '4') {
            T v;
            std::cout << "input keys: ";
            std::cin >> v;
            graph.removeVertex(v);
        }
    }
}

void Menu() {
    char command;
    //----------------------------------------------------------
    while (true) {

        std::cout << "Choose the graph\n";
        std::cout << "	1 - Directed\n";
        std::cout << "	2 - Undirected\n";
        std::cout << "	0 - exit\n";

        //----------------------------------------------------------

        std::cin >> command;

        if (command == '0') {
            return;
        }
        if (command == '1') {
            Directed_UI<int, int>();

        }
        if (command == '2') {
            Undirected_UI<int, int>();
        }
    }
}





#include <windows.h>

int main()
{
    UndirectedGraph<int,int> graph = UndirectedGraph<int,int>();
    graph.addEdge(1,4);
    graph.addEdge(1,5);
    graph.addEdge(1,3);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(2,4);
    graph.addEdge(3,4);
    graph.addEdge(3,5);
    graph.addEdge(4,6);
    graph.addEdge(5,4);
    graph.addEdge(3,7);
    graph.addEdge(2,6);
    graph.addEdge(1,7);
    graph.addEdge(5,7);


    write_undirected_graph_dot("g.dot", graph);
    system("sfdp -s172 g.dot -Tpng -og.png");

}
