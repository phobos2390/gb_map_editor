pipe_tiles_start:

pipe_tile:
.full_junction:
DB %00100100, %00100100
DB %00100100, %00100100
DB %11000011, %11000011
DB %00000000, %00000000
DB %00000000, %00000000
DB %11000011, %11000011
DB %00100100, %00100100
DB %00100100, %00100100

.left_to_ground:
DB %00000000, %00000000
DB %00111000, %00111000
DB %11111100, %11111100
DB %00001100, %00001100
DB %00001100, %00001100
DB %11111100, %11111100
DB %00111000, %00111000
DB %00000000, %00000000

.right_to_ground:
DB %00000000, %00000000
DB %00011100, %00011100
DB %00111111, %00111111
DB %00110000, %00110000
DB %00110000, %00110000
DB %00111111, %00111111
DB %00011100, %00011100
DB %00000000, %00000000

.down_to_ground:
DB %00000000, %00000000
DB %00000000, %00000000
DB %00111100, %00111100
DB %01111110, %01111110
DB %01100110, %01100110
DB %01100110, %01100110
DB %00100100, %00100100
DB %00100100, %00100100

.up_to_ground:
DB %00100100, %00100100
DB %00100100, %00100100
DB %01100110, %01100110
DB %01100110, %01100110
DB %01111110, %01111110
DB %00111100, %00111100
DB %00000000, %00000000
DB %00000000, %00000000

.left_right_pipe:
DB %00000000, %00000000
DB %00000000, %00000000
DB %11111111, %11111111
DB %00000000, %00000000
DB %00000000, %00000000
DB %11111111, %11111111
DB %00000000, %00000000
DB %00000000, %00000000

.up_down_pipe:
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100100, %00100100

.left_up_pipe:
DB %00100100, %00100100
DB %00100100, %00100100
DB %11000100, %11000100
DB %00001000, %00001000
DB %00010000, %00010000
DB %11100000, %11100000
DB %00000000, %00000000
DB %00000000, %00000000

.up_right_pipe:
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100011, %00100011
DB %00010000, %00010000
DB %00001000, %00001000
DB %00000111, %00000111
DB %00000000, %00000000
DB %00000000, %00000000

.down_left_pipe:
DB %00000000, %00000000
DB %00000000, %00000000
DB %11100000, %11100000
DB %00010000, %00010000
DB %00001000, %00001000
DB %11000100, %11000100
DB %00100100, %00100100
DB %00100100, %00100100

.right_down_pipe:
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000111, %00000111
DB %00001000, %00001000
DB %00010000, %00010000
DB %00100011, %00100011
DB %00100100, %00100100
DB %00100100, %00100100

.down_left_up_junction:
DB %00100100, %00100100
DB %00100100, %00100100
DB %11000100, %11000100
DB %00000100, %00000100
DB %00000100, %00000100
DB %11000100, %11000100
DB %00100100, %00100100
DB %00100100, %00100100

.left_up_right_junction:
DB %00100100, %00100100
DB %00100100, %00100100
DB %11000011, %11000011
DB %00000000, %00000000
DB %00000000, %00000000
DB %11111111, %11111111
DB %00000000, %00000000
DB %00000000, %00000000

.up_right_down_junction:
DB %00100100, %00100100
DB %00100100, %00100100
DB %00100011, %00100011
DB %00100000, %00100000
DB %00100000, %00100000
DB %00100011, %00100011
DB %00100100, %00100100
DB %00100100, %00100100

.right_down_left_junction:
DB %00000000, %00000000
DB %00000000, %00000000
DB %11111111, %11111111
DB %00000000, %00000000
DB %00000000, %00000000
DB %11000011, %11000011
DB %00100100, %00100100
DB %00100100, %00100100

.left_pipe_stop:
DB %00000000, %00000000
DB %10000000, %10000000
DB %10000000, %10000000
DB %10000000, %10000000
DB %10000000, %10000000
DB %10000000, %10000000
DB %10000000, %10000000
DB %00000000, %00000000

.up_pipe_stop:
DB %01111110, %01111110
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000

.right_pipe_stop:
DB %00000000, %00000000
DB %00000001, %00000001
DB %00000001, %00000001
DB %00000001, %00000001
DB %00000001, %00000001
DB %00000001, %00000001
DB %00000001, %00000001
DB %00000000, %00000000

.down_pipe_stop:
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %00000000, %00000000
DB %01111110, %01111110

pipe_tiles_end:
