// Planar graph algorithms, based on [1, pp. 18-23].
// [1] Edelsbrunner & Harer (2010). Computational topology.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_PLANAR_GRAPH_H_
#define GRAPHS_PLANAR_GRAPH_H_

#include <cstdlib>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

namespace topo {

// Peculiar way to express a planar graph, but useful for the purposes of
// testing out Tutte's theorem on straight line embeddings. This graph has a
// total number of vertices:   n = outer_vertices + inner_vertices.
// The vertices and the degrees are ordered by outer vertices first, then inner.
//
// Not designed for optimized performance. Mainly for plotting and ease of
// prototyping purposes.
class PlanarGraph {
  using Edge = std::pair<size_t, size_t>;

 public:
  PlanarGraph(size_t outer_vertices, size_t inner_vertices);

  // Returns the degree for `vertex`.
  size_t Degree(size_t vertex) const;

  // Returns all edges for a given vertex.
  const std::vector<Edge*>& Edges(size_t vertex) const;

  // Add a connection between vertex `i` to vertex `j`.
  void AddEdge(size_t i, size_t j);

  // Getters for vertex information.
  inline size_t OuterVertices() const { return outer_vertices_; }
  inline size_t InnerVertices() const { return inner_vertices_; }
  inline size_t N() const { return n_; }

 private:
  const size_t outer_vertices_;
  const size_t inner_vertices_;
  const size_t n_;
  std::list<Edge> unique_edges_;
  std::unordered_map<size_t, std::vector<Edge*>> vertex_edges_map_;
};

}  // namespace topo

#endif  // GRAPHS_PLANAR_GRAPH_H_
