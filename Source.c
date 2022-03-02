#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include<Windows.h>
#include <stdbool.h>

// User defined types
typedef double data_set_type;

/*!	Swap the contents of the two memory locations */
void swap(data_set_type* pa, data_set_type* pb) {
	data_set_type hold = *pa;
	*pa = *pb;
	*pb = hold;
}
/*!	Sort an array using Shell's sort. */
void  shell_sort(data_set_type arr[], int size) {
	int stepSize = size / 2;
	while (stepSize > 0) {
		for (int idxLastInSegment = stepSize; idxLastInSegment < size; ++idxLastInSegment) {
			int idxCurrent = idxLastInSegment;
			while (idxCurrent >= stepSize && arr[idxCurrent] < arr[idxCurrent - stepSize]) {
				swap(&arr[idxCurrent], &arr[idxCurrent - stepSize]);
				idxCurrent -= stepSize;
			}
		}
		stepSize /= 2;
	}
}
void printLine() {
	printf("\n");
	for (int i = 0; i < 100; i++) {
		printf("%c", 205);
	}
}
void makeArrayCopy(int size, double array[], double array2[]) {
	for (int i = 0; i < size; i++) {
		array2[i] = array[i];
	}
}
double findMedian(double array[], int size) {
	if (size % 2 == 0) {
		return (array[(size - 1) / 2] + array[(size - 1) / 2 + 1]) / 2;
	}
	else {
		return array[size / 2];
	}
}

void findMode(double array[], int size) {
	int counter = 1;
	int* frequency = (int*)malloc(sizeof(int) * size + 1);
	//int frequency[1000] = { 0 };

	int visited = -1;
	for (int i = 0; i < size; i++) {
		int count = 1;
		for (int j = i + 1; j < size; j++) {
			if (array[i] == array[j]) {
				count++;
				frequency[j] = visited;
			}
		}
		if (frequency[i] != visited)
			frequency[i] = count;
	}
	int highFreq = 0;
	int highNumIndex = -1;
	int num = frequency[0];
	int repetitiveValues = 0;
	for (int i = 0; i < size; i++) {
		if (highFreq < frequency[i]) {
			highFreq = frequency[i];
			highNumIndex = i;
		}
	}
	for (int i = 0; i < size; i++) {
		if (highFreq == frequency[i]) {
			repetitiveValues++;
		}
		if (frequency[i] == -1) {
			repetitiveValues++;
		}
	}
	printf("Mode = { ");
	_Bool modeCounter = 1;
	for (int i = 0; i < size; i++) {
		if (size == 1 || repetitiveValues == size) {
			puts("no mode }");
			break;
		}
		if (highFreq == frequency[i]) {
			if (modeCounter) {
				printf("%.1lf", array[i]);
				modeCounter = 0;
			}
			else
				printf(", %.1lf", array[i]);
		}
		if (i == size - 1) {
			printf(" } x %d", highFreq);
		}
	}
	free(frequency);
}

double findVariance(int size, double array[], double mean) {
	double variance = 0;
	for (int i = 0; i < size; i++) {
		variance += (array[i] - mean) * (array[i] - mean);
	}
	variance /= size;
	return variance;
}

double findSlope(int size, double mean, double yMean, double array[]) {
	double ssxx = 0;
	double ssxy = 0;
	for (int i = 0; i < size; i++) {
		ssxx += (array[i] - mean) * (array[i] - mean);
		ssxy += (array[i] - mean) * (i - yMean);
	}
	return ssxy / ssxx;
}

