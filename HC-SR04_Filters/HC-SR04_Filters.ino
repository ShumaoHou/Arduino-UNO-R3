/**
   使用三种不同的滤波器对超声波传感器采集到的数据进行滤波，
   同时与原始值进行比较，
   在10cm、30cm、100cm处进行采样，
   将原始数据、处理后的数据、真实数据用二维图进行展示。

   组号：
      36
   组长：
      侯树茂 MF1832056
   组员：
      韩越  MF1832052
      何炜杰 MF1832054
      何仔龙 MF1832055
*/

#define TRIG_PIN 4       // 超声波Trig引脚
#define ECHO_PIN 5       // 超声波Echo引脚
//#define LIGHT_PIN A0     // 光线传感器引脚

#define N 11    // 采样次数
#define DELAY_TIME 100 // 每次输出间隔时间

/* 滤波值 */
float TRUE_VALUE = 10.0;  // 真实数据(cm)
float Filter_1_Value;     // 中位平均滤波
float Filter_2_Value;     // 中位值滤波法
float Filter_3_Value;     // 算术平均滤波法

float Value;              // 原始数据

void setup() {
  pinMode(TRIG_PIN, OUTPUT);      // 设置Trig引脚为输出
  pinMode(ECHO_PIN, INPUT);       // 设置Echo引脚为输入

  Value = Get_Value();  // 初始化Value值
  //  Value = analogRead(A0);//读取模拟脚0
  Serial.begin(9600);  // 初始化串口通信
}

void loop() {
  // 获得滤波值
  Filter_1_Value = Filter_1(N);
  Filter_2_Value = Filter_2(N);
  Filter_3_Value = Filter_3(N);
  Value = Get_Value();

//  Serial.print(TRUE_VALUE);       Serial.print("\t");
  Serial.print(Value);            Serial.print("\t");
  Serial.print(Filter_1_Value);   Serial.print("\t");
  Serial.print(Filter_2_Value);   Serial.print("\t");
  Serial.println(Filter_3_Value);
  delay(DELAY_TIME);
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
  //  return analogRead(LIGHT_PIN);
}
/**
   中位值平均滤波法（又称防脉冲干扰平均滤波法）
*/
float Filter_1(int FILTER_N) {
  int i, j;
  float filter_temp, filter_sum = 0;
  float filter_buf[FILTER_N];
  for (i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_Value();
    delay(10);
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
/**
   中位值滤波法
*/
float Filter_2(int FILTER_N) {
  float filter_buf[FILTER_N];
  int i, j;
  float filter_temp;
  for (i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_Value();
    delay(10);
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
/**
   算术平均滤波法
*/
float Filter_3(int FILTER_N) {
  int i;
  float filter_sum = 0;
  for (i = 0; i < FILTER_N; i++) {
    filter_sum += Get_Value();
    delay(10);
  }
  return (filter_sum / FILTER_N);
}
