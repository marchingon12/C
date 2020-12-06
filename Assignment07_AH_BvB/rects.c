/*
August Ho und Benjamin von Behren
Assignment 07
Aufgabe 1: Rechtecke
*/


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


// b)
// Erstellt eine RangeFill.
Fill make_range_fill(char lower, char upper) {
    require("valid lower and upper char", lower > 0 && lower <= upper && upper <= 127);
    Fill fill;
    fill.tag = RANGE;
    fill.rf.start = lower;
    fill.rf.end = upper;
    return fill;
}

// Erstellt eine PatternFill.
Fill make_pattern_fill(String s) {
    require("valid input", s_length(s) > 0);
    Fill fill;
    fill.tag = PATTERN;
    fill.pf.pattern = s;
    return fill;
}


// c)
// Erstellt eine SimpleFill.
Fill make_simple_fill(char c) {
    require("valid in range ", c > 0 && c <= 127);
    require("printable char", isprint(c));
    Fill fill;
    fill.tag = SIMPLE;
    fill.sf.c = c;
    return fill;

}


// d)
// Initialisiert ein Rechteck mit den entsprechenden Parametern.
Rect make_rect(int x, int y, int width, int height, Fill fill) {
    require("non-negative x", x >= 0);
    require("non-negative y", y >= 0);
    require("non-negative width", width >= 0);
    require("non-negative height", height >= 0);
    require("valid fill.tag", fill.tag == RANGE || fill.tag == SIMPLE || fill.tag == PATTERN);
    Rect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    rect.fill = fill;
    return rect;
}


// e)

// Erstellt einen String mit den chars von lower bis einschließlich upper.
String range_to_pattern(char lower, char upper) {
    require("valid lower and upper char", lower > 0 && lower <= upper && upper <= 127);
    int length = upper - lower + 1;
    String s = xcalloc(sizeof(char), length + 1);   // erstelle String

    // fuelle String mit entsprechenden Chars
    int i = 0;   // Position im String
    for (char c = lower; c <= upper; c++) {
        s[i] = c;
        i++;
    }
    return s;
}

// Erstellt einen String der Laenge length mit dem sich wiederholenden Muster pattern.
String complete_pattern(String pattern, int length) {
    String s = xcalloc(sizeof(char), length + 1);
    int pattern_length = s_length(pattern);
    for(int i = 0; i < length; i++){
        s[i] = s_get(pattern, i%pattern_length);
    }
    return s;
}

// Erstellt einen String, der die komplette Fuellung des Rechteckes enthält.
String get_complete_fill(int width, int heigth, Fill fill) {
    int complete_fill_length = (width - 2) * (heigth - 2);
    if (complete_fill_length <= 0) {
        return "";
    }

    switch (fill.tag){
        case RANGE:
            return complete_pattern(range_to_pattern(fill.rf.start, fill.rf.end), complete_fill_length);
        case SIMPLE:
            return s_repeat(complete_fill_length, fill.sf.c);
        case PATTERN:
            return complete_pattern(fill.pf.pattern, complete_fill_length);
    }
    return "";
}


// Gibt x Leerzeichen aus.
void draw_x_position(int x) {
    for (int i = 0; i < x; i++){
        prints(" ");
    }
}

// Gibt y leere Zeilen aus.
void draw_y_position(int y) {
    for (int i = 0; i < y; i++){
        println();
    }
}

// Gibt die erste bzw. letzte Zeile des Rechtecks aus.
void draw_first_or_last_line(int width, int x) {
    draw_x_position(x);
    if (width == 1) {
        prints("+");
    } else if (width > 1) {
        prints("+");
        for (int i = 0; i < width - 2; i++) {
            prints("-");
        }
        prints("+");
    }
    println();
}

// Gibt eine mittlere Zeile des Rechtecks wieder und gibt den aktualisierten fill_count wieder.
int draw_middle_line(int fill_count, String complete_fill, int width, int x) {
    draw_x_position(x);
    if (width == 1) {
        prints("|");
    } else if (width > 1) {
        prints("|");
        for (int i = 0; i < width - 2; i++) {
            printc(s_get(complete_fill, fill_count));
            fill_count++;
        }
        prints("|");
    }
    println();

    return fill_count;
}

// Zeichnet das Rechteck.
void draw_rect(Rect rect) {
    int x = rect.x;
    int y = rect.y;
    int width = rect.width;
    int height = rect.height;
    Fill fill = rect.fill;

    String complete_fill = get_complete_fill(width, height, fill);
    int fill_count = 0;     // wird um eins erhöht, wenn ein char von complete_fill ausgegeben wird

    //printsln("start drawing:");

    draw_y_position(y);

    draw_first_or_last_line(width, x);

    if (height >=2) {
        for (int i = 0; i < height - 2; i++) {
            fill_count = draw_middle_line(fill_count, complete_fill, width, x);
        }
        draw_first_or_last_line(width, x);
    }

    //printsln("end drawing");
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
int main(void) {
    // Mindestens 6 verschiedene Rechtecke mit unterschiedlichen Position, Fuellungen und Groeßen.
    draw_rect(make_rect(1, 1, 1, 1, make_simple_fill('o')));


    printsln("make_rect(x, y, width, height, fill)\n");

    // "without fill"
    printsln("make_rect(0, 0, 2, 2, make_simple_fill('.'))");
    Rect test_rect_1 = make_rect(0, 0, 2, 2, make_simple_fill('.'));
    draw_rect(test_rect_1);

    printsln("make_rect(0, 0, 3, 1, make_simple_fill('.'))");
    Rect test_rect_2 = make_rect(0, 0, 3, 1, make_simple_fill('.'));
    draw_rect(test_rect_2);

    printsln("make_rect(0, 0, 1, 3, make_simple_fill('.'))");
    Rect test_rect_3 = make_rect(0, 0, 1, 3, make_simple_fill('.'));
    draw_rect(test_rect_3);


    // simple fill
    printsln("make_rect(1, 1, 9, 4, make_simple_fill('0'))");
    Rect test_rect_sf1 = make_rect(1, 1, 9, 4, make_simple_fill('0'));
    draw_rect(test_rect_sf1);

    printsln("make_rect(5, 0, 3, 5, make_simple_fill('o'))");
    Rect test_rect_sf2 = make_rect(5, 0, 3, 5, make_simple_fill('o'));
    draw_rect(test_rect_sf2);

    // range fill
    printsln("make_rect(1, 3, 5, 6, make_range_fill('0', '3'))");
    Rect test_rect_rf1 = make_rect(1, 3, 5, 6, make_range_fill('0', '3'));
    draw_rect(test_rect_rf1);

    printsln("make_rect(0, 0, 3, 4, make_range_fill('0', '1'))");
    Rect test_rect_rf2 = make_rect(0, 0, 3, 4, make_range_fill('0', '1'));
    draw_rect(test_rect_rf2);

    // pattern fill
    printsln("make_rect(2, 1, 9, 6, make_pattern_fill(\"abcdef\"))");
    Rect test_rect_pf1 = make_rect(2, 1, 9, 6, make_pattern_fill("abcdef"));
    draw_rect(test_rect_pf1);

    printsln("make_rect(15, 0, 15, 10, make_pattern_fill(\".o\"))");
    Rect test_rect_pf2 = make_rect(15, 0, 15, 10, make_pattern_fill(".o"));
    draw_rect(test_rect_pf2);

    return 0;
}
