;;
;; This file is part of HuDK.
;; ASM and C open source software development kit for the NEC PC Engine.
;; Licensed under the MIT License
;; (c) 2016-2019 MooZ
;;

  .if !(CDROM)
    ; IRQ vectors (HuCard only)
    .code
    .bank 0
    .org  $fff6
    .dw   _irq_2
    .dw   _irq_1
    .dw   _timer
    .dw   _nmi
    .dw   _reset

    .org  $e000
    .include "pceas/macro.inc"
    .include "byte.inc"
    .include "word.inc"
    .include "system.inc"
    .include "memcpy.inc"
    .include "vdc.inc"
    .include "vce.inc"
    .include "psg.inc"
    .include "irq.inc"

    .include "irq_reset.s"
    .include "irq_nmi.s"
    .include "irq_timer.s"
    .include "irq_1.s"
    .include "irq_2.s"

    .include "mpr.s"
    .include "joypad.s"
    .include "psg.s"
    .include "vdc.s"
    .include "vdc_sprite.s"
    .include "vce.s"
    .include "font.s"    
    .include "font.inc"
    .include "print.s"
    .include "map.s"
    .include "math.s"
    .include "bcd.s"

  .else
    ; [todo]
  .endif ; !(CDROM)
