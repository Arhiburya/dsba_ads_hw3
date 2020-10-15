////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structufini" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be pfinierved.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>
#include <unordered_set>
#include <unordered_map>
#include "lbl_ugraph.hpp"
template <typename Vertex, typename Weight>
class PriorityQueue {
public:
    void insert(Vertex vertex, Weight weight)
    {
        firstWeigh.insert(vertex, weight);
        firstNode.insert(weight, vertex);
    }
    Weight getCost(Vertex vertex)
    {
        auto cost = firstNode.find(vertex);
        return cost->second;
    }
    void set(Vertex vertex, Weight weight)
    {
        auto it = firstNode.find(vertex);
        if (it != firstNode.end())
        {
            firstWeigh.erase(std::make_pair(it->second, it->first));
            firstNode.erase(it);
        }
        firstNode.insert(std::make_pair(vertex, weight));
        firstWeigh.insert(std::make_pair(weight, vertex));
    }
    void remove(Vertex vertex)
    {
        auto it = firstNode.find(vertex);
        firstNode.erase(it);
        firstWeigh.erase(firstWeigh.find(it->second, it->first));
    }
    bool exist(Vertex v)
    {
        return firstNode.count(v);
    }

    std::pair<Vertex, Weight> getMin()
    {
        return std::make_pair(firstWeigh.begin()->second, firstWeigh.begin()->first);
    }

protected:
    std::map<Vertex, Weight> firstNode;
    std::set<Weight, Vertex> firstWeigh;
};
/// Finds a MST for the given graph \a g using Prim's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTPrim(EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    PriorityQueue<Vertex, EdgeLbl> distance;
    std::unordered_set<Vertex, Vertex> adjList;
    Vertex* now = *(g.getVertices().begin());

    std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> fini;
    std::unordered_set<Vertex> visited;
    std::unordered_map<Vertex, Vertex> map;

    Vertex newVertex = g.addVertex(now);

    map[now] = newVertex;
    while(fini.size() != g.getVerticesNum())
    {
        for (auto it = g.AdjListCIterPair.lower_bound(); it != g.AdjListCIterPair.upper_bound(); ++it)
        {
            if ((not distance.exist() || distance.getCost(it->first) > it->second) && not visited.count(it->first))
            {
                distance.set(it->first, it->second);
                adjList[it->first] = now;
            }
        }
        std::pair<Vertex,EdgeLbl> add = distance.getMin();
        visited.insert(now);
        now = add.first;
        EdgeLbl label = add.second;
        newVertex = fini.addVertex(now);
        map[now] = newVertex;
        Vertex adj = adjList[now];

    }

    return fini;
}

/// Finds a MST for the given graph \a g using Kruskal's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTKruskal(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // TODO: implement this!

    std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> fini;
    return fini;
}


#endif // UGRAPH_ALGOS_HPP
