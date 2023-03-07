/* #define NS_PRIVATE_IMPLEMENTATION */
/* #define CA_PRIVATE_IMPLEMENTATION */
/* #define MTL_PRIVATE_IMPLEMENTATION */
/* #include <Metal/Metal.hpp> */
/* #include <Foundation/Foundation.hpp> */
/* #include <QuartzCore/QuartzCore.hpp> */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#define M 10248
#define N 10248

// Declare
float matrix1_cpu[M][N];
float matrix2_cpu[M][N];
float matrix_ret_cpu[M][N];

// Print matrix
template<size_t m, size_t n>
std::ostream& operator<<(std::ostream& os, const float (&matrix)[m][n]) {
  for (int i=0;i<m;i++) {
    for (int j=0;j<n;j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return os;
}

template<size_t m, size_t n>
void init_random(float (&matrix)[m][n], float LOW=0.0, float HIGH=1.0) {
  for (int i=0;i<m;i++) {
    for (int j=0;j<n;j++) {
      float num = LOW + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(HIGH-LOW)));
      matrix[i][j] = num;
    }
  }
}

template<size_t m, size_t n>
void add_matrix_cpu(float (&m1)[m][n], float (&m2)[m][n], float (&ret)[m][n]) {
  for (int i=0;i<m;i++) {
    for (int j=0;j<n;j++) {
      ret[i][j] = m1[i][j] + m2[i][j];
    }
  }
}

int main() {
  /* srand(time(NULL)); */
  // Create a Metal device
  /* id<MTL::Device> device = MTL::CreateSystemDefaultDevice(); */

  /* MTL::Buffer *pBuffer = device->newBuffer( */

  // Init
  init_random(matrix1_cpu, 0, 10);
  init_random(matrix2_cpu, 0, 10);

  /* std::cout << matrix1_cpu << std::endl; */
  /* std::cout << matrix2_cpu << std::endl; */
  auto start = std::chrono::high_resolution_clock::now();
  add_matrix_cpu(matrix1_cpu, matrix2_cpu, matrix_ret_cpu);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  float in_second = static_cast<float>(duration.count())/1e6;
  float flops = M*N/in_second/1e12;
  std::cout << duration.count() << "ms" << std::endl;
  std::cout << in_second << "s" << std::endl;
  std::cout << "Single thread TFLOPS: " << flops << std::endl;
  /* std::cout << matrix_ret_cpu; */
}

