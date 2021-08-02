// Disjoint set systems.
// Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_DISJOINT_SET_SYSTEMS_H_
#define GRAPHS_DISJOINT_SET_SYSTEMS_H_

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

 private:
  const int num_vertices_;
  // Data structure for the disjoint set system.
  std::vector<Vertex> system_;
};

}  // namespace topo

#endif  // GRAPHS_DISJOINT_SET_SYSTEMS_H_
