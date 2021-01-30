#include <iostream>
#include <cstdio> //IO
#include <vector>

using namespace std;

/* Space: O(n) Complexity: O(n) */
int merge(int *v, int start, int middle, int end){
	int i = start; //begin of first ordered vector
	int j = middle + 1; //begin of second ordered vector
	int k = start; //begin of new vector merged
	int num_inverses = 0;

	vector<int> aux (end + 1); //vector starts from 0

	while(i <= middle && j <= end){
		if (v[i] > v[j]){ //It's inverse
			aux[k++] = v[j++];

			/* Note that as the lists are ordered, if v[i] be greater than v[j], all v's after v[i] it'll be too */
			num_inverses += (middle - i) + 1; //vector starts from 0, therefore, the plus 1
		} else {
			aux[k++] = v[i++];
		}
	}

	/* Treats cases when vector it's even and the two halves have different sizes */
	while(i <= middle){
		aux[k++] = v[i++];
	}
	
	while(j <= end){
		aux[k++] = v[j++];
	}
	
	/* Copy to original vector the new ordered part */
	for (i = start; i <= end; i++){
		v[i] = aux[i];
	}

	return num_inverses;
}

/* Based on Merge Sort */
/* Space: O(n)  Complexity: O(n*logn) */
int countInversiveRecursive(int* v, int start, int end){
	//there is nothing more to compare
	if (start == end) 
		return 0;
	
	int num_inverses = 0;
	
	int middle = (start+end) / 2;

	num_inverses += countInversiveRecursive(v, start, middle);
	num_inverses += countInversiveRecursive(v, middle + 1, end);
	num_inverses += merge(v, start, middle, end);

	return num_inverses;
}

int countInversiveIterative(int* v, int n){
	int num_inverses = 0;

	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			if (v[i] > v[j])
				num_inverses++;
		}
	}

	return num_inverses;
}

int main(){
	int num_tests;
	int n;
	int v[10000];

	cin >> num_tests;

	for (int i = 0; i < num_tests; i++){
		cin >> n;

		for (int j = 0; j < n; j++){
			cin >> v[j];
		}

		cout << countInversiveRecursive(v, 0, n-1) << endl;
	}
}


