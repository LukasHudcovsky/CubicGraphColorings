#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "snark.h"

int** vytvorMaticu(int m, int n) {
    int **a;
    a = new int *[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
    }
    return a;
}

void zmazMaticu(int **a, int m) {
    for (int i = 0; i < m; i++) {
        delete[] a[i];
    }
    delete[] a;
}

void vypisMaticu(int** a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
        	std::cout << a[i][j] << " ";
    	}
    	std::cout << "\n";
    }
}

int main(){
	FILE *fr;
	int c, x;
	int q = -1;
	int count = 0;
	std::vector<int> r;
	std::set<int> set;
	int pocet = 0;
	
	for(int k=4; k<=18; k+=2){
		char *str = new char[7];
		sprintf(str, "%d.txt", k);
		fr = fopen(str, "r");
		int **a = vytvorMaticu(k, 3);
		int **b = vytvorMaticu(k, 3);
		
		std::cout << k << " vrcholov: ";
		while(true){
			if(fscanf(fr, "%s", str)==-1) break;
			fscanf(fr, "%s", str);
			
			for(int i=0; i<k; i++){
				for(int j=0; j<3; j++){
					fscanf(fr, "%d", &x);
					a[i][j] = x-1;
					b[i][j] = 0;
				}
			}
			
		    if(!jeKazdyVrcholSlaby(a, b, k)){
		    	q = 0;
		    	pocet++;
			} 
		}
		
		if(q==-1){
			std::cout << "Vsetky grafy su vyhovujuce\n";
		}
		if(q==0){
			std::cout << "Existuje protipriklad\n";
		}

		zmazMaticu(a, k);
		zmazMaticu(b, k); 
		fclose(fr);
	}
	
	std::cout << "pocet protiprikladov: " << pocet << "\n";
}
