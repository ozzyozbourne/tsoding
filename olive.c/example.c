#include "olive.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFF2020FF

static uint32_t pixels[WIDTH * HEIGHT];

void olivec_fill_circle(uint32_t *const pixel, const size_t pixel_width, const size_t pixel_height, 
        const int cx, const int cy, const size_t r, const uint32_t color)
{
    const int r_sqrt = (int)(r*r);
    const int p_ht_cast = (int)pixel_height;
    const int p_wd_cast = (int)pixel_width;

    const int x1 = cx - (int)r;
    const int y1 = cy - (int)r;
    const int x2 = cx + (int)r;
    const int y2 = cy + (int)r;
    
    for (int y = y1; y <= y2; y++){
        if (0 <= y && y < p_ht_cast){
            for (int x = x1; x <= x2; x++){
                if (0 <= x && x < p_wd_cast){
                   const int dx = x - cx; 
                   const int dy = y - cy;
                   if (dx*dx + dy*dy <= r_sqrt) { pixel[y*pixel_width + x] = color; }
                }
            }
        } 
    }
}


bool checkers_example(void)
{
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            uint32_t color = BACKGROUND_COLOR; 
            if ((x + y)%2 == 0){ color = 0xFF0000FF; }
            olivec_fill_rect(pixels, WIDTH, HEIGHT, x*CELL_WIDTH, y*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }

    const char *file_path = "checker.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err){
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(err));
        return false;
    }
    return true;

}

bool circle_example(void)
{
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            size_t radius = CELL_WIDTH;
            if (CELL_HEIGHT < radius) { radius = CELL_HEIGHT; }
            olivec_fill_circle(pixels, WIDTH, HEIGHT, x*CELL_WIDTH + CELL_WIDTH/2, y*CELL_HEIGHT + CELL_HEIGHT/2, radius/2, 
                    FOREGROUND_COLOR);
        }
    }

    const char *const file_path = "circle.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err){
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(err));
        return false;
    }
    return true;
}

int main(void)
{
    if (!checkers_example()){ return -1; }
    if (!circle_example()){ return -1; }
    return 0;
}
