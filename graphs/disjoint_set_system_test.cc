#include "disjoint_set_system.h"

#include <gtest/gtest.h>

TEST(DisjointSetSystemTest, FindSetFullyDisjoint) {
  const int num_vertices = 10;
  topo::DisjointSetSystem sys{num_vertices};
  // Each vertex should be its own root (no edges, so all disjoint sets).
  for (int i = 0; i < num_vertices; ++i) EXPECT_EQ(sys.FindSet(i), i);
}

TEST(DisjointSetSystemTest, FindSetOutOfBounds) {
  const int num_vertices = 10;
  topo::DisjointSetSystem sys{num_vertices};
  EXPECT_THROW(
      {
        try {
          sys.FindSet(100);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(e.what(), "Out of bounds");
          throw;
        }
      },
      std::invalid_argument);
}

TEST(DisjointSetSystemTest, NumSetsFullyDisjoint) {
  const int num_vertices = 10;
  topo::DisjointSetSystem sys{num_vertices};
  EXPECT_EQ(sys.NumSets(), num_vertices);
}

TEST(DisjointSetSystemTest, AddEdgeMultiple) {
  const int num_vertices = 3;
  topo::DisjointSetSystem sys{num_vertices};
  EXPECT_EQ(sys.NumSets(), 3);
  EXPECT_EQ(sys.FindSet(0), 0);
  EXPECT_EQ(sys.FindSet(1), 1);
  EXPECT_EQ(sys.FindSet(2), 2);
  // Build the following tree:     1
  //                              / \
  //                             0   2
  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 0);
  EXPECT_EQ(sys.NumSets(), 2);
  EXPECT_EQ(sys.FindSet(0), 1);
  EXPECT_EQ(sys.FindSet(1), 1);
  EXPECT_EQ(sys.FindSet(2), 2);

  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 2);
  EXPECT_EQ(sys.NumSets(), 1);
  EXPECT_EQ(sys.FindSet(0), 1);
  EXPECT_EQ(sys.FindSet(1), 1);
  EXPECT_EQ(sys.FindSet(2), 1);
}

TEST(DisjointSetSystemTest, UnionFromLeaves) {
  const int num_vertices = 5;
  topo::DisjointSetSystem sys{num_vertices};
  // Build the following tree:       3
  //                                . \
  //                               1   4
  //                              / \
  //                             0   2
  // by joining the {0, 1, 2} and the {3, 4} sets.
  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 0);
  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 2);
  sys.AddEdge(/*parent_index=*/3, /*child_index*/ 4);
  EXPECT_EQ(sys.NumSets(), 2);
  sys.Union(0, 4);
  EXPECT_EQ(sys.NumSets(), 1);

  // Now check the actual edges from the union.
  const std::vector<topo::Vertex> vertices = sys.Vertices();
  EXPECT_TRUE(vertices[1].parent != nullptr);
  EXPECT_EQ(vertices[1].parent->index, 3);
}

TEST(DisjointSetSystemTest, UnionFromRoots) {
  const int num_vertices = 5;
  topo::DisjointSetSystem sys{num_vertices};
  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 0);
  sys.AddEdge(/*parent_index=*/1, /*child_index*/ 2);
  sys.AddEdge(/*parent_index=*/3, /*child_index*/ 4);
  EXPECT_EQ(sys.NumSets(), 2);
  sys.Union(1, 4);
  EXPECT_EQ(sys.NumSets(), 1);

  // Now check the actual edges from the union.
  const std::vector<topo::Vertex> vertices = sys.Vertices();
  EXPECT_TRUE(vertices[1].parent != nullptr);
  EXPECT_EQ(vertices[1].parent->index, 3);
}
