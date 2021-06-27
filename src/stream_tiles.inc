IF !DEF(STREAM_TILES_INC)
STREAM_TILES_INC set 1

INCLUDE "constants.inc"
INCLUDE "register_utils.inc"
INCLUDE "vram_utils.inc"

SECTION "Tile defs", WRAM0
stream_tile_data:
.source_location_start:   DS 2
.source_location_current: DS 2
.source_location_end:     DS 2
.tileset_location:        DS 2

SECTION "Stream tile update", ROM0
update_stream_tile:
    PUSH_HL_BC_DE
      ld hl, stream_tile_data.source_location_current
      ld a, [hl+]
      ld h, [hl]
      ld l, a
      ld bc, tile_size
      add hl, bc
      ld bc, stream_tile_data.source_location_end    
      push hl
        call ld_hl_ibc
        LD_BC_HL
      pop hl
      push hl
        SUB16 hl, bc
        ld a, h
        or l    
        jr z, .set_current_to_start
      pop hl
      ld bc, stream_tile_data.source_location_current
      call ld_ibc_hl
      jr .update
.set_current_to_start:
      pop hl
      push hl
      push bc
        ld bc, stream_tile_data.source_location_start
        call ld_hl_ibc
        ld bc, stream_tile_data.source_location_current
        call ld_ibc_hl
      pop bc
      pop hl
.update:
      ld hl,stream_tile_data.source_location_current
      ld a, [hl+]
      ld h, [hl]
      ld l, a
      push hl
        ld hl, stream_tile_data.tileset_location
        call ld_de_ihl
      pop hl
      VBLANK_WAIT_INT
      ld b, tile_size
      call memcopy_fast
    POP_HL_BC_DE
    ret

SECTION "Start tile stream", ROM0
; a - tile character to stream
; bc - source start
; de - source end
init_stream_tile_a_bc_de:
    push hl
      push af
        ld hl, stream_tile_data.source_location_start
        ld a, c
        ld [hl+], a ; start
        ld a, b
        ld [hl+], a
        ld a, c
        ld [hl+], a ; current
        ld a, b
        ld [hl+], a
        ld a, e
        ld [hl+], a ; end
        ld a, d
        ld [hl+], a
      pop af
      push hl
        ld hl, tileset_start
        ld bc, tile_size
.loop:
        dec a
        jr z, .end
        add hl, bc
        jr .loop
.end:
        LD_BC_HL
      pop hl
      ld a, c
      ld [hl+], a
      ld a, b
      ld [hl+], a
    pop hl
    ret

ENDC
