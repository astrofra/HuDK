;;
;; This file is part of HuDK.
;; ASM and C open source software development kit for the NEC PC Engine.
;; Licensed under the MIT License
;; (c) 2016-2019 MooZ
;;

;;
;; Title: Sprite routines.
;;
    .zp
sprite_vram_base .ds 2

    .code
;;
;; function: vdc_sat_addr
;; Set the VRAM address of the sprite attribute table.
;;
;; Parameters:
;;   _si - sprite table VRAM address.
;;
vdc_sat_addr
    vdc_reg #VDC_SAT_SRC 

    lda    <_si
    sta    <sprite_vram_base
    sta    video_data_l

    lda    <_si+1
    sta    <sprite_vram_base+1
    sta    video_data_h

    rts

;;
;; function: vdc_sat_entry
;; Computes and set VRAM write address to SAT entry..
;;
;; Parameters:
;;   X - sprite number
;;
;; Returns:
;;   _si - sprite VRAM address
;;
vdc_sat_entry:
    ; current sprite address = sprite_vram_base + (#entry * 8)
    stz    <_si+1
    
    txa
    asl    A
    asl    A
    asl    A
    rol    <_si+1
    
    clc
    adc    <sprite_vram_base
    sta    <_si
    
    lda    <sprite_vram_base
    adc    <_si+1
    sta    <_si+1

    vdc_reg  #VDC_MAWR
    vdc_data <_si

    rts