#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>
#include <Foundation/Foundation.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <time.h>

#define N 10
// Create a Metal device
MTL::Device *device = MTL::CreateSystemDefaultDevice();
MTL::Buffer *mBufferA = device->newBuffer(N, MTL::ResourceStorageModeShared);
MTL::Buffer *mBufferB = device->newBuffer(N, MTL::ResourceStorageModeShared);
MTL::Buffer *mBufferResult = device->newBuffer(N, MTL::ResourceStorageModeShared);


void randn(MTL::Buffer *buffer) {
  float *dataPtr = (float* )buffer->contents();
  for (unsigned long index = 0; index < N; index++) {
    dataPtr[index] = (float)rand() / (float)(RAND_MAX);
  }
}

void printBuffer(MTL::Buffer *buffer) {
  float *dataPtr = (float* )buffer->contents();
  for (unsigned long index = 0; index < N; index++) {
    printf("%f ", dataPtr[index]);
  }
}

class Matrix {
  public:
    MTL::Buffer *buffer;
    std::vector<int> strides;
    std::vector<int> shapes;
    Matrix(MTL::Buffer *b) { 
      buffer = b; 
    }
};

int main() {
  srand(time(NULL));
  randn(mBufferA);
  printBuffer(mBufferA);
  /* randn(mBufferB); */
}
