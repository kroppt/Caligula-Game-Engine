#include <harfbuzz/hb-ft.h>
#include <string>
#include <texture.hpp>

const int FONTSIZE_SMALL = 24;
const int FONTSIZE_MEDIUM = 48;
const int FONTSIZE_LARGE = 72;
const int FONTSIZE_DEFAULT = FONTSIZE_MEDIUM;

typedef struct {
    double r, g, b, a;
} RGBA;

class TextRender {
    public:
        TextRender();
        ~TextRender();
        void ChangeFontName(const std::string);
        void ChangeFontSize(const double);
        void ChangeFontRGBA(const double, const double, const double, const double);
        void ChangeFontBackgroundRGBA(const double, const double, const double, const double);
        Texture *WriteText(const char *);
    private:
        std::string font_name;
        int font_size;
        RGBA font_rgba;
        RGBA font_bg_rgba;
        hb_font_t *curr_font;
        FT_Face ft_face;
        FT_Library ft_library;
};
