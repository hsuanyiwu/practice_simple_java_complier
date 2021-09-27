

# Simple Java



## 目的

實作文件 Modern Compiler Design Associated Supplemental Materials C Implementation Details 中的作業部份，作業己定義了程式的骨架，並指出我們應該作什麼。

<img src="image\image-20210925160701163.png" alt="image-20210925160701163"  />




## Chapter 2

##### Lexical Analysis



筆記

* 規則中有保留字元都需加上 “ ” ， BEGIN 是LEX的保留字，建議非字元都加上 “ ” 比較不易出錯

* 函式 yylex() 作的事情

```c
while(TRUE) {
1. Find a regular expression rule that matches the next section of the input file
2. Execute the action for that rule
}
```

* lex 如何處理有一個以上的規則符合的情況

> 1. Always match to the longest possible string.
> 2. If two different rules match the same longest string, use the regular expression that appears first in the
input file.

* 考慮以下規則

```c
for		{ return FOR; }
else    { return ELSE; }
[0-9]+ 	{ return INTEGER; }
[a-zA-Z][a-zA-Z0-9]* { return IDENTIFIER; }
```

輸入 "for" 同時匹配 FOR及IDENTIFIER，for 定義較前，所以回傳 FOR，這裡若是IDENTIFIER定義較前則for或是else會變成無效的規則，永遠不會被回傳 

輸入 "for5" 並不會回傳 FOR，因為符合情況1最長匹配所以回傳的是 IDENTIFIER

* 預設行為

若字元不符合任何規則的則會被輸出，可以假設 lex 預設作了這樣的事

```
.		{ printf("%s", yytext); }
\n		{ printf("%s", yytext); }
```



 ### 作業記錄

* 在windos 平台下使用 [ win_flex / win_bison](https://sourceforge.net/projects/winflexbison/)，新增檔案 lex.bat，內容如下，這樣可在command-line的環境下執行 lex

  > win_flex %*

* 作業中只記錄了每個token的行號，稍作修改成也可記錄欄位置

```c
struct position {
    int line_number;
    int column_number;
};

typedef union { 
     struct {
        int value;
        struct position pos;
     } integer_value;
     struct {
        char *value;
        struct position pos;
     } string_value;
     struct position pos;
} YYSTYPE;
```

* 測試 test4.java

```c
  void main() {
     int x; 
     x = 3;
     x = x + foo();
     Print(x);
  }
```

<img src="image\image-20210925191553454.png" alt="image-20210925191553454"  />



* assignment operator '=' 被解譯成 GETS，需注意在grammar中的使用
* 作業要求simple java 有支援巢狀的comment，但大部份的語言沒這樣作，什麼時候才為需要巢狀的comment。
* test3.sjava 中有非語法的字元＃，需加入規則處理類似字元，且應該需要報錯且不是略過。
	
	> 遇到錯誤的字元如何中斷 lex 工作

