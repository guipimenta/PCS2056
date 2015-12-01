; example compiled program
; into mvn code using execution record

; this is common to all
; compiled programs
; =======================

&  /0000  ; absolut start
JP START

; Load parameter
SPOS       <
SLOADPARAM <
LOADPARAM  <

; Store parameter
SSPOS      <
SSVAL      <
STOREPARAM <

; Creates locals
PLVAL      <
PSLOCAL    <

; Read local
LLPOS      < 
LLRET      <
LOCALLOAD  <

; Store local
SLVAL      <
SLPOS      <
STORELOCAL <

; Call function
PSTACKP <
PSIZE   <
RETADR  <
TOCALL  <
CALL    <

; imports
CALLRET  <

; this should always be here to call main routine
START LV /FF
      LV END
      MM RETADR
      LV /00
      MM PSIZE
      LV MAIN
      MM TOCALL
      SC CALL
      END HM /00
      HM /00

; =====================
; ends of common area

PARAMN K /000   ; N parameter of function fatorial
BUFFER K /000   ; buffer
RETURN K /000   ; return address
FATORIAL K /000  ; start of fatorial function
         ;
         ; declare integer #fat
         ;
         LV /00       
         MM PLVAL
         SC PSLOCAL
         ;
         ; declare integer #temp2
         ;
         LV /00
         MM PLVAL
         SC PSLOCAL
         ;
         ;  if #n == 1
         ;
         LV /00       ; first parameter
         MM SPOS      ; paramter to read parameter 
         SC LOADPARAM ; loads parameter
         LD SSVAL     ; loads parameter
         -  /01       ; #n == 1?
         JZ EQUALS    ; equals
         ;
         ; #temp2 = #n - 1
         ;
         LV /00       ; loads first parameter
         MM SPOS      ; stores it
         SC LOADPARAM ; load fist parameter (#n)
         LD SLOADPARAM ; loads into register (#n)
         -  /01       ; subtracts one
         MM BUFFER    ; all functions should have buffer
         LV /01       ; read of second local (#temp2)
         MM LLPOS     ; parameter to write local routine
         LD BUFFER    ; loads buffer
         MM SLVAL     ; stores value to be stores into #temp2
         SC STORELOCAL ; calls load route: #temp2 = #n - 1
         ;
         ; fatorial(#temp2)
         ;
         LV /01       ; loads second local
         MM LLPOS     ; stores as parameter to load function
         SC LOCALLOAD ; calls read local subrotine
         LD LLRET     ; loads value
         MM PARAMN    ; stores parameter into N
         LV /01       ; fatorial has 1 argument
         MM PSIZE     ; stores argument size
         LV PARAMN    ; top of vector
         MM PSTACKP   ; stores at params vector pointer
         LV RETMAIN   ; return address
         MM RETADR    ; return address
         LV FATORIAL  ; load fatorial address function
         MM TOCALL    ; what function to be called
         SC CALL      ; fatorial(#temp2)
         LV /00       ; first parameter
         MM SPOS      ; paramter to read parameter 
         SC LOADPARAM ; loads parameter
         ;
         ; #fat = #n * fatorial(#temp2)
         ;
         *  RETURN     ; return value
         MM SLVAL      ; value to be stored
         LV /00        ; read of second local (#fat)
         MM LLPOS      ; parameter to write local routine
         SC STORELOCAL ; calls save routine
         ;
         ; return #fat ; returns #fat
         ;
         LV /00        ; read first local (#fat)
         MM LLPOS      ; stores as parameter
         SC LOCALLOAD  ; calls load local subroutine
         LD LLRET      ; loads value
         MM RETURN     ; returns
         SC CALLRET    ; goback
EQUALS   LV /01       ; start to return
         MM RETURN    ; return 1;
         SC CALLRET   ; returns


MAIN K /0000
     ;
     ; declare integer #fat
     ;
     LV /00  
     MM PLVAL   
     SC PSLOCAL
     ;
     ; fatorial(5) call
     ;
     LV /01     ; fatorial has 1 argument
     MM PSIZE   ; stores argument size
     LV /05     ; loads value 05
     MM PARAMN  ; stores parameter into N
     LV PARAMN  ; top of vector
     MM PSTACKP ; stores at params vector pointer
     LV RETMAIN ; return address
     MM RETADR  ; return address
     LV FATORIAL ; load fatorial address function
     MM TOCALL  ; what function to be called
     SC CALL    ; fatorial(5)
RETMAIN K /000 
     ;
     ; #fat = fatorial(5)
     ;
     LD RETURN  ; loads returned value
     MM SLVAL   ; stores into storelocal param
     LV /00     ; to store on first local
     MM SLPOS   ; set position param
     SC STORELOCAL ; stores
     SC CALLRET

# EXECUTION