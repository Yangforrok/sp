```
$ ./test.sh
++ gcc -w c4.c -o c4
++ ./c4 -s test/power.c
1: #include <stdio.h>
2: 
3: int power(int a, int n) {
4:     if (n < 0) return 1 / power(a, -n);
    ENT  0
    LLA  2
    LI
    PSH
    IMM  0
    LT
    BZ   0
    IMM  1
    PSH
    LLA  3
    LI
    PSH
    IMM  -1
    PSH
    LLA  2
    LI
    MUL
    PSH
    JSR  10682520
    ADJ  2
    DIV
    LEV
5:     else if (n == 0) return 1;
    JMP  0
    LLA  2
    LI
    PSH
    IMM  0
    EQ
    BZ   0
    IMM  1
    LEV
6:     else return a * power(a, n - 1);
    JMP  0
    LLA  3
    LI
    PSH
    LLA  3
    LI
    PSH
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    PSH
    JSR  10682520
    ADJ  2
    MUL
    LEV
7: }
    LEV
8:
9: int main() {
10:     printf("3^2 = %.2f\n", power(3, 2));
    ENT  0
    IMM  10944672
    PSH
    IMM  3
    PSH
    IMM  2
    PSH
    JSR  10682520
    ADJ  2
    PSH
    PRTF
    ADJ  2
11: }
    LEV
```