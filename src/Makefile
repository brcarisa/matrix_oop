TARGET = matrix_oop.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -O3 -lstdc++
TEST_FLAGS = -lgtest -pthread
TEST_TARGET = testing_exe
MODULES= $(wildcard *.cc)
OBJECTS = $(patsubst %.cc, %.o, $(MODULES))

all: clean $(TARGET)

build: $(TARGET)

rebuild: clean $(TARGET)

%.o: %.cc
	@mkdir -p obj
	@$(CC) -c $(CFLAGS) $< -o ./obj/$@

$(TARGET): $(OBJECTS)
	@ar rc $(TARGET) $(wildcard obj/*.o)

test: $(TARGET)
	@g++ $(CFLAGS) ./test/*.cc $(TEST_FLAGS) $(TARGET) -o ./test/$(TEST_TARGET)
	@./test/$(TEST_TARGET)

clean:
	@rm -rf obj *.a *.o test/$(TEST_TARGET) *.dSYM **/*.dSYM *.log **/*.log

.PHONY: all build rebuild test clean
