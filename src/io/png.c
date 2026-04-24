#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stego.h"

unsigned char* read_png(const char *filename,int *w,int *h){
    FILE *fp=fopen(filename,"rb");
    if(!fp) return NULL;

    png_structp png=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
    png_infop info=png_create_info_struct(png);

    png_init_io(png,fp);
    png_read_info(png,info);

    *w=png_get_image_width(png,info);
    *h=png_get_image_height(png,info);

    png_set_expand(png);
    png_set_add_alpha(png,0xFF,PNG_FILLER_AFTER);

    png_read_update_info(png,info);

    png_bytep *rows=malloc(sizeof(png_bytep)*(*h));
    for(int y=0;y<*h;y++)
        rows[y]=malloc(png_get_rowbytes(png,info));

    png_read_image(png,rows);

    unsigned char *data=malloc((*w)*(*h)*4);

    for(int y=0;y<*h;y++){
        memcpy(data+y*(*w)*4,rows[y],(*w)*4);
        free(rows[y]);
    }
    free(rows);
    fclose(fp);
    return data;
}

void write_png(const char *filename,unsigned char *data,int w,int h){
    FILE *fp=fopen(filename,"wb");

    png_structp png=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
    png_infop info=png_create_info_struct(png);

    png_init_io(png,fp);

    png_set_IHDR(png,info,w,h,8,PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png,info);

    png_bytep *rows=malloc(sizeof(png_bytep)*h);
    for(int y=0;y<h;y++) rows[y]=data+y*w*4;

    png_write_image(png,rows);
    png_write_end(png,NULL);

    free(rows);
    fclose(fp);
}
