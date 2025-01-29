#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#define return_defer(value) do { result = (value); goto defer; } while(0)
typedef int Errno;

Errno olivec_save_to_ppm_file(const uint32_t*, const size_t, const size_t, const char*);

int main(void) {
    const int number = 12345;
    const void *ptr = &number;
    const unsigned char *byte_ptr = (const unsigned char *)ptr;
    
    printf("Original ptr address: %p\n", (void*)ptr);
    printf("Byte ptr address:     %p\n", (void*)byte_ptr);
    
    // They point to the same location!
    printf("First byte of data: %02X\n", *byte_ptr);
    return 0;
}


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
            uint8_t bytes[3] = { 
                (pixel>>(8*0))&0xFF, 
                (pixel>>(8*1))&0xFF,
                (pixel>>(8*2))&0xFF
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);
        }
    }

defer:
    if (f) { fclose(f); }
    return 0;
}

