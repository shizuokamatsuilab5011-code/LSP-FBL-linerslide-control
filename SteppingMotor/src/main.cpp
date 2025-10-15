#include <Arduino.h>

#define enPin 3   // ENピン（有効/無効ピン）
#define dirPin 5  // 方向ピン
#define stepPin 7 // ステップピン

#define stepsPerRevolution 400 // モータの1回転あたりのステップ数（マイクロステップの設定により変わります

// プロトタイプ宣言
void rotateMotor();

void setup()
{
  // シリアル通信の初期化
  Serial.begin(9600);
  Serial.println("start!");

  // ピンモードの設定
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  Serial.println("pinMode setup done!");

  // モータを1回転させる関数
  rotateMotor();
}

void loop()
{
  Serial.println("loop start!");
  // シリアル入力があるか確認
  if (Serial.available() > 0)
  {
    // 1バイトのデータを読み込む
    char input = Serial.read();
    // 入力が 'd' なら時計回り
    if (input == 'd')
    {
      Serial.println("down...");
      digitalWrite(dirPin, HIGH); // 時計回りに設定
      digitalWrite(enPin, LOW);   // モータを有効化
      rotateMotor();              // モータを回転させる関数を呼び出す
      digitalWrite(enPin, HIGH);  // モータを無効化
    }
    // 入力が 'u' なら反時計回り
    if (input == 'u')
    {
      Serial.println("up...");
      digitalWrite(dirPin, LOW); // 反時計回りに設定
      digitalWrite(enPin, LOW);  // モータを有効化
      rotateMotor();             // モータを回転させる関数を呼び出す
      digitalWrite(enPin, HIGH); // モータを無効化
    }
  }
}

void rotateMotor()
{
  for (int i = 0; i < stepsPerRevolution - 200; i++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100000); // パルスの幅を調整して回転速度を決定ここも適宜調整してください
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100); // パルス間隔を調整ここも適宜調整してください
  }
}