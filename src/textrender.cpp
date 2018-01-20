#include "textrender.h"
#include <string>
#include <string.h>
#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>

using namespace std;

TextRender::TextRender() {
    TextRender("", FONTSIZE_DEFAULT);
}

TextRender::~TextRender() {
}

TextRender::TextRender(const string font_name, const double font_size) {
    this->ChangeFont(font_name, font_size);
}

void TextRender::ChangeFont(const string font_name, const double font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

int TextRender::WriteText(const char * text) {
    this->font_name = "";
    this->font_size = FONTSIZE_DEFAULT;
    int width = this->font_size;
    int height = this->font_size;
    if (FT_Init_FreeType(&ft_library)) {
        abort();
    }
    if (FT_New_Face(this->ft_library, "resources/LiberationSerif-Regular.ttf", 0, &this->ft_face)) {
        abort();
    }
    if (FT_Set_Char_Size(this->ft_face, font_size*64, font_size*64, 0, 0)) {
        abort();
    }
    this->curr_font = hb_ft_font_create(this->ft_face, NULL);
    hb_font_t * hb_font = this->curr_font;
    hb_buffer_t * hb_buffer;
    hb_buffer = hb_buffer_create();
    hb_buffer_add_utf8(hb_buffer, text, -1, 0, -1);
    hb_buffer_guess_segment_properties(hb_buffer);
    hb_shape(hb_font, hb_buffer, NULL, 0);

    uint glyph_count = hb_buffer_get_length(hb_buffer);
    hb_glyph_info_t * glyph_info = hb_buffer_get_glyph_infos(hb_buffer, NULL);
    hb_glyph_position_t * glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, NULL);

    for (uint i = 0; i < glyph_count; i++) {
        width += glyph_pos[i].x_advance / 64.;
        height -= glyph_pos[i].y_advance / 64.;
    }
    cairo_surface_t * cairo_surface;
    cairo_t * cr;
    cairo_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(cairo_surface);
    cairo_set_source_rgba(cr, 1., 1., 1., 1.);
    cairo_paint(cr);
    cairo_set_source_rgba(cr, 0., 0., 0., 1.);

    cairo_font_face_t * c_ft_face = cairo_ft_font_face_create_for_ft_face(this->ft_face, 0);
    cairo_set_font_face(cr, c_ft_face);
    cairo_set_font_size(cr, this->font_size);

    /* Set up baseline. */
    if (HB_DIRECTION_IS_HORIZONTAL (hb_buffer_get_direction(hb_buffer))) {
        cairo_font_extents_t font_extents;
        cairo_font_extents(cr, &font_extents);
        double baseline = (this->font_size - font_extents.height) + font_extents.ascent;
        cairo_translate(cr, 0, baseline);
    } else {
        cairo_translate(cr, this->font_size, 0);
    }

    cairo_glyph_t * cairo_glyphs = cairo_glyph_allocate(glyph_count);
    double current_x = 0;
    double current_y = 0;
    for (int i = 0; i < glyph_count; i++) {
        cairo_glyphs[i].index = glyph_info[i].codepoint;
        cairo_glyphs[i].x = current_x + glyph_pos[i].x_offset / 64.;
        cairo_glyphs[i].y = -(current_y + glyph_pos[i].y_offset / 64.);
        current_x += glyph_pos[i].x_advance / 64.;
        current_y += glyph_pos[i].y_advance / 64.;
    }
    cairo_show_glyphs(cr, cairo_glyphs, glyph_count);
    cairo_surface_write_to_png(cairo_surface, "out.png");
    cairo_glyph_free(cairo_glyphs);
    cairo_destroy(cr);
    cairo_surface_destroy(cairo_surface);
    hb_buffer_destroy(hb_buffer);
}
