# khyberDB

A simple in-memory key-value cache database with CLI interface, implemented in C++20.

## Motivation

Modern C++ key-value store demonstrating idiomatic C++20 and best practices.

## Quickstart

### C++ Build (Linux/macOS)

**Prerequisites:**
- C++20-capable compiler (GCC 12+ or Clang 15+)
- CMake 3.20+
- Ninja (recommended) or Make

**Build Steps:**
```bash
# Configure
cmake -S . -B build -G Ninja

# Build
cmake --build build

# Run tests
cmake --build build --target test
```

**Or using Make:**
```bash
mkdir build && cd build
cmake ..
make
make test
```

### Running the CLI

```bash
./build/khyberdb put key1 value1
./build/khyberdb get key1
./build/khyberdb delete key1
./build/khyberdb size
```

## Testing and Benchmarks

```bash
# Run tests
cd build && ctest --output-on-failure

# Run benchmarks
./build/bench_khyberdb
```

## Development Workflow

### Branch Strategy
- `master`: Stable C++ implementation
- `rust-to-cpp20`: Migration history (original port)

### Commit Conventions
Standard commit messages with clear descriptions

### Static Analysis

**clang-tidy:**
```bash
clang-tidy src/*.cpp -checks=* -- -I src -std=c++20
```

**clang-format:**
```bash
clang-format -i src/*.cpp src/*.h
```

### Sanitizer Builds

**Debug build with sanitizers:**
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build
```

ASAN and UBSAN are automatically enabled in Debug builds.

## Migration Status

See [migration-plan.md](migration-plan.md) for detailed status.

### Completed
- ✅ Core DB implementation
- ✅ CLI interface
- ✅ Unit tests
- ✅ CMake build system
- ✅ CI/CD pipeline

### In Progress
- ⏳ Integration tests
- ⏳ Benchmark comparisons

## Architecture

See [ARCHITECTURE.md](ARCHITECTURE.md) for system design and diagrams.

## Key Design Choices

| Feature | Implementation |
|---------|---------------|
| Key-Value Store | `std::unordered_map<K, V>` |
| Optional Returns | `std::optional<T>` |
| String Parameters | `const std::string&` |
| CLI Parsing | `CLI11` |
| Module System | Headers + namespace |

## Design Notes

### Error Handling
- Simple cases: `std::optional` for nullable returns
- Complex errors: Would use `tl::expected<T, E>` (dependency included)

### Memory Management
- RAII for automatic cleanup
- No manual memory management required

### Concurrency
- Single-threaded design (not thread-safe)
- Could be extended with mutex guards if needed

## Contributing

1. Fork the repository
2. Create a feature branch from `master`
3. Make changes with tests
4. Ensure CI passes
5. Open a pull request

## License

[To be specified]