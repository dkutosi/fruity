/* 
  
Author: Daniel Namokoyi
Assignment : Two
Date: may 1,, 2016

This program uses pipes as a way of passing two intergers between parent process and child process.
When executed, the program is supposed to find N prime numbers are determined from standard input. 
The program passes a counter from parent to child to keep track of the next prime candidate that is to 
be considered. If a number is found to be prime, it sent to the standard output. All other numbers are omitted.
Much of the code in the program was build upon based on an example provied to the class by Dr eckart to illustrrate
pipes. It has been modifed to consider prime candidates. 

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <math.h>


int numOfPrimes = 0;

int thisPrime(int num);
int isPrime(int num);

/* This method takes in a number and calculates the Nth prime given that number.  */
/* The method stores the result in an array held in stored memory  */
int thisPrime(int num){
	
	int thisNum = 2;
	int count;
	
	for(count = 0; count < num; thisNum++){
		if(isPrime(thisNum) == 1){
			count++;
		}
	}
	if ((thisNum - 1) != 0){
			return thisNum-1;
	}
	
	return 0;
}

/* This method takes in a number and checks if its prime. It returns 0 for false and 1 for true.  */		
int isPrime(int num){
	int i;
	for(i = 2; i < num; ++i){
		if(num % i == 0){
			return 0;
		}
	}
	return 1;
}

/* This method take in N number, increments it by one and calls the  prime function to determine
the N prime number. The prime number is then printed out to output.*/
int addition(int num){
	
	int number = 1;
	number = number + num;
	int see;
	see = thisPrime(num);
	printf("%d\n", see);
	
	return number;
}

/* The main/driver process. */
int main(int argc, char *argv[]) {
	
	if(argc <= 1){
		printf("Expecting <number1>");
		exit(0);
	}
	numOfPrimes = atoi(argv[1]);

	if (numOfPrimes < 1){
		printf("Sorry, cant determine %d prime numbers", numOfPrimes);
		exit(0);
	}
	
	
        int parent2child_tube[3];
        int child2parent_tube[3];
	pid_t child;

        pipe(parent2child_tube);
        pipe(child2parent_tube);

     if(child = fork()){
		// Parent process

		// Convert parent output file descriptor to FILE*
		FILE* parent_OUTPUT = fdopen(parent2child_tube[1], "w");

		// Convert parent input file descriptor to FILE*
		FILE* parent_INPUT = fdopen(child2parent_tube[0], "r");

		// Send and receive messages until message value is <= 1.
		double value = 1;
		do {
			// Send value to child.
			fprintf(parent_OUTPUT, "%lf\n", value);
			fflush(parent_OUTPUT);

			// Receive updated value from child.
			fscanf(parent_INPUT, "%lf", &value);

			// Do computation.
			value = addition(value);
			
		} while (value < numOfPrimes);

	} else {
		// Child process

		// Convert child output file descriptor to FILE*
		FILE* child_OUTPUT = fdopen(child2parent_tube[1], "w");

		// Convert child input file descriptor to FILE*
		FILE* child_INPUT = fdopen(parent2child_tube[0], "r");

		// Receive and send messages.
		while (1) {
			double value;

			// Receive value from parent.
			fscanf(child_INPUT, "%lf", &value);
			//printf("Child received %lf from parent.\n", value);

			// Do computation.
			value = addition(value);
			
			// Send updated value back to parent.
			fprintf(child_OUTPUT, "%lf\n", value);
			fflush(child_OUTPUT);
		}
	}

	// Parent is done, so kill the child rather than leave an orphan.
	kill(child, 9);
}
