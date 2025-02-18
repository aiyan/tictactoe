#include "Benchmark.h"
#include "RandomAgent.h"
#include "ManualAgent.h"
#include "PerfectAgent.h"

int main(int argc, char **argv) {
  auto A1 = new PerfectAgent{};
  auto A2 = new PerfectAgent{};

//Benchmark::match(A1, A2);
  Benchmark::benchmark(A1, 10000);

  delete A1;
  delete A2;

  return 0;
}
