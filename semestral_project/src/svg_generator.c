#include "../include/shared.h"
#include "../include/svg_generator.h"

// Based on https://github.com/memononen/nanosvg
//
// reduced number of functions + rewritten everything to avoid dynamic memory allocations
// Also documentation is written by us (Denys and Mykola)

/*!
 * \brief Write html + svg plots to the file
 * 
 * Function for processing data from motors and writing it as html file with svg plots
 * It will display 3 plots:
 * 		Actual motor position (absolute value)
 * 		Desire motor position (absolute value)
 * 		Pwm duty cycle (+- 100%)
 * 		
 * The graphs should show at least 2 seconds of history with time resolution ≤ 5 ms.
 *
 * @param desc : FILE* - file descriptor
 */
void generate_html_file(FILE *f) {
    float x_actual[HISTORY_SIZE];
    float y_actual[HISTORY_SIZE];
    float y_desired[HISTORY_SIZE];
    float y_pwm[HISTORY_SIZE];
    int i;
    uint32_t s = motor_history.array_start_index;
    int copy_array_idx = 0;
    for (i = s; i != (s + HISTORY_SIZE) % HISTORY_CYCLIC_ARRAY_SIZE; i = (i + 1) %
                                                                         HISTORY_CYCLIC_ARRAY_SIZE, copy_array_idx++) {
        y_desired[copy_array_idx] = (float) motor_history.desired_position[i];
        y_actual[copy_array_idx] = (float) motor_history.position[i];
        y_pwm[copy_array_idx] = (float) motor_history.pwm_duty[i];

        x_actual[copy_array_idx] = (float) motor_history.timestamp[i];
    }

    // creating svg part
    svg_draw_to_file_xy(f, "#ff0000", x_actual, y_actual, HISTORY_SIZE, "t", "Actual position (abs units)");
    svg_draw_to_file_xy(f, "#00ff00", x_actual, y_desired, HISTORY_SIZE, "t", "Desired position (abs units)");
    svg_draw_to_file_xy(f, "#0000ff", x_actual, y_pwm, HISTORY_SIZE, "t", "PWM duty cicle, +-100%");
}

/*!
 * open svg tag
 * @param ctx - pointer to main svg context data structure
 * @param name - opening tag's name
 * @param use_opt - 1 if there are some options in opening tag or not, 0 otherwise
 */
void svg_tag_start(svg_context *ctx, const char *name, int use_opt) {
    fprintf(ctx->f, "\n<%s %s", name, (use_opt ? " " : ">"));
}

/*!
 * add svg closing tag
 * @param ctx - pointer to main svg context data structure
 */
void svg_finish(svg_context *ctx) {
    fprintf(ctx->f, "</svg>");
}

/*!
 * add end tag symbol
 * @param ctx - pointer to main svg context data structure
 * @param selfclose - 1 if tag is self closing, 0 otherwise
 */
void svg_opt_end(svg_context *ctx, int selfclose) {
    fprintf(ctx->f, " %s>\n", (selfclose ? "/" : ""));
}

/*!
 * add float option to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param key - option name
 * @param v - option value
 */
void svg_optf(svg_context *ctx, const char *key, float v) {
    fprintf(ctx->f, "%s=\"%f\" ", key, v);
}

/*!
 * add int option to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param key - option name
 * @param v - option value
 */
void svg_opti(svg_context *ctx, const char *key, int v) {
    fprintf(ctx->f, "%s=\"%i\" ", key, v);
}

/*!
 * add string option to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param key - option name
 * @param v - option value
 */
void svg_opta(svg_context *ctx, const char *key, const char *v) {
    fprintf(ctx->f, "%s=\"%s\" ", key, v);
}

/*!
 * add fill option to svg tag (using fill_color option from ctx)
 * @param ctx - pointer to main svg context data structure
 */
void svg_opt_fill(svg_context *ctx) {
    fprintf(ctx->f, "fill=\"%s\" ", ctx->fill_color);
}

/*!
 * add fill=none option to svg tag
 * @param ctx - pointer to main svg context data structure
 */
void svg_opt_fill_none(svg_context *ctx) {
    fprintf(ctx->f, "fill=\"none\" ");
}

/*!
 * add svg 'stroke' tag of ctx->stroke_color with ctx->stroke_width and ctx->dash_array
 * @param ctx - pointer to main svg context data structure
 */
void svg_opt_stroke(svg_context *ctx) {
    fprintf(ctx->f, "stroke=\"%s\" stroke-width=\"%i\" stroke-dasharray=\"%s\" ",
            ctx->stroke_color,
            ctx->stroke_width,
            ctx->dash_array);
}

/*!
 * open a long option svg tag
 * @param ctx - pointer to main svg context data structure
 * @param key - option name
 */
