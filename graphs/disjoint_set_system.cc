#include "disjoint_set_system.h"

namespace topo {

DisjointSetSystem::DisjointSetSystem(int num_vertices) {
  system_.reserve(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    system_.push_back(Vertex{.parent = nullptr, .index = i});
  }
}

int DisjointSetSystem::FindSet(int index) const {
  if (index >= system_.size()) throw std::invalid_argument("Out of bounds");
  const Vertex& v = system_[index];
  return (v.parent == nullptr) ? v.index : FindSet(v.parent->index);
}

void DisjointSetSystem::Union(int index_i, int index_j) {
  // TODO(tonioteran) Implement.
}

int DisjointSetSystem::NumSets() const {
  int num_sets = 0;
  for (const Vertex& v : system_) {
    if (v.parent == nullptr) num_sets += 1;
  }
  return num_sets;
}

void DisjointSetSystem::AddEdge(int parent_index, int child_index) {
  Vertex& child = system_[child_index];
  child.parent = &system_[parent_index];
}

}  // namespace topo
