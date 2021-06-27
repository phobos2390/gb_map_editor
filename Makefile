NAME := map_editor
TEST_NAME := test_$(NAME)
MBC_TYPE := 0x1B
RAM_SIZE := 0x2
TEST_ENGINE_DIR := ./gb_asm_test/src
UTILS_DIR := ./gb_asm_utils
TEST_DIRECTORY := ./src/test
ADDITIONAL_INCLUDES := "-i ./src"
EMULATOR := sameboy
DEBUGGER := sameboy_debugger

build:
	@mkdir -p build
	rgbasm -i $(UTILS_DIR)/src -i data -i src src/*.asm -o build/$(NAME).o 
	rgblink -o build/$(NAME).gb build/$(NAME).o -m build/$(NAME).map -n build/$(NAME).sym
	rgbfix -c -m $(MBC_TYPE) -r $(RAM_SIZE) -v -p 0 build/$(NAME).gb

build_test:
	make -f gb_asm_test/Makefile build_test \
	    ADDITIONAL_INCLUDES=$(ADDITIONAL_INCLUDES) \
	    TEST_ENGINE_DIR=$(TEST_ENGINE_DIR) \
	    TEST_DIRECTORY=$(TEST_DIRECTORY) \
	    TEST_NAME=$(TEST_NAME)

clean:
	rm -rf build/
	
run: build
	$(EMULATOR) build/$(NAME).gb

test: build_test
	$(DEBUGGER) build/$(TEST_NAME).gb

all: build_test

