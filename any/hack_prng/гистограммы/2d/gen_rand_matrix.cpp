#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

// задать:
int pseudoLen = 250000; // длина последовательности псевдослучайных чисел
int upperBond = 50;
int numBoxes = pow(upperBond, 2); // число коробок для подсчета гистограммы
int meanValue = int(1.0*pseudoLen/numBoxes); // "ожидаемое" (теоретическое) среднее значение

int main() {
	
     double randNumber1 = 0, randNumber2;
     int j1, j2;
     
     vector<vector<int>> count(upperBond, vector<int>(upperBond, 0));
    
     
     // инициализируем датчик	
     srand(time(0)); 	
     
     randNumber1 = upperBond*1.0*rand()/RAND_MAX;
	
     // генерируем последовательность заданной длины
     for (int i = 0; i < pseudoLen; i++) {
     	// получаем число от 0 до upperBond - 1
        randNumber2 = upperBond*1.0*rand()/RAND_MAX;
	
        // ищем номера ячейки в матрице:
        j1 = j2 = -1;
        for (int j = 0; j < numBoxes; j++) {
        	if (randNumber1 >= j & randNumber1 < j+1) 
                j1 = j;
            if (randNumber2 >= j & randNumber2 < j+1) 
                j2 = j;
            
            if (j1 > -1 && j2 > -1) break;
        }
        
        if (j1 > -1 && j2 > -1) 
            count[j1][j2]++;
        
        randNumber1 = randNumber2;
     }

     // пишем гистограмму в файл
     FILE *fileOut = fopen("histogram_2d.dat", "w");
     //fprintf(fileOut, "%10d\t%10d\n", meanValue, meanValue);     
     for (int j = 0; j < upperBond; j++) {
        //fprintf(fileOut, "%5d", j+1);
        for (int i = 0; i < upperBond; i++) 
            fprintf(fileOut, "%5d ", count[j][i]);
        fprintf(fileOut, "\n");
     }
     fclose(fileOut);
     
     return 0;
}
