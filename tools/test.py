import numpy as np
import time


def benchmark(flop, op, op_name):
  print(op_name)
  print(f"{flop/1e9:.3f} GFLOP")
  start = time.monotonic()
  op()
  end = time.monotonic()
  d = end-start
  print(f"Time: {d*1000:.3f}ms")
  print(f"{(flop/d)*1e-9:.3f} GFLOP/S")
  print()

n = 8192
A = np.random.rand(n, n).astype(np.float64)
B = np.random.rand(n, n).astype(np.float64)

benchmark(n*n*2*n, lambda: A@B, "matmul")
# benchmark(n*n, lambda: A+B, "add")
