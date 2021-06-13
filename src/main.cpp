#include <Arduino.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <esp_system.h>

// need to be defined in some other file.
// e.g. const char *SSIDS = ["my-ap1", "my-ap2", nullptr];
//      const char *PASSWORDS = ["password1", "password2", nullptr];
extern const char *SSIDS[];
extern const char *PASSWORDS[];

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

const int WIDTH = 128;
const int HEIGHT = 64;

int gScrollX = 0;
int gScrollY = 0;
// viewport top-left
int gTop = 0;
int gLeft = 0;
WebServer server(80);

uint32_t vram[][HEIGHT][WIDTH / 32] = {
    {
        {0x00000000, 0xff000000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x00ff0000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x0000ff00, 0x33333333, 0x33333333},
        {0x00000000, 0x000000ff, 0x33333333, 0x33333333},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0x55555555, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xaaaaaaaa, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0x55555555, 0x00000000, 0x33333333, 0x33333333},
        {0x00000010, 0x00000000, 0x33333333, 0x33333333},
        {0xffff5508, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffffaa04, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffff5502, 0x00000000, 0x33333333, 0x33333333},
        {0xffffaa01, 0x00000000, 0x33333333, 0x33333333},
        ////////////////////////////////////////////////
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0x55555555, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xaaaaaaaa, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0x55555555, 0x00000000, 0x33333333, 0x33333333},
        {0x00000010, 0x00000000, 0x33333333, 0x33333333},
        {0xffff5508, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffffaa04, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffff5502, 0x00000000, 0x33333333, 0x33333333},
        {0xffffaa01, 0x00000000, 0x33333333, 0x33333333},
        {0x00000000, 0xff000000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x00ff0000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x0000ff00, 0x33333333, 0x33333333},
        {0x00000000, 0x000000ff, 0x33333333, 0x33333333},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
    },
    {
        {0x00000000, 0xff000000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x00ff0000, 0xcccccccc, 0xcccccccc},
        {0x00000000, 0x0000ff00, 0x33333333, 0x33333333},
        {0x00000000, 0x000000ff, 0x33333333, 0x33333333},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xffffff00, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0xfffffff0, 0x00000000, 0x33333333, 0x33333333},
        {0x55555555, 0x00000000, 0xcccccccc, 0xcccccccc},
        {0xaaaaaaaa, 0x00000000, 0xcccccccc, 0xcccccccc},
    }};

hw_timer_t *gTimer;      // = timerBegin(0, 80, true);  // 80 にすると 1us
hw_timer_t *gTimerSlow;  // = timerBegin(1, 80, true);

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
  gLeft = (gLeft + gScrollX + WIDTH) % WIDTH;
  gTop = (gTop + gScrollY + HEIGHT) % HEIGHT;
  timerAlarmEnable(gTimer);
}

void IRAM_ATTR interruptFunc() {
  static int row = 0;
  static int plane = 0;  // 0, 1, 2
  uint32_t theRow = 0;

  int p = gLeft / 32;
  uint32_t bs = 0x80000000 >> (gLeft + 32 % 32);  // 転送元ビット
  uint32_t bd = 0x80000000;                       // 転送先(theRow)ビット

  timerAlarmDisable(gTimerSlow);

  for (int i = 0; i < 32; i++) {
    switch (plane & 31) {
      case 0:
      case 3:
      case 6:
      case 9:
        if (vram[0][(row + gTop) % HEIGHT][p] & bs) {
          theRow |= bd;
        }
        break;
      case 1:
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

  timerAlarmEnable(gTimerSlow);
}

int h2d1(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  return tolower(c) - 'a' + 10;
}

void connectWiFi() {
  int i = 0;
  while (true) {
    WiFi.begin(SSIDS[i], PASSWORDS[i]);
    Serial.println(SSIDS[i]);
    for (int j = 0; j < 32; j++) {
      if (WiFi.status() == WL_CONNECTED) return;
      digitalWrite(LED, !digitalRead(LED));
      delay(200);
    }
    i++;
    if (SSIDS[i] == nullptr) {
      i = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);
  for (int i : pins) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  connectWiFi();
  MDNS.begin("iotdisplay");
  server.begin();
  server.on("/", []() {
    String cmd = server.arg("cmd");
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
    server.send(200, "text/plain", "ok");
  });
  // 行のみ指定可能
  // /set?row=**&data=55aa1701....
  server.on("/set", []() {
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
    server.send(200, "text/plain", "ok");
  });

  gTimer = timerBegin(0, 80, true);  // 80 にすると 1us
  gTimerSlow = timerBegin(1, 80, true);

  Serial.println("connected.");

  timerAttachInterrupt(gTimer, interruptFunc, true);
  timerAlarmWrite(gTimer, 50, true);
  timerAttachInterrupt(gTimerSlow, interruptFuncSlow, true);
  timerAlarmWrite(gTimerSlow, 100000, true);
  timerAlarmEnable(gTimer);
  timerAlarmEnable(gTimerSlow);
  ledcSetup(0, 10000, 8);  // 第2引数は周波数
  ledcAttachPin(LED, 0);
}

void loop() {
  server.handleClient();
  Serial.println(WiFi.localIP());
  delay(10);
}
