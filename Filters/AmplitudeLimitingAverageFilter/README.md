# 限幅平均滤波法

## 方法：

相当于“限幅滤波法”+“递推平均滤波法”；

每次采样到的新数据先进行限幅处理，

再送入队列进行递推平均滤波处理。

## 优点：

- 融合了两种滤波法的优点；
- 对于偶然出现的脉冲性干扰，可消除由于脉冲干扰所引起的采样值偏差。

## 缺点：

- 比较浪费RAM。