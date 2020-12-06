/*
August Ho und Benjamin von Behren
Assignment 07
Aufgabe 3: Dateien einlesen und verarbeiten
*/

/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a)
typedef struct Statistics{
    int avg_year, number_m, number_f;
    double avg_height_m, avg_height_f;
} Statistics;


// b)
// Initialisiert eine Statistik mit Nullen.
Statistics make_statistics() {
    Statistics stat = {0, 0, 0, 0.0, 0.0};
    return stat;
}


// c)
// Printet die Werte der Statistik.
void print_statistics(Statistics stat) {
    printf("mean year:           %7d\n", stat.avg_year);
    printf("number males:        %7d\n", stat.number_m);
    printf("number females:      %7d\n", stat.number_f);
    printf("mean heigth males:   %7.2f m\n", stat.avg_height_m);
    printf("mean height females: %7.2f m\n", stat.avg_height_f);
}


// d)
// Erstellt die Statistik der Werte im String table.
Statistics compute_statistics(String table) {
    Statistics stat = make_statistics();

    table = s_sub(table, s_index(table, "\n") + 1, s_last_index(table, "\n") + 1);  // entfert erste Zeile; + 1 zählt Zeilenumbruch mit
    int table_length = s_length(table);
    int line_length = s_index(table, "\n") + 1;
    int number_of_lines = table_length / line_length;
    //printsln(table);

    int sum_year = 0;
    const int YEAR_LENGTH = 4;
    int sum_number_males = 0;
    int sum_number_females = 0;
    double sum_height_males = 0.0;
    double sum_height_females = 0.0;
    const int HEIGHT_LENGTH = 5;

    for (int i = 0; i < number_of_lines; i++) {
        String line = s_sub(table, i*line_length, (i+1)*line_length);
        //prints(line);

		//stats für Jahren
        String year = s_sub(line, 0, YEAR_LENGTH);
        sum_year += i_of_s(year);

		//stats für male/female und die höhe dazu
        String height_string = s_sub(line, line_length - HEIGHT_LENGTH, line_length);
        double height = d_of_s(height_string);
        if (s_contains(line, "m")) {
            sum_number_males++;
            sum_height_males += height;
        } else { // female
            sum_number_females++;
            sum_height_females += height;
        }
    }

	// average werte berechnen
    stat.avg_year = sum_year / number_of_lines;
    stat.number_m = sum_number_males;
    stat.number_f = sum_number_females;
    stat.avg_height_m = sum_height_males / sum_number_males;
    stat.avg_height_f = sum_height_females / sum_number_females;
    return stat;
}


int main(void) {
	String table = s_read_file("people.txt");
	//printsln(table);
	Statistics stat = compute_statistics(table);
	print_statistics(stat);
	return 0;
}
