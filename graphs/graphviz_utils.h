// Simple utilities for producing dot graphviz files from disjoint set systems.
// Antonio Teran (toniioteran@gmail.com)

#ifndef GRAPHS_GRAPHVIZ_UTILS_H_
#define GRAPHS_GRAPHVIZ_UTILS_H_

#include "disjoint_set_system.h"

namespace topo {

// Creates graphviz-compatible dot file with the `system`s graph representation.
void WriteGraphToDisk(const std::string& output_file,
                      const DisjointSetSystem& system);

}  // namespace topo

#endif  // GRAPHS_GRAPHVIZ_UTILS_H_
