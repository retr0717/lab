assume cs:code , ds:data
data segment
   str1 db 0ah,"Enter 1st no :$"
   str2 db 0ah,"Enter 2nd no: $"
   str3 db 0ah,"The sum is:  $ "
data ends
code segment
start: 
  mov ax,data
  mov ds,ax
       
    
  lea dx,str1
  mov ah,09h
  int 21h
       

  mov ah,01h
  int 21h
       
  sub al,30h ; convert ASCII to binary
  mov bl,al ; move al binary to bl
       
       
  lea dx,str2
  mov ah,09h
  int 21h
       
       
	mov ah,01h
	int 21h
	sub al,30h
		 
	lea dx,str3
	mov ah,09h
	int 21h
		

	add al,bl
		
		
	mov ah,00h
	aaa ; (ASCII Adjust After Addition): Adjusts the result in AL and AH for BCD (Binary Coded Decimal).
		
		
	mov bl,al
	mov dl,ah ; ah contains the higher bits it the result is a two digit.
		
		
	add dl,30h ; converting the higher bit to ascii by adding 30h.

		
		
	mov ah,02h
	int 21h

	mov dl,bl
	add dl,30h


	mov ah,02h
	int 21h
		
	mov ah,4ch
	int 21h
code ends
		
end start
