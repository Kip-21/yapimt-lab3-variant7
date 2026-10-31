.386
.MODEL FLAT
PUBLIC _MakePalindrome

.CODE
; MakePalindrome(const char* source, char* result, int length), cdecl.
_MakePalindrome PROC
    PUSH EBP
    MOV EBP, ESP
    PUSH ESI
    PUSH EDI

    ; Копируем исходную строку в начало результата.
    CLD
    MOV ESI, [EBP+8]
    MOV EDI, [EBP+12]
    MOV ECX, [EBP+16]
    REP MOVSB

    ; Читаем исходную строку с конца и дописываем её копию.
    MOV ECX, [EBP+16]
    JECXZ palindromeReady
    MOV ESI, [EBP+8]
    ADD ESI, ECX
    DEC ESI
copyBackwards:
    STD
    LODSB
    CLD
    STOSB
    LOOP copyBackwards

palindromeReady:
    MOV BYTE PTR [EDI], 0
    POP EDI
    POP ESI
    POP EBP
    RET
_MakePalindrome ENDP
END
