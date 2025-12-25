.PHONY: all build debug test benchmark lint format coverage clean help

# Variables
BUILD_DIR = build
CMAKE = cmake
MAKE = make

# Default target
all: build

# Build in Release mode
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON
	@cd $(BUILD_DIR) && $(MAKE)

# Build in Debug mode with coverage
debug:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON
	@cd $(BUILD_DIR) && $(MAKE)

# Run all tests
test: debug
	@echo "Running tests..."
	@cd $(BUILD_DIR) && ./test_array
	@cd $(BUILD_DIR) && ./test_list
	@cd $(BUILD_DIR) && ./test_stack
	@cd $(BUILD_DIR) && ./test_queue
	@cd $(BUILD_DIR) && ./test_hash_table
	@cd $(BUILD_DIR) && ./test_tree
	@echo "\nAll tests completed!"

# Run benchmarks
benchmark: build
	@echo "Running benchmarks..."
	@cd $(BUILD_DIR) && ./benchmark

# Run linter
lint:
	@echo "Running clang-tidy..."
	@clang-tidy src/*.cpp -- -std=c++17 -I./src
	@clang-tidy tests/*.cpp -- -std=c++17 -I./src -I./tests

# Format code
format:
	@echo "Running clang-format..."
	@clang-format -i src/*.cpp src/*.h tests/*.cpp

# Generate coverage report
coverage: debug test
	@echo "Generating coverage report..."
	@cd $(BUILD_DIR) && lcov --capture --directory . --output-file coverage.info
	@cd $(BUILD_DIR) && lcov --remove coverage.info '/usr/*' --output-file coverage.info
	@cd $(BUILD_DIR) && lcov --list coverage.info
	@cd $(BUILD_DIR) && genhtml coverage.info --output-directory ../docs/coverage_report
	@echo "Coverage report generated in docs/coverage_report"

# Run main program
run: build
	@cd $(BUILD_DIR) && ./main

# Clean build directory
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf docs/coverage_report
	@rm -f *.bin
	@echo "Cleaned build directory"

# Show help
help:
	@echo "Available targets:"
	@echo "  build     - Build project in Release mode"
	@echo "  debug     - Build project in Debug mode with coverage"
	@echo "  test      - Build and run all tests"
	@echo "  benchmark - Build and run benchmarks"
	@echo "  lint      - Run clang-tidy"
	@echo "  format    - Format code with clang-format"
	@echo "  coverage  - Generate coverage report"
	@echo "  run       - Build and run main program"
	@echo "  clean     - Clean build directory"
	@echo "  help      - Show this help"