double findYintercept(double mean, double yMean, double slope) {
	return yMean - slope * mean;
}
int main(int argc, char* argv[]) {
	int capacity = 5;
	SetConsoleOutputCP(850);//codepage

	printf("Regression Stats(v1.0.0), %c2019 Danish Davis\n", 184);
	puts("=============================================");
	puts("Enter white - space separated real numbers.Terminate input with ^ Z");
	double* numberPointer = (double*)malloc(sizeof(double) * capacity + 1);
	if (numberPointer == NULL) {
		return NULL;
	}
	int size = 0;
	double number = 1.0;
	double total = 0;
	double num = 0.0;
	char ch;
	double mynum = 0;
	_Bool isfirst = true;
	_Bool isNegative = false;
	double* pszDouble = NULL;
	if (argc < 2) {
		while ((ch = getchar()) != EOF)
		{
			if (size == capacity) {
				capacity *= 2;
				pszDouble = (double*)realloc(numberPointer, (sizeof(double) * capacity) + 1);
				if (pszDouble == NULL) {
					free(numberPointer);
					return NULL;
				}
				numberPointer = pszDouble;
			}
			if (ch == '.')
			{
				number = 0.1;
			}
			if (ch == '-' && isfirst == true) {
				isNegative = true;
				isfirst = false;
			}
			else if ((ch >= '0') && (ch <= '9'))
			{
				if (number == 1)
				{
					num *= 10;
					num += ch - '0';
				}
				else
				{
					num += (ch - '0') * number;
					number /= 10;
				}
			}
			if (isspace(ch)) {
				mynum = num;
				if (isNegative == true) {
					mynum *= -1;
				}
				isfirst = true;
				isNegative = false;
				num = 0;
				number = 1;
				numberPointer[size++] = mynum;
				//printf("%lf\n", mynum);
				//printf("%.2f\n", numberPointer[size - 1]);
				total += mynum;
			}
		}
	}
	else
	{
		FILE* stream = stdin;
		if (argc == 2) {
			if ((stream = fopen(argv[1], "rb")) == NULL) {
				printf("error <%s> ", argv[1]);
				perror(" ");
				return EXIT_FAILURE;
			}
		}
		double fileNum = 0.0;
		while (fscanf(stream, "%lf", &fileNum) != EOF) {
			if (size == capacity) {
				capacity *= 2;
				pszDouble = (double*)realloc(numberPointer, (sizeof(double) * capacity) + 1);
				if (pszDouble == NULL) {
					free(numberPointer);
					return NULL;
				}
				numberPointer = pszDouble;
			}
			numberPointer[size++] = fileNum;
			total += fileNum;
			fileNum = 0.0;
		}
		fclose(stream);
	}
	double* arrayCopy = (double*)malloc(sizeof(double) * capacity + 1);
	if (arrayCopy == NULL) {
		printf("NO MEMORY");
		return NULL;
	}
	makeArrayCopy(size, numberPointer, arrayCopy);
	shell_sort(numberPointer, size);
	puts("Standard Analysis");
	printLine();
	printf("\n# elements = %zu\n", size);
	printf("Range = [%g .. %g]\n", numberPointer[0], numberPointer[size - 1]);
	printf("Arithmetic median = %.2lf\n", findMedian(numberPointer, size));
	double mean = (double)total / size;
	printf("Arithmetic mean = %.2lf\n", mean);
	findMode(numberPointer, size);
	double variance = findVariance(size, numberPointer, mean);
	printf("\nVariance = %.2lf\n", variance);
	double deviation = sqrt(variance);
	printf("Standard deviation = %.5lf\n\n", deviation);
	double yMean = (size - 1) / 2.0;
	double slope = findSlope(size, mean, yMean, arrayCopy);
	printf("Linear Line Regression: slope = %.2lf", slope);
	double yIntercept = findYintercept(mean, yMean, slope);
	printf(" Y-Intercept %.2lf\n", yIntercept);

	printLine();
	puts("\nFrequency Table\n---------------");
	double highestNumber = numberPointer[size - 1];
	double lowestNumber = numberPointer[0];
	int asciA = 65;
	double tableDifference = (highestNumber - lowestNumber + 0.1) / 10.0;
	double holdValue = lowestNumber;
	int occurance = 0;
	double percentage = 0;
	double percentageArray[10] = { 0 };
	double highestPercentage = 0;
	for (int i = 0; i < 10; i++) {
		if (i == 9) {
			printf("%c [ %.1lf . . %.1lf ] =", asciA++, holdValue, holdValue + tableDifference);
		}
		else {
			printf("%c [ %.1lf . . %.1lf ) =", asciA++, holdValue, holdValue + tableDifference);
		}
		for (int j = 0; j < size; j++) {
			if (numberPointer[j] >= holdValue && numberPointer[j] < (holdValue + tableDifference)) {
				occurance++;
			}
		}
		percentage = (double)occurance / size * 100;
		if (highestPercentage < percentage) {
			highestPercentage = percentage;
		}
		percentageArray[i] = percentage;
		printf(" %d : %.2lf%%\n", occurance, percentage);
		holdValue += tableDifference;
		percentage = 0;
		occurance = 0;
	}
	printLine();
	puts("\nFrequency Histogram\n---------------");
	printLine();
	highestPercentage = ceil(highestPercentage / 5) * 5;
	double percentageDiffrence = highestPercentage / 10.0;
	double percentageHold = percentageDiffrence;
	printf("\nGrp	   %% 0");
	for (int i = 1; i <= 10; i++) {
		printf("%8.1lf", percentageHold);
		percentageHold += percentageDiffrence;
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%c", 196);
	}
	for (int i = 0; i <= 80; i++) {
		if (i == 0) {
			printf("%c", 218);
		}
		else if (i % 8 == 0) {
			printf("%c", 194);
		}
		else {
			printf("%c", 196);
		}
	}
	asciA = 65;
	int barLength = 0;
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%c %6.2lf%%   %c", asciA++, percentageArray[i], 179);
		barLength = (int)(80 / highestPercentage * percentageArray[i]);
		for (int k = 0; k < barLength; k++) {
			printf("%c", 254);
		}
		printf("\n");
	}
	for (int i = 0; i < 12; i++) {
		printf("%c", 196);
	}
	for (int i = 0; i <= 80; i++) {
		if (i == 0) {
			printf("%c", 192);
		}
		else if (i % 8 == 0) {
			printf("%c", 194);
		}
		else {
			printf("%c", 196);
		}
	}
	//----------------------------------------------------------------------------------------------------------
	printLine();
	puts("\n\nBox plot\n---------------");
	printLine();
	printf("\nIdx %13.2lf %76.2lf\n", lowestNumber, highestNumber);
	for (int i = 0; i < 12; i++) {
		printf("%c", 196);
	}
	for (int i = 0; i <= 80; i++) {
		if (i == 0) {
			printf("%c", 218);
		}
		else if (i % 8 == 0) {
			printf("%c", 194);
		}
		else {
			printf("%c", 196);
		}
	}
	double commonDiffrence = (double)size / 10;
	if (size < 10) {
		commonDiffrence = 1;
	}
	double holdIndex = commonDiffrence;
	double indexValue = 0;
	double startPercentage = 0.0;
	double endPercentage = 0.0;
	double lowestNum = 0;
	double highestNum = 0;
	int previousIndex = 0;
	double startingPosition = 0;
	double endingPosition = 0;

	printf("\n");
	for (int i = 0; i < 10; i++) {
		indexValue = floor(holdIndex);
		if (i == 9) {
			indexValue = size;
			printf("%6.0lf %6c", indexValue, 179);
		}
		else {
			indexValue = floor(holdIndex);
			printf("%6.0lf %6c", indexValue, 179);
		}
		lowestNum = arrayCopy[previousIndex];
		highestNum = arrayCopy[previousIndex];
		//printf("%.2lf ", lowestNum);
		//printf("%.2lf ", highestNum);
		for (int j = previousIndex; j < indexValue; j++) {
			if (arrayCopy[j] > highestNum) {
				highestNum = arrayCopy[j];
			}
			if (arrayCopy[j] < lowestNum) {
				lowestNum = arrayCopy[j];
			}
		}
		//printf("%.2lf ", lowestNum);
		//printf("%.2lf ", highestNum);
		startPercentage = ((lowestNum - lowestNumber) * 100) / (highestNumber - lowestNumber);
		endPercentage = ((highestNum - lowestNumber) * 100) / (highestNumber - lowestNumber);
		//printf("%.2lf%% ", startPercentage);
		startingPosition = (startPercentage * 80) / 100.0;
		endingPosition = (endPercentage * 80) / 100.0;
		//printf("%.2lf ", startingPosition);
		//printf("%.2lf ", endingPosition);
		if (startingPosition == endingPosition) {
			for (int k = 0; k <= 80; k++) {
				if (k < startingPosition) {
					printf(" ");
				}
				else {
					printf("%c", 254);
					break;
				}
			}
		}
		else {
			for (int k = 0; k <= 80; k++) {
				if (k < startingPosition) {
					printf(" ");
				}
				else {
					printf("%c", 254);
				}
				if (k == (int)endingPosition) {
					break;
				}
			}

		}
		previousIndex = indexValue;

		holdIndex += commonDiffrence;
		printf("\n");
		if (i + 1 == size) {
			break;
		}
	}

	for (int i = 0; i < 12; i++) {
		printf("%c", 196);
	}
	for (int i = 0; i <= 80; i++) {
		if (i == 0) {
			printf("%c", 192);
		}
		else if (i % 8 == 0) {
			printf("%c", 194);
		}
		else {
			printf("%c", 196);
		}
	}


	free(arrayCopy);
	free(numberPointer);
	return 0;
}