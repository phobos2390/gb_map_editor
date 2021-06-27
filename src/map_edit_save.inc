IF !DEF(MAP_EDIT_SAVE_INC)
MAP_EDIT_SAVE_INC SET 1

INCLUDE "sram_utils.inc"
INCLUDE "vram_utils.inc"

SECTION "Init map", ROM0
init_map:
        ld a, CART_RAM_ENABLE
        ld [rRAMG], a
        ld hl, _SRAM
        ld a, [hl+]
        ld h, [hl]
        ld l, a
        ld a, CART_RAM_DISABLE
        ld [rRAMG], a
        
        ld bc, $FFFF - background_size + 1
        add hl, bc
        ld a, h
        or l
        jr nz, .init_sram

.use_sram:
        ld de, background_start
        ld bc, background_size
        call memcopy_from_sram
        ret

.init_sram:
        ld d, $FF
        ld bc, $1000
        call memset_sram

        ld d, $0D
        ld hl, background_start
        ld bc, background_size
        push bc
          VBLANK_WAIT_INT
          call memset
        pop bc
        call memset_sram
        ret

ENDC