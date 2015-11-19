;
;   Execution Record
;
;       Used to organized function calls and save context

@ /0000 ; absolut start
JP       TEST

; Stack Structure

STACK    $ =100     ; defines a stack for 100 bytes
UNITSIZE K /0004    ; each unit in the stack contains 
BASEP    K STACK    ; base pointer
STACKTP  K STACK    ; top of stack pointer
STACKTMP K /0000    ; just a holder

; instruction assember
READINS  K /8000    ; used to assembly a read instruction
STOREINS K /9000    ; used to assembly a store to memory


; Parameters to call subrotines
POPVAL  K   /0A0A   ; address to get poped value
PUSHVAL K   /0A0A   ; address to push value

; Stack API
; Exports methods
;START >
;PUSH  >
;POP   >

; Exports parameters
;POPVAL  >
;PUSHVAL >

; Push into stack
; TODO: avoid stack overflow
PUSH    JP /000
        LD  STACKTP     ; loads latest position
        +   STOREINS    ; generates instruction
        MM  STORE       ; saves address
        LD  PUSHVAL     ; loads push val
STORE   K   /0000       ; assembled instruction
        LD  STACKTP     ; loads stack top
        +   UNITSIZE    ; update it
        MM  STACKTP     ; stores it 
        RS  PUSH        ; returns push

; Pop into register
POP     JP /000
        LD STACKTP      ; loads stack pointer
        -  UNITSIZE     ; update val
        MM STACKTP      ; stores updated val
        LD STACKTP      ; load latest positon
        +  READINS      ; assembly a load instruction
        MM LOAD         ; stores assembled instruction
LOAD    K  /0000        ; executes assembled instruction
        MM POPVAL       ; stores pop val
        RS POP          ; return pop

TEST    LV  /AA
        MM  UPPER
        LV  /FF
        MM  LOWER
        SC  ASMNUM
        MM  PUSHVAL
        SC  PUSH
        LV  /CC
        MM  UPPER
        LV  /45
        MM  LOWER
        SC  ASMNUM
        MM  PUSHVAL
        SC  PUSH
        SC  POP
        LD  POPVAL       
        HM  /00

;
; Number assembler
;
UPPER       K  /0000    ; upper part of number
LOWER       K  /0000    ; lower part of number
ASSEMBLED   K  /0000    ; assembled number
CONSTMUL    K  /0100    ; multiply constant

; Assembly number with 4 bytes
ASMNUM  JP /000
        LD UPPER        ; loads UPPER
        *  CONSTMUL     ; multiplies 10
        +  LOWER        ; sums up lower part
        MM ASSEMBLED    ; stores assembled number
        RS ASMNUM       ; returns




# EXECUTION
