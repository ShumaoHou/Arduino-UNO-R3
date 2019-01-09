#define FILTER_N 12
int Filter_Value;
int filter_buf[FILTER_N];

void setup() {
  Serial.begin(9600);// 初始化串口通信
  randomSeed(analogRead(0)); // 产生随机种子
  filter_buf[FILTER_N - 2] = 300;
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

// 限幅平均滤波法
#define FILTER_A 1
int Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N - 1] = Get_AD();
  if (((filter_buf[FILTER_N - 1] - filter_buf[FILTER_N - 2]) > FILTER_A) || ((filter_buf[FILTER_N - 2] - filter_buf[FILTER_N - 1]) > FILTER_A))
    filter_buf[FILTER_N - 1] = filter_buf[FILTER_N - 2];
  for (i = 0; i < FILTER_N - 1; i++) {
    filter_buf[i] = filter_buf[i + 1];
    filter_sum += filter_buf[i];
  }
  return (int)filter_sum / (FILTER_N - 1);
}
