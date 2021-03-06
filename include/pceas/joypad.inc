;;
;; This file is part of HuDK.
;; ASM and C open source software development kit for the NEC PC Engine.
;; Licensed under the MIT License
;; (c) 2016-2019 MooZ
;;

  .bss
  
; This array holds the values for 5 2-buttons joypad.
joypad .ds 5

; Delta joypad values.
joytrg .ds 5

; Previous joypad values.
joyold .ds 5

; This array contains the values for buttons III, IV, V and VI of 6 buttons
; joypads.
joypad_6 .ds 5

; Delta joypad values.
joytrg_6 .ds 5

; Previous joypad values.
joyold_6 .ds 5

	.code