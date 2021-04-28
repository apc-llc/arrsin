import numpy as np
import timeit

x = np.random.uniform(-1, 1, size=(int(1e8),))

start_time = timeit.default_timer()
f = lambda x_i: np.sin(x_i)
x = f(x)
print(timeit.default_timer() - start_time)

# BENCH DEV Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
# BENCH NAME CPU (Python)
# BENCH EXEC python3 ./arrsin.py
# BENCH SCORE 1.5295206309999998
# BENCH CHECK check sum = -3187.199840
