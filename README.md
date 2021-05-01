# n-queens

Stupid n-queens implementation in C++ to solve an example in a book

A solution with n=8:

```
👸⬜⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛👸⬛⬜⬛
⬛⬜⬛⬜⬛⬜⬛👸
⬜⬛⬜⬛⬜👸⬜⬛
⬛⬜👸⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛👸⬛
⬛👸⬛⬜⬛⬜⬛⬜
⬜⬛⬜👸⬜⬛⬜⬛
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
N_QUEENS_BLACK="• " N_QUEENS_WHITE="• " N_QUEENS_QUEEN="♛ " ./build/n_queens 
N_QUEENS_BLACK="⬛ " N_QUEENS_WHITE="⬜ " N_QUEENS_QUEEN="👸 " ./build/n_queens
```

## Example of alternative build and run

```bash
cmake -H. -Bbuild -DNB_QUEENS=4
cmake --build build
N_QUEENS_BLACK="• " N_QUEENS_WHITE="• " N_QUEENS_QUEEN="♛ " ./build/n_queens 
```

```
• ♛ • • 
• • • ♛ 
♛ • • • 
• • ♛ •
```
