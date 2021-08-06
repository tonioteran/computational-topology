// Finding straight-line embeddings using Tutte's theorem for a planar graph.
// See for example https://en.wikipedia.org/wiki/Tutte_embedding.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/tutte_embedding.h"

#include <cmath>
#include <iostream>

namespace topo {

Eigen::Matrix<double, 2, Eigen::Dynamic> FindTutteEmbedding(
    const PlanarGraph& G) {
  Eigen::Matrix<double, 2, Eigen::Dynamic> embedding =
      Eigen::MatrixXd::Zero(2, G.N());

  // Find positions for the outer edge vertices.
  const Eigen::Matrix<double, 2, Eigen::Dynamic> outer_positions =
      GetBoundaryPositions(G.OuterVertices());
  embedding.block(0, 0, 2, G.OuterVertices()) = outer_positions;

  const Eigen::MatrixXd tutte_matrix = BuildTutteMatrix(G);

  return embedding;
}

Eigen::Matrix<double, 2, Eigen::Dynamic> GetBoundaryPositions(
    size_t num_vertices) {
  Eigen::Matrix<double, 2, Eigen::Dynamic> positions =
      Eigen::MatrixXd::Zero(2, num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    positions.col(i) =
        Eigen::Vector2d{std::cos((2 * (i + 1) * M_PI) / num_vertices),
                        std::sin((2 * (i + 1) * M_PI) / num_vertices)};
  }
  return positions;
}

Eigen::MatrixXd BuildTutteMatrix(const PlanarGraph& G) {
  // The full matrix will be of size (inner vertices X inner vertices).
  const size_t n_inner = G.InnerVertices();
  Eigen::MatrixXd M = Eigen::MatrixXd::Zero(n_inner, n_inner);
}

}  // namespace topo
