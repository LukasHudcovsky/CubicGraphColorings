#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
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
	std::ifstream s;
	FILE *f;
	
	for(int n=32; n<=36; n+=2){
		char *name = new char[12];
		sprintf(name, "graphs%d.g6", n);
		
		int start;
		f = fopen("posledny.txt", "r");
		fscanf(f, "%d", &start);
		fclose(f);
		
		s.open(name);
		std::string str;
		std::vector<int> r;
		bool t = true;
		
		int **a = vytvorMaticu(n, 3);
		int **b = vytvorMaticu(n, 3);
		
		std::cout << n << " vrcholov(cast "<< start/6000000+1 << "): ";
		int num = 0;
		
		for(int i=0; i<start; i++){
			getline(s, str);
		}
		
		while(getline(s, str) && num<6000000){
			int max = 0;
			int x = -1;
			int y = 1;
			
		    for (int i = 0; i < n; i++) {
		        for(int j=0; j<3; j++){
		        	a[i][j] = -1;
					b[i][j] = 0;
				}
		    }
   	 
		    int limit = n*(n-1)/2;
   	 		int counter = 0;
   	 
			for(int i=1; i<str.length(); i++){
				int c = str[i];
				c -= 63;
				for(int j=0; j<6; j++){
					counter++;
					if(counter>limit){
						break;
					}
					if(x==max){
						y++;
						x = 0;
						max++;
					}
					else{
						x++;
					}
					if(((1 << (5-j)) & c) != 0){
						int k = 0;
						int l = 0;
						while(a[x][k]!=-1){
							k++;
						}
						while(a[y][l]!=-1){
							l++;
						}
						a[x][k] = y;
						a[y][l] = x;
					}
				}
			}
			
			if(!existujeSpecialne3Zafarbenie(a, b, n)){
				t = false;	
				
				for (int i = 0; i < n; i++) {
			        for(int j=0; j<3; j++){
			        	std::cout << a[i][j] << " ";
					}
					std::cout << "\n";
		    	}
		    	break;
			}
			
			/*if(!jeKazdyVrcholSilny(a, b, n)){
				t = false;	
				
				for (int i = 0; i < n; i++) {
			        for(int j=0; j<3; j++){
			        	std::cout << a[i][j] << " ";
					}
					std::cout << "\n";
		    	}
		    	break;
			}*/
			
			if(num%10000==0) std::cout << num << "\n";
			num++;
		}
		
		f = fopen("posledny.txt", "w");
		fprintf(f, "%d", num+start);
		fclose(f);
		
		s.close();
		zmazMaticu(a, n);
		zmazMaticu(b, n);
		
		if(t){
			std::cout << "Vsetky grafy su vyhovujuce\n";
		}
		else{
			std::cout << "Tento graf je protipriklad\n";
			break;
		}
	}
    
}
