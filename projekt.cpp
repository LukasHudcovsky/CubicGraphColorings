#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

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

bool nextPermutation(int *p, int n){
	if(n==2 && p[0]==p[1]){
		return false;
	}
	if(n==3 && p[0]==p[1] && p[1]==p[2] && p[2]==p[0]){
		if(p[0]==3){
			return false;
		}
		else{
			p[0]++;
			p[1]++;
			p[2]++;
			return true;
		}
	}
	
	int x = -1;
	for(int i=n-1; i>0; i--){
		if(p[i-1]<p[i]){
			x = i-1;
			break;
		}
	}
	if(x==-1){
		if(n==2){
			p[0] = 6-p[0]-p[1];
			p[1] = p[0];
			return true;
		}
		if(n==3){
			p[0] = 1;
			p[1] = 1;
			p[2] = 1;
			return true;
		}
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

bool existuje3Zafarbenie(int **a, int **b, int k, int v, vector<int> &r){
	int *x = new int[k];
	map<int, int> m;
	int j = 0;
	int w = 0;
	x[0] = v;
	m.insert(pair<int, int>(v, 0));
	
	bool dir = true;
	while(j < k){
		
		if(j < 0){
			delete b;
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
					int pocet[3] = {0, 0, 0};
					for(int i=0; i<k; i++){
						if(b[i][0]==b[i][1] && b[i][2]==b[i][1]){
							pocet[b[i][0]-1]++;
							r.push_back(i);
						}
					}
					if(pocet[0]==pocet[1] && pocet[2]==pocet[1]){
						break;	
					}
					else{
						r.clear();
						j--;
						dir = false;
						continue;
					}
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
		
		else if(q==1){
			p[l] = 3 - (b[x[j]][0]+b[x[j]][1]+b[x[j]][2])%3;
			l++;
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
					int zero = 0;
					int sum = 0;
					for(int h=0; h<3; h++){
						if(b[a[x[j]][i]][h]==0){
							zero++;
						}
						sum += b[a[x[j]][i]][h];
					}
					if(zero == 1 && (sum+p[u])%3 != 0){
						f = false;
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

bool jeKazdyVrcholSilny(int **a, int **b, int k){
	set<int> set1;
	set<int> set2;
	vector<int> r;
	vector<int>::iterator it;
	for(int i=0; i<k; i++){
		set1.insert(i);
	}
	
	while(!set1.empty()){
		bool t = existuje3Zafarbenie(a, b, k, *set1.begin(), r);
		if(!t){
			return false;
		}
		for(it = r.begin(); it != r.end(); it++){
			if(set1.find(*it) != set1.end()){
				set2.insert(*it);
			}
		}
		set1.swap(set2);
		set2.clear();
		r.clear();
		for(int i=0; i<k; i++){
			if((b[i][0]+b[i][1]+b[i][2])%3 != 0){
				cout << "CHYBA!\n";
			}
			for(int j=0; j<3; j++){
				if(b[i][j]>3 || b[i][j]<1){
					cout << "CHYBA!\n";
				}
				b[i][j] = 0;
			}
		}
	}
	
	return true;
}

int main(){
	FILE *fr;
	int c, x;
	int q = -1;
	int count = 0;
	vector<int> r;
	
	for(int k=18; k<=30; k+=2){
		char *str = new char[7];
		sprintf(str, "SC4.%d", k);
		fr = fopen(str, "r");
		fscanf(fr, "%d", &c);
		int **a = vytvorMaticu(k, 3);
		int **b = vytvorMaticu(k, 3);
		
		cout << k << " vrcholov: ";
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
			
		    if(!jeKazdyVrcholSilny(a, b, k)){
				q = count;
			}
			
			/*if(!existuje3Zafarbenie(a, b, k, 0, r)){
				q = count;
			}	*/
			count++; 
		}
		if(q==-1){
			cout << "Vsetky grafy su vyhovujuce\n";
		}
		else{
			cout << "Graf " << q << " je protipriklad\n";
			q = -1;
		}
		zmazMaticu(a, k);
		zmazMaticu(b, k); 
		fclose(fr);
	}
		
}
