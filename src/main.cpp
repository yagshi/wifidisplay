#include <Arduino.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <esp_system.h>
#include <time.h>

// need to be defined in some other file.
// e.g. const char *SSIDS[] = {"my-ap1", "my-ap2", nullptr};
//      const char *PASSWORDS[] = {"password1", "password2", nullptr};
extern const char *SSIDS[];
extern const char *PASSWORDS[];

extern unsigned char font55[][5];
const char *MDNSNAME = "iotdisplay";

const int pins[] = {
    //    4, 16, 17, 5, 18, 19, 21,
    // 25, 26, 27, 14, 12, 13,
    22, 32, 33, 25, 26, 27,
};

const int LED = 2;  // on board
const int LED_R = 17;
const int LED_G = 16;
const int LED_B = 4;
const int BUZZ = 5;
const int BUTTON = 23;
// 以下の  const は pins への間接参照
const int ENABLE = 5;
const int LATCH = 4;
const int CLOCK = 3;
const int COL_B = 2;
const int COL_A = 1;
const int ROW = 0;

const int WIDTH = 384;
const int HEIGHT = 64;

int gWidth = WIDTH;  // スクロール範囲

int gScrollX = 1;
int gScrollY = 0;
// viewport top-left
int gTop = 0;
int gLeft = 0;

enum LEDSTATE { eOff, eNormal, eBreathing, eWarning, eNotification };
enum LEDSTATE gLedState = eBreathing;
// int gLedState = 0;
time_t gTimeRecv = (time_t)0;
WebServer server(80);

