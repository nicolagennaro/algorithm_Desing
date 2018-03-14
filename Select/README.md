# Select algorithm

compile with `make`
the program takes the vector size (it's randomly allocated) and the index of the value
we want to retrieve. The output is first the value returned by select, then the vector
is sorted using insertion_sort, and the correct element is printed.

the line "DFLAGS = -D DEBUG" add some output useful for debugging, discouraged if
the vector is long