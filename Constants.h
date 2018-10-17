#pragma once

//inits
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;
static const int SCREEN_HALF_HEIGHT = SCREEN_HEIGHT / 2;

static const int FRAMES = 60;
static const int FRAME_DELAY = 1000 / FRAMES;

static const int ROTATION = 90;

static const int BACKGROUND_WIDTH = 800;
static const int BACKGROUND_HEIGHT = 640;
static const int BACKGROUND_Y_OFFSET = SCREEN_HEIGHT - BACKGROUND_HEIGHT;
static const int BACKGROUND_X_OFFSET = -BACKGROUND_WIDTH / 2 + SCREEN_HALF_WIDTH;

static const int CURSOR_WIDTH = 32;
static const int CURSOR_HEIGHT = 32;

static const int MAX_ARRAY_SIZE = 16;

static const int BOX_SIZE = 10;


//Runtime consts
static const float BACKGROUND_SCALING_TARGET = 1.0;
static const float BACKGROUND_SCALING = 3.0;
static const float SPRITE_SCALING = 3.0;
static const float SPRITE_SCALING_TARGET = 1.0;

static const float PLAYER_PRIORITY_INCREMENT = -0.2;
static const int PLAYER_SPEED = 3;

static const int SPRITE_LENGTH = 128;
static const int SPRITE_SCALED = SPRITE_LENGTH * SPRITE_SCALING;
static const int SPRITE_RIGHT_EDGE_OF_SCREEN = SCREEN_WIDTH - SPRITE_SCALED;
static const int SPRITE_BOTTOM_OF_SCREEN = SCREEN_HEIGHT - SPRITE_SCALED;
static const int SPRITE_LEFT_EDGE_OF_SCREEN = 0;


//Attack consts
static const float WHIP_RANGE = 1.5f;
static const float WHIP_WHIFF = 0;

static const float JUMP_KICK_RANGE = 3.0f;
static const float JUMP_KICK_WHIFF = 3.0f;

static const float GRAB_RANGE = 0.5f;
static const float GRAB_WHIFF = 0.5f;

static const int ROUNDWIN = 3;
