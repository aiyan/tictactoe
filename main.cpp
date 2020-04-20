#include "Benchmark.h"
#include "RandomAgent.h"
#include "ManualAgent.h"
#include "PerfectAgent.h"

int main(int argc, char **argv) {
  Benchmark B;

  auto A1 = new PerfectAgent{};
  auto A2 = new PerfectAgent{};

//  B.match(A1, A2);
  B.benchmark(A1, 10000);

  delete A1;
  delete A2;

  return 0;
}
