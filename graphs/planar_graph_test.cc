// Unit testing the simple PlanarGraph class.
// Copyright 2021 Antonio Teran (toniioteran@gmail.com)

#include "graphs/planar_graph.h"

#include <gtest/gtest.h>

TEST(PlanarGraphTest, EmptyGraph) {
  const size_t inner = 5;
  const size_t outer = 5;
  topo::PlanarGraph G(inner, outer);
  for (int i = 0; i < inner + outer; ++i) {
    EXPECT_EQ(G.Degree(i), 0);
  }
}

TEST(PlanarGraphTest, OutOfBoundsDegreeCheck) {
  const size_t inner = 5;
  const size_t outer = 5;
  topo::PlanarGraph G(inner, outer);
  EXPECT_THROW(
      {
        try {
          G.Degree(100);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(e.what(), "Out of bounds");
          throw;
        }
      },
      std::invalid_argument);
}

TEST(PlanarGraphTest, AddEdgeCheckDegrees) {
  const size_t inner = 5;
  const size_t outer = 5;
  topo::PlanarGraph G(inner, outer);

  G.AddEdge(0, 1);
  EXPECT_EQ(G.Degree(0), 1);
  EXPECT_EQ(G.Degree(1), 1);
  G.AddEdge(0, 9);
  EXPECT_EQ(G.Degree(0), 2);
  EXPECT_EQ(G.Degree(1), 1);

  const auto& edges = G.Edges(0);
  EXPECT_EQ(edges.size(), 2);
  EXPECT_EQ(edges[0]->first, 0);
  EXPECT_EQ(edges[0]->second, 1);
  EXPECT_EQ(edges[1]->first, 0);
  EXPECT_EQ(edges[1]->second, 9);
}

TEST(PlanarGraphTest, InvalidAddEdges) {
  const size_t inner = 5;
  const size_t outer = 5;
  topo::PlanarGraph G(inner, outer);
  EXPECT_THROW(
      {
        try {
          G.AddEdge(0, 100);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(e.what(), "Out of bounds, head");
          throw;
        }
      },
      std::invalid_argument);
  EXPECT_THROW(
      {
        try {
          G.AddEdge(100, 0);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(e.what(), "Out of bounds, tail");
          throw;
        }
      },
      std::invalid_argument);
}
