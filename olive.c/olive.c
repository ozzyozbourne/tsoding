#ifndef OLIVE_C
#define OLIVE_C

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void olivec_fill(uint32_t *const pixels, const size_t width, const size_t height, const uint32_t color)
{
    for (size_t i = 0; i < width*height; i++) { pixels[i] = color; }
}

typedef int Errno;

#define return_defer(value) do { result = (value); goto defer; } while(0)

Errno olivec_save_to_ppm_file(const uint32_t *const pixels, const size_t width, const size_t height, const char *const file_path)
{
    int result = 0;
    FILE *f = NULL;
    { 
        f = fopen(file_path, "wb");
        if (f == NULL) { return_defer(errno); }

        fprintf(f, "P6\n%zu %zu 255\n", width, height);
        if (ferror(f)){ return_defer(errno); }

        for (size_t i = 0; i < width*height; i++){
            const uint32_t pixel = pixels[i];
            const uint8_t bytes[3] = { //Little endian so laid in memory as BGRA
                (pixel>>(8*0))&0xFF, // Extract BLUE 
                (pixel>>(8*1))&0xFF, // Extract GREEN
                (pixel>>(8*2))&0xFF  // Extract RED 
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);
        }
    }

defer:
    if (f) { fclose(f); }
    return result;
}

void olivec_fill_rect(uint32_t *const pixels, const size_t pixel_width, const size_t pixel_height, 
                      int x0, int y0, const size_t w, const size_t h, const uint32_t color)
{
    const int p_ht_cast = (int)pixel_height;
    const int p_wd_cast = (int)pixel_width;
    const int h_cast = (int)h;
    const int w_cast = (int)w;

    for (int dy = 0; dy < h_cast; dy++){
        const int y = y0 + dy; // position to start 
        if (0 <= y && y < p_ht_cast){
            for (int dx = 0; dx < w_cast; dx++){
                const int x =  x0 + dx;
                if (0 <= x && x < p_wd_cast){ pixels[y*pixel_width + x] = color; }
            }
        }
    }       
}

void olivec_fill_circle(uint32_t *const pixel, const size_t pixel_width, const size_t pixel_height, 
        const int cx, const int cy, const size_t r, const uint32_t color)
{
    const int r_sqrt = (int)(r*r);
    const int p_ht_cast = (int)pixel_height;
    const int p_wd_cast = (int)pixel_width;
    // so here we are creating a square whose l and b = 2r
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

#endif /* ifndef OLIVE_C */