void svg_opt_long_beg(svg_context *ctx, const char *key) {
    fprintf(ctx->f, "%s=\"", key);
}

/*!
 * close a long option svg tag
 * @param ctx - pointer to main svg context data structure
 */
void svg_opt_long_end(svg_context *ctx) {
    fprintf(ctx->f, "\" ");
}

/*!
 * Add x and y rotation to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param angle - rotation angle
 * @param cx - rotation in x coor, px
 * @param cy - rotation in y coor, px
 */
void svg_rotate(svg_context *ctx, int angle, int cx, int cy) {
    fprintf(ctx->f, "translate(%i,%i) rotate(%i) translate(%i,%i) ", cx, cy, angle, -cx, -cy);
}

/*!
 * Add x and y translations to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param dx - translation in x coor, px
 * @param dy - translation in y coor, px
 */
void svg_translate(svg_context *ctx, int dx, int dy) {
    fprintf(ctx->f, "translate(%i,%i) ", dx, dy);
}

/*!
 * Add x and y scaling to svg tag
 * @param ctx - pointer to main svg context data structure
 * @param sx - x scaling coefficient
 * @param sy - y scaling coefficient
 */
void svg_scale(svg_context *ctx, float sx, float sy) {
    fprintf(ctx->f, "scale(%f,%f) ", sx, sy);
}

/*!
 * Close the svg tag
 * @param ctx - pointer to main svg context data structure
 * @param name - pointer to the name of the tag to be closed
 */
void svg_tag_end(svg_context *ctx, const char *name) {
    fprintf(ctx->f, "\n</%s>", name);
}

/*!
 * Add a line to svg
 * @param ctx - pointer to main svg context data structure
 * @param x1 - x coor of position where to put object (beginning)
 * @param y1 - y coor of position where to put object (beginning)
 * @param x2 - x coor of position where to put object (end)
 * @param y2 - y coor of position where to put object (end)
 */
void svg_line(svg_context *ctx, float x1, float y1, float x2, float y2) {
    svg_tag_start(ctx, "line", 1);
    {
        svg_optf(ctx, "x1", cordx(x1));
        svg_optf(ctx, "y1", cordy(y1));
        svg_optf(ctx, "x2", cordx(x2));
        svg_optf(ctx, "y2", cordy(y2));
        svg_opt_stroke(ctx);
    }
    svg_opt_end(ctx, 1);
}

/*!
 * Add an arrow to svg
 * @param ctx - pointer to main svg context data structure
 * @param x1 - x coor of position where to put object (beginning)
 * @param y1 - y coor of position where to put object (beginning)
 * @param x2 - x coor of position where to put object (end)
 * @param y2 - y coor of position where to put object (end)
 */
void svg_arrow(svg_context *ctx, float x1, float y1, float x2, float y2) {
    svg_tag_start(ctx, "line", 1);
    {
        svg_optf(ctx, "x1", cordx(x1));
        svg_optf(ctx, "y1", cordy(y1));
        svg_optf(ctx, "x2", cordx(x2));
        svg_optf(ctx, "y2", cordy(y2));
        svg_opta(ctx, "marker-end", "url(#markerArrow)");
        svg_opt_stroke(ctx);
    }
    svg_opt_end(ctx, 1);
}

/*!
 *
 * @param ctx - pointer to main svg context data structure
 * @param x - x coor of position where to put object
 * @param y - y coor of position where to put object
 * @param count
 */
void svg_path_data(svg_context *ctx, const float *x, const float *y, size_t count) {
    size_t i;
    svg_tag_start(ctx, "path", 1);
    {
        fprintf(ctx->f, " d=\"");
        for (i = 0; i < count; ++i) {
            fprintf(ctx->f, "%s%f,%f\n", (i == 0 ? "M" : " L"), cordx(x[i]), cordy(y[i]));
        }
        fprintf(ctx->f, "\" ");
        svg_opt_fill_none(ctx);
        svg_opt_stroke(ctx);
    }
    svg_opt_end(ctx, 1);
}

/*!
 * Add rectangle to svg
 * @param ctx - pointer to main svg context data structure
 * @param x - x coor of position where to put object
 * @param y - y coor of position where to put object
 * @param w - width of the object, in px
 * @param h - height of the object, in px
 */
void svg_rect(svg_context *ctx, float x, float y, float w, float h) {
    svg_tag_start(ctx, "rect", 1);
    svg_optf(ctx, "x", cordx(x));
    svg_optf(ctx, "y", cordy(y));
    svg_optf(ctx, "width", w);
    svg_optf(ctx, "height", h);
    svg_opt_fill(ctx);
    svg_opt_stroke(ctx);
    svg_opt_end(ctx, 1);
}

