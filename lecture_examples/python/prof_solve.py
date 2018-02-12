
import pylab as pl


def solve_inv(A, B):
    return pl.inv(A) * B

def solve(A, B):
    return pl.solve(A, B)

A = pl.matrix(pl.randn(3000,3000))
B = pl.matrix(pl.randn(3000,1))

solve(A, B)
solve_inv(A, B)
