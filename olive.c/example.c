#include "olive.c"
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACK_GROUND_COLOR 0xFF202020

static uint32_t pixels[WIDTH * HEIGHT];

bool checkers_example(void){
    olivec_fill(pixels, WIDTH, HEIGHT, BACK_GROUND_COLOR);

    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            uint32_t color = BACK_GROUND_COLOR; 
            if ((x + y)%2 == 0){ color = 0xFF0000FF; }
            olivec_fill_rect(pixels, WIDTH, HEIGHT, x*CELL_WIDTH, y*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }

    const char *file_path = "output.ppm";
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
    return 0;
}
