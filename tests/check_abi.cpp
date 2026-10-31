#include <cstdio>
#include <cstring>

extern "C" void __cdecl MakePalindrome(const char*, char*, int);

bool check(const char* source, char* result, int inputLength) {
    unsigned beforeEsp, afterEsp, beforeEbp, afterEbp;
    unsigned ebxValue, esiValue, ediValue, flags;
    __asm {
        mov beforeEsp, esp
        mov beforeEbp, ebp
        mov ebx, 11223344h
        mov esi, 55667788h
        mov edi, 12345678h
        push inputLength
        push result
        push source
        call MakePalindrome
        add esp, 12
        mov afterEsp, esp
        mov afterEbp, ebp
        mov ebxValue, ebx
        mov esiValue, esi
        mov ediValue, edi
        pushfd
        pop eax
        mov flags, eax
    }
    return beforeEsp == afterEsp && beforeEbp == afterEbp
        && ebxValue == 0x11223344 && esiValue == 0x55667788
        && ediValue == 0x12345678 && (flags & 0x400) == 0;
}

int main() {
    char source[256], original[256];
    unsigned char buffer[513];
    for (int n = 0; n <= 255; ++n) {
        for (int i = 0; i < 256; ++i)
            source[i] = static_cast<char>(i % 254 + 1);
        std::memcpy(original, source, sizeof source);
        std::memset(buffer, 0xCC, sizeof buffer);
        char* result = reinterpret_cast<char*>(buffer + 1);
        if (!check(source, result, n)) return 1;
        if (buffer[0] != 0xCC || buffer[2 * n + 2] != 0xCC) return 2;
        if (result[2 * n] != 0) return 3;
        if (std::memcmp(source, original, sizeof source) != 0) return 4;
        for (int i = 0; i < n; ++i)
            if (result[i] != source[i] || result[n + i] != source[n - i - 1])
                return 5;
    }
    std::puts("Passed 256/256 ABI and buffer checks (lengths 0..255).");
    return 0;
}
