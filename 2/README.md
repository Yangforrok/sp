# Compiler

## 語法

```
PROG = STMTS
BLOCK = { STMTS }
STMTS = STMT*
STMT = WHILE | BLOCK | ASSIGN | IF | DOWHILE
WHILE = while (E) STMT
IF = if (E) STMT (else STMT)?
DOWHILE = do STMT while (E);
ASSIGN = id '=' E;
E = F (op E)*
F = (E) | Number | Id
```

## 執行結果

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/02-compiler/03-compiler
$ make clean
rm -f *.o *.exe

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/02-compiler/03-compiler
$ make
gcc -std=c99 -O0 compiler.c -o compiler

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/02-compiler/03-compiler
$ ./compiler
do {
  a = a + 1;
} while (a < 10);

============ parse =============
(L0)
a = t0
t0 = a + 1
if t0 goto L0
(L1)
``` 
============ parse =============：

表示解析過程的開始。
(L0)：

標籤 L0，表示 do while 迴圈的開始位置。
a = t0：

將變量 a 的值賦給臨時變量 t0。
t0 = a + 1：

計算 a + 1 並將結果賦給臨時變量 t0。
if t0 goto L0：

如果 t0 為真，則跳轉到標籤 L0，繼續迴圈。
(L1)：

標籤 L1，表示 do while 迴圈的結束位置。