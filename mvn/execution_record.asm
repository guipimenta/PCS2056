;
;   Execution Record
;
;       Used to organized function calls and save context

@        /0000  ; absolut start
JP       MAIN   ; goes to main (test) function

;
; Variables and constant declarions
;

; Stack Structure
STACK    $ =100     ; defines a stack for 100 bytes
UNITSIZE K /0002    ; each unit in the stack contains 
BASEP    K STACK    ; base pointer
STACKTP  K STACK    ; top of stack pointer

; Instruction assember
READINS  K /8000    ; used to assembly a read instruction
STOREINS K /9000    ; used to assembly a store to memory
SCINS    K /A000    ; call instruction


; Parameters from pop/push function
POPVAL  K   /0A0A   ; address to get poped value
PUSHVAL K   /0A0A   ; address to push value


; PUSH:
;   Store 1 byte value on the stack
; Parameters:
;   PUSHVAL: memory address to read byte from

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

; LOADPARM
;   Load parameter from frame on the stack and 
;   put it into register
; Parameters:
;   SPOS:  position to be read (0 based vector)

SPOS  K   /0000         ; declaration of position

LOADPARM JP /000        ; return address
         LD SPOS        ; loads base pointer
         *  UNITSIZE    ; calculates position
         +  BASEP       ; add offset to pointer
         +  READINS     ; create a instruction
         MM GETPARM     ; saves instruction
GETPARM  K  /0000       ; fetches param
         RS LOADPARM    ; returns

; POP
;   Pop 1 byte value from the stack
; Parameters:
;   POPVAL: where to store value poped from stack

POP     JP /000
        LD STACKTP      ; loads stack pointer
        -  BASEP        ; subtracts base pointer
        JN PRETURN      ; if negative, stack is empty
        LD STACKTP      ; loads stack pointer
        -  UNITSIZE     ; update val
        MM STACKTP      ; stores updated val
        LD STACKTP      ; load latest positon
        +  READINS      ; assembly a load instruction
        MM LOAD         ; stores assembled instruction
LOAD    K  /0000        ; executes assembled instruction
        MM POPVAL       ; stores pop val
PRETURN RS POP          ; return pop

;
; Switch context functions
;

; CALL
;   function to create a new context
; PARAMETERS
;   PARMS:      vector containg the function parameters
;   PSIZE:      size of PARMS vector
;   RETADR:     return address of function
;   TOCALL:     function to be called

; internal variables of call
i       K  /0000   ; counter
PSTACKP K  /0000   ; pointer to params stack
PSIZE   K  /0000   ; parameter size
RETADR  K  /0000   ; return address of current function
TOCALL  K  /0000   ; function to be called

;function body
CALL    JP  /000     ; return address
        LV  /00      ; zeros counter
        MM  i        ; stores zero counter
        LD  STACKTP  ; load stack top pointer
        MM  BASEP    ; moves base pointer to stack top pointer
        LD  PSIZE    ; calculates stack real size
        *   UNITSIZE ; multiply by unit size
        MM  PSIZE    ; saves params size
FORL    LD  i        ; loads counter
        -   PSIZE    ; compares to the size
        JZ  FORLEND  ; end of loop
        LD  READINS  ; start instruction to read next param
        +   PSTACKP  ; creates new read function
        MM  LOADP    ; stores at load new parameters
LOADP   K   /0000    ; load next param
        MM  PUSHVAL  ; stores parameter to be pushed
        SC  PUSH     ; push parameter into stack
        LD  PSTACKP  ; loads stack pointer
        +   UNITSIZE ; goes to next position
        MM  PSTACKP  ; stores
        LD  i        ; loads i
        +   UNITSIZE ; sums unit size
        MM  i        ; new i
        JP  FORL     ; goest to for
FORLEND LD  RETADR   ; load return address
        MM  PUSHVAL  ; prepares to store return address
        SC  PUSH     ; stores return address
        LD  UNITSIZE ; load constant 2
        *   /02      ; return address + frame size
        +   i        ; sums 2 to i, calculate size of the frame
        MM  PUSHVAL  ; prepares push framesize
        SC  PUSH     ; push return address
        LD  TOCALL   ; loads to call address
        +   SCINS    ; creates new to call instruction
        MM  CALLSUB  ; saves created instruction
CALLSUB K   /0000    ; calls subrotine
CRETURN RS CALL      ; when all functions are called

; CALLRET
;   returns to previous function

CTEMP1   K   /0000    ; return address
CTEMP2   K   /0000    ; frame size

