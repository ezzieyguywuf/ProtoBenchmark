This is just a small test to compare two design patterns.

Make sure to clone with submodules:

```shell
$ git clone --recurse-submodules https://github.com/ezzieyguywuf/ProtoBenchmark
```

If you forgot to do that, you can still get the submodules:

```shell
$ git submodule init
$ git submodule update
```

To build:

```shell
$ mkdir build
$ cd build
$ cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON ..
$ make -j$(nproc)
```

To run:

```shell
./run
```

You can see the `benchmark` help with:

```shell
./run --help
```
