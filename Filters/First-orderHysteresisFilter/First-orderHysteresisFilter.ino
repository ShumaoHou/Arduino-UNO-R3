int Filter_Value;
int Value;

void setup() {
  Serial.begin(9600);// 初始化串口通信
  randomSeed(analogRead(0)); // 产生随机种子
  Value = 300;
}

void loop() {
  Filter_Value = Filter();// 获得滤波器输出值
  Serial.println(Filter_Value); // 串口输出
  delay(50);
}

// 用于随机产生一个300左右的当前值
int Get_AD() {
  return random(295, 305);
}

// 一阶滞后滤波法
#define FILTER_A 0.01
int Filter() {
  int NewValue;
  NewValue = Get_AD();
  Value = (int)((float)NewValue * FILTER_A + (1.0 - FILTER_A) * (float)Value);
  return Value;
}
