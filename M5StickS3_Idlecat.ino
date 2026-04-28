#include <M5Unified.h>

// ---------- Display ----------
M5Canvas canvas(&M5.Display);
int SCREEN_W, SCREEN_H;

// ---------- Your palettes ----------
const uint16_t catColors[10] = { 0x0000, 0x2965, 0x2965, 0x6B4D, 0xFFFF, 0xB7FF, 0xFBB6, 0xFE25, 0xFE7C, 0xFC7A };
const uint16_t roomColors[8] = { 0xFEFB, 0xC4B0, 0x9DFF, 0x6B4D, 0x3CC7, 0xA2C7, 0xC1C7, 0xFEC8 };

// ---------- Your art ----------
const uint8_t catAwake[24][24] = {
  {0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
  {0,0,1,1,1,1,3,3,1,3,3,1,3,3,1,1,1,1,0,0,0,0,0,0},
  {0,2,1,1,1,1,3,3,1,3,3,1,3,3,1,1,1,1,2,0,0,0,0,0},
  {0,2,2,1,1,1,3,3,1,3,3,1,3,3,1,1,1,2,2,0,0,0,0,0},
  {0,2,2,2,1,1,3,3,1,3,3,1,3,3,1,1,2,2,2,0,0,0,0,0},
  {0,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0},
  {0,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0},
  {0,2,1,1,1,5,5,1,1,1,1,1,1,5,5,1,1,1,2,0,0,0,0,0},
  {0,1,1,1,1,5,5,1,1,4,4,1,1,5,5,1,1,1,1,0,0,0,0,0},
  {0,1,1,1,1,5,5,4,4,4,4,4,4,5,5,1,1,1,1,0,0,0,0,0},
  {0,1,1,8,8,1,4,4,4,9,9,4,4,4,1,8,8,1,1,0,0,0,0,0},
  {0,0,1,1,1,1,4,4,4,4,4,4,4,4,1,1,1,1,0,0,0,0,1,1},
  {0,0,0,1,1,4,4,4,4,4,4,4,4,4,4,1,1,0,0,0,0,1,1,2},
  {0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,6,6,6,6,7,7,6,6,6,6,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,1,1,1,1,1,7,7,1,1,1,1,1,0,0,0,0,1,1,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
  {0,0,2,1,1,3,1,1,1,1,1,1,1,3,1,1,1,1,2,0,0,0,0,0},
  {0,0,2,2,1,3,3,1,1,1,1,1,1,3,3,1,1,2,2,1,0,0,0,0},
  {0,0,2,2,1,3,3,1,1,1,1,1,1,3,3,1,1,2,2,1,0,0,0,0},
  {0,0,1,1,1,3,3,1,1,1,1,1,1,3,3,1,1,1,1,1,0,0,0,0}
};

const uint8_t catSleep[24][24] = {
  {0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
  {0,0,1,1,1,1,3,3,1,3,3,1,3,3,1,1,1,1,0,0,0,0,0,0},
  {0,2,1,1,1,1,3,3,1,3,3,1,3,3,1,1,1,1,2,0,0,0,0,0},
  {0,2,2,1,1,1,3,3,1,3,3,1,3,3,1,1,1,2,2,0,0,0,0,0},
  {0,2,2,2,1,1,3,3,1,3,3,1,3,3,1,1,2,2,2,0,0,0,0,0},
  {0,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0},
  {0,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0},
  {0,2,1,1,5,5,5,1,1,1,1,1,1,5,5,5,1,1,2,0,0,0,0,0},
  {0,1,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,0,0,0,0,0},
  {0,1,1,1,1,1,1,4,4,4,4,4,4,1,1,1,1,1,1,0,0,0,0,0},
  {0,1,1,8,8,1,4,4,4,9,9,4,4,4,1,8,8,1,1,0,0,0,0,0},
  {0,0,1,1,1,1,4,4,4,4,4,4,4,4,1,1,1,1,0,0,0,0,0,0},
  {0,0,0,1,1,4,4,4,4,4,4,4,4,4,4,1,1,0,0,0,0,0,0,0},
  {0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,6,6,6,6,7,7,6,6,6,6,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,1,1,1,1,7,7,1,1,1,1,1,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
  {0,0,2,1,1,3,1,1,1,1,1,1,1,3,1,1,1,1,2,0,0,0,1,1},
  {0,0,2,2,1,3,3,1,1,1,1,1,1,3,3,1,1,2,2,1,0,1,1,1},
  {0,0,2,2,1,3,3,1,1,1,1,1,1,3,3,1,1,2,2,1,1,1,1,0},
  {0,0,1,1,1,3,3,1,1,1,1,1,1,3,3,1,1,1,1,1,0,0,0,0}
};

const uint8_t roomMap[30][20] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0},
  {0,3,2,2,2,2,2,2,3,0,0,0,0,0,4,0,4,0,0,0},
  {0,3,2,2,2,2,2,2,3,0,0,0,0,0,0,4,4,4,0,0},
  {0,3,2,2,2,2,2,2,3,0,0,0,0,0,4,4,4,4,4,0},
  {0,3,2,2,2,2,2,2,3,0,0,0,0,0,0,4,5,5,4,0},
  {0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,5,5,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// ---------- Layout ----------
const int CAT_SIZE     = 24;
const int CAT_SCALE    = 4;       // 24 * 4 = 96 px on screen
const int CAT_Y_OFFSET = 10;     // shift cat up
const int ROOM_W       = 20;
const int ROOM_H       = 30;

// ---------- Particle tunables (your tweaks) ----------
const int CONFETTI_COUNT = 12;    // fewer pieces
const int CONFETTI_SIZE  = 4;     // bigger pieces
const int HEART_BURST    = 1;     // fewer hearts
const int HEART_SCALE    = 5;     // bigger hearts

// ---------- Particles ----------
struct Particle {
  float x, y, vx, vy;
  uint16_t color;
  uint8_t life;
  uint8_t kind;  // 0=confetti, 1=heart, 2=Z
};
const int MAX_PARTICLES = 60;
Particle particles[MAX_PARTICLES];

uint16_t confettiPalette[] = {
  0xF800, 0xFD20, 0xFFE0, 0x07E0, 0x07FF, 0x001F, 0xF81F, 0xFC9F
};

void spawnConfetti(int count) {
  int cx = SCREEN_W / 2, cy = SCREEN_H / 2;
  int spawned = 0;
  for (int i = 0; i < MAX_PARTICLES && spawned < count; i++) {
    if (particles[i].life == 0) {
      particles[i].x = cx;
      particles[i].y = cy;
      particles[i].vx = (random(-100, 101)) / 30.0;
      particles[i].vy = (random(-150, -30)) / 30.0;
      particles[i].color = confettiPalette[random(8)];
      particles[i].life = 70;
      particles[i].kind = 0;
      spawned++;
    }
  }
}

void spawnHeartBurst() {
  int cx = SCREEN_W / 2, cy = SCREEN_H / 2 - 1;
  int spawned = 0;
  for (int i = 0; i < MAX_PARTICLES && spawned < HEART_BURST; i++) {
    if (particles[i].life == 0) {
      particles[i].x = cx + random(-6, 7);
      particles[i].y = cy;
      particles[i].vx = random(-15, 16) / 30.0;
      particles[i].vy = -1.0;
      particles[i].color = 0xF81F;
      particles[i].life = 90;
      particles[i].kind = 1;
      spawned++;
    }
  }
}

void spawnSleepZ() {
  int cx = SCREEN_W / 2 + 30;
  int cy = SCREEN_H / 2 - 40;
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life == 0) {
      particles[i].x = cx;
      particles[i].y = cy;
      particles[i].vx = 0.3;
      particles[i].vy = -0.4;
      particles[i].color = 0x9CD3;
      particles[i].life = 100;
      particles[i].kind = 2;
      return;
    }
  }
}

void updateParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      if (particles[i].kind == 0) particles[i].vy += 0.15;
      if (particles[i].kind == 2) particles[i].x += sinf(particles[i].life * 0.1) * 0.3;
      particles[i].life--;
    }
  }
}

