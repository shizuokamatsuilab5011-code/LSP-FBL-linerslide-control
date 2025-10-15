#include <Arduino.h>

#define enPin 3   // EN�s���i�L��/�����s���j
#define dirPin 5  // �����s��
#define stepPin 7 // �X�e�b�v�s��

#define stepsPerRevolution 400 // ���[�^��1��]������̃X�e�b�v���i�}�C�N���X�e�b�v�̐ݒ�ɂ��ς��܂�

// �v���g�^�C�v�錾
void rotateMotor();

void setup()
{
  // �V���A���ʐM�̏�����
  Serial.begin(9600);
  Serial.println("start!");

  // �s�����[�h�̐ݒ�
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  Serial.println("pinMode setup done!");

  // ���[�^��1��]������֐�
  rotateMotor();
}

void loop()
{
  Serial.println("loop start!");
  // �V���A�����͂����邩�m�F
  if (Serial.available() > 0)
  {
    // 1�o�C�g�̃f�[�^��ǂݍ���
    char input = Serial.read();
    // ���͂� 'd' �Ȃ玞�v���
    if (input == 'd')
    {
      Serial.println("down...");
      digitalWrite(dirPin, HIGH); // ���v���ɐݒ�
      digitalWrite(enPin, LOW);   // ���[�^��L����
      rotateMotor();              // ���[�^����]������֐����Ăяo��
      digitalWrite(enPin, HIGH);  // ���[�^�𖳌���
    }
    // ���͂� 'u' �Ȃ甽���v���
    if (input == 'u')
    {
      Serial.println("up...");
      digitalWrite(dirPin, LOW); // �����v���ɐݒ�
      digitalWrite(enPin, LOW);  // ���[�^��L����
      rotateMotor();             // ���[�^����]������֐����Ăяo��
      digitalWrite(enPin, HIGH); // ���[�^�𖳌���
    }
  }
}

void rotateMotor()
{
  for (int i = 0; i < stepsPerRevolution - 200; i++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100000); // �p���X�̕��𒲐����ĉ�]���x�����肱�����K�X�������Ă�������
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100); // �p���X�Ԋu�𒲐��������K�X�������Ă�������
  }
}