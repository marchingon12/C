/*
Compile: make people
Run: ./people
*/

/*
- average rounded year of birth
- amount of men in the table
- amount of women in the table
- average body size of men
- average bod size of women
 */

#include "base.h"
#include "string.h"


const int LINE_NUM = 1000;

// a) struct Statistics ...
typedef struct Statistics {
	int mean_year, number_males, number_females;
	double mean_height_males, mean_height_females;
} Stats;

// b) ... make_statistics...
Stats make_statistics(void){
	Stats o = {0, 0, 0.0, 0.0, 0.0};
	return o;
}

// c) ... print_statistics...
void print_statistics(Stats o){
	printf("mean year:              %d\n", o.mean_year);
	printf("number males:           %d\n", o.number_males);
	printf("number females:         %d\n", o.number_females);
	printf("mean height males:      %.2f m\n", o.mean_height_males);
	printf("mean height females:    %.2f m\n", o.mean_height_females);
}

/**
 * get sub string of input string with index to a space, tab or \n.
 * @param  s      input string
 * @param  index  index number
 * @param  length length of string s
 * @return        sub string
 */
String get_substring(String s, int index, int length){
	int end_index = index;
	while(end_index < length && s_get(s, end_index) != ' ' && s_get(s, end_index) != '\n' && s_get(s, end_index) != '	'){
		end_index++;
	}
	return s_sub(s, index, end_index);
}

// d) ... compute_statistics...
Stats compute_statistics(String table){
	Stats o = make_statistics();
	//skip the first line, start from second line
	int i = 16;
	int length = s_length(table);
	String s;
	//counters
	int numYears = 0, heightMales = 0, heightFemales = 0, numMales = 0, numFemales = 0;


	//skip first line, in total 1001 lines so 1001 - 1
	for (int line = 1; line <= LINE_NUM; line++) {
		for (int column = 1; column <= 4; column++) {
			s = get_substring(table, i, length);
			//1st cycle starts here: in column 1 is years
			if (column == 1) {
				numYears += i_of_s(s);
			}
			//2nd cycle starts here: in column 2 is male/female
			if (column == 2) {
				//count number of males else females
				if (s_get(s, 0) == 'm') {
					numMales += 1;
				} else if (s_get(s, 0) == 'f') {
					numFemales += 1;
				}
			}
			//3rd cycle starts here: in column 3 is heights
			//HELP: somehow need to get the substring of column 2 to identify m/f
			//idea: put column 2 and 3 in array, use pointers to point and add
			if (column == 3) {
				if (s == "m") {
					heightMales += i_of_s(s);
				} else if (s == "f") {
					heightFemales += i_of_s(s);
				}
			}
		}
		s = get_substring(table, i, length);
		int count = 0;
		// if done then force skip line
		i = skip_line(table,i,n);
		/*
		for (int index = i; index <= length - 1 ; index++){
			char h = s_get(table, index);
			if(h == '\n'){
				count = count + 1;
				break;
			}
			count = count + 1;
		}
		i = count + index ;
		*/
	}


	o.mean_year += d_of_s(table);

	// calculate mean of Year
	o.mean_year = o.mean_year / LINE_NUM;
	// assign number of males
	o.number_males = numMales;
	// assign number of females
	o.number_females = numFemales;
	// calculate mean height of males
	o.mean_height_males = heightMales / LINE_NUM;
	// calculate mean height of females
	o.mean_height_females = heightFemales / LINE_NUM;
	return o;
}

int main(void) {
	String table = s_read_file("people.txt");
	//Stats people = compute_statistics(table);
	//print_statistics(people);
	//printsln(table);
	Stats o = {0, 0, 0.0, 0.0, 0.0};
	print_statistics(o);
	return 0;
}
