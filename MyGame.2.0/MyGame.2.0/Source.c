//Доделать передвижение

#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <rlgl.h>
#include <stdint.h>
#include <stdio.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 136

#define BODY_WIDTH 10 
#define BODY_HEIGHT 10

const int EAT_WIDTH = 8;
const int EAT_HEIGHT = 8;
const int FIELD_WIDTH = SCREEN_WIDTH / BODY_WIDTH;
const int FIELD_HEIGHT = SCREEN_HEIGHT / BODY_HEIGHT;

const Vector2 ZERO_VEC = { 0, 0 };

typedef struct SnakeNode_ {
    int32_t lifetime;
    bool eat_inside;
} SnakeNode;

typedef struct Snake_ {
    int length;
    int pos_x;
    int pos_y;
    int dir_x;
    int dir_y;
    float speed;
    float last_step_update;
    bool hunger;
}Snake;

typedef struct Eat_ {
    int x;
    int y;
    bool mega;
}Eat;

Eat eat = { -1, -1 };
Eat eat_mega = { -1, -1 };

SnakeNode snake_body[24][13];

bool is_game_over = false;

Snake snake = {
    .length = 2,
    .pos_x = 12,
    .pos_y = 6,
    .dir_x = 1,
    .dir_y = 0,
    .speed = 0.15f,
    .last_step_update = 0,
    .hunger = false,
    }; 

void InitSnake() 
{
    for (int i = 0; i < snake.length; i++) 
    {
        int x = snake.pos_x - snake.dir_x * i;
        int y = snake.pos_y - snake.dir_y * i;
        snake_body[x][y].lifetime = snake.length - i;
    }
}

void DropEat() {
    int x;
    int y;
    do {
       x = GetRandomValue(0, FIELD_WIDTH - 1);
       y = GetRandomValue(0, FIELD_HEIGHT - 1);
    } while (snake_body[x][y].lifetime > 0);
    eat.x = x;
    eat.y = y;
}

void Setup() {
    for (int i = 0; i < FIELD_WIDTH; i++) 
    {
        for (int j = 0; j < FIELD_HEIGHT; j++) 
        {
            snake_body[i][j].lifetime = 0;
            snake_body[i][j].eat_inside = false;
        }
    }
    InitSnake();
    DropEat();
}


void DrawSnake(){
    for (int i = 0; i < FIELD_WIDTH; i++) 
    {
        for (int j = 0; j < FIELD_HEIGHT; j++) 
        {
            if (snake_body[i][j].lifetime > 0) 
            {
                DrawRectangle(BODY_WIDTH * i, BODY_HEIGHT * j, BODY_WIDTH, BODY_HEIGHT, GREEN);
           }
        }
    }
    DrawRectangle(snake.pos_x * BODY_WIDTH, snake.pos_y * BODY_HEIGHT, BODY_WIDTH, BODY_HEIGHT, RED);
}

void Control() {
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) 
    {
        snake.dir_y = 1;
        snake.dir_x = 0;
    }
    if ((snake.dir_y == 0)&&(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) 
    {
        snake.dir_y = -1;
        snake.dir_x = 0;
    }
    if ((snake.dir_x == 0)&&(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))) 
    {
        snake.dir_y = 0;
        snake.dir_x = -1;
    }
    if ((snake.dir_x == 0)&&(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) 
    {
        snake.dir_y = 0;
        snake.dir_x = 1;
    }
}

//void Bite_Chech() {
//    if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0) {
//        is_game_over = true;
//    }
//}

void CheckEat() {
    if(snake.pos_x == eat.x && snake.pos_y == eat.y){
        snake.length++;
        snake.hunger = true;
        DropEat();
    }
}

void MoveSnake() {
    snake.last_step_update += GetFrameTime(); //В секундах
    if (snake.last_step_update >= snake.speed) 
    {
        snake.last_step_update = 0;
    }
    else 
    {
        return;
    }

    
    if (snake.hunger) {
        snake.hunger = false;   
    }
    else{
        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            for (int j = 0; j < FIELD_HEIGHT; j++)
            {
                if (snake_body[i][j].lifetime > 0)
                {
                    snake_body[i][j].lifetime--;
                }
            }
        }
    }

    snake.pos_x += snake.dir_x;
    snake.pos_y += snake.dir_y;

    if (snake.pos_x >= FIELD_WIDTH)
    {
        snake.pos_x = 0;
    }
    if (snake.pos_x < 0)
    {
        snake.pos_x = FIELD_WIDTH - 1;
    }
    if (snake.pos_y >= FIELD_HEIGHT)
    {
        snake.pos_y = 0;
    }
    if (snake.pos_y < 0)
    {
        snake.pos_y = FIELD_HEIGHT - 1;
    }

    snake_body[snake.pos_x][snake.pos_y].lifetime = snake.length;
}

void DrawEat() {
    int tmpW = (BODY_WIDTH - EAT_WIDTH) / 2;
    int tmpH = (BODY_HEIGHT - EAT_HEIGHT) / 2;
    DrawRectangle(eat.x * BODY_WIDTH + tmpW, eat.y * BODY_HEIGHT + tmpH, EAT_HEIGHT, EAT_WIDTH, RED);
}

void Movement(){
    CheckEat();
    MoveSnake();
    Control();
    /*Bite_Chech();*/
}

void Eat_Draw() {
    DrawEat();
    DrawSnake();
}

Rectangle GetCanvasTarget() {
    float sh = (float)GetScreenHeight();
    float sw = (float)GetScreenWidth();
    float scale = fminf(sh / SCREEN_HEIGHT, sw / SCREEN_WIDTH);
    Rectangle rec = { 0, 0, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale };
    return rec;
}

int main(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);   
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game"); 
    SetTargetFPS(60); 

   RenderTexture2D canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
   Rectangle canvas_field = {0, 0, (float)canvas.texture.width, (float)canvas.texture.height};
   SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
   Setup();
   
    while (!WindowShouldClose()) 
    {
        BeginDrawing(); 
        ClearBackground(RED);

        BeginTextureMode(canvas);
        ClearBackground(BLACK);
        Eat_Draw();

        EndTextureMode(canvas);

        DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget(), ZERO_VEC, 0.0f, WHITE);

        EndDrawing();
        Movement();
    }

    CloseWindow(); 
    return 0;
}
