CPP = @clang++
CPPFLAGS = -std=c++17 -march=native -O2 -pthread \
           $(WARNING_FLAGS) $(INCLUDE_FLAGS)
WARNING_FLAGS = -Wall -Wextra -Wpedantic \
                -Wshadow -Wconversion -Wdeprecated -Wold-style-cast\
                -Wfatal-errors -Werror
INCLUDE_FLAGS = -I$(SRC_DIR) -I$(CATCH_DIR) -I$(STB_DIR) -I$(PROGRESSBAR_DIR)

DIR_GUARD = @mkdir -p $(@D)
ECHO = @echo
REMOVE = @rm -rf

################################################################################
# Directories
################################################################################
SRC_DIR = src
TESTS_DIR = tests
BUILD_DIR = build

################################################################################
# Libraries
################################################################################
CATCH_DIR = vendor/catchorg/Catch2
STB_DIR = vendor/nothings/stb
PROGRESSBAR_DIR = vendor/prakhar1989/progress-cpp

################################################################################
# Files
################################################################################
BIN = raytracer
TEST_BIN = test
SRC_FILES = $(wildcard $(SRC_DIR)/Core/*.cpp) \
            $(wildcard $(SRC_DIR)/Scene/*.cpp) \
            $(wildcard $(SRC_DIR)/Scene/Lights/*.cpp) \
            $(wildcard $(SRC_DIR)/Scene/Objects/*.cpp) \
            $(wildcard $(SRC_DIR)/Scene/Objects/Materials/*.cpp) \
            $(wildcard $(SRC_DIR)/Scene/Objects/Materials/Patterns/*.cpp) \
			$(wildcard $(SRC_DIR)/Chapters/*.cpp)
TEST_FILES = $(wildcard $(TESTS_DIR)/*.test.cpp)
TEST_MAIN = $(TESTS_DIR)/TestMain.cpp
MAIN = $(SRC_DIR)/Main.cpp

MAIN_OBJ = $(MAIN:%.cpp=$(BUILD_DIR)/%.o)
SRC_OBJ = $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJ = $(TEST_FILES:%.cpp=$(BUILD_DIR)/%.o) \
           $(TEST_MAIN:%.cpp=$(BUILD_DIR)/%.o)

################################################################################
# Dependencies
################################################################################
MAIN_DEP = $(MAIN_OBJ:%.o=%.d)
SRC_DEP = $(SRC_OBJ:%.o=%.d)
TEST_DEP = $(TEST_OBJ:%.o=%.d)
DEP = $(MAIN_DEP) $(SRC_DEP) $(TEST_DEP)

################################################################################
# Build Targets
################################################################################
$(BIN) : $(MAIN_OBJ) $(SRC_OBJ)
	$(ECHO) "\033[1m\033[94m[Building]\033[0m $@"
	$(DIR_GUARD)
	$(CPP) $(CPPFLAGS) $^ -o $@

$(BUILD_DIR)/$(TEST_BIN) : $(SRC_OBJ) $(TEST_OBJ)
	$(ECHO) "\033[1m\033[94m[Building]\033[0m $@"
	$(DIR_GUARD)
	$(CPP) $(CPPFLAGS) $^ -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp Makefile
	$(ECHO) "\033[1m\033[94m[Compiling] \033[0m$<"
	$(DIR_GUARD)
	$(CPP) $(CPPFLAGS) -MMD -c $< -o $@

################################################################################
# Test
################################################################################
.PHONY : test
test : $(BUILD_DIR)/$(TEST_BIN)
	$(ECHO) "\033[1m\033[94m[Running Tests]\033[0m"
	@./$<

################################################################################
# Run
################################################################################
.PHONY : run
run : $(BIN)
	$(ECHO) "\033[1m\033[94m[Running Ray Tracer]\033[0m"
	@./$<

################################################################################
# Clean
################################################################################
.PHONY : clean
clean :
	$(ECHO) "\033[1m\033[94m[Cleaning up]\033[0m"
	$(REMOVE) $(BUILD_DIR) $(BIN)
