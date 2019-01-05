LINKER        = g++
LINKERFLAGS   =  -s
COMPILER      = g++
COMPILERFLAGS =  -std=c++14 -Wall
BIN           = expr-parser-test
LIBS          = -lboost_filesystem -lboost_system
vpath %.cpp src
vpath %.o build
OBJ           = expr-parser-test.o get_processed_text.o get_init_state.o print_char32.o search_char.o sets_for_classes.o expr_scaner.o idx_to_string.o error_count.o aux_expr_scaner.o char_conv.o file_contents.o char_trie.o fsize.o expr_parser.o aux_expr_scaner_classes_table.o
LINKOBJ       = build/expr-parser-test.o build/get_processed_text.o build/get_init_state.o build/print_char32.o build/search_char.o build/sets_for_classes.o build/expr_scaner.o build/idx_to_string.o build/error_count.o build/aux_expr_scaner.o build/char_conv.o build/file_contents.o build/char_trie.o build/fsize.o build/expr_parser.o build/aux_expr_scaner_classes_table.o

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom 
	rm -f ./build/*.o
	rm -f ./build/$(BIN)

.cpp.o:
	$(COMPILER) -c $< -o $@ $(COMPILERFLAGS) 
	mv $@ ./build

$(BIN):$(OBJ)
	$(LINKER) -o $(BIN) $(LINKOBJ) $(LIBS) $(LINKERFLAGS)
	mv $(BIN) ./build