IF !DEF(CURSOR_UPDATE_INC)
CURSOR_UPDATE_INC SET 1

INCLUDE "oam_utils.inc"

SECTION "Cursor values", WRAM0
cursor_values_start:
cursor_x: ds 1
cursor_y: ds 1
cursor_tile_start: ds 1
cursor_tile_current: ds 1
cursor_tile_end: ds 1
cursor_sprite_number: ds 1
cursor_values_end:

SECTION "Cursor init", ROM0
cursor_init:
  xor a ; ld a, $0 fast
  ld hl, cursor_values_start
  ld [hl+], a ; ld via a [cursor_x], $0
  ld [hl+], a ; ld via a [cursor_y], $0
  inc a
  ld [hl+], a ; ld via a [cursor_tile_start], $1
  ld [hl+], a ; ld via a [cursor_tile_current], $1
  inc a
  ld [hl+], a ; ld via a [cursor_tile_end], $2
  ld [hl], a  ; ld via a [cursor_sprite_number], $2
  ret

SECTION "Cursor update", ROM0
cursor_update:
  ld hl, cursor_tile_current
  ld a, [hl+]
  cp [hl] ; cursor_tile_current > cursor_tile_end?
  jp nz, .inc_tile
  ; cursor_tile_current == cursor_tile_end
  ld hl, cursor_tile_start
  ld a, [hl+]
  ld [hl], a ; ld [cursor_tile_current], [cursor_tile_start]
  jp .update_oam_sprite
.inc_tile:
  inc a
  dec hl
  ld [hl], a
.update_oam_sprite:
  xor a
  ld e, a     ; e = 0
  ld hl, cursor_values_start
  ld a, [hl+] ; ld a, [cursor_x]
  ld b, a     ; b = x position
  ld a, [hl+] ; ld a, [cursor_y]
  ld c, a     ; c = y position
  inc hl      ; hl: cursor_tile_start -> cursor_tile_current
  ld a, [hl+] ; ld a, [cursor_tile_current]
  ld d, a     ; d = current cursor tile
  inc hl      ; hl: cursor_tile_end -> cursor_sprite_number
  ld a, [hl]  ; ld a, [cursor_sprite_number]  
;   b - x position
;   c - y position
;   d - character tile 
;   e - flags
;   a - sprite number
  call set_sprite_a
  ret

ENDC ; CURSOR_UPDATE_INC