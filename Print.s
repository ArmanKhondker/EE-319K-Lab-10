; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix
ASCII EQU -4
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH {R1-R9,LR}
	SUB SP,#40; allocation of 40 locations for local variable  by default intialized to 0
	MOV R2,#10 ; R2 IS THE DIVISOR
	MOV R4,#0;
	MOV R5,#0X30; 
	MOV R6,SP; 
	STR R5, [SP,#ASCII]
	
STOREDIGITS
	UDIV R3,R0,R2; R3=N/10
	MUL R1,R3,R2; R1=N/10*10
	SUB R1,R0,R1; R1=N%10
	STRB R1,[SP,R4];   first acccess to change the value
	ADD R4,R4,#1;		moving to the next variable
	MOV R0,R3;
	CMP R0,#0;
	BNE STOREDIGITS
OUTDIGITS
	SUB R4,R4,#1;
	LDRB R0,[SP,R4];   2nd access to read it
;	LDR R5, [R6,#ASCII]; R5 HAS VALUE OF 0X30
;ADD R0,R0,R5;
	ADD R0,R0,#0X30
	BL ST7735_OutChar;
	CMP R4,#0;
	BNE OUTDIGITS
	
 
 
 
 ADD SP,#40;	deallocation
 POP {R1-R9,LR}


      BX  LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	PUSH {R1-R9,LR}
	SUB SP,#40
	MOV R2,#10 ; R2 IS THE DIVISOR
	MOV R4,#0;
	MOV R5,#0;
	MOV R6,#4;
STOREDIGITS2
	UDIV R3,R0,R2; R3=N/10
	MUL R1,R3,R2; R1=N/10*10
	SUB R1,R0,R1; R1=N%10
	STRB R1,[SP,R4];
	ADD R4,R4,#1;
	MOV R0,R3;
	CMP R0,#0;
	BNE STOREDIGITS2
SOM	CMP R4,#3
	BHI OUTDIGITS2
	MOV R1,#0;
	STRB R1,[SP,R4];
	ADD R4,R4,#1;
	B SOM
	
OUTDIGITS2
	ADD R5,#1;
	CMP R5,#2;			TAKING CARE OF THE . IN THE NUMBERS
	BNE CONTINUE;
	MOV R0, #46;
	BL ST7735_OutChar;
	
CONTINUE	
	CMP R4,#4
	BLS CONTINUE2
SPECIALCASE
	MOV R0,#42
	BL ST7735_OutChar;
	MOV R0,#46
	BL ST7735_OutChar;
	MOV R0,#42
	BL ST7735_OutChar;
	MOV R0,#42
	BL ST7735_OutChar;
	MOV R0,#42
	BL ST7735_OutChar;
	B DONE2
	
	
CONTINUE2	
	SUB R4,R4,#1;
	LDRB R0,[SP,R4]
	ADD R0,#0X30;
	BL ST7735_OutChar;
	CMP R4,#0;
	BNE OUTDIGITS2
DONE2	
 
 
 
 ADD SP,#40;
 POP {R1-R9,LR}

     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
