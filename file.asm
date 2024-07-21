IN R0       	; User to input 27 in R0
IN R1 	    	; User to input 36 in R1
MOV R1, R2   	; R2 has 36
DEC R2      	; R2 has 35
MOV 27, R3		; R3 has 27
INC R3			; R3 has 28
STORE R0, 27	; Memory 27 has 27
ADD R1, R0		; R0 has 63
STORE R0, [R0]	; Memory 63 has 63
STORE R4, 0		; Memory 0 has 0
STORE R2, [R2]	; Memory 35 has 35
MOV R2, R4		; R4 has 35
SUB R3, R4		; R4 has 7
STORE R4, [R4]	; Memory 7 has 7
MOV R3, R5		; R5 has 28
SHL R5, 1		; R5 has 56
STORE R5, [R5]	; Memory 56 has 56
SHR R5, 2		; R5 from 56 to 14
STORE R5, [R5]	; Memory 14 has 14
STORE R1, [R1]	; Memory 36 has 36
STORE R3, [R3]	; Memory 28 has 28
DIV R4, R0		; R0 has 63 / 7 = 9
STORE R0, [R0]	; Memory 9 has 9
MOV R2, R6		; R6 has 35
DIV R4, R6		; R6 has 35 / 7 = 5
MOV R0, R1		; R1 has 9
MUL R6, R1		; R1 has 5 * 9 = 45
STORE R1, [R1]	; Memory 45 has 45
DEC R6			; R6 has 4
ADD R6, R1		; R1 has 49
STORE R1, [R1]	; Memory 49 has 49
INC R6			; R6 has 5
ADD R6, R1		; R1 has 54
STORE R1, [R1]	; Memory 54 has 54
ROL R1, 3		; R1 rotate from 54 -> 108 -> 216 -> 177
OUT R1			; Show the content of R1
SHR R1, 3		; R1 shift from 177 -> 88 -> 44 -> 22
DEC R6			; R6 becomes 4
MOV R1, R4		; R4 becomes 22
SUB R6, R4		; R4 becomes 18
STORE R4, [R4]	; Memory 18 has 18
DEC R1			; R1 becomes 21
STORE R1, [R1]	; Memory 21 has 21
LOAD R3, 54		; Load memory 54 to R3, R3 has 54
ROR R3, 4		; R3 rotates from 54 -> 27 -> 141 -> 198 -> 99
MOV R3, R2		; R2 becomes 99
MOV R4, R0		; R0 becomes 18
ADD R1, R0		; R0 becomes 18 + 21 = 39
SUB R0, R3		; R3 becomes 99 - 30 = 69
SUB R4, R3		; R3 becomes 60 - 18 = 42
STORE R3, [R3]	; Memory 42 becomes 42
MOV [R3], R5	; R5 becomes 42
LOAD R6, [R1]	; Load memory 21 to R6, R6 becomes 21