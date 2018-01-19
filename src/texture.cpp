#include "texture.h"

using namespace std;

TextureLoader::TextureLoader() {
    t_err = ERR_SUCCESS;
    fp = nullptr;
}

TextureLoader::TextureLoader(const char *str) {
    if (str) {
        t_err = ERR_SUCCESS;
        setFile(str);
    } else
        t_err = ERR_BAD_INPUT;
}

// set t_err if fails
void TextureLoader::setFile(const char *str) {
    if (!str)
        t_err = ERR_BAD_INPUT;
    else if (!(fp = fopen(str, "rb")))
        t_err = ERR_FAILED_OPENING_FILE;
    else
        t_err = ERR_SUCCESS;
}

// returns ERR_SUCCESS on success
int TextureLoader::readFile() {
    //unsigned char buf[8] = {0};
    //if (!fread(buf, sizeof(char), 8, fp)) return (t_err = ERR_FAILED_READING_FILE);
    //if (png_sig_cmp(buf, 0, 8)) return (t_err = ERR_BAD_INPUT);
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return (t_err = ERR_BAD_FILE_FORMAT);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        return (t_err = ERR_BAD_FILE_FORMAT);
    }
    if(setjmp(png_jmpbuf(png_ptr))) return (t_err = ERR_BAD_FILE_FORMAT);
    png_init_io(png_ptr, fp);
    //png_read_info(png_ptr, info_ptr);
	//int width           = png_get_image_width(png_ptr, info_ptr);
	int height          = png_get_image_height(png_ptr, info_ptr);
	//png_byte color_type = png_get_color_type(png, info);
	//png_byte bit_depth  = png_get_bit_depth(png, info);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_BGR, NULL);
    png_read_update_info(png_ptr, info_ptr);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++)
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_image(png_ptr, row_pointers);
    fclose(fp); fp = nullptr;
    return (t_err = ERR_SUCCESS);
}

unsigned char **TextureLoader::getBuffer() {
    return row_pointers;
}
