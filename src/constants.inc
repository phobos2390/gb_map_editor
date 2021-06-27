; src/constants.inc
IF !DEF(CONSTANTS_INC)
CONSTANTS_INC SET 1

INCLUDE "hardware.inc"

OAM_tileset_start EQU $8000
tileset_start EQU $8000
tile_size EQU $10
background_start EQU _SCRN0
background_size EQU $400
back_width EQU $20
width_mask EQU $E0
back_height EQU $20
font_shadow EQU _SRAM + $2

ENDC ; CONSTANTS_INC