/*!
 * Add text to svg
 * @param ctx - pointer to main svg context data structure
 * @param txt - pointer to text to put it on the svg
 * @param x - x coor of position where to put text
 * @param y - y coor of position where to put text
 */
void svg_text(svg_context *ctx, const char *txt, float x, float y) {
    svg_tag_start(ctx, "text", 1);
    svg_optf(ctx, "x", cordx(x));
    svg_optf(ctx, "y", cordy(y));
    svg_opti(ctx, "font-size", (int) ctx->text_size);
    svg_opta(ctx, "font-family", ctx->text_family);
    svg_opt_fill(ctx);
    svg_opt_stroke(ctx);
    svg_opt_end(ctx, 0);
    fprintf(ctx->f, "%s", txt);
    svg_tag_end(ctx, "text");
}

void svg_set_fill(svg_context *ctx, const char *color) {
    strcpy(ctx->fill_color, color);
}

void svg_set_dash(svg_context *ctx, const char *dash) {
    strcpy(ctx->dash_array, dash);
}

void svg_set_stroke(svg_context *ctx, const char *color) {
    strcpy(ctx->stroke_color, color);
}

/*!
 * find min and max of an array
 * @param data float array
 * @param min pointer where to put min
 * @param max pointer where to put max
 * @param count size of an array
 */
void max_min(const float *data, float *min, float *max, size_t count) {
    size_t i;
    for (i = 0; i < count; ++i)
        if (i == 0) {
            *min = data[i];
            *max = data[i];
        } else if (data[i] < *min)
            *min = data[i];
        else if (data[i] > *max)
            *max = data[i];
}

/**
 * Plot x-y data to SVG file
 * @param f opened file for writing
 * @param color line color
 * @param y data values
 * @param x ordered x values from min to max
 * @param count elements count
 * @param x_label label for Ax
 * @param y_label label for Ay
 */
