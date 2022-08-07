# Description

This is an implementation of the universally composable oblivious transfer protocol presented in [CRYPTO'08](https://link.springer.com/chapter/10.1007/978-3-540-85174-5_31). 

The repository includes:
- A library for operations inside fields of prime order
- A library for Elliptic Curve Cryptography operations (specifically curve secp256r1 and curve bn254). 
- A library for dual-mode encryption scheme (it currently contains only a construction base don DDH). 
- The OT protocol 

# Building
```
mkdir build
cd build && cmake ..
make
ctest --verbose
```
