ASSUME CS:code, DS:data

data segment
  list db 01h, 02h, 03h, 04h  ; List of numbers
  num db 05h                  ; Number to search for
  str1 db 0ah, "Found $"
  str2 db 0ah, "Not Found $"
  count equ 04h               ; Count of elements in the list
data ends

code segment
START:
  mov ax, data      ; Load data segment address
  mov DS, ax        ; Initialize DS register

  mov bl, count     ; Load the count of elements into BL
  mov al, num       ; Load the number to search for into AL
  lea si, list      ; Load the address of the list into SI

SEARCH_LOOP:
  cmp al, [si]      ; Compare the number (AL) with the current list element
  je FOUND          ; Jump to FOUND if they are equal
  inc si            ; Move to the next element in the list
  dec bl            ; Decrement the counter
  jnz SEARCH_LOOP          ; Continue looping if counter (BL) is not zero

  lea dx, str2      ; If not found, load "Not Found" message
  mov ah, 09h       ; DOS function to display string
  int 21h
  jmp STOP          ; Exit program

FOUND:
  lea dx, str1      ; If found, load "Found" message
  mov ah, 09h       ; DOS function to display string
  int 21h

STOP:
  mov ah, 4ch       ; DOS terminate program function
  int 21h

code ends
end START

