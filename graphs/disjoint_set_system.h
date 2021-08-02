// Disjoint set systems, based on [1, pp. 6-8].
// [1] Edelsbrunner & Harer (2010). Computational topology.
// Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_DISJOINT_SET_SYSTEMS_H_
#define GRAPHS_DISJOINT_SET_SYSTEMS_H_

#include <vector>

namespace topo {

struct Vertex {
  // For a root vertex, this is always `nullptr`.
  Vertex* parent = nullptr;
  // The integer index for this Vertex.
  int index;
};

class DisjointSetSystem {
 public:
  explicit DisjointSetSystem(int num_vertices);

  // Returns the name (index of the root) of the set that contains `index`.
  int FindSet(int index) const;

  // Replaces index i's and j's sets by the union of both.
  void Union(int index_i, int index_j);

  // Returns the number of separate sets in the system.
  int NumSets() const;

  // Places a directed edge between the parent and child vertices.
  void AddEdge(int parent_index, int child_index);

  // Return the underlying data structure with the graph's vertices.
  inline const std::vector<Vertex>& Vertices() const { return system_; }

 private:
  // Data structure for the disjoint set system.
  std::vector<Vertex> system_;
};

}  // namespace topo

#endif  // GRAPHS_DISJOINT_SET_SYSTEMS_H_
