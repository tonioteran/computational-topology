// Finding straight-line embeddings using Tutte's theorem for a planar graph.
// See for example https://en.wikipedia.org/wiki/Tutte_embedding.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_TUTTE_EMBEDDING_H_
#define GRAPHS_TUTTE_EMBEDDING_H_

#include <Eigen/Core>
#include <tuple>

#include "graphs/planar_graph.h"

namespace topo {

// Simple algorithm based on Tutte's theorem for constructing a straight-line
// embedding of a planar graph. Returns the R^2 positions of the vertices as an
// 2xN matrix, where N is the number of vertices in the planar graph G.
Eigen::Matrix<double, 2, Eigen::Dynamic> FindTutteEmbedding(
    const PlanarGraph& G);

// Places the outer vertices along the boundary of a disk.
Eigen::Matrix<double, 2, Eigen::Dynamic> GetBoundaryPositions(
    size_t outer_vertices);

// Returns the Tutte matrix, and the RHS vectors for the X and Y systems.
std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Eigen::VectorXd> BuildTutteSystem(
    const PlanarGraph& G,
    const Eigen::Matrix<double, 2, Eigen::Dynamic>& outer_positions);

}  // namespace topo

#endif  // GRAPHS_TUTTE_EMBEDDING_H_
