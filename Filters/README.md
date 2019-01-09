# 滤波器

[代码来源:十大滤波算法程序大全（Arduino精编无错版）](https://www.geek-workshop.com/thread-7694-1-1.html)

1. AmplitudeLimiterFilter 限幅滤波器（程序判断滤波器）
2. MiddlevalueFilter 中位值滤波器
3. ArithmeticAverageFilter 算术均值滤波器
4. RecursiveAveragingFilter 递推平均滤波器（滑动平均滤波器）
5. MiddlevalueAverageFilter 中位值平均滤波器（防脉冲干扰平均滤波器）
6. AmplitudeLimitingAverageFilter 限幅平均滤波器
7. First-orderHysteresisFilter 一阶滞后滤波器
8. WeightedRecursiveAverageFilter 加权递推平均滤波器
9. DebounceFilter 消抖滤波器
10. LimitingDebounceFilter 限幅消抖滤波器

代码中的Get_AD()可以替换成获取传感器值的函数，数值类型要自己替换。

应用实例：[HC-SR04_Filters](https://github.com/mndream/Arduino-UNO-R3/tree/master/HC-SR04_Filters)