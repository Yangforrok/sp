
## 文件

- `race.c`：此版本未使用互斥鎖，導致競態條件的發生。
- `norace.c`：此版本使用互斥鎖來防止競態條件。

## 執行結果

### race_condition.c

#### 說明

- 初始賬戶餘額：500
- 循環次數：1000000
- ATM1 和 ATM2 分別執行 +1 和 -1 操作
- 當賬戶餘額不是 500 時報錯，顯示錯誤的值

#### 結果

Account balance: 432
Error: Expected account balance is 500, but got 432

### norace.c

#### 說明

- 初始賬戶餘額：500
- 循環次數：100000
- ATM1 和 ATM2 每次執行 +1 操作，共執行 100000 次
- 使用互斥鎖保護賬戶餘額修改操作
- 最終預期賬戶餘額：200500

#### 結果

Account balance: 200500
Account balance is correct.