#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void print_state(unsigned long);
void array_shift(unsigned long, double *, double, double *);

unsigned long incubation_time, sick_time;
double population, alive, naive, *incubating, total_incubating, *sick, total_sick, dead, immune;

int main(int argc, char *argv[]) {
	unsigned long simulation_time, i;
	double infection_rate, contacts, death_rate;
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [ <locale> ]\n", argv[0]);
		fflush(stderr);
		return EXIT_FAILURE;
	}
	if (argc == 2 && !setlocale(LC_ALL, argv[1])) {
		fprintf(stderr, "Could not set locale %s\n", argv[1]);
		fflush(stderr);
		return EXIT_FAILURE;
	}
	if (scanf("%lf%lf%lf%lu%lu%lf%lu", &population, &infection_rate, &contacts, &incubation_time, &sick_time, &death_rate, &simulation_time) != 7 || population < 1 || infection_rate < 0 || infection_rate > 1 || contacts < 0 || contacts > population || incubation_time < 1UL || sick_time < 1UL || death_rate < 0 || death_rate > 1) {
		fprintf(stderr, "Input parameters expected: <population> <infection_rate> <contacts> <incubation_time> <sick_time> <death_rate> <simulation_time>\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	alive = population;
	naive = population-1;
	incubating = malloc(sizeof(double)*incubation_time);
	if (!incubating) {
		fprintf(stderr, "Could not allocate memory for incubating\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	incubating[0UL] = 1;
	for (i = 1UL; i < incubation_time; i++) {
		incubating[i] = 0;
	}
	total_incubating = 1;
	sick = calloc(sick_time, sizeof(double));
	if (!sick) {
		fprintf(stderr, "Could not allocate memory for sick\n");
		fflush(stderr);
		free(incubating);
		return EXIT_FAILURE;
	}
	total_sick = 0;
	dead = 0;
	immune = 0;
	printf("ROUND\tStanding\tContacts\tInfected\tDead (new)\tImmune (new)\tAFTER ROUND\tAlive\tNaive");
	for (i = 1UL; i <= incubation_time; i++) {
		printf("\tInc. R%lu", i);
	}
	printf("\tInc. (total)");
	for (i = 1UL; i <= sick_time; i++) {
		printf("\tSick R%lu", i);
	}
	puts("\tSick (total)\tDead (total)\tImmune (total)");
	printf("0\t\t\t\t\t");
	print_state(0UL);
	for (i = 1UL; i <= simulation_time; i++) {
		double round_standing, round_contacts, round_infected, round_dead, round_immune;
		round_standing = naive+total_incubating+immune;
		round_contacts = total_incubating*contacts*round_standing/population;
		if (round_contacts > round_standing) {
			round_contacts = round_standing;
		}
		round_infected = naive/round_standing*infection_rate*round_contacts;
		round_dead = sick[sick_time-1UL]*death_rate;
		dead += round_dead;
		round_immune = sick[sick_time-1UL]-round_dead;
		immune += round_immune;
		array_shift(sick_time, sick, incubating[incubation_time-1UL], &total_sick);
		array_shift(incubation_time, incubating, round_infected, &total_incubating);
		naive -= round_infected;
		alive -= round_dead;
		printf("%lu\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf", i, round_standing, round_contacts, round_infected, round_dead, round_immune);
		print_state(i);
	}
	free(sick);
	free(incubating);
	return EXIT_SUCCESS;
}

void print_state(unsigned long round) {
	unsigned long i;
	printf("\t%lu\t%.3lf\t%.3lf", round, alive, naive);
	for (i = 0UL; i < incubation_time; i++) {
		printf("\t%.3lf", incubating[i]);
	}
	printf("\t%.3lf", total_incubating);
	for (i = 0UL; i < sick_time; i++) {
		printf("\t%.3lf", sick[i]);
	}
	printf("\t%.3lf\t%.3lf\t%.3lf\n", total_sick, dead, immune);
	fflush(stdout);
}

void array_shift(unsigned long size, double *array, double first, double *total) {
	unsigned long i;
	*total -= array[size-1UL];
	for (i = size-1UL; i > 0UL; i--) {
		array[i] = array[i-1UL];
	}
	array[0UL] = first;
	*total += array[0UL];
	if (*total < 0) {
		*total = 0;
	}
}