uint32_t vram[][HEIGHT][WIDTH / 32] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000003,
      0x8c0cb403, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x0078000e, 0x00038019, 0xc0000e00, 0x000e0000, 0x00000000, 0x7039e007,
      0x7f8dbc03, 0x0063c000, 0x00006700, 0x0001c000, 0x00000000, 0x00000000},
     {0x00739cec, 0x03fb0019, 0x80000e00, 0x000e0001, 0xc6000000, 0x7030e00e,
      0x7f8dfe03, 0x0067e300, 0x00006600, 0x0001c000, 0x00000000, 0x00000000},
     {0x00719ce0, 0x03f80018, 0x00000e00, 0x000e0000, 0xce000000, 0x7000e005,
      0x8c1ffe7f, 0xf84e4300, 0x00006000, 0x0001c000, 0x00000000, 0x00000000},
     {0x00619ccc, 0x038301f9, 0x879b8e3c, 0xe30fce30, 0xec3c3f1e, 0x7e306003,
      0xffdffe7f, 0xf8ce0fcf, 0x1b87e637, 0x0fc1f9c6, 0x00000000, 0x00000000},
     {0x00619ece, 0x038383f9, 0xcf9fce7e, 0x670fe670, 0x6c7e7f3e, 0x7f386007,
      0xffcdff63, 0x18cf8fdf, 0x9fcfe73f, 0x9fc1fcce, 0x00000000, 0x00000000},
     {0x0061b6ce, 0x03f38399, 0xcc1cce06, 0x760e6760, 0x78066630, 0x7338600f,
      0x031c3e63, 0x18c7c701, 0x9cce6739, 0x9981ccec, 0x00000000, 0x00000000},
     {0x0061f6ce, 0x7bf38319, 0xcf1cee1f, 0x360e7360, 0x381f663c, 0x7338600f,
      0x7f9ffe7f, 0xf881e707, 0xdccc6739, 0x9981ce6c, 0x00000000, 0x00000000},
     {0x0061f7ce, 0x7b838319, 0xc79cee77, 0x360e7360, 0x38777e1e, 0x73386007,
      0x7fdfff7f, 0xf880e71d, 0xdccc6739, 0x9f81ce6c, 0x00000000, 0x00000000},
     {0x0060f7ce, 0x038383b9, 0xc1dcce67, 0x3c0e63c0, 0x38676007, 0x73386003,
      0x233cde63, 0x198c6719, 0xdccee739, 0x9801cc78, 0x42100000, 0x00000000},
     {0x0060f38e, 0x038383f9, 0xcf9fce7f, 0x1c0fe1c0, 0x387f7e3e, 0x73386003,
      0x333dfc03, 0x018fe3df, 0xdccfe739, 0x9f81fc38, 0xe7380000, 0x00000000},
     {0x0070e38e, 0x038381d9, 0xcf1f863f, 0x1c0dc1c0, 0x383f7f3c, 0x7338e003,
      0x330dfc03, 0x0187c3cf, 0xdcc76739, 0x9fc1b838, 0xe7380000, 0x00000000},
     {0x00700000, 0x00000000, 0x001c0000, 0x18000180, 0x00006300, 0x0000e003,
      0x0f0f7f03, 0x01000000, 0x00000000, 0x18c00030, 0x00000000, 0x00000000},
     {0x00780000, 0x00000000, 0x001c0000, 0x78000780, 0x00006700, 0x0001e003,
      0x060d2603, 0x03000000, 0x00000000, 0x19c000f0, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00180000, 0x70000700, 0x00007e00, 0x00000000,
      0x00000000, 0x03000000, 0x00000000, 0x1f8000e0, 0x00000000, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000004, 0x00010000, 0x80000c00, 0x00000000, 0x00000000, 0x00100001,
      0x0c0cb403, 0x00000000, 0x00000200, 0x00000000, 0x00000000, 0x00000000},
     {0x007b886c, 0x00030019, 0x80000c00, 0x000c0001, 0x86000000, 0x6031e003,
      0x3f8cb403, 0x00678000, 0x00006600, 0x00018000, 0x00000000, 0x00000000},
     {0x00718c64, 0x03f90018, 0x80000c00, 0x000c0001, 0xce000000, 0x6010e007,
      0x3f8dfe03, 0x004fe700, 0x00006200, 0x00018000, 0x00000000, 0x00000000},
     {0x00739cc0, 0x03f80018, 0x00000c00, 0x000c0000, 0xc6000000, 0x6000e007,
      0x8c3ffe7f, 0xf86e4700, 0x00006000, 0x00018000, 0x00000000, 0x00000000},
     {0x00719eee, 0x030380d9, 0xc71f8c1c, 0x630dc630, 0xcc1c1f1c, 0x6f38e001,
      0xffbef47f, 0xf84e0787, 0x1bc36737, 0x87c1b8c6, 0x00000000, 0x00000000},
     {0x00619ccc, 0x038301f9, 0x8fdfcc7e, 0x630fe630, 0xfc7e7f3f, 0x7f306003,
      0x7f9ffe63, 0x184f0f9f, 0x9fc7e63f, 0x9fc1fcc6, 0x00000000, 0x00000000},
     {0x0061decc, 0x03f30339, 0x8e1dec27, 0x670ef670, 0x7c276638, 0x77306007,
      0x030f7563, 0x1887c309, 0xddcce63b, 0x9981dece, 0x00000000, 0x00000000},
     {0x0061b7cc, 0x73f30319, 0x8f18cc3e, 0x760c6760, 0x783e763c, 0x63306007,
      0xffde3e7f, 0xf8c3e30f, 0x98cc6631, 0x9d818cec, 0x00000000, 0x00000000},
     {0x0060b68c, 0x73030719, 0x83d8cc7e, 0x3e0c63e0, 0x307e3c0f, 0x63306003,
      0xff9ffe7f, 0xf980731f, 0x98dc6631, 0x8f018c7c, 0x00000000, 0x00000000},
     {0x0061e38c, 0x03030319, 0x8999ec66, 0x1e0ce1e0, 0x30667826, 0x63306003,
      0x331f9463, 0x1884e319, 0x98cc6631, 0x9e019c3c, 0xe7380000, 0x00000000},
     {0x0070e7cc, 0x030303f9, 0x9fdfce7e, 0x1c0fe1c0, 0x307e7f7f, 0x6330e003,
      0x730cde03, 0x018fe79f, 0x98cfe631, 0x9fc1fc38, 0xe7380000, 0x00000000},
     {0x0070e38c, 0x030300f9, 0x879b0772, 0x180d8180, 0x30723f1e, 0x6330e003,
      0x3b0ddf03, 0x010781dc, 0x98c3e631, 0x8fc1b030, 0x42100000, 0x00000000},
     {0x00780000, 0x00000000, 0x00180000, 0x18000180, 0x00006300, 0x0001e003,
      0x070fbf03, 0x01800000, 0x00000000, 0x18c00030, 0x00000000, 0x00000000},
     {0x00780000, 0x00000000, 0x00180000, 0x78000780, 0x0000e300, 0x0001e003,
      0x0f0c3e03, 0x01000000, 0x00000000, 0x38c000f0, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x001c0000, 0x60000600, 0x00007f00, 0x00000000,
      0x00000000, 0x01000000, 0x00000000, 0x1fc000c0, 0x00000000, 0x00000000}}};

hw_timer_t *gTimer;      // = timerBegin(0, 80, true);  //
                         // 80 にすると 1us
hw_timer_t *gTimerSlow;  // = timerBegin(1, 80, true);

void cls() {
  for (int plane = 0; plane < 2; plane++) {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH / 32; x++) {
        vram[plane][y][x] = 0;
      }
    }
  }
}

