import numpy as np
import timeit

x = np.random.uniform(-1, 1, size=(int(1e8),))

start_time = timeit.default_timer()
f = lambda x_i: np.sin(x_i)
x = f(x)
print(timeit.default_timer() - start_time)

# python3 ./arrsin.py
# 1.5295206309999998

