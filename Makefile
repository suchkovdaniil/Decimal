FLAGS := -Wall -Werror -Wextra -std=c11
BUILD_DIR := ./build
CORE_DIR := ./core
CORE_SOURCE := $(wildcard $(CORE_DIR)/s21_*.c)
CORE_OBJECTS := $(patsubst $(CORE_DIR)/%.c, $(BUILD_DIR)/%.o, $(CORE_SOURCE))
UNAME_S := $(shell uname -s)


ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
	CFLAGS = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	CFLAGS = 
endif

all: clean s21_string.a

clean:
	rm -f s21_string.a
	rm -rf $(BUILD_DIR)
	rm -f $(CORE_DIR)/*.o
	rm -f ./test.out
	rm -rf ./logs
	rm -rf *.gcov

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(CORE_DIR)/%.c | $(BUILD_DIR)
	gcc $(FLAGS) -c $< -o $@

s21_string.a: $(CORE_OBJECTS)
	ar rc s21_string.a $^

gcov_report: s21_string.a
	mkdir -p logs
	gcc -fprofile-arcs -ftest-coverage s21_string.a ${CORE_SOURCE} test.c $(CFLAGS) -o logs/gcov_report
	./logs/gcov_report
	gcovr --html-details -e "test.c" -o logs/report.html
	$(OPEN_CMD) logs/report.html