#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

// задать:
int pseudoLen = 10000; // длина последовательности псевдослучайных чисел
int numBoxes = 50; // число коробок для подсчета гистограммы
int meanValue = int(1.0*pseudoLen/numBoxes);

int main() {
	
     double randNumber = 0;
     
     vector<int> count;
     count.resize(numBoxes);
     
     // инициализируем датчик	
     srand(time(0)); 	
     // генерируем последовательность заданной длины
     for (int i = 0; i < pseudoLen; i++) {
     	// получаем число от 0 до numBoxes - 1
	randNumber = numBoxes*1.0*rand()/RAND_MAX;
	
        for (int j = 0; j < numBoxes; j++) {
        	if (randNumber >= j && randNumber < j+1) 
        		count[j]++;
        }
     }

     // пишем гистограмму в файл
     FILE *fileOut = fopen("histogram.dat", "w");
     fprintf(fileOut, "%10d\t%10d\n", meanValue, meanValue);     
     for (int j = 0; j < numBoxes; j++) {
        fprintf(fileOut, "%5d\t%10d\n", j+1, count[j]);
     }
     fclose(fileOut);
     
     return 0;
}
