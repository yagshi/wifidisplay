#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>

const int pins[] = {
    4, 16, 17, 5, 18, 19, 21,
};
const int LED = 2;
// 以下の  const は pins への間接参照
const int ENABLE = 5;
const int LATCH = 4;
const int CLOCK = 3;
const int COL_B = 2;
const int COL_A = 1;
const int ROW = 0;

unsigned int vram[][16] = {
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0xffffff00,
        0xffffff00,
        0xfffffff0,
        0xfffffff0,
        0x55555555,
        0xaaaaaaaa,
        0x55555555,
        0x00000010,
        0xffff5508,
        0xffffaa04,
        0xffff5502,
        0xffffaa01,
    },
    {
        0x00000000,
        0x00000000,
        0xfffffff0,
        0xfffffff0,
        0x00000000,
        0x00000000,
        0xfffffff0,
        0xfffffff0,
        0x00000000,
        0xaaaaaaaa,
        0x55555555,
        0x00000000,
        0x00000000,
        0xaaaaaaaa,
        0x55555555,
        0x00000000,
    },
};

hw_timer_t *gTimer = timerBegin(0, 80, true);  // 80 にすると 1us
hw_timer_t *gTimerSlow = timerBegin(1, 80, true);

void IRAM_ATTR interruptFuncSlow() {
  static int pwm = 10;
  static int v = 8;  // デューティの変化分
  pwm = (pwm + v) & 0xff;
  if (pwm > 240 || pwm < 10) {
    v = -v;
    pwm += v;
  }
  ledcWrite(0, pwm);
  for (int i = 0; i < 16; i++) {
    vram[0][i] = ((vram[0][i] << 1) & 0xffffffff) | vram[0][i] >> 31;
    vram[1][i] = ((vram[1][i] << 1) & 0xffffffff) | vram[1][i] >> 31;
  }
}

// 01 1
// 10 2
// 11 3

void IRAM_ATTR interruptFunc() {
  static int row = 0;
  static int plane = 0;  // 0, 1, 2
  int theRow = 0;

  switch (plane & 31) {
    case 0:
    case 3:
    case 6:
    case 9:
      theRow = vram[0][row];
      break;
    case 1:
      theRow = vram[1][row];
      break;
    default:
      theRow = vram[0][row] & vram[1][row];
  }

  if ((plane & 0x03) == 0) {
    theRow |= vram[0][row];
  }

  if ((plane & 0x07) == 0) {
    theRow |= vram[1][row];
  }

  for (int c = 0, bh = 65536, bl = 1; c < 16; c++, bh += bh, bl += bl) {
    digitalWrite(pins[CLOCK], 0);
    digitalWrite(pins[ROW], row == c ? 1 : 0);
    digitalWrite(pins[COL_A], theRow & bh ? 1 : 0);
    digitalWrite(pins[COL_B], theRow & bl ? 1 : 0);
    digitalWrite(pins[CLOCK], 1);
  }
  digitalWrite(pins[LATCH], 1);
  digitalWrite(pins[LATCH], 0);
  row++;
  if (row > 15) {
    row = 0;
    plane++;
  }
}

void setup() {
  for (int i : pins) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  timerAttachInterrupt(gTimer, interruptFunc, true);
  timerAlarmWrite(gTimer, 50, true);
  timerAttachInterrupt(gTimerSlow, interruptFuncSlow, true);
  timerAlarmWrite(gTimerSlow, 100000, true);
  timerAlarmEnable(gTimer);
  timerAlarmEnable(gTimerSlow);
  ledcSetup(0, 10000, 8);  // 第2引数は周波数
  ledcAttachPin(LED, 0);
}

void loop() { delay(100); }
