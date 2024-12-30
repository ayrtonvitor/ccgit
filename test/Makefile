PROJECT_DIR := ..
SRC_DIR := $(PROJECT_DIR)/src
BUILD_DIR := $(PROJECT_DIR)/build
TEST_DIR := $(PROJECT_DIR)/test
TEST_EXEC := $(BUILD_DIR)/tests/all_tests

CC := gcc
CFLAGS := -Wall -Wextra -g -I$(SRC_DIR)
CLFLAGS := -lcmocka

CMAKE_TOOLCHAIN_FILE := ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
CMAKE_FLAGS := -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_DIR := $(TEST_DIR)/build/objects
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRCS))
SRC_OBJ_DIR := $(BUILD_DIR)/CMakeFiles/git.dir/src
SRC_OBJS := $(filter-out $(SRC_OBJ_DIR)/main.c.o, $(wildcard $(SRC_OBJ_DIR)/*.o))

.PHONY: all
all: build build_tests run_tests clean rebuild

.PHONY: build
build:
	@echo "Build the project..."
	cmake -B $(BUILD_DIR) -S $(PROJECT_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR)

.PHONY: build_tests
build_tests: $(TEST_OBJS)
	@echo "Building the tests..."
	$(CC) $(TEST_OBJS) -o $(TEST_EXEC) $(SRC_OBJS) $(CLFLAGS)
	@echo "Test exectuable created: $(TEST_EXEC)"

$(TEST_OBJS): $(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run_tests
run_tests: build_tests
	@echo "Running the tests..."
	$(TEST_EXEC)

.PHONY: clean
clean:
	@echo "Cleaning the test exec directory..."
	rm -rf $(TEST_EXEC)

.PHONY: rebuild
rebuild: clean build
