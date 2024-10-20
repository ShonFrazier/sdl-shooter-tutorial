#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define PLAYER_SPEED        10
#define PLAYER_BULLET_SPEED 25

#define MAX_KEYBOARD_KEYS 350

typedef enum {
  TeamPlayer,
  TeamPig
} TeamSide;