// Bigger heart - parameterized scale (s=2 makes it 10x10)
void drawHeart(int x, int y, uint16_t c, int s) {
  canvas.fillRect(x,         y,         2*s, 2*s, c);
  canvas.fillRect(x + 3*s,   y,         2*s, 2*s, c);
  canvas.fillRect(x,         y + 2*s,   5*s, 1*s, c);
  canvas.fillRect(x + 1*s,   y + 3*s,   3*s, 1*s, c);
  if (s >= 2) canvas.fillRect(x + 2*s, y + 4*s, 1*s, 1*s, c);
}

void drawZ(int x, int y, uint16_t c) {
  canvas.drawLine(x,   y,   x+4, y,   c);
  canvas.drawLine(x+4, y,   x,   y+4, c);
  canvas.drawLine(x,   y+4, x+4, y+4, c);
}

// ---- THE FIX: use 24x24 loop and read from catColors palette ----
void drawCat(int ox, int oy, bool sleeping) {
  for (int y = 0; y < CAT_SIZE; y++) {
    for (int x = 0; x < CAT_SIZE; x++) {
      uint8_t p = sleeping ? catSleep[y][x] : catAwake[y][x];
      if (p == 0) continue;  // transparent
      canvas.fillRect(ox + x*CAT_SCALE, oy + y*CAT_SCALE,
                      CAT_SCALE, CAT_SCALE, catColors[p]);
    }
  }
}

