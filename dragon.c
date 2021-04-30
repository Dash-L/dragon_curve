#include <string.h>
#include <math.h>
#include <stdio.h>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 640
#define MAX_ITERS 17
#define WAIT_FRAMES 60

/*****************
 * Dynamic Array *
 *****************/
typedef struct Array {
  Vector2* data;
  int len;
  int cap;
} array;

array array_with_cap(int cap) {
  return (array){(Vector2 *)MemAlloc(cap * sizeof(Vector2)), 0, cap};
}

void insert(array *arr, Vector2 elem, int index) {
  arr->len++;
  if (arr->len > arr->cap) {
    arr->cap *= 2;
    arr->data = (Vector2 *)MemRealloc(arr->data, arr->cap * sizeof(Vector2));
  }
  memmove(arr->data+index+1, arr->data+index, (arr->len-index-1) * sizeof(Vector2));
  arr->data[index] = elem;
}

void push(array *arr, Vector2 elem) {
  insert(arr, elem, arr->len);
}

/**************
 * Math Utils *
 **************/
float min(float x, float y) {
  return x < y ? x : y;
}

Vector2 midpoint(Vector2 p1, Vector2 p2) {
  return (Vector2){
    min(p1.x, p2.x) + fabsf(p1.x - p2.x) / 2.f,
    min(p1.y, p2.y) + fabsf(p1.y - p2.y) / 2.f,
  };
}

/****************
 * Main Program *
 ****************/
int main(void) {
  InitWindow(WIDTH, HEIGHT, "Dragon Fractal");
  SetTargetFPS(60);

  Texture nums[MAX_ITERS+1];
  for (int i = 0; i <= MAX_ITERS; ++i) {
    char buf[3];
    sprintf(buf, "%d", i);
    nums[i] = LoadTextureFromImage(ImageText(buf, 20, BLACK));
  }

  int i = 0;
  int nframes = 0;

  array points = array_with_cap(1024);
  push(&points, (Vector2){200.f, 200.f});
  push(&points, (Vector2){WIDTH - 150.f, 200.f});

  while (!WindowShouldClose()) {
    if (nframes >= WAIT_FRAMES) {
      if (i < MAX_ITERS) {
        for (int j = 0, o = 1, sign = 1; j < powf(2, i); ++j, o += 2, sign *= -1) {
          Vector2 p1 = points.data[o - 1];
          Vector2 p2 = points.data[o];
          Vector2 mp = midpoint(p1, p2);
          Vector2 point = (Vector2){
              mp.x + ((p1.y - p2.y) / 2.f) * sign,
              mp.y - ((p1.x - p2.x) / 2.f) * sign,
          };
          insert(&points, point, o);
        }
        i++;
      }
      nframes = 0;
    } else {
      nframes++;
    }
    /***********
     * Drawing *
     ***********/
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(nums[i], 10, 10, BLACK);
    for (int i = 0; i < points.len-1; ++i) {
      DrawLineEx(points.data[i], points.data[i+1], 2.f, BLACK);
    }
    EndDrawing();
  }

  CloseWindow();

  MemFree(points.data);

  return 0;
}
