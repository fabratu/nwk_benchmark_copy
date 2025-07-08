#include <chrono>
#include <cstring>
#include <iostream>
#include <optional>
#include <networkit/Globals.hpp>
#include <networkit/algebraic/AlgebraicGlobals.hpp>
#include <networkit/auxiliary/Log.hpp>
#include <networkit/auxiliary/Random.hpp>
#include <networkit/community/Modularity.hpp>
#include <networkit/community/PLM.hpp>
#include <networkit/graph/Graph.hpp>
#include <networkit/graph/GraphTools.hpp>
#include <networkit/io/METISGraphReader.hpp>
#include <networkit/io/NetworkitBinaryReader.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::seconds;
typedef std::chrono::duration<double> dur;

using namespace NetworKit;

Graph G;

int num_runs = 50;
count n;

void printUse() {
  std::cerr << "Usage: ./eval_nwk [0]\n"
            << "[0]: path to graph file in MatrixMarket, METIS or graph-tool "
               "binary format\n";
}

std::string getFileFormat(const std::string &file) {
  auto pos = file.find_last_of(".");
  if (pos != std::string::npos) {
    return file.substr(pos + 1);
  }
  return "";
}

bool parseInput(std::vector<std::string> args) {
  const auto file = args.at(1);
  const auto format = getFileFormat(file);
  if (format.empty()) {
    printUse();
    std::cerr << "first argument path must a path to a graph file" << std::endl;
    return false;
  } else if (format == "nkb") {
    G = NetworkitBinaryReader{}.read(file);
  } else if (format == "graph") {
    G = METISGraphReader{}.read(file);
  } else {
    printUse();
    std::cerr << "invalid graph format" << std::endl;
    return false;
  }
  G.removeSelfLoops();
  G.removeMultiEdges();
  assert(!G.isDirected());

  n = G.numberOfNodes();
  return true;
}

void runPLM(Graph &G) {

    auto t1 = high_resolution_clock::now();
    PLM plm(G);
    plm.run();
    auto t2 = high_resolution_clock::now();
    dur rt = t2 - t1;
    std::cout << "PLM runtime: " << rt.count() << "s" << std::endl;

    t1 = high_resolution_clock::now();
    auto part = plm.getPartition();
    t2 = high_resolution_clock::now();
    dur part_rt = t2 - t1;
    std::cout << "Partition extraction runtime: " << part_rt.count() << "s" << std::endl;

    t1 = high_resolution_clock::now();
    Modularity mod;
    double stat_w = mod.getQuality(part, G);
    t2 = high_resolution_clock::now();
    dur com_rt = t2 - t1;
    std::cout << "Modularity computation runtime: " << com_rt.count() << "s" << std::endl;
}

int main(int argc, char *argv[]) {

  Aux::Log::setLogLevel("QUIET");


  if (!parseInput(std::vector<std::string>(argv, argv + argc))) {
    return 1;
  }
      Aux::Log::setLogLevel("INFO");
  for (int i = 0; i < num_runs; i++) {
    std::cout << "Run " << i + 1 << " of " << num_runs << std::endl;
    runPLM(G);
  }

  return 0;
}