IF !DEF(TEST_LIST_INC)
TEST_LIST_INC SET 1

INCLUDE "sample_test.inc"

SECTION "test_directory", ROM0
test_defs: 
.begin:
.first_begin:
  DW hello_world_test_name, hello_world_test
.first_end:
  ; -------------------------------------------------------------------
  ;     ADD any additional tests below
  ; -------------------------------------------------------------------
.end:

sizeof_test_defs EQU (test_defs.end - test_defs.begin)
sizeof_single_test_def EQU (test_defs.first_end - test_defs.first_begin)
number_of_tests EQU sizeof_test_defs / sizeof_single_test_def

SECTION "test_names", ROM0
hello_world_test_name: DB "hello world! test",$0
; -------------------------------------------------------------------
;     ADD any additional test names below
; -------------------------------------------------------------------

ENDC ; TEST_LIST_INC
