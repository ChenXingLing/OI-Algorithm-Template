**【常规套路】**

**题目描述：**  
给出一个长为 $n$ 的大串 $A$ 和一个长为 $m$ 的小串，字符串可带通配符，求 $B$ 在 $A$ 中的出现位置集合。

[残缺的字符串 $\text{[P4173]}$](https://www.luogu.com.cn/problem/P4173)

**解题思路：**  
$(1).$ 翻转大串 $A$ 得到 $A'$

$(2).$ 设通配符为 $0$，构造匹配函数：$C(ed,j)=(A_{ed-j+1}-B_j)^2 \times A_{ed-j+1}\times B_j$

$(3).$ 构造完全匹配函数：$PA'(ed)=\sum_{j=1}^{m}C(ed,j)$。

$(4).$ 化简，跑 $\text{FTT}$ 求出 $PA'$ 序列，则 $PA(st)=PA'(n-st+1)$，满足 $PA(st)=0$ 的位置 $st$ 集合即为答案。

**【另一种套路】**

**题目描述：**  

没有通配符，字符串只由 $k$ 种组成（$k$ 为较小常数），其他同上。

[$\text{Fuzzy Search [CF528D]}$](https://www.luogu.com.cn/problem/CF528D)

**解题思路：**  

分别单独计算 $k$ 种字符，对于每一种 $ch$，构造匹配函数：$C(ed,j)=[A_{ed-j+1} \text{可以匹配 }ch] \times [B_j==ch]$，满足 $PA(st)=m$ 的位置 $st$ 集合即为答案。

类似的还有：[$\text{DNA [TJOI2017] [P3763]}$](https://www.luogu.com.cn/problem/P3763)

