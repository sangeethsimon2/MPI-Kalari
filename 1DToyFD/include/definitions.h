#include <iostream>
#include<cstdlib>
#include<cassert>
#include <vector>
#include <string>
#include <fstream>
 #include <sstream>
#include <cmath>
#include <mpi.h>
#include <cstddef>
#include <algorithm>

constexpr int MASTER=0;




void allocateMemory(std::vector<double>&, const int);
void deAllocateMemory(std::vector<double>&);
void computeArraySliceIndexForEachRank(const int&, const int&, const int&, const int&, int&, int&, int&);
void computeExchangeNeighbourIndexForEachRank(const int, const int, int&, int&);
void initialize(std::vector<double>&, const int, const int, const int, bool);
void updateVector(std::vector<double>&, const int);