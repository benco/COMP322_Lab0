/*
 * Ben Companeitz
 * COMP 322
 * Lab #0 - 9/4/15
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[])
{
    printf("Lab0: Making Sense of Ones and Zeroes\n");

	int filedes = 0;
	if (argc > 1) {
		if (argv[1][0] != '-') {
			filedes = open(argv[1], O_RDONLY); 
		}
	}
	if (filedes < 0) {
		printf("Open probably broke trying to open your file!");
	}

	printf("Original ASCII    Decimal  Parity   T.Error\n");
	printf("-------- -------- -------- -------- --------\n"); 

	int rresp = 0;
	char * byte, * par, * err;
	byte = malloc(sizeof(char)*8), par = malloc(sizeof(char)*8), err = malloc(sizeof(char)*8); 
	par = "________", err = "________";
	char ch, asc;
	int dec = 0, count = 0, pcount = 1;
	while (rresp = read(filedes, &ch, 1)) {
		if ((ch != '0' && ch != '1') || count >= 8) {
			//dec = dec * pow(2, (-1*(8-count)));
			if (fmod(pcount, 2) == 0) {
				par = "Even";
				if (count == 8) {
					err = "False";
				} else {
					err = " True";
				}
			} else {
				par = " Odd";
				err = " True";
			}
			for (int i = count; i < 8; i++) {
				byte[i] = '0';
			}
			printf("%8s %8c %8d %8s %8s\n", byte, dec, dec, par, err);
			dec = 0, count = 0; pcount = 0;
			if (ch != '0' || ch != '1') {
				continue;
			}
		}
		if (ch == '1') {
			if (count != 0) {
				dec += pow(2, (7-count));
			}
			pcount++;
		} 
		byte[count] = ch;
		count++;
	}

	return 0;
}
