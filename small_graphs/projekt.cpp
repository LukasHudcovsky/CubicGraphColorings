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

int main(){
	FILE *fr;
	int c, x;
	int q = -1;
	int count = 0;
	std::vector<int> r;
	std::set<int> set;
	
	for(int k=18; k<=30; k+=2){
		char *str = new char[7];
		sprintf(str, "SC4.%d", k);
		fr = fopen(str, "r");
		fscanf(fr, "%d", &c);
		int **a = vytvorMaticu(k, 3);
		int **b = vytvorMaticu(k, 3);
		
		std::cout << k << " vrcholov: ";
		for(int l=0; l<c; l++){
			fscanf(fr, "%d", &x);
			fscanf(fr, "%d", &x);
			for(int i=0; i<k; i++){
				for(int j=0; j<3; j++){
					fscanf(fr, "%d", &x);
					a[i][j] = x;
					b[i][j] = 0;
				}
			}
			
		    /*if(!jeKazdyVrcholSilny(a, b, k)){
				q = count;
			}*/
			
			/*if(!zafarbenieKostra(a, b, k, 0, r, set, set)){
				q = count;
			}*/
			
			if(!jeKazdaDvojicaSilna(a, b, k)){
				q = count;
			}	
			count++; 
		}
		if(q==-1){
			std::cout << "Vsetky grafy su vyhovujuce\n";
		}
		else{
			std::cout << "Graf " << q << " je protipriklad\n";
			q = -1;
		}
		zmazMaticu(a, k);
		zmazMaticu(b, k); 
		fclose(fr);
	}
		
}