CALLRET     K   /0000     ; return address
            SC  POP       ; pops current frame size
            SC  POP       ; return address (to be called)
            LD  POPVAL    ; loads pop value (return address)
            MM  CTEMP1    ; saves return address
            LD  BASEP     ; loads base pointer
            MM  STACKTP   ; new stack top pointer
            LD  BASEP     ; loads base pointer
            -   UNITSIZE  ; goes back 1 position
            +   READINS   ; creates a read instruction
            MM  LOADFSIZE ; stores instruction
LOADFSIZE   K   /0000     ; loads frame size
            MM  CTEMP2    ; stores frame size
            LD  BASEP     ; loads base pointer
            -   CTEMP2    ; goes back to previous stack
            MM  BASEP     ; base pointer to start of previous stack
            LD  CTEMP1    ; loads return address
            +   SCINS     ; loads SC instruction
            MM  GOTOPREV  ; returns to previous function
GOTOPREV    K   /0000     ; returns 



; CHANGEBP:
;   Move pointers to new position on context switch
; Parameters:
;   BASEOFFSET: offset of the new position in
;               relation to old base pointer

BASEOFFSET  K  /0000

CHANGEBP JP /000         ; return address
         LD BASEOFFSET   ; loads offset
         +  BASEP        ; add it base pointer
         MM BASEP        ; store new value
         LD BASEOFFSET   ; loads offset
         +  STACKTP      ; add it to stack pointer
         MM STACKTP      ; stores new value
         RS CHANGEBP     ; returns
; Second call
; teste2
TEMP2   K  /0000
TEST2   JP /0000         ; return address
        LV /00           ; load 0
        MM SPOS          ; stores position of param
        SC LOADPARM      ; loads parameter
        MM TEMP2         ; stores parameter
        LV /02           ; loads constant
        *  TEMP2         ; multiply
        SC CALLRET       ; returns

; test
; simulates params stack
TEMP1  K  /0000
TEST    JP /000           ; return address
        LV /00            ; try to read first param
        MM SPOS           ; stores
        SC LOADPARM       ; calls load param function
        MM TEMP1          ; stores temp1       
        LV /01            ; try to read second param
        MM SPOS           ; sttores
        SC LOADPARM       ; calls load param function
        +  TEMP1          ; stores a + b
        MM TEMP1          ; stores into temp
        LV /01            ; loads value 3
        MM PSIZE          ; two parameters
        LD TEMP1          ; loads value 2
        MM PARAM1         ; parameter 1
        LV PARAM1         ; top of vector
        MM PSTACKP        ; stores at params vector
        LV RETFCAL        ; loads return address
        MM RETADR         ; address return of main
        LV TEST2          ; loads function address
        MM TOCALL         ; function that should be called
        SC CALL           ; lets do it!
        RS TEST           ; end of routine
RETFCAL LV /FF            ; loads a value
        SC CALLRET        ; goes back to main routine
        

; this is a test routine
; program entry point

STACKTEST    LV  /AA
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
             RS  STACKTEST

 ; header to call function
PARAM1  K    /0000
PARAM2  K    /0000
PARAM3  K    /0000

MAIN         LV     /03          ; loads value 3
             MM     PSIZE        ; two parameters
             LV     /01          ; loads value 2
             MM     PARAM1       ; parameter 1
             LV     /02          ; loads value 3
             MM     PARAM2       ; parameter 2
             LV     /00          ; parameter 3   
             MM     PARAM3       ; start of parameter vector
             LV     PARAM1       ; top of vector
             MM     PSTACKP      ; stores at params vector
             LV     RETMAIN      ; loads return address
             MM     RETADR       ; address return of main
             LV     TEST         ; loads function address
             MM     TOCALL       ; function that should be called
             SC     CALL         ; lets do it!
RETMAIN      LV     /0A          ; return of main
OVER         HM     /00          ; over 


;
; Number assembler
;
;   Generates numbers that are composed by lower and upper
;   params:
;       UPPER: upper part of the number
;       LOWER: lower part of the number
;   returns:
;       ASSEMBLED: equals UPPER LOWER
;

UPPER       K  /0000    ; upper part of number
LOWER       K  /0000    ; lower part of number
ASSEMBLED   K  /0000    ; assembled number
CONSTMUL    K  /0100    ; multiply constant

; ASMNUM
;   Assembly 1 byte number with upper and low word
; Parameters
;   UPPER: upper word from number
;   LOWER: lower word from number
; Returns
;   ASSEMBLED: 1 byte number (HL)

ASMNUM  JP /000
        LD UPPER        ; loads UPPER
        *  CONSTMUL     ; multiplies 10
        +  LOWER        ; sums up lower part
        MM ASSEMBLED    ; stores assembled number
        RS ASMNUM       ; returns



; physical end of program
# EXECUTION
