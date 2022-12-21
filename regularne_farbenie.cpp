#include <iostream>
#include <map>
using namespace std; 

int** vytvorTriTri(){
	int **a;
    a = new int *[6];
    for (int i = 0; i < 6; i++) {
        a[i] = new int[3];
        for(int j=0; j<3; j++){
        	if(i<3){
        		a[i][j] = j+3;
			}
        	else{
        		a[i][j] = j;
			}
		}
    }
    return a;
}

int** vytvorPetersen(){
	int **a;
    a = new int *[10];
    for (int i = 0; i < 10; i++) {
        a[i] = new int[3];
        if(i<5){
        	if((i+4)%5 < (i+6)%5){
        		a[i][0] = (i+4)%5;
        		a[i][1] = (i+6)%5;
			}
			else{
				a[i][1] = (i+4)%5;
        		a[i][0] = (i+6)%5;
			}
        	
        	a[i][2] = i+5;
		}
        else{
        	a[i][0] = i%5;
        	if((i+2)%10 < (i+3)%10){
        		a[i][1] = (i+2)%5 + 5;
        		a[i][2] = (i+3)%5 + 5;
			}
			else{
				a[i][2] = (i+2)%5 + 5;
        		a[i][1] = (i+3)%5 + 5;
			}
		}
    }
    return a;
}

bool nextPermutation(int *p, int n){
	int x = -1;
	for(int i=n-1; i>0; i--){
		if(p[i-1]<p[i]){
			x = i-1;
			break;
		}
	}
	if(x==-1){
		return false;
	}
	
	int y;
	for(int i=x+1; i<n; i++){
		if(p[i]>p[x]){
			y = i;
		}
		else{
			break;
		}
	}
	
	int tmp = p[x];
	p[x] = p[y];
	p[y] = tmp;
	
	for(int i=x+1; i<n-i+x; i++){
		tmp = p[i];
		p[i] = p[n-i+x];
		p[n-i+x] = tmp;
	}
	return true;
}

bool existuje3Zafarbenie(int **a, int **b, int k){
	int *x = new int[k];
	map<int, int> m;
	int j = 0;
	int w = 0;
	x[0] = 0;
	m.insert(pair<int, int>(0, 0));
	
	bool dir = true;
	while(j < k){
		if(j < 0){
			return false;
		}
		
		int q=0;
		for(int i=0; i<3; i++){
			if(b[x[j]][i] == 0){
				q++;
			}
		}
		
		int *p = new int[3];
		int l = 0;
		if(q==0){
			if(dir){
				if(j==k-1){
					break;	
				}
				else{
					j++;
					continue;
				}
			}
			for(int i=0; i<3; i++){
				if(m.find(a[x[j]][i])==m.end() || m.find(a[x[j]][i])->second > m.find(x[j])->second){
					p[l] = b[x[j]][i];
					l++;
					b[x[j]][i] = 0;
					for(int g=0; g<3; g++){
						if(a[a[x[j]][i]][g]==x[j]){
							b[a[x[j]][i]][g] = 0;	
						}
					}
				}
			}
			if(!nextPermutation(p, l)){
				j--;
				dir = false;
				continue;
			}
		}
		
		else{
			for(int i=1; i<=3; i++){
				bool t = true;
				for(int g=0; g<3; g++){
					if(b[x[j]][g]==i){
						t = false;
					}
				}
				if(t){
					p[l] = i;
					l++;	
				}
				if(l==q){
					break;
				}
			}
		}
		
		bool e = false;
		do{
			bool f = true;
			int u = 0;
			for(int i=0; i<3; i++){
				if(b[x[j]][i] == 0){
					for(int h=0; h<3; h++){
						if(b[a[x[j]][i]][h]==p[u]){
							f = false;
						}
					}
					u++;
				}
			}
			if(f){
				u = 0;
				for(int i=0; i<3; i++){
					if(b[x[j]][i] == 0){
						b[x[j]][i] = p[u];
						for(int g=0; g<3; g++){
							if(a[a[x[j]][i]][g]==x[j]){
								b[a[x[j]][i]][g] = p[u];	
							}
						}
						if(m.find(a[x[j]][i]) == m.end()){
							w++;
							x[w] = a[x[j]][i];
							m.insert(pair<int, int>(x[w], w));
						}
						u++;
					}
				}
				e = true;
				break;	
			}
			
		} while(nextPermutation(p, l));
		
		if(e){
			j++;
			dir = true;	
		}
		else{
			j--;
			dir = false;
		}
		
	}
	return true;
}

int main(){
	int **a = vytvorPetersen();
	int **b = new int *[10];
	for(int i=0; i<10; i++){
		b[i] = new int[3];
		for(int j=0; j<3; j++){
			b[i][j] = 0;
		}
	}	
	if(existuje3Zafarbenie(a, b, 10)){
		cout << "true\n";
	}
	else{
		cout << "false\n";
	}
}
