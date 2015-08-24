#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;


//Quick Sort
int split(int* array, int pivot, int startIndex, int endIndex){
    int leftBoundary = startIndex;
    int rightBoundary = endIndex;

    while(leftBoundary < rightBoundary){
         while( pivot < array[rightBoundary]
                && rightBoundary > leftBoundary){
              rightBoundary--;                      //move left
         }
         swap(array[leftBoundary], array[rightBoundary]);
         while( pivot >= array[leftBoundary]
                && leftBoundary < rightBoundary){
              leftBoundary++;                        //move right
         }
         swap(array[rightBoundary], array[leftBoundary]);
    }
    return leftBoundary;
}


void quickSort(int* array, int startIndex, int endIndex){
    int pivot = array[startIndex];
    int splitPoint;
     
    if(endIndex > startIndex){
        splitPoint = split(array, pivot, startIndex, endIndex);
        array[splitPoint] = pivot;
        quickSort(array, startIndex, splitPoint-1); 	 //Quick sort first half
        quickSort(array, splitPoint+1, endIndex);    //Quick sort second half
    }
}

//find upper and lower bounds
int findBounds(int numToFind, int boundaryVal, int a[], int i){

	//Find Bounds
		for(int j=0; j<i;j++){
		
			//for odd num
			if(numToFind%2 == 1){
				if(a[j]<=boundaryVal && a[j+1]>boundaryVal){
					return j-1;
					
				}
			}else{//even
			
				
				if(a[j] == boundaryVal){
				
					return j-1;
				
				}
			
			}
		
		}
		

}  

//returns number of duplicates of boundaryVal
int duplicatesOfBoundaryVal(int size, int boundaryVal, int a[]){
	int occurances = 0;
	
	for(int i = 0; i < size; i++){
		if(boundaryVal == a[i]){
			occurances += 1;
		}
	}
	return occurances;
}

//calculates factorial
int factorial(int n){

	int factorial;

	if(n==0){
	
		factorial = 1;
	
	}else{
	
		factorial = n;
		for(int i=n-1;i>1;i--){
	
			factorial=i*factorial;
	
		}
	}

	return factorial;
}


//Calculate the number of duplicates that add up to numToFind
int combination(int occurances){

	int combination;
	
	combination = factorial(occurances)/(((factorial(occurances-2)) * 2));
	
	return combination;

}

//return size of array
int getArray(ifstream *infile, int a[]){

	string line = "";
	int element = 0;
	int i = 0;
	
	while(!infile->eof()){
	
		getline(*infile, line);
		if(line.empty())
			break;
	
		//get element in array
		element = atoi(line.c_str());
		a[i] = element;
		//cout << a[i] << " ";
		i++;
		
	}
	//cout << endl;
	return i;	

}

int main(int argc, char *argv[]){

	ifstream infile;
	ofstream outfile;
	
	
	//Open Files
	if(argc != 3){
		printf("Error: Incorrect number of inputs\n");
		exit(0);
	}
	
	infile.open(argv[1]);
	if(!infile.is_open()){
		perror("Error\nUnable to open input file");
		exit(0);	
	}
	
	outfile.open(argv[2]);
	if(!outfile.is_open()){
		perror("Error\nUnable to open output file");
		exit(0);	
	}
	
	//Declare and initialize
	int a[1028];
	int size;
	size = getArray(&infile, a);
	

	int numToFind;
	int indexNumToFind;
	int boundaryVal;
	int index;
	int occurances;
	
	quickSort(a, 0, size-1);
	/*for(int i=0; i<size;i++)
		cout << a[i] << " ";*/


	for(int i=2; i<size;i++){
	
		numToFind = a[i];
		
		indexNumToFind = i;
		boundaryVal = numToFind/2;
		
		
		index = findBounds(numToFind, boundaryVal, a, i);

		if(numToFind%2 == 0){
			occurances = duplicatesOfBoundaryVal(size, boundaryVal,a);
			
			//Duplicates
			for(int j=0;j<combination(occurances);j++){
				outfile << numToFind;
				outfile << "\t" << boundaryVal << "\t" << boundaryVal << "\n";
			}
			
		}
		
		//Upper Half
		for(int j=index+1; j<=indexNumToFind-1; j++){
		
			int diff = numToFind-a[j];
			
			//Lower Half
			for(int k=0; k<=index;k++){
			
				//cout << "DIFF: " << diff << endl;
			
				if(diff == a[k]){
					outfile << numToFind;
					outfile << "\t" << a[k] << "\t" << a[j] << "\n";
				
				}
			
			}
	
		}

		/*cout << "i: " << i << endl;
		cout << "NUMTOFIND: " << numToFind << endl;
		cout << "BOUNDARYVAL: " << boundaryVal << endl;
		cout << "INDEX: " << index << endl;		
		cout << "Occurances: " << occurances << endl << endl;*/
	}


	return 0;

}
