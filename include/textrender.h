#include <harfbuzz/hb-ft.h>
#include <string>

const int FONTSIZE_SMALL = 24;
const int FONTSIZE_MEDIUM = 48;
const int FONTSIZE_LARGE = 72;
const int FONTSIZE_DEFAULT = FONTSIZE_MEDIUM;

class TextRender {
    public:
        TextRender();
        ~TextRender();
        TextRender(const std::string, const double);
        void ChangeFont(const std::string, const double);
        void WriteText(const char *);
    private:
        int font_size;
        std::string font_name;
        hb_font_t * curr_font;
        FT_Face ft_face;
        FT_Library ft_library;
};