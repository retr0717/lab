
ASSUME CS:code, DS:data

data segment
  a dw 0602h       ; First 16-bit number
  b dw 0702h       ; Second 16-bit number
  v dw ?       ; Result storage
data ends

code segment
START:
  mov ax, data      ; Load the address of the data segment
  mov ds, ax        ; Initialize the data segment register

  mov ax, a         ; Load the value of 'a' into AX
  mov bx, b         ; Load the value of 'b' into BX
  add ax, bx        ; Add BX to AX (AX = AX + BX)

  mov v, ax         ; Store the result in 'c'

  ; Exit program
  mov ah, 4ch       ; DOS terminate program function
  int 21h
code ends

end START

