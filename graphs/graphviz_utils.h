// Simple utilities for producing dot graphviz files from custom graphs.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_GRAPHVIZ_UTILS_H_
#define GRAPHS_GRAPHVIZ_UTILS_H_

#include <string>

#include "graphs/disjoint_set_system.h"
#include "graphs/planar_graph.h"

namespace topo {

// Creates graphviz-compatible dot file with the `system`s graph representation.
void WriteGraphToDisk(const std::string& output_file,
                      const DisjointSetSystem& system);

// Draws straight-line embedding for a planar graph as a graphviz graph to disk.
void DrawStraightLineEmbedding(const std::string& output_file,
                               const PlanarGraph& G, double scale = 1.0);

}  // namespace topo

#endif  // GRAPHS_GRAPHVIZ_UTILS_H_