void drawText(int x0, int y0, const char *s) {
  for (; *s; s++, x0 += 6) {
    if (x0 >= WIDTH) {
      x0 = 0;
    }
    for (int r = 0, y = y0; r < 5; r++, y = (y + 1) % HEIGHT) {
      int xp = x0 / 32;
      uint32_t bd = 0x80000000 >> (x0 % 32);
      for (int bs = 0b10000; bs; bs >>= 1) {
        if (font55[(int)*s][r] & bs) {
          vram[0][y][xp] |= bd;
          vram[1][y][xp] |= bd;
        } else {
          vram[0][y][xp] &= ~bd;
          vram[1][y][xp] &= ~bd;
        }
        bd >>= 1;
        if (bd == 0) {
          bd = 0x80000000;
          xp++;
          if (xp >= WIDTH / 32) {
            xp = 0;
          }
        }
      }
    }
  }
}

void IRAM_ATTR pressed() {
  gLedState = gLedState == eOff ? eBreathing : eOff;
  if (gLedState == eOff) {
    ledcAttachPin(LED_R, 0);
    ledcAttachPin(LED_G, 0);
    ledcAttachPin(LED_B, 0);
  } else {
    ledcDetachPin(LED_R);
    ledcDetachPin(LED_G);
    ledcDetachPin(LED_B);
    digitalWrite(LED_R, 0);
    digitalWrite(LED_G, 0);
    digitalWrite(LED_B, 0);
  }
}

void IRAM_ATTR interruptFuncSlow() {
  static int pwm = 10;
  static int v = 8;  // デューティの変化分
  pwm = (pwm + v) & 0xff;
  if (pwm > 240 || pwm < 10) {
    v = -v;
    pwm += v;
  }
  ledcWrite(0, pwm);
  timerAlarmDisable(gTimer);
  gLeft = (gLeft + gScrollX + gWidth) % gWidth;
  gTop = (gTop + gScrollY + HEIGHT) % HEIGHT;
  timerAlarmEnable(gTimer);

  switch (gLedState) {
    case eOff:
      ledcDetachPin(LED_R);
      ledcDetachPin(LED_G);
      ledcDetachPin(LED_B);
      digitalWrite(LED_R, 0);
      digitalWrite(LED_G, 0);
      digitalWrite(LED_B, 0);
      break;
    case eBreathing:
      ledcAttachPin(LED_R, 0);
      ledcAttachPin(LED_G, 0);
      ledcAttachPin(LED_B, 0);
      break;
  }
}

void IRAM_ATTR interruptFunc() {
  static int row = 0;
  static int plane = 0;  // 0, 1, 2
  uint32_t theRow = 0;

  int p0 = gLeft / 32;
  uint32_t bs0 = 0x80000000 >> (gLeft + 32 % 32);  // 転送元ビット
  uint32_t bd = 0x80000000;                        // 転送先(theRow)ビット

  uint32_t bs = bs0;
  timerAlarmDisable(gTimerSlow);

  for (int i = 0, p = p0, x = gLeft; i < 32; i++) {
    switch (plane & 15) {
      case 0:
      case 3:
      case 6:
      case 9:
        if (vram[0][(row + gTop) % HEIGHT][p] & bs) {
          theRow |= bd;
        }
        break;
      case 1:
      case 5:
        if (vram[1][(row + gTop) % HEIGHT][p] & bs) {
          theRow |= bd;
        }
        break;
      default:
        if (vram[0][(row + gTop) % HEIGHT][p] &
            vram[1][(row + gTop) % HEIGHT][p] & bs) {
          theRow |= bd;
        }
    }
    bd = bd >> 1;
    bs = bs >> 1;
    if (bs == 0) {
      bs = 0x80000000;
      p = (p + 1) % (WIDTH / 32);
    }
    if (++x >= gWidth) {
      p = 0;
      bs = 0x80000000;
      x = 0;
    }
  }

  for (unsigned int c = 0, bh = 1 << 31, bl = 1 << 15; c < 16;
       c++, bh = bh >> 1, bl = bl >> 1) {
    digitalWrite(pins[CLOCK], 0);
    digitalWrite(pins[ROW], (15 - row) == c ? 1 : 0);
    digitalWrite(pins[COL_A], theRow & bl ? 1 : 0);
    digitalWrite(pins[COL_B], theRow & bh ? 1 : 0);
    digitalWrite(pins[CLOCK], 1);
  }
  digitalWrite(pins[LATCH], 1);
  digitalWrite(pins[LATCH], 0);
  row++;
  if (row > 15) {
    row = 0;
    plane++;
  }
  timerAlarmEnable(gTimerSlow);
}

