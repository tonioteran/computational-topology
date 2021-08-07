// Simple utilities for producing dot graphviz files from custom graphs.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)
#include "graphs/graphviz_utils.h"

#include <fstream>
#include <string>

#include "graphs/tutte_embedding.h"

namespace topo {

void WriteGraphToDisk(const std::string& output_file,
                      const DisjointSetSystem& system) {
  std::ofstream out_stream(output_file);
  out_stream << "digraph {\n";

  for (const Vertex& v : system.Vertices()) {
    if (v.parent == nullptr) {
      out_stream << v.index << "\n";
    } else {
      out_stream << v.parent->index << " -> " << v.index << "\n";
    }
  }

  out_stream << "}\n";
  out_stream.close();
}

void DrawStraightLineEmbedding(const std::string& output_file,
                               const PlanarGraph& G, double scale) {
  const Eigen::MatrixXd positions = FindTutteEmbedding(G);
  std::ofstream out_stream(output_file);
  out_stream << "graph {\n";

  // Set the individual nodes in their own embedding positions.
  for (size_t v = 0; v < G.N(); ++v) {
    const Eigen::Vector2d p = scale * positions.col(v);
    out_stream << v << " [pos=\"" << p(0) << "," << p(1) << "!\"]\n";
  }

  // Draw the straight lines for each edge.
  for (const PlanarGraph::Edge& e : G.Edges()) {
    out_stream << e.first << " -- " << e.second << "\n";
  }

  out_stream << "}\n";
  out_stream.close();
}

}  // namespace topo
