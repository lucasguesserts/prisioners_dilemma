![Logo of the project](./prisoners_dilemma_logo.svg)
Logo made from the original images: <a href="https://www.vecteezy.com/free-vector/devil">Devil</a> and <a href="https://www.vecteezy.com/free-vector/angel-wings">Angel</a>.

# Prisoner's Dilemma

Simulate a competition among several different strategies.

## Getting started

### Building and Installing

```shell
git clone git@github.com:lucasguesserts/prisoners_dilemma.git
cd prisoners_dilemma
./install_catch2.sh
./install_hdf5.sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
make test
make install
```

Execute instead `cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install/prefix` if you want the install location to be `/path/to/install/prefix`.

### Dependencies

This project depends on two libraries: [HDF5](https://bitbucket.hdfgroup.org/projects/HDFFV/repos/hdf5/browse) and [Catch2](https://github.com/catchorg/Catch2). For both of them, scripts for installing are made available.

You will also need some tools for building the project. The REQUIRED tools are: GCC, GNU Make, CMake, Git, wget, and tar.

## Using

Once installed, you can start using the project. Add the following command to your top level `CMakeLists.txt`:

```cmake
find_package(prisoners_dilemma)
```

### Other Options

#### Using the `Findprisoners_dilemma.cmake`

It is available the [Findprisoners_dilemma.cmake](./pkg/Findprisoners_dilemma.cmake). Install the project and add the following line to your top level `CMakeLists.txt`:

```cmake
set(CMAKE_MODULE_PATH "path/to/Findprisoners_dilemma.cmake")
```

#### Different install prefix

If you have installed the project not in a default location, then add the following line to your top level `CMakeLists.txt`:

```cmake
set(prisoners_dilemma_ROOT "/path/to/install/prefix")
```

## Links

- Project homepage: https://github.com/lucasguesserts/prisoners_dilemma
- Issue tracker: https://github.com/your/awesome-project/issues
- Useful resources:
  - Catch2 project, the test framework used here and recommended for writing unit-tests: https://github.com/catchorg/Catch2
  - Prisoners dilemma strategies: http://www.prisoners-dilemma.com/


## Licensing

The code in this project is licensed under [MIT License](./LICENSE).