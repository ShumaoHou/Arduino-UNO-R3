/* 引脚变量 */
const int buttonPin = 2;      // 定义按钮引脚
const int ledPin = 13;        // 定义LED引脚

/* 状态变量 */
volatile int nowButtonState = LOW;     // 记录中断时按钮的状态
int ledState = LOW;           // 记录LED的状态
int buttonState = LOW;        // 记录之前按键状态
int lastButtonState = LOW;    // 记录上一次按键的状态
int longPressCounter = 0;     // 记录长击次数
int resultCounter = 0;        // 记录连续长击的次数

/* 消抖变量 */
long lastDebounceTime = 0;  // 按键最后一次被触发
long debounceDelay = 500;   // 消抖的时间间隔
long beginButtonTime = 0;   // 按键按下瞬间的时间
long longPressDelay = 1000; // 超过此间隙则定义为长按

void setup() {
  pinMode(ledPin, OUTPUT);              // 初始化LED为输出模式
  pinMode(buttonPin, INPUT_PULLUP);     // 初始化大按钮模块为输入下拉模式
  digitalWrite(ledPin, ledState);       // 设置LED初始状态
  attachInterrupt(digitalPinToInterrupt(buttonPin), blink, CHANGE); //按钮状态改变触发中断，调用blink函数
  Serial.begin(9600);
}

void loop() {
  if (nowButtonState != lastButtonState) {
    lastDebounceTime = millis();  // 记录抖动初始时间
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {  // 时间间隙超过抖动间隙
    if (nowButtonState != buttonState) {  // 如果按键状态改变了:
      buttonState = nowButtonState;
      if (buttonState == LOW) {     // FSM, 按键按下
        beginButtonTime = millis(); // 记录按键按下初始时间
        ledState = HIGH;            // 按下灯亮
      }else{  // FSM，按键抬起
        if ((millis() - beginButtonTime) > longPressDelay) {  // 长按
          longPressCounter++;
          Serial.println("1");
        } else {  // 短按
          if (longPressCounter > 0) {
            resultCounter++;
            Serial.print("连续1(包括单个1)出现的状态总共的次数: ");
            Serial.println(resultCounter);
            longPressCounter = 0; // 长按计数归零
          }
          Serial.println("0");
        }
        ledState = LOW; // 抬起灯灭
      }
    }
  }
  digitalWrite(ledPin, ledState);   // 设置LED:
  lastButtonState = nowButtonState; // 保存处理结果:
}

/* ISR */
void blink() {
  nowButtonState = digitalRead(buttonPin);
}