void svg_draw_to_file_xy(FILE *f,
                         const char *color,
                         float *x, float *y,
                         size_t count,
                         const char *x_label, const char *y_label) {
    float min_y, min_x, max_y, max_x;
    float height, width, t;
    float mx, my;
    float tx, ty;
    char temp[30];
//    svg_context *ctx;
    if (count == 0)return;
    min_x = x[0];
    max_x = x[count - 1];
    /* Find minimum and maximium of Y axis. X mast be already ordered*/
    max_min(y, &min_y, &max_y, count);
    width = max_x - min_x;
    height = max_y - min_y;

    struct svg_context ctx_obj = {
            .text_size = 14,
            .stroke_width = 1,
            .stroke = 1,
            .fill = 0,
            .f = f,
            .width = PLOT_WIDTH,
            .height = PLOT_HEIGHT,
            .padding = 50,
            .flip = 1,
            .mx = 1,
            .my = 1,
            .ofx = 0,
            .ofy = 0,
    };
    svg_context *ctx = &ctx_obj;
    strcpy(ctx->fill_color, "#ffffff\0");
    strcpy(ctx->stroke_color, "#000000\0");
    strcpy(ctx->text_family, "monospace\0");
    strcpy(ctx->dash_array, "\0");

    /* Begin document */

    fprintf(ctx->f, "<svg version=\"1.2\" width=\"%i\" height=\"%i\" xmlns=\"http://www.w3.org/2000/svg\">",
            ctx->width, ctx->height);
    mx = (float) (ctx->width - 2 * ctx->padding) / (float) width;
    my = (float) (ctx->height - 2 * ctx->padding) / (float) height;
    fprintf(f, "<defs>\n");
    MARKER_ARROW;
    fprintf(f, "</defs>\n");
    svg_set_fill(ctx, "#ffffff");
    svg_rect(ctx, 0, 0, (float) ctx->width, (float) ctx->height);

    /*Vertical lines*/
    svg_set_stroke(ctx, "#aaaaaa");

    ctx->stroke_width = 1;
    for (t = min_x + width / 10; t < max_x; t = t + width / 10) {
        tx = (t - min_x) * mx + (float) ctx->padding;

        svg_set_dash(ctx, "5,5");
        svg_line(ctx, tx, (float) (ctx->height - ctx->padding), tx, (float) ctx->padding);
        svg_set_dash(ctx, "");
        svg_tag_start(ctx, "g", 1);
        {
            sprintf(temp, "%i", (int) t);
            svg_opt_long_beg(ctx, "transform");
            svg_rotate(ctx, -90, (int) tx - 3, ctx->height - ctx->padding - 10);
            svg_translate(ctx, (int) tx - 3, ctx->height - ctx->padding - 10);
            svg_opt_long_end(ctx);
            svg_opt_end(ctx, 0);

            svg_text(ctx, temp, 0, 0);
        }
        svg_tag_end(ctx, "g");
    }
    /*Horizontal lines*/
    svg_set_stroke(ctx, "#aaaaaa");

    ctx->stroke_width = 1;
    for (t = min_y + height / 10; t < max_y; t = t + height / 10.0) {
        ty = (float) ctx->height - (t - min_y) * my - (float) ctx->padding;
        svg_set_dash(ctx, "5,5");
        svg_line(ctx, (float) ctx->padding, ty, (float) (ctx->width - ctx->padding), ty);
        svg_set_dash(ctx, "");
        sprintf(temp, "%i", (int) t);
        svg_text(ctx, temp, (float) ctx->padding + 3, ty - 3);
    }

    svg_tag_start(ctx, "g", 1);
    {
        ctx->mx = mx;
        ctx->my = my;
        ctx->ofx = min_x;
        ctx->ofy = min_y;
        svg_opt_long_beg(ctx, "transform");
        svg_translate(ctx, ctx->padding, ctx->padding);
        svg_scale(ctx, 1, -1);
        svg_translate(ctx, 0, -ctx->height + 2 * ctx->padding);
        svg_opt_long_end(ctx);
        svg_opt_end(ctx, 0);


        /* Plot data */
        svg_set_stroke(ctx, color);
        svg_set_dash(ctx, "");
        svg_path_data(ctx, x, y, count);
        svg_set_stroke(ctx, "#000000");

    }
    svg_tag_end(ctx, "g");
    ctx->mx = 1;
    ctx->my = 1;
    ctx->ofx = 0;
    ctx->ofy = 0;
    sprintf(temp, "%i", (int) max_y);
    svg_text(ctx, temp, (float) ctx->padding + 3, (float) ctx->padding);
    sprintf(temp, "%i", (int) max_x);
    svg_tag_start(ctx, "g", 1);
    {
        svg_opt_long_beg(ctx, "transform");
        svg_rotate(ctx, -90,
                   (int) (ctx->width - ctx->padding - ctx->text_size / 2),
                   (int) (ctx->height - ctx->padding - ctx->text_size));
        svg_translate(ctx,
                      (int) (ctx->width - ctx->padding - ctx->text_size),
                      (int) (ctx->height - ctx->padding - ctx->text_size));
        svg_opt_long_end(ctx);
        svg_opt_end(ctx, 0);
        svg_text(ctx, temp, 0, 0);
    }
    svg_tag_end(ctx, "g");
    /*axis*/
    svg_set_fill(ctx, "#000000");
    svg_set_stroke(ctx, "#000000");
    svg_set_dash(ctx, "");
    ctx->stroke_width = 2;
    ctx->text_size = (ctx->padding) / 2;

    /* Y */
    svg_set_stroke(ctx, "#000000");
    svg_set_dash(ctx, "");

    svg_arrow(ctx,
              (float) (ctx->padding),
              (float) (ctx->height - ctx->padding / 2.0),
              (float) (ctx->padding),
              (float) (ctx->padding / 2.0));
    ctx->stroke_width = 1;
    svg_text(ctx, y_label,
             (float) (ctx->padding + ctx->text_size / 4.0),
             (float) (ctx->padding / 2.0 + ctx->text_size / 4.0));

    sprintf(temp, "%i", (int) x[0]);

    ctx->text_size = 14;
    svg_tag_start(ctx, "g", 1);
    {
        svg_opt_long_beg(ctx, "transform");
        svg_rotate(ctx, -90, (int) (ctx->padding - ctx->text_size / 2),
                   (int) (ctx->height - ctx->padding - ctx->text_size));
        svg_translate(ctx, (int) (ctx->padding - ctx->text_size),
                      (int) (ctx->height - ctx->padding - ctx->text_size));
        svg_opt_long_end(ctx);
        svg_opt_end(ctx, 0);
        svg_text(ctx, temp, 0, 0);
    }
    svg_tag_end(ctx, "g");
    ctx->text_size = ctx->padding / 2;

    ctx->stroke_width = 2;

    /* X */
    svg_arrow(ctx,
              (float) ctx->padding / 2,
              (float) (ctx->height - ctx->padding),
              (float) (ctx->width - ctx->padding / 2.0),
              (float) (ctx->height - ctx->padding));
    ctx->stroke_width = 1;
    ctx->text_size = ctx->padding / 2;

    svg_text(ctx, x_label,
             (float) (ctx->width - strlen(x_label) * ctx->text_size),
             (float) (ctx->height - ctx->padding - ctx->text_size / 2.0));
    sprintf(temp, "%i", (int) min_y);
    ctx->text_size = 14;
    svg_text(ctx, temp, (float) ctx->padding + 3, (float) (ctx->height - ctx->padding + ctx->text_size));

    svg_finish(ctx);
}