// ---- THE FIX: draw the room from roomMap, not hardcoded shapes ----
void drawRoom() {
  float cellW = (float)SCREEN_W / ROOM_W;
  float cellH = (float)SCREEN_H / ROOM_H;
  for (int y = 0; y < ROOM_H; y++) {
    for (int x = 0; x < ROOM_W; x++) {
      uint8_t v = roomMap[y][x];
      int px = (int)(x * cellW);
      int py = (int)(y * cellH);
      int pw = (int)((x + 1) * cellW) - px + 1;
      int ph = (int)((y + 1) * cellH) - py + 1;
      canvas.fillRect(px, py, pw, ph, roomColors[v]);
    }
  }
}

// ---------- Sound ----------
void playMeow() {
  M5.Speaker.tone(700, 80);  delay(80);
  M5.Speaker.tone(900, 120); delay(120);
  M5.Speaker.tone(600, 100);
}
void playPartySound() {
  int notes[] = {523, 659, 784, 1047};
  for (int i = 0; i < 4; i++) { M5.Speaker.tone(notes[i], 80); delay(70); }
}

// ---------- Shake & idle ----------
float shakeEnergy = 0;
const float SHAKE_THRESHOLD = 4.0;
unsigned long lastInteraction = 0;
const unsigned long SLEEP_AFTER_MS = 4000;
unsigned long lastZSpawn = 0;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setRotation(0);
  M5.Speaker.setVolume(120);
  SCREEN_W = M5.Display.width();
  SCREEN_H = M5.Display.height();
  canvas.createSprite(SCREEN_W, SCREEN_H);
  randomSeed(esp_random());
  lastInteraction = millis();
}

void loop() {
  M5.update();

  float ax, ay, az;
  if (M5.Imu.getAccel(&ax, &ay, &az)) {
    float mag = sqrtf(ax*ax + ay*ay + az*az);
    float jolt = fabsf(mag - 1.0);
    shakeEnergy = shakeEnergy * 0.85 + jolt;
  }

  if (shakeEnergy > SHAKE_THRESHOLD) {
    spawnConfetti(CONFETTI_COUNT);
    playPartySound();
    shakeEnergy = 0;
    lastInteraction = millis();
  }

  if (M5.BtnA.wasPressed()) {
    spawnHeartBurst();
    playMeow();
    lastInteraction = millis();
  }

  bool isSleeping = (millis() - lastInteraction > SLEEP_AFTER_MS);

  if (isSleeping && millis() - lastZSpawn > 1500) {
    spawnSleepZ();
    lastZSpawn = millis();
  }

  updateParticles();

  // Draw frame
  canvas.fillSprite(roomColors[0]);
  drawRoom();

  int bounce = isSleeping ? (millis() / 800) % 2 : (millis() / 250) % 2;
  int catX = (SCREEN_W - CAT_SIZE * CAT_SCALE) / 2;
  int catY = (SCREEN_H - CAT_SIZE * CAT_SCALE) / 2 + bounce + CAT_Y_OFFSET;
  drawCat(catX, catY, isSleeping);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      if (particles[i].kind == 0) {
        canvas.fillRect((int)particles[i].x, (int)particles[i].y,
                        CONFETTI_SIZE, CONFETTI_SIZE, particles[i].color);
      } else if (particles[i].kind == 1) {
        drawHeart((int)particles[i].x, (int)particles[i].y,
                  particles[i].color, HEART_SCALE);
      } else {
        drawZ((int)particles[i].x, (int)particles[i].y, particles[i].color);
      }
    }
  }

  canvas.pushSprite(0, 0);
  delay(16);
}

