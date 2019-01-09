/**
 * 中位值滤波法
*/
#define TRIG_PIN 4       // 超声波Trig引脚
#define ECHO_PIN 5       // 超声波Echo引脚
#define FILTER_N 101     // 采样次数

float Filter_Value;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);      // 设置Trig引脚为输出
  pinMode(ECHO_PIN, INPUT);       // 设置Echo引脚为输入

  Serial.begin(9600);// 初始化串口通信
}

void loop() {
  Filter_Value = Filter();// 获得滤波器输出值
  Serial.println(Filter_Value); // 串口输出
  delay(50);
}

// 获取当前的感应值
float Get_Value() {
  float cm;                   //距离变量
  float temp;                 //存储回波等待时间
  //给Trig发送一个低高低的短时间脉冲,触发测距
  digitalWrite(TRIG_PIN, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);        //等待 2微妙
  digitalWrite(TRIG_PIN, HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);        //等待 10微妙
  digitalWrite(TRIG_PIN, LOW); //给Trig发送一个低电平
  temp = float(pulseIn(ECHO_PIN, HIGH)); //存储回波等待时间
  cm = (temp * 17 ) / 1000;              //把回波时间换算成cm
  return cm;
}

float Filter() {
  float filter_buf[FILTER_N];
  int i, j;
  float filter_temp;
  for (i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_Value();
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
  return filter_buf[(FILTER_N - 1) / 2];
}
