ASSUME CS:code, DS:data
data segment
  msg1 db "Hello $"
  msg2 db "World $"
data ends

code segment
START:
  mov ax,data
  mov DS, ax
  mov dx, offset msg1
  mov ah, 09h
  int 21h
  mov dx, offset msg2
  mov ah, 09h
  int 21h
  mov ah, 4ch
  int 21h
code ends
end START
