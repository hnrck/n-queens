# n-queens

Stupid n-queens implementation in C++ to solve an example in a book

A solution with n=8:

```
πΈβ¬β¬β¬β¬β¬β¬β¬
β¬β¬β¬β¬πΈβ¬β¬β¬
β¬β¬β¬β¬β¬β¬β¬πΈ
β¬β¬β¬β¬β¬πΈβ¬β¬
β¬β¬πΈβ¬β¬β¬β¬β¬
β¬β¬β¬β¬β¬β¬πΈβ¬
β¬πΈβ¬β¬β¬β¬β¬β¬
β¬β¬β¬πΈβ¬β¬β¬β¬
```

# Usage

## Compile

```bash
cmake -H. -Bbuild
cmake --build build
```

## Execute

```bash
./build/n_queens
```

# Alternative usage

## Change number of queens at compile time

```bash
cmake -H. -Bbuild -DNB_QUEENS=4
```

## Change string representation at run time

```bash
N_QUEENS_BLACK="β’ " N_QUEENS_WHITE="β’ " N_QUEENS_QUEEN="β " ./build/n_queens 
N_QUEENS_BLACK="β¬ " N_QUEENS_WHITE="β¬ " N_QUEENS_QUEEN="πΈ " ./build/n_queens
```

## Example of alternative build and run

```bash
cmake -H. -Bbuild -DNB_QUEENS=4
cmake --build build
N_QUEENS_BLACK="β’ " N_QUEENS_WHITE="β’ " N_QUEENS_QUEEN="β " ./build/n_queens 
```

```
β’ β β’ β’ 
β’ β’ β’ β 
β β’ β’ β’ 
β’ β’ β β’
```
