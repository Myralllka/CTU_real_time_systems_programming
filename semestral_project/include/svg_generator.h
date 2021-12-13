#ifndef SVGGENERATOR
#define SVGGENERATOR

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PLOT_WIDTH 1000
#define PLOT_HEIGHT 300

#define MARKER_ARROW fprintf(f,"<marker id=\"markerArrow\" markerWidth=\"13\" markerHeight=\"13\" refX=\"7\" refY=\"6\" orient=\"auto\">\n<path d=\"M2,8 L11,6 L2,4 Z\" style=\"fill: #000000;stroke: black;\" />    </marker>")

#define cordx(var) (((var)-ctx->ofx)*(ctx->mx))
#define cordy(var) (((var)-ctx->ofy)*(ctx->my))

typedef struct svg_context {
    char stroke_color[20];
    char fill_color[20];
    char text_family[30];
    char dash_array[30];
    unsigned int text_size;
    unsigned int stroke_width;

    int stroke, fill;
    /*document*/
    int padding;
    int width, height;
    int flip;
    int decimals;
    float mx, my, ofx, ofy;
    FILE *f;

} svg_context;


void svg_draw_to_file_xy(FILE *f,
                         const char *color,
                         float *x, float *y,
                         size_t count,
                         const char *x_label, const char *y_label);

void generate_html_file(FILE *f);

#endif
