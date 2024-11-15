ASSUME CS:code, DS:data
data segment
  str1 db 0ah,"Enter the num : $"
  str2 db 0ah,"Sum : $"
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

  mov bh, al
  int 21h
  mov bl, al

  sub bx, 3030h ; convert ascii to bcd.

  ; display string
  lea dx, str1
  mov ah, 09h
  int 21h

  ; read second number.
  mov ah, 01h
  int 21h

  mov ch, al
  int 21h
  mov cl, al
  sub cx, 3030h

  ; display string 2.
  lea dx, str2
  mov ah, 09h
  int 21h

  ;add two nos.
  mov ax, bx
  mov bx, cx
  add ax, bx

  mov bl, al
  mov al, ah
  mov ah, 00h
  aaa             ; ASCII adjust after addition operation
                  ; now bl, al, ah contain the result
                  ; for eg, if result is 105 then ah=1 al=0 bl=5
  
  mov bh, al ; moving value in al to bh, because when a display operation is done 
		          ;the displayed value is also stored to al. so the existing value in al will be lost.
              ;so taking a copy of al
  mov dl, ah
  add dl, 30h ; BCD to ascii

  ;print ah
  mov ah, 02h
  int 21h

  mov dl, bh
  add dl, 30h
  ;print bh
  mov ah, 02h
  int 21h

  ;print bl
  mov dl, bl
  add dl, 30h
  mov ah, 02h
  int 21h

  mov ah, 04h
  int 21h

code ends
end START
