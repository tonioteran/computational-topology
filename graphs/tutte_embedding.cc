// Finding straight-line embeddings using Tutte's theorem for a planar graph.
// See for example https://en.wikipedia.org/wiki/Tutte_embedding.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/tutte_embedding.h"

#include <Eigen/Dense>
#include <cmath>

namespace topo {

Eigen::Matrix<double, 2, Eigen::Dynamic> FindTutteEmbedding(
    const PlanarGraph& G) {
  Eigen::Matrix<double, 2, Eigen::Dynamic> embedding =
      Eigen::MatrixXd::Zero(2, G.N());

  // Find positions for the outer edge vertices.
  const Eigen::Matrix<double, 2, Eigen::Dynamic> outer_positions =
      GetBoundaryPositions(G.OuterVertices());
  embedding.block(0, 0, 2, G.OuterVertices()) = outer_positions;

  // Find positions for the inner vertices by solving Tutte's linear system.
  const auto [A, Bx, By] = BuildTutteSystem(G, outer_positions);
  const Eigen::VectorXd x_inner = A.colPivHouseholderQr().solve(Bx);
  const Eigen::VectorXd y_inner = A.colPivHouseholderQr().solve(By);

  // Bundle and return.
  embedding.block(0, G.OuterVertices(), 1, G.InnerVertices()) =
      x_inner.transpose();
  embedding.block(1, G.OuterVertices(), 1, G.InnerVertices()) =
      y_inner.transpose();
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

std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Eigen::VectorXd> BuildTutteSystem(
    const PlanarGraph& G,
    const Eigen::Matrix<double, 2, Eigen::Dynamic>& outer_positions) {
  // The full matrix will be of size (inner vertices X inner vertices).
  const size_t n_outer = G.OuterVertices();
  const size_t n_inner = G.InnerVertices();
  Eigen::MatrixXd A = Eigen::MatrixXd::Identity(n_inner, n_inner);
  Eigen::VectorXd Bx = Eigen::VectorXd::Zero(n_inner);
  Eigen::VectorXd By = Eigen::VectorXd::Zero(n_inner);

  // For each inner vertex, iterate over edges to build matrix and RHS vectors.
  for (size_t vertex = n_outer; vertex < G.N(); ++vertex) {
    const size_t degree = G.Degree(vertex);
    const double weight = 1.0 / static_cast<double>(degree);
    const size_t row = vertex - n_outer;
    for (const PlanarGraph::Edge* e : G.Edges(vertex)) {
      const size_t neighbor = (e->first == vertex) ? e->second : e->first;
      if (neighbor < n_outer) {
        // Outer neighbor, modify RHS vectors.
        Bx(row) += weight * outer_positions(0, neighbor);
        By(row) += weight * outer_positions(1, neighbor);
      } else {
        // Inner neighbor, add entry to the matrix.
        const size_t col = neighbor - n_outer;
        A(row, col) = -weight;
      }
    }
  }

  return {A, Bx, By};
}

}  // namespace topo
