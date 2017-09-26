// 不借助第三个变量交换两个整数的值

// 假设两个数x和y，则有：
// 方法1：算术运算（加减）：

void swap1(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

// 方法2：乘除法。

void swap2(int &a, int &b){
    a = a * b;
    b = a / b;
    a = a / b;
}

// 方法3：异或法。

void swap3(int &a, int &b){
    a ^= b;         //x先存x和y两者的信息
    b ^= a;         //保持x不变，利用x异或反转y的原始值使其等于x的原始值
    a ^= b;         //保持y不变，利用x异或反转y的原始值使其等于y的原始值
}
