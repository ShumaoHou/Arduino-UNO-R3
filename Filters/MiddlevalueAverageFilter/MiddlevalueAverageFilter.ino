int Filter_Value;

void setup() {
  Serial.begin(9600);// 初始化串口通信
  randomSeed(analogRead(0)); // 产生随机种子
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

// 中位值平均滤波法（又称防脉冲干扰平均滤波法）（算法1）
#define FILTER_N 100
int Filter() {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for (i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_AD();
    delay(1);
      
  }
  // 采样值从小到大排列（冒泡法）
  for (j = 0; j < FILTER_N - 1; j++) {
    for (i = 0; i < FILTER_N - 1 - j; i++) {
      if (filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;     
      }
         
    }
      
  }
  // 去除最大最小极值后求平均
  for (i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}


//中位值平均滤波法（又称防脉冲干扰平均滤波法）（算法2）
/*
  #define FILTER_N 100
  int Filter() {
  int i;
  int filter_sum = 0;
  int filter_max, filter_min;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
  filter_buf[i] = Get_AD();
  delay(1);
  }
  filter_max = filter_buf[0];
  filter_min = filter_buf[0];
  filter_sum = filter_buf[0];
  for(i = FILTER_N - 1; i > 0; i--) {
  if(filter_buf[i] > filter_max)
  filter_max=filter_buf[i];
  else if(filter_buf[i] < filter_min)
  filter_min=filter_buf[i];
  filter_sum = filter_sum + filter_buf[i];
  filter_buf[i] = filter_buf[i - 1];
  }
  i = FILTER_N - 2;
  filter_sum = filter_sum - filter_max - filter_min + i / 2; // +i/2 的目的是为了四舍五入
  filter_sum = filter_sum / i;
  return filter_sum;
  }*/
