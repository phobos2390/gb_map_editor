IF !DEF(MAP_TILE_PLACEMENT_MODE)
MAP_TILE_PLACEMENT_MODE SET 1

INCLUDE "cursor_update.inc"
INCLUDE "default_button_callbacks.inc"
INCLUDE "hardware.inc"

BACK_SCRN set _SCRN0
BACK_SCRN_MIN set BACK_SCRN
BACK_SCRN_MAX set BACK_SCRN + $0400

SECTION "Map tile placement values", WRAM0
map_tile_placement_values_start:
map_tile_placement_tile_value:     DS 1
map_tile_placement_tile_pos_x:     DS 1
map_tile_placement_tile_pos_y:     DS 1
map_tile_placement_tile_spr_n:     DS 1
map_tile_placement_cursor_x:       DS 1
map_tile_placement_cursor_y:       DS 1
map_tile_placement_background_ptr: DS 2
map_tile_placement_scroll_y_max:   DS 1
map_tile_placement_scroll_x_max:   DS 1
map_tile_placement_scroll_y_min:   DS 1
map_tile_placement_scroll_x_min:   DS 1
map_tile_placement_values_end:

SECTION "Map tile placement a callback", ROM0
map_tile_placement_a_cb:
  VBLANK_WAIT_INT
  PUSH_HL_BC_DE
    ld bc, map_tile_placement_background_ptr
    call ld_hl_ibc
    ld a, [map_tile_placement_tile_value]
    ld [hl], a
    ld bc, background_start    
    ld d, a
    SUB16 hl, bc
    ld bc, _SRAM + $2
    add hl, bc
    ld a, CART_RAM_ENABLE
    ld [rRAMG], a
    ld a, d
    ld [hl], a
    ld a, CART_RAM_DISABLE
    ld [rRAMG], a    
  POP_HL_BC_DE
  jp default_button_a_cb

SECTION "Map tile placement b callback", ROM0
map_tile_placement_b_cb:
  ld a, [map_tile_placement_tile_value]
  inc a
  ld [map_tile_placement_tile_value], a
  call update_selected_tile_sprite
  jp default_button_b_cb

SECTION "Map tile placement start callback", ROM0
map_tile_placement_start_cb:
  jp default_button_start_cb

SECTION "Map tile placement select callback", ROM0
map_tile_placement_select_cb:
  ld a, [map_tile_placement_tile_value]
  dec a
  ld [map_tile_placement_tile_value], a
  call update_selected_tile_sprite
  jp default_button_select_cb

SECTION "Map tile placement up callback", ROM0
map_tile_placement_up_cb:
  ld a, [map_tile_placement_cursor_y]
  push hl
    ld hl, map_tile_placement_scroll_y_min
    cp [hl]
  pop hl
  jp z, .scroll_y
  sub $8
  ld [map_tile_placement_cursor_y], a
  ld [cursor_y], a
  jp .dec_background_ptr
.scroll_y:
  ld a, [rSCY]
  sub $8
  ld [rSCY], a
.dec_background_ptr:
  PUSH_HL_BC_DE
    ld de, map_tile_placement_background_ptr
    call ld_hl_ide
    ld bc, $FFE0 ; -= 20
    add hl, bc
    ld a, h
    cp HIGH(BACK_SCRN_MIN)
    jp nc, .loop_set_background_ptr  
.loop_background_pointer:
    add $4
    ld h, a
.loop_set_background_ptr:
    call ld_ide_hl
  POP_HL_BC_DE
.end:
  PUSH_HL_BC_DE
    call cursor_update
  POP_HL_BC_DE
  jp default_button_up_cb

SECTION "Map tile placement down callback", ROM0
map_tile_placement_down_cb:
  ld a, [map_tile_placement_cursor_y]
  push hl
    ld hl, map_tile_placement_scroll_y_max
    cp [hl]
  pop hl
  jp z, .scroll_y
  add $8
  ld [map_tile_placement_cursor_y], a
  ld [cursor_y], a
  jp .inc_background_ptr
.scroll_y:
  ld a, [rSCY]
  add $8
  ld [rSCY], a
.inc_background_ptr:
  PUSH_HL_BC_DE
    ld de, map_tile_placement_background_ptr
    call ld_hl_ide
    ld bc, $20
    add hl, bc
    ld a, h
    cp HIGH(BACK_SCRN_MAX)
    jp c, .loop_set_background_ptr  
.loop_background_pointer:
    sub $4
    ld h, a
.loop_set_background_ptr:
    call ld_ide_hl
  POP_HL_BC_DE
.end:
  PUSH_HL_BC_DE
    call cursor_update
  POP_HL_BC_DE
  jp default_button_down_cb

SECTION "Map tile placement left callback", ROM0
map_tile_placement_left_cb:
  ld a, [map_tile_placement_cursor_x]
  push hl
    ld hl, map_tile_placement_scroll_x_min
    cp [hl]
  pop hl
  jp z, .scroll_x
  sub $8
  ld [map_tile_placement_cursor_x], a
  ld [cursor_x], a
  jp .dec_background_ptr
