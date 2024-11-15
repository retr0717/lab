ASSUME CS:code, DS:data
data segment
  str1 db 0ah,"Enter the num : $"
  str2 db 0ah,"The num is : $"
data ends
code segment
START:
  mov ax, data
  mov DS, ax
  lea dx, str1
  mov ah, 09h
  int 21h
  mov ah, 01h
  int 21h
  mov bl, al
  lea dx, str2
  mov ah, 09h
  int 21h
  mov dl, bl
  mov ah, 02h
  int 21h
  mov ah, 4ch
  int 21h
code ends
end START
