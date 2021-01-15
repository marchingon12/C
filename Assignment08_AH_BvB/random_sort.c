/*
August Ho und Benjamin von Behren
Assignment 08
Aufgabe 2: Sortieren durch zufälliges Vertauschen
*/


/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"
#include <math.h>

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;


struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}


// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}

//end of template code

//now it is your turn ... 

// (a) 
// Compares the given cars and returns their order: 1 -> 
int compare(Car car1, Car car2) {
    if (car1.year > car2.year) {
        return 1;
    } else if (car1.year < car2.year) {
        return -1;
    } else {    // same age
        int ret = strcmp(car1.brand, car2.brand);
        if (ret < 0) {
            return 1;
        } else if (ret > 0) {
            return -1;
        } else {
            return 0;
        }
    }
}


// (b) 
// Tests the compare function.
void compare_test() {
    // for comparison the car brands:
    //   0     1        2         3       4       5        6        7
    // "VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
    Car car1 = { brands[0], 0, 0, 1.0 };
    Car car2 = { brands[0], 0, 0, 1.0 };
    int result = 0;
    
    car1.year = 2000; car1.brand = brands[0];
    car2.year = 1999; car2.brand = brands[0];
    result = 1;
    test_equal_i(compare(car1, car2), result);
    
    car1.year = 1990; car1.brand = brands[0];
    car2.year = 2002; car2.brand = brands[0];
    result = -1;
    test_equal_i(compare(car1, car2), result);
    
    car1.year = 1990; car1.brand = brands[7];
    car2.year = 2002; car2.brand = brands[3];
    result = -1;
    test_equal_i(compare(car1, car2), result);
    
    car1.year = 2000; car1.brand = brands[6];
    car2.year = 2000; car2.brand = brands[6];
    result = 0;
    test_equal_i(compare(car1, car2), result);
    
    car1.year = 2000; car1.brand = brands[5];
    car2.year = 2000; car2.brand = brands[6];
    result = -1;
    test_equal_i(compare(car1, car2), result);
    
    car1.year = 2000; car1.brand = brands[2];
    car2.year = 2000; car2.brand = brands[0];
    result = 1;
    test_equal_i(compare(car1, car2), result);
}


// (c)
// Checks wether the array of cars is sorted.
bool sorted(Car* a, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (compare(a[i], a[i + 1]) == -1) {
            return false;
        }
    }
    return true;
}


// (d,e) 
// Swap two randomly chosen cars until the array is sorted.
int random_sort(Car* a, int length) {
    int swaps = 0;
    
    //return 0;

    while(!sorted(a, length)) {
        int index1 = i_rnd(length);
        int index2 = i_rnd(length);
        // make sure that index1 and index2 are different
        while (index2 == index1) {
            index2 = i_rnd(length);
        }
        
        // swap cars
        Car car_temp = a[index1];
        a[index1] = a[index2];
        a[index2] = car_temp;
        
        swaps++;
    }
    return swaps;
}
/*
    e)
    Bei jedem Durchlauf der while-Schleife in der Funktion random_sort wird die Funktion sorted aufgerufen.
    In dieser findet mindestens ein Vergleich und höchstens number_of_random_cars - 1 Vergleiche statt.
    Beim letzten Aufruf von sorted wird compare genau number_of_random_cars - 1 mal aufgerufen.
    Für swaps und die Anzahl der Aufrufe von compare (comps) gilt demnach:
    swaps * 1 + number_of_random_cars <= comps <= swaps * (number_of_random_cars - 1) + number_of_random_cars
*/

// (f) 
// Does a random_sort on a random generated array with the given number_of_random_cars for samples times and 
// returns how many swaps were needed on average.
int random_sort_swaps_average(int number_of_random_cars, int samples) {
    int swaps_sum = 0;
    Car* car_park;
    for (int i = 0; i < samples; i++) {
        car_park = create_car_park(number_of_random_cars);
        
        swaps_sum += random_sort(car_park, number_of_random_cars);
    }
    delete_car_park(car_park);
    return swaps_sum / samples;
}

int main(void) {
	
	//compare_test();	
	
	
	//some output
	int number_of_random_cars = 10;
	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sorting...\n");
    
    int test_swaps = random_sort(car_park, number_of_random_cars);
	printf("%d swaps were needed\n", test_swaps);
	
	print_car_array(car_park, number_of_random_cars);
	
	delete_car_park(car_park);
	
	
	
	// (f)
    
    int samples = 100;
    printf("samples = %d\nlength \tavg_swaps\n", samples);
    
    int array_length = 3;
    int avg_swaps = random_sort_swaps_average(array_length, samples);
    printf("%2d \t%7d\n", array_length, avg_swaps);
    
    array_length = 5;
    avg_swaps = random_sort_swaps_average(array_length, samples);
    printf("%2d \t%7d\n", array_length, avg_swaps);
    
    array_length = 7;
    avg_swaps = random_sort_swaps_average(array_length, samples);
    printf("%2d \t%7d\n", array_length, avg_swaps);
    
    array_length = 9;
    avg_swaps = random_sort_swaps_average(array_length, samples);
    printf("%2d \t%7d\n", array_length, avg_swaps);
    
    array_length = 10;
    avg_swaps = random_sort_swaps_average(array_length, samples);
    printf("%2d \t%7d\n", array_length, avg_swaps);
    /*
        example output:
        samples = 100
        length  avg_swaps
         3            3
         5          134
         7         4998
         9       339450
        10      4291232
        
    */
    return 0;
}
