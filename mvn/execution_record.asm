;
;	Execution Record
;
;		Used to organized function calls and save context

@ /0000 ; absolut start
JP 		 TEST

; Stack Structure

STACK	 $ =100		; defines a stack for 100 bytes
UNITSIZE K /0001	; each unit in the stack contains 1 byte
BASEP	 K /0000	; base pointer
STACKTP  K /0000	; top of stack pointer
STACKTMP K /0000	; just a holder

; Parameters to call subrotines
POPVAL 	K	/0000 	; address to get poped value
PUSHVAL K	/0000	; address to push value

; Stack API
; Exports methods
;START >
;PUSH  >
;POP   >

; Exports parameters
;POPVAL  >
;PUSHVAL >

; Init Stack
START 	JP /000
		LV STACK 	; load stack first position
		MM BASEP	; stores first position
		MM STACKTP  ; stores stack top = base pointer
		RS START 	; returns start

; Push into stack
; TODO: avoid stack overflow
PUSH 	JP /000
		LV	STACKTP		; loads latest position
		+	UNITSIZE	; goto next position avaliable
		MM  STACKTMP	; saves address
		LD  PUSHVAL 	; reads into register
		MM  STACKTMP	; pushes value into stack
		RS  PUSH 		; returns push

; Pop into register
POP 	JP /000
		LD 	STACKTP 	; loads stack value
		MM	POPVAL		; stores value into parameter
		LV	STACKTP 	; loads stack pointer address
		-	UNITSIZE	; subtracts unit size 
TEST	SC 	START 		
		HM 	/00
# EXECUTION