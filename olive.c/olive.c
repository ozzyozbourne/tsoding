#ifndef OLIVE_C
#define OLIVE_C
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for(size_t i = 0; i < width*height; i++) { pixels[i] = color; }
}

typedef int Errno;

#define return_defer(value) do { result = (value); goto defer; } while(0)

Errno olivec_save_to_ppm_file(const uint32_t *pixels, const size_t width, const size_t height, const char *file_path)
{
    int result = 0;
    FILE *f = NULL;
    { 
        f = fopen(file_path, "wb");
        if (f == NULL) { return_defer(errno); }

        fprintf(f, "P6\n%zu %zu 255\n", width, height);
        if (ferror(f)){ return_defer(errno); }

        for(size_t i = 0; i < width*height; i++){
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = { //Little endian so laid in memory as BGRA
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

#endif /* ifndef OLIVE_C */