int h2d1(char c) {  // hex to decimal
  if (c >= '0' && c <= '9') return c - '0';
  return tolower(c) - 'a' + 10;
}

void setupWiFi() {
  int i = 0;
  while (true) {
    WiFi.begin(SSIDS[i], PASSWORDS[i]);
    Serial.println(SSIDS[i]);
    for (int j = 0; j < 32; j++) {
      if (WiFi.status() == WL_CONNECTED) {
        configTime(3600 * 9, 0, "jp.pool.ntp.org", "ntp.nict.jp");
        MDNS.begin(MDNSNAME);
        MDNS.addService("http", "tcp", 80);
        return;
      }
      digitalWrite(LED, !digitalRead(LED));
      delay(200);
    }
    i++;
    if (SSIDS[i] == nullptr) {
      i = 0;
    }
  }
}

void setupServer() {
  server.begin();
  server.on("/", []() {
    String cmd = server.arg("cmd");
    int width = server.arg("width").toInt();
    timerAlarmDisable(gTimer);
    if (cmd == "home") {
      gTop = 0;
      gLeft = 0;
    }
    if (cmd == "scrollL" || cmd == "scroll") {
      gScrollX = 1;
    }
    if (cmd == "scrollR") {
      gScrollX = -1;
    }
    if (cmd == "scrollU") {
      gScrollY = 1;
    }
    if (cmd == "scrollD") {
      gScrollY = -1;
    }
    if (cmd == "stop") {
      gScrollX = 0;
      gScrollY = 0;
    }
    if (width > 0) {
      gWidth = width;
    }
    timerAlarmEnable(gTimer);
    server.send(200, "text/plain", "ok\n");
  });
  // 行のみ指定可能
  // /set?row=**&data=55aa1701....
  server.on("/set", []() {
    gTimeRecv = time(NULL);
    int row = server.arg("row").toInt();
    int plane = server.arg("plane").toInt() & 3;
    int offset = 0;  // VRAM 1要素(32bit)単位でいくつめか
    String data = server.arg("data");
    while (offset * 8 < data.length()) {
      uint32_t d = (h2d1(data.charAt(offset * 8 + 0)) << 28) +
                   (h2d1(data.charAt(offset * 8 + 1)) << 24) +
                   (h2d1(data.charAt(offset * 8 + 2)) << 20) +
                   (h2d1(data.charAt(offset * 8 + 3)) << 16) +
                   (h2d1(data.charAt(offset * 8 + 4)) << 12) +
                   (h2d1(data.charAt(offset * 8 + 5)) << 8) +
                   (h2d1(data.charAt(offset * 8 + 6)) << 4) +
                   (h2d1(data.charAt(offset * 8 + 7)) << 0);
      vram[plane][row][offset] = d;
      offset++;
    }
    server.send(200, "text/plain", "ok\n");
  });
}

void setup() {
  Serial.begin(115200);
  for (int i : pins) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  digitalWrite(pins[ENABLE], 1);  // disable
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  setupWiFi();

  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), pressed, FALLING);

  digitalWrite(pins[ENABLE], 0);  // enable

  gTimerSlow = timerBegin(1, 80, true);

  gTimer = timerBegin(0, 80, true);  // 80 にすると 1us

  timerAttachInterrupt(gTimer, interruptFunc, true);
  timerAlarmWrite(gTimer, 50, true);
  timerAttachInterrupt(gTimerSlow, interruptFuncSlow, true);
  timerAlarmWrite(gTimerSlow, 40000, true);
  timerAlarmEnable(gTimer);
  timerAlarmEnable(gTimerSlow);
  ledcSetup(0, 10000, 8);  // 第2引数は周波数
  // ledcSetup(1, 500, 8);    // 第2引数は周波数
  // ledcAttachPin(BUZZ, 1);
  ledcWrite(1, 128);
  setupServer();
  ledcAttachPin(LED, 0);
  drawText(0, 0, (const char *)WiFi.localIP().toString().c_str());
}

void loop() {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      server.handleClient();
      break;
    case WL_CONNECTION_LOST:
      Serial.println("connection lost");
      break;
    case WL_DISCONNECTED:
      Serial.println("disconnected");
      break;
    default:
      Serial.println(WiFi.status());
      break;
  }
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
  }

  if (time(NULL) - gTimeRecv > 600) {
    gTimeRecv = time(NULL);
    cls();
    drawText(0, 2, "NO NEW INFORMATION");
    drawText(0, 10, "(CONNECTION LOST?)");
    Serial.println("connectoin lost?");
    gWidth = 6 * 18 + 10;
    gLedState = eWarning;
  }

  Serial.println(time(NULL));
  delay(15);
}
