IF !DEF(SAMPLE_TEST_INC)
SAMPLE_TEST_INC SET 1

SECTION "hello_world_test", ROM0
hello_world_test:  
  ld hl, $1 ; return 1 (success)
  ret


ENDC ; SAMPLE_TEST_INC