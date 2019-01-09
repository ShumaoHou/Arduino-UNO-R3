/**
 * 限幅滤波法(又称程序判断滤波法）
*/
#define TRIG_PIN 4       // 超声波Trig引脚
#define ECHO_PIN 5       // 超声波Echo引脚
#define FILTER_A 5       // 最大差值

float Filter_Value;
float Value;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);      // 设置Trig引脚为输出
  pinMode(ECHO_PIN, INPUT);       // 设置Echo引脚为输入

  Value = Get_Value();  // 初始化Value值
  Serial.begin(9600);  // 初始化串口通信
}

void loop() {
  Filter_Value = Filter();// 获得滤波器输出值
  Value = Filter_Value;// 最近一次有效采样的值，该变量为全局变量
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
  float NewValue;
  NewValue = Get_Value();
  if (((NewValue - Value) > FILTER_A) || ((Value - NewValue) > FILTER_A))
    return Value;
  else
    return NewValue;
}
