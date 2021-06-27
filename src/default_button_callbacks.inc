IF !DEF(DEFAULT_BUTTON_CALLBACKS_INC)
DEFAULT_BUTTON_CALLBACKS_INC SET 1

INCLUDE "register_utils.inc"

SECTION "button tile defs", WRAM0
button_tile_data:
.start:
button_tile_left: DS 1
button_tile_up: DS 1
button_tile_down: DS 1
button_tile_right: DS 1
button_tile_select: DS 1
button_tile_start: DS 1
button_tile_b: DS 1
button_tile_a: DS 1
button_sprite_details_start:
button_sprite_x: DS 1
button_sprite_y: DS 1
button_sprite_number: DS 1
button_timeout_values:
button_timeout_set_value: DS 1
button_timeout_counter: DS 1
button_tile_data_end:

SECTION "button a callback", ROM0
default_button_a_cb:
  ld a, [button_tile_a]
  jp update_button_sprite_a

SECTION "button b callback", ROM0
default_button_b_cb:
  ld a, [button_tile_b]
  jp update_button_sprite_a

SECTION "button start callback", ROM0
default_button_start_cb:
  ld a, [button_tile_start]
  jp update_button_sprite_a

SECTION "button select callback", ROM0
default_button_select_cb:
  ld a, [button_tile_select]
  jp update_button_sprite_a

SECTION "button up callback", ROM0
default_button_up_cb:
  ld a, [button_tile_up]
  jp update_button_sprite_a

SECTION "button down callback", ROM0
default_button_down_cb:
  ld a, [button_tile_down]
  jp update_button_sprite_a

SECTION "button left callback", ROM0
default_button_left_cb:
  ld a, [button_tile_left]
  jp update_button_sprite_a

SECTION "button right callback", ROM0
default_button_right_cb:
  ld a, [button_tile_right]
  jp update_button_sprite_a

SECTION "button sprite reset", ROM0
button_sprite_reset_cb:
  ld a, $0
  jp update_button_sprite_a

SECTION "update button sprite at a", ROM0
; a - sprite tile data to use
update_button_sprite_a:
  PUSH_HL_BC_DE
    ld d, a     ; d - character tile
    ld hl, button_sprite_details_start
    ld a, [hl+] ; ld a, [button_sprite_x]
    ld b, a     ; b - x position
    ld a, [hl+] ; ld a, [button_sprite_y]
    ld c, a     ; c - y position
    xor a       ; ld a, $0
    ld e, a     ; e - flags
    ld a, [hl]  ; a - sprite number
    call set_sprite_a
    ld hl, button_timeout_set_value
    ld a, [hl+] ; ld a, [button_timeout_set_value]
    ld [hl], a  ; ld [button_timeout_counter], a (counter = max value)
  POP_HL_BC_DE
  ret

SECTION "countdown button timeout", ROM0
button_sprite_timeout_cb:
  push hl
    ld a, [button_timeout_counter] 
    dec a
    jp nz, .update_counter
  pop hl
  jp button_sprite_reset_cb
.update_counter:
    ld [button_timeout_counter], a
  pop hl
  ret

SECTION "init default button callbacks", ROM0
init_default_button_callbacks:
;    button callback function order
;    pad_up_f
;    pad_down_f
;    pad_left_f
;    pad_right_f
;    button_a_f
;    button_b_f
;    button_start_f
;    button_select_f

  ld bc, pad_up_f
  ld hl, default_button_up_cb
  call ld_ibc_hl ; pad_up_f = &default_button_up_cb

  ld bc, pad_down_f
  ld hl, default_button_down_cb
  call ld_ibc_hl ; pad_down_f = &default_button_down_cb

  ld bc, pad_left_f
  ld hl, default_button_left_cb
  call ld_ibc_hl ; pad_left_f = &default_button_left_cb

  ld bc, pad_right_f
  ld hl, default_button_right_cb
  call ld_ibc_hl ; pad_right_f = &default_button_right_cb

  ld bc, button_a_f
  ld hl, default_button_a_cb
  call ld_ibc_hl ; pad_a_f = &default_button_a_cb

  ld bc, button_b_f
  ld hl, default_button_b_cb
  call ld_ibc_hl ; pad_b_f = &default_button_b_cb

  ld bc, button_start_f
  ld hl, default_button_start_cb
  call ld_ibc_hl ; pad_start_f = &default_button_start_cb

  ld bc, button_select_f
  ld hl, default_button_select_cb
  call ld_ibc_hl ; pad_select_f = &default_button_select_cb
  ret

SECTION "init default button data", ROM0
init_default_button_data:
  ld hl, button_tile_data
  ld a, $3
  ld [hl+], a ; ld [button_tile_left], $6
  inc a
  ld [hl+], a ; ld [button_tile_up], $7
  inc a
  ld [hl+], a ; ld [button_tile_down], $8
  inc a
  ld [hl+], a ; ld [button_tile_right], $9
  inc a
  ld [hl+], a ; ld [button_tile_select], $A
  inc a
  ld [hl+], a ; ld [button_tile_start], $B
  inc a
  ld [hl+], a ; ld [button_tile_b], $C
  inc a
  ld [hl+], a ; ld [button_tile_a], $D
  ld a, $8
  ld [hl+], a ; ld [button_tile_sprite_x], $80
  ld a, $98
  ld [hl+], a ; ld [button_tile_sprite_y], $80
  ld a, $1
  ld [hl+], a ; ld [button_tile_sprite_number], $1 ; OAM sprite 1
  ld a, $8
  ld [hl+], a ; ld [button_timeout_set_value], $10
  ld [hl], a  ; ld [button_timeout_counter], $10
  ret

SECTION "set default button mode", ROM0
set_default_button_mode:
  call init_default_button_data
  call init_default_button_callbacks
  ret

ENDC ; DEFAULT_BUTTON_CALLBACKS_INC