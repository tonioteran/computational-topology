// Unit tests for Tutte embedding computation.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/tutte_embedding.h"

#include <gtest/gtest.h>

#include "graphs/planar_graph.h"

TEST(TutteEmbeddingTest, DrawingTest) {
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

  const Eigen::Matrix<double, 2, Eigen::Dynamic> embedding =
      FindTutteEmbedding(G);

  std::cout << embedding << std::endl;
}
