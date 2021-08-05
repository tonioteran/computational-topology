// Planar graph algorithms, based on [1, pp. 18-23].
// [1] Edelsbrunner & Harer (2010). Computational topology.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/planar_graph.h"

namespace topo {

PlanarGraph::PlanarGraph(size_t outer_vertices, size_t inner_vertices)
    : outer_vertices_(outer_vertices), inner_vertices_(inner_vertices) {}

size_t PlanarGraph::Degree(size_t vertex) const {
  if (vertex >= outer_vertices_ + inner_vertices_)
    throw std::invalid_argument("Out of bounds");
  return (vertex_edges_map_.find(vertex) == vertex_edges_map_.end())
             ? 0
             : vertex_edges_map_.at(vertex).size();
}

void PlanarGraph::AddEdge(size_t i, size_t j) {
  unique_edges_.emplace_back(i, j);
  vertex_edges_map_[i].push_back(&(unique_edges_.back()));
  vertex_edges_map_[j].push_back(&(unique_edges_.back()));
}

}  // namespace topo
