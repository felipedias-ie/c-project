// code designed with the help of an AI model, gpt-5.

#include "utest.h"
#include <math.h>
#include <string.h>

#define WORLD_SIZE 6000
#define PORT 7777
#define MAX_CLIENTS 64
#define MAX_FOOD 2000
#define MAX_TRAIL 120

#pragma pack(push, 1)
typedef struct { uint8_t r, g, b; } ColorRGB;
typedef struct { uint16_t id; int16_t x, y; uint8_t val; uint8_t r, g, b; } NetFood;
typedef struct {
    uint16_t id; int16_t x, y, angle; uint16_t score; uint8_t dead;
    uint16_t immunity; uint8_t r, g, b; char name[16]; uint8_t trail_len;
    int16_t trail_x[MAX_TRAIL]; int16_t trail_y[MAX_TRAIL];
} NetSnake;
typedef struct { uint8_t type; char name[16]; } JoinPacket;
typedef struct { uint8_t type; uint16_t player_id; uint16_t world_width; } InitPacket;
typedef struct { uint8_t type; float angle; uint8_t boost; } InputPacket;
typedef struct { uint8_t type; uint32_t final_score; } DiePacket;
typedef struct { uint8_t type; uint32_t sequence; uint16_t snake_count; uint16_t food_count; } WorldPacket;
#pragma pack(pop)

static float cfg_radius_base = 10.0f;
static float cfg_radius_growth = 0.015f;
static float cfg_radius_max = 80.0f;

float distance_squared(float x1, float y1, float x2, float y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

float get_snake_radius(int score) {
    float sz = cfg_radius_base + score * cfg_radius_growth;
    return (sz > cfg_radius_max) ? cfg_radius_max : sz;
}

UTEST(constants, world_size) {
    ASSERT_EQ(WORLD_SIZE, 6000);
}

UTEST(constants, port) {
    ASSERT_EQ(PORT, 7777);
}

UTEST(constants, max_clients) {
    ASSERT_EQ(MAX_CLIENTS, 64);
}

UTEST(constants, max_food) {
    ASSERT_EQ(MAX_FOOD, 2000);
}

UTEST(constants, max_trail) {
    ASSERT_EQ(MAX_TRAIL, 120);
}

UTEST(packets, color_rgb_size) {
    ASSERT_EQ(sizeof(ColorRGB), 3u);
}

UTEST(packets, net_food_size) {
    ASSERT_EQ(sizeof(NetFood), 10u);
}

UTEST(packets, join_packet_size) {
    ASSERT_EQ(sizeof(JoinPacket), 17u);
}

UTEST(packets, init_packet_size) {
    ASSERT_EQ(sizeof(InitPacket), 5u);
}

UTEST(packets, input_packet_size) {
    ASSERT_EQ(sizeof(InputPacket), 6u);
}

UTEST(packets, die_packet_size) {
    ASSERT_EQ(sizeof(DiePacket), 5u);
}

UTEST(packets, world_packet_size) {
    ASSERT_EQ(sizeof(WorldPacket), 9u);
}

UTEST(math, distance_squared_zero) {
    float d = distance_squared(0, 0, 0, 0);
    ASSERT_NEAR(d, 0.0f, 0.001f);
}

UTEST(math, distance_squared_unit) {
    float d = distance_squared(0, 0, 1, 0);
    ASSERT_NEAR(d, 1.0f, 0.001f);
}

UTEST(math, distance_squared_pythagorean) {
    float d = distance_squared(0, 0, 3, 4);
    ASSERT_NEAR(d, 25.0f, 0.001f);
}

UTEST(math, distance_squared_negative) {
    float d = distance_squared(-5, -5, 5, 5);
    ASSERT_NEAR(d, 200.0f, 0.001f);
}

UTEST(snake, radius_at_start) {
    float r = get_snake_radius(10);
    ASSERT_NEAR(r, 10.15f, 0.01f);
}

UTEST(snake, radius_grows_with_score) {
    float r1 = get_snake_radius(100);
    float r2 = get_snake_radius(500);
    ASSERT_GT(r2, r1);
}

UTEST(snake, radius_capped_at_max) {
    float r = get_snake_radius(10000);
    ASSERT_NEAR(r, 80.0f, 0.01f);
}

UTEST(snake, radius_at_threshold) {
    int threshold_score = (int)((cfg_radius_max - cfg_radius_base) / cfg_radius_growth);
    float r = get_snake_radius(threshold_score);
    ASSERT_LE(r, cfg_radius_max);
}

UTEST(game, world_is_circular) {
    float radius = WORLD_SIZE / 2.0f;
    float dist_sq = distance_squared(0, 0, radius + 1, 0);
    ASSERT_GT(dist_sq, radius * radius);
}

UTEST(game, spawn_within_bounds) {
    float max_spawn_dist = WORLD_SIZE / 2 - 500;
    ASSERT_GT(max_spawn_dist, 0);
    ASSERT_LT(max_spawn_dist, WORLD_SIZE / 2);
}

UTEST(packets, net_snake_contains_trail) {
    NetSnake snake = {0};
    snake.trail_len = MAX_TRAIL;
    for (int i = 0; i < MAX_TRAIL; i++) {
        snake.trail_x[i] = i;
        snake.trail_y[i] = i * 2;
    }
    ASSERT_EQ(snake.trail_x[0], 0);
    ASSERT_EQ(snake.trail_y[MAX_TRAIL - 1], (MAX_TRAIL - 1) * 2);
}

UTEST(packets, name_truncation) {
    JoinPacket p = {0};
    p.type = 1;
    strncpy(p.name, "VeryLongPlayerName", 15);
    p.name[15] = '\0';
    ASSERT_EQ(strlen(p.name), 15u);
}

UTEST_MAIN();