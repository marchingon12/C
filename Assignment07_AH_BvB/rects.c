#include "base.h"
/*
    make rects
    ./rects
    make rects && ./rects
*/

enum FillProperty{
    RANGE,
    SIMPLE,
    PATTERN
} typedef TFillProperty;

struct RangeFill{
    char start;
    char end;
} typedef RangeFill;

struct SimpleFill{
    char c;
} typedef SimpleFill;

struct PatternFill{
    String pattern;
} typedef PatternFill;

struct Fill{
    TFillProperty tag;
    union{
        PatternFill pf;
        SimpleFill sf;
        RangeFill rf;  
    };
}typedef Fill;

struct Rect{
    int x, y;
    int width, height;
    Fill fill;    
} typedef Rect;

Fill make_range_fill(char lower, char upper){
    //todo:
    Fill fill;

    return fill;
}

Fill make_pattern_fill(String s){
    require("valid input", s_length(s) > 0);
    Fill fill;
    fill.tag = PATTERN;
    fill.pf.pattern = s;
    return fill;
}

Fill make_simple_fill(char c){
    //todo:
    Fill fill;

    return fill;
    
}

Rect make_rect(int x, int y, int width, int height, Fill fill){
    //todo:
    Rect rect;

    return rect;
}    

void draw_rect(Rect rect){
    //todo:
    
}
/*
width = 1, height = 1
+

width = 1, height = 2
+
+

width = 2, height = 1
++

width = 2, height = 2
++
++

width = 3, height = 2
+-+
+-+

width = 3, height = 3, x = 1, y = 0, fill = simple with 'o'

 +-+
 |o|
 +-+
 
width = 15, height = 10, x = 15, y = 0, fill = pattern with ".o"
               +-------------+
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               +-------------+
*/
int main(void){
    // Mindestens 6 verschiedene Rechtecke mit unterschiedlichen Position, Fuellungen und Groeßen.
    //draw_rect(make_rect(1, 1, 1, 1, make_simple_fill('o')));
    
    return 0;
}