#include "graphviz_utils.h"

#include <fstream>

namespace topo {

void WriteGraphToDisk(const std::string& output_file,
                      const DisjointSetSystem& system) {
  std::ofstream out_stream(output_file);
  out_stream << "digraph {\n";

  for (const Vertex& v : system.Vertices()) {
    if (v.parent == nullptr) {
      out_stream << v.index << "\n";
    } else {
      out_stream << v.parent->index << " -> " << v.index << "\n";
    }
  }

  out_stream << "}\n";
  out_stream.close();
}

}  // namespace topo
