; main area
INCLUDE "vblank_utils.inc"
INCLUDE "hardware.inc"
INCLUDE "register_utils.inc"
INCLUDE "print_utils.inc"
INCLUDE "constants.inc"
INCLUDE "interrupt_vectors.inc"
INCLUDE "vram_utils.inc"
INCLUDE "joypad_eval.inc"
INCLUDE "oam_utils.inc"
INCLUDE "timing_utils.inc"
INCLUDE "sram_utils.inc"
INCLUDE "model_number_util.inc"

INCLUDE "cursor_update.inc"
INCLUDE "default_button_callbacks.inc"
INCLUDE "map_tile_placement_mode.inc"
INCLUDE "stream_tiles.inc"
INCLUDE "map_edit_save.inc"

INCLUDE "furnace_stream.inc"

SECTION "Game code", ROM0
main:
  ld [GB_model_number], a
  call init_display
  call init_font
  call init_window
  call init_vblank_list
  call init_timing_table
  
  call init_vram_iterator

  call init_joypad_table
  call init_callbacks


  call init_sprite_table

  call cursor_init
  
  call timer_cb_init

  ld de, timing_table_cb
  call int_set_timer_de

  call init_vblank_callback

  call user_init

  call final_init
  ei

  jp main_loop

.lockup
  halt
  jp .lockup

  halt
  halt

SECTION "user data init", ROM0
user_init:
  call init_map_tile_placement_mode
  call set_map_tile_placement_mode

  ld a, $36
  ld bc, furnace_stream.full_sequence_start
  ld de, furnace_stream.full_sequence_end
  call init_stream_tile_a_bc_de

  call init_map

  ret

SECTION "INIT vblank callback", ROM0
init_vblank_callback:
  ld hl, vblank_callback
  LD_I_ADDR_R16 vblank_f, hl
  ret

SECTION "vblank_callback", ROM0
vblank_callback:
  call read_joypad
  call eval_held_button
  call eval_rising_edge
  call dma_update_sprites
  ret

SECTION "INIT timers", ROM0
timer_cb_init:
  call set_cursor_upper_left

  ld hl, update_stream_tile
  ld bc, 0
  ld de, $10
  call add_timing_table_entry_callback

  ld hl, cursor_update ; hl function
  ld bc, 0             ; bc context
  ld de, $10           ; de ticks_per_invocation  
  call add_timing_table_entry_callback

  ld hl, button_sprite_timeout_cb ; hl function
  ld bc, 0                        ; bc context
  ld de, $1                       ; de ticks_per_invocation
  call add_timing_table_entry_callback

  ret

SECTION "setup cursor", ROM0
set_cursor_upper_left:
  ld a, $10
  ld [cursor_y], a
  ld a, $8
  ld [cursor_x], a
  call cursor_update
  ret

SECTION "Sprite pallete", ROM0
regular_pallete:
DW %0111111111111111
DW %0000011111100000
DW %0111110000000000
DW %0000000000000000

SECTION "set OAM sprite pallete", ROM0
init_sprite_pallete:
  ld a, [GB_model_number]
  cp $1
  ret z

  ld a, [rIE]
  push af
    ld a, IEF_VBLANK
    ld [rIE], a
    halt
    halt
  pop af
  ld [rIE], a

  ld a, %10000000
  ld [rOCPS], a

  ld c, LOW(rOCPD)

  call init_sprite_pallete.subroutine
  xor a
  ld [rOCPS], a

  ld a, %10000000
  ld [rBCPS], a

  ld c, LOW(rBCPD)
  call init_sprite_pallete.subroutine
  xor a
  ld [rBCPS], a

  ret

.subroutine:
  ld b, $8
.loop:
  ld hl, regular_pallete
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl+]
  ldh [c], a
  ld a, [hl]
  ldh [c], a
  dec b
  jr nz, .loop
  ret

  
  ret

SECTION "Initialize display", ROM0
init_display:
  VBLANK_WAIT

  xor a ; ld a, 0 ; We only need to reset a value with bit 7 reset, but 0 does the job
  ld [rLCDC], a ; We will have to write to LCDC again later, so it's not a bother, really.
  ret

SECTION "Initialize font", ROM0
init_font:
;  bc - IN & OUT size
;  de - destination pointer
  ld hl, FontTiles
  ld de, tileset_start
  ld bc, FontTilesEnd - FontTiles
  call memcopy_to_vram
  
  ret

SECTION "Finalize initialization", ROM0
final_init:
  ; Init display registers
  ld a, %11100100
  ld [rBGP], a
  ld [rOBP0], a
  ld [rOBP1], a

  call init_sprite_pallete

  xor a ; ld a, 0
  ld [rSCY], a
  ld [rSCX], a

  ; Shut sound down
  ld [rNR52], a

  ; Turn on screen, background,  bg data       window data, enable window, and sprite, tileset_select
  ld a, LCDCF_ON | LCDCF_BGON | LCDCF_BG9800 | LCDCF_WIN9C00| LCDCF_WINON | LCDCF_OBJON | LCDCF_BG8000
  ld [rLCDC], a

  ld a, [rTAC]
  or a, TACF_START ; enable timer
  ld [rTAC], a

  ld a, [rIE]
  or IEF_HILO | IEF_SERIAL | IEF_TIMER | IEF_LCDC | IEF_VBLANK
  ld [rIE], a

  ret

SECTION "Font", ROM0
FontTiles:
INCLUDE "base_tiles.inc"
INCLUDE "background.inc"
INCLUDE "ore_tiles.inc"
INCLUDE "pipe_tiles.inc"
INCLUDE "misc_tiles.inc"
INCLUDE "furnace_base.inc"
FontTilesEnd:

