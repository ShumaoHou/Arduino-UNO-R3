/* 引脚变量*/
const int ledPin = 11;  // 11引脚为虚拟引脚
/* 状态变量*/
int delayTime = 5;  // 每个数值亮度保持时间(毫秒)
int maxLight = 255; // 最大亮度

void setup() {
  pinMode(ledPin, OUTPUT);  // 设置引脚为输出
}

void loop() {
  // LED由暗(0)到亮(maxLight)
  for (int i = 0; i <= maxLight; i ++) {
    analogWrite(ledPin, i); // 虚拟写入亮度
    delay(delayTime);       // 保持亮度
  }
  // LED由亮(maxLight)到暗(0)
  for (int i = maxLight; i >= 0; i --) {
    analogWrite(ledPin, i);
    delay(delayTime);
  }
}
