// Unit tests for Tutte embedding computation.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/tutte_embedding.h"

#include <gtest/gtest.h>

#include "graphs/planar_graph.h"

namespace {

topo::PlanarGraph BuildTestGraph() {
  const size_t inner = 5;
  const size_t outer = 5;
  topo::PlanarGraph G(inner, outer);

  // Add a bunch of edges.
  // From vertex 0.
  G.AddEdge(0, 1);
  G.AddEdge(0, 4);
  G.AddEdge(0, 5);
  G.AddEdge(0, 9);

  // From vertex 1.
  G.AddEdge(1, 2);
  G.AddEdge(1, 5);
  G.AddEdge(1, 6);

  // From vertex 2.
  G.AddEdge(2, 3);
  G.AddEdge(2, 6);
  G.AddEdge(2, 7);

  // From vertex 3.
  G.AddEdge(3, 4);
  G.AddEdge(3, 7);
  G.AddEdge(3, 8);

  // From vertex 4.
  G.AddEdge(4, 8);
  G.AddEdge(4, 9);

  // From vertex 5.
  G.AddEdge(5, 6);
  G.AddEdge(5, 7);
  G.AddEdge(5, 8);
  G.AddEdge(5, 9);

  // From vertex 6.
  G.AddEdge(6, 7);

  // From vertex 7.
  G.AddEdge(7, 8);

  // From vertex 8.
  G.AddEdge(8, 9);

  return G;
}

}  // namespace

TEST(TutteEmbeddingTest, TutteSystem) {
  const topo::PlanarGraph G = BuildTestGraph();
  const Eigen::Matrix<double, 2, Eigen::Dynamic> outer_positions =
      topo::GetBoundaryPositions(G.OuterVertices());
  const auto [A, Bx, By] = topo::BuildTutteSystem(G, outer_positions);

  // Compare against ground truth example from MATLAB.
  // clang-format off
  const Eigen::MatrixXd A_ground_truth = ((Eigen::MatrixXd(5, 5) <<
                1.0000,  -0.1667,  -0.1667,  -0.1667,  -0.1667,
               -0.2500,   1.0000,  -0.2500,   0.0000,   0.0000,
               -0.2000,  -0.2000,   1.0000,  -0.2000,   0.0000,
               -0.2000,   0.0000,  -0.2000,   1.0000,  -0.2000,
               -0.2500,   0.0000,   0.0000,  -0.2500,   1.0000).finished());
  // clang-format on
  EXPECT_TRUE(A.isApprox(A_ground_truth, 1e-4));
}

TEST(TutteEmbeddingTest, FullEmbeddingTest) {
  const topo::PlanarGraph G = BuildTestGraph();
  const Eigen::Matrix<double, 2, Eigen::Dynamic> embedding =
      FindTutteEmbedding(G);

  // Compare against ground truth example from MATLAB.
  const Eigen::MatrixXd embedding_ground_truth =
      ((Eigen::MatrixXd(2, 10) << 0.3090, -0.8090, -0.8090, 0.3090, 1.0000,
        -0.0714, -0.4592, -0.1472, 0.2947, 0.3831, 0.9511, 0.5878, -0.5878,
        -0.9511, -0.0000, 0.2198, -0.0197, -0.2988, -0.1552, 0.2539)
           .finished());
  EXPECT_TRUE(embedding.isApprox(embedding_ground_truth, 1e-4));
}
