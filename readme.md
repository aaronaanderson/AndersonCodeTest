# Code Test Readme

## Cloning

This repository includes JUCE as a submodule. To initilaize the submodule automatically when cloning, use: 

```
git clone --recurse-submodules https://github.com/aaronaanderson/AndersonCodeTest.git
```

## Building 

This build uses CMake. For default generators:

```
cd AndersonCodeTest
mkdir build 
cd build
cmake ../
```
Use cmake's output to compile, resulting in an executable named 'CodeTest_Anderson'