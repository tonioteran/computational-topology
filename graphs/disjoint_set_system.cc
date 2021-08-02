#include "disjoint_set_system.h"

namespace topo {

DisjointSetSystem::DisjointSetSystem(int num_vertices)
    : num_vertices_(num_vertices) {
  system_ = std::vector<Vertex>(num_vertices);
}

int DisjointSetSystem::FindSet(int index) const {
  // TODO(tonioteran) Implement.
}

void DisjointSetSystem::Union(int index_i, int index_j) {
  // TODO(tonioteran) Implement.
}

}  // namespace topo
