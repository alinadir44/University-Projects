# Parallel Sorting with OpenMP and Pthreads
The project consists of the comparison between the parallel computing APIs Pthreads, Open MP and demonstration of the various differences in their underlying mechanisms, operation, performance, efficiency, and scalability. Sorting algorithms will be used since they most elaborately represent **data parallelism**, in which some large array to be sorted can be divided into multiple sub arrays/structures, and each of these smaller arrays will then be individually handled by a certain processor to which they will be assigned, and each processor will then perform the sorting either _concurrently_, or in _parallel_.
## Algorithms chosen for analysis
### Quick Sort (O(nlogn))
### Merge Sort (O(nlogn))
### Radix Sort (O(n*d))
## Compilation
### OpenMP
`gcc -o fname fname.c -fopenmp `
### Pthreads
`gcc -o fname fname.c -lpthread `
