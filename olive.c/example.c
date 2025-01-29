#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

static uint32_t pixels[WIDTH * HEIGHT];

int main(void)
{
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF00FF00);
    const char *file_path = "output.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err){
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(err));
        return 1;
    }
    return 0;
}