.scroll_x:
  ld a, [rSCX]
  sub $8
  ld [rSCX], a
.dec_background_ptr:
  PUSH_HL_BC_DE
    ld de, map_tile_placement_background_ptr
    call ld_hl_ide
    ld a, l
    and $E0
    ld c, a
    dec hl
    ld a, l
    and $E0
    xor c
    jp z, .update_background_ptr_value
    ld bc, $20
    add hl, bc
.update_background_ptr_value:
    call ld_ide_hl
  POP_HL_BC_DE
.end:
  PUSH_HL_BC_DE
    call cursor_update
  POP_HL_BC_DE
  jp default_button_left_cb

SECTION "Map tile placement right callback", ROM0
map_tile_placement_right_cb:
  ld a, [map_tile_placement_cursor_x]
  push hl
    ld hl, map_tile_placement_scroll_x_max
    cp [hl]
  pop hl
  jp z, .scroll_x
  add $8
  ld [map_tile_placement_cursor_x], a
  ld [cursor_x], a
  jp .inc_background_ptr
.scroll_x:
  ld a, [rSCX]
  add $8
  ld [rSCX], a
.inc_background_ptr:
  PUSH_HL_BC_DE
    ld de, map_tile_placement_background_ptr
    call ld_hl_ide
    ld a, l
    and $E0
    ld c, a
    inc hl
    ld a, l
    and $E0
    xor c
    jp z, .update_background_ptr_value
    ld bc, $FFE0
    add hl, bc
.update_background_ptr_value:
    call ld_ide_hl
  POP_HL_BC_DE
.end:
  PUSH_HL_BC_DE
    call cursor_update
  POP_HL_BC_DE
  jp default_button_right_cb

SECTION "Update tile selected sprite", ROM0
update_selected_tile_sprite:
  PUSH_HL_BC_DE
    ld hl, map_tile_placement_tile_value
    ld a, [hl+] ; ld a, [map_tile_placement_tile_value]
    ld d, a
    ld a, [hl+] ; ld a, [map_tile_placement_tile_pos_x]
    ld b, a
    ld a, [hl+] ; ld a, [map_tile_placement_tile_pos_y]
    ld c, a     
    xor a
    ld e, a
    ld a, [hl+] ; ld a, [map_tile_placement_tile_spr_n]
    ;   b - x position
    ;   c - y position
    ;   d - character tile 
    ;   e - flags
    ;   a - sprite number
    call set_sprite_a
  POP_HL_BC_DE
  ret

SECTION "Map tile placement mode", ROM0
set_map_tile_placement_mode:
  call set_default_button_mode
  ld a, disable_a_held & disable_b_held & disable_select_held
  ld [held_mask], a

  ld hl, map_tile_placement_a_cb
  ld bc, button_a_f
  call ld_ibc_hl

  ld hl, map_tile_placement_b_cb
  ld bc, button_b_f
  call ld_ibc_hl

  ld hl, map_tile_placement_start_cb
  ld bc, button_start_f
  call ld_ibc_hl

  ld hl, map_tile_placement_select_cb
  ld bc, button_select_f
  call ld_ibc_hl

  ld hl, map_tile_placement_up_cb
  ld bc, pad_up_f
  call ld_ibc_hl

  ld hl, map_tile_placement_down_cb
  ld bc, pad_down_f
  call ld_ibc_hl

  ld hl, map_tile_placement_left_cb
  ld bc, pad_left_f
  call ld_ibc_hl

  ld hl, map_tile_placement_right_cb
  ld bc, pad_right_f
  call ld_ibc_hl

  call update_selected_tile_sprite
  ret

SECTION "Init map tile placement mode", ROM0
init_map_tile_placement_mode:
  ld hl, map_tile_placement_values_start
  ld a, $0D
  ld [hl+], a ; ld [map_tile_placement_tile_value], $20
  ld a, $10
  ld [hl+], a ; ld [map_tile_placement_tile_pos_x], $10
  ld a, $98
  ld [hl+], a ; ld [map_tile_placement_tile_pos_y], $98
  ld a, $3
  ld [hl+], a ; ld [map_tile_placement_tile_spr_n], $8
  ld a, $8
  ld [hl+], a ; ld [map_tile_placement_cursor_x], $8 
  ld a, $10
  ld [hl+], a ; ld [map_tile_placement_cursor_y], $10
  ld a, LOW(BACK_SCRN)
  ld [hl+], a
  ld a, HIGH(BACK_SCRN)
  ld [hl+], a ; ld [map_tile_placement_background_ptr], BACK_SCRN
  ld a, $90
  ld [hl+], a ; ld [map_tile_placement_scroll_y_max], $90 (Tile $12)
  ld a, $A0
  ld [hl+], a ; ld [map_tile_placement_scroll_x_max], $A0 (Tile $14)
  ld a, $10
  ld [hl+], a ; ld [map_tile_placement_scroll_y_min], $10
  ld a, $8
  ld [hl+], a ; ld [map_tile_placement_scroll_x_min], $8  
  ret

ENDC ; MAP_TILE_PLACEMENT_MODE