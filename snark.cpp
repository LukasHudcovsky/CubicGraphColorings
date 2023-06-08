#include "snark.h"
#include <vector>
#include <set>
#include <map>
#include <iostream>

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}


bool nextPermutationRegular(int *perm, int n){
	int x = -1;
	for(int i=n-1; i>0; i--){
		if(perm[i-1]<perm[i]){
			x = i-1;
			break;
		}
	}
	if(x==-1){
		return false;
	}
	
	int y;
	for(int i=x+1; i<n; i++){
		if(perm[i]>perm[x]){
			y = i;
		}
		else{
			break;
		}
	}
	
	swap(perm[x], perm[y]);
	
	for(int i=x+1; i<n-i+x; i++){
		swap(perm[i], perm[n-i+x]);
	}
	return true;
}


bool nextPermutationSpecial(int *perm, int n){
	if(n==2 && perm[0]==perm[1]){
		return false;
	}
	if(n==3 && perm[0]==perm[1] && perm[1]==perm[2] && perm[2]==perm[0]){
		if(perm[0]==3){
			return false;
		}
		else{
			perm[0]++;
			perm[1]++;
			perm[2]++;
			return true;
		}
	}
	
	int x = -1;
	for(int i=n-1; i>0; i--){
		if(perm[i-1]<perm[i]){
			x = i-1;
			break;
		}
	}
	if(x==-1){
		if(n==2){
			perm[0] = 6-perm[0]-perm[1];
			perm[1] = perm[0];
			return true;
		}
		if(n==3){
			perm[0] = 1;
			perm[1] = 1;
			perm[2] = 1;
			return true;
		}
		return false;
	}
	
	int y;
	for(int i=x+1; i<n; i++){
		if(perm[i]>perm[x]){
			y = i;
		}
		else{
			break;
		}
	}
	
	swap(perm[x], perm[y]);
	
	for(int i=x+1; i<n-i+x; i++){
		swap(perm[i], perm[n-i+x]);
	}
	return true;
}


bool zafarbenieKostra(int **a, int **b, int k, int start, std::set<int> &same_color, std::set<int> strong, std::set<int> weak){
	int *x = new int[k];
	std::map<int, int> m;
	int j = 0;
	int w = 0;
	x[0] = start;
	m.insert(std::pair<int, int>(start, 0));
	
	bool dir = true;
	while(j < k){
		
		if(j < 0){
			delete[] x;
			return false;
		}
		
		//vypocitanie kolko hran vrchola je este nezafarbenych
		int q=0;
		for(int i=0; i<3; i++){
			if(b[x[j]][i] == 0){
				q++;
			}
		}
		
		int *perm = new int[3];
		int l = 0;
		if(q==0){
			if(dir){
				if(strong.find(x[j])!=strong.end() && b[x[j]][0]==b[x[j]][1] && b[x[j]][2]==b[x[j]][1]){
					j--;
					dir = false;
					delete[] perm;
					continue;
				}
				
				if(weak.find(x[j])!=weak.end() && b[x[j]][0]!=b[x[j]][1]){
					j--;
					dir = false;
					delete[] perm;
					continue;
				}
				
				if(j==k-1){
					int pocet[3] = {0, 0, 0};
					for(int i=0; i<k; i++){
						if(b[i][0]==b[i][1] && b[i][2]==b[i][1]){
							if(strong.find(i)!=strong.end()){
								pocet[0] = -1;
								break;
							}
							pocet[b[i][0]-1]++;
							same_color.insert(i);
						}
						else if(weak.find(i)!=weak.end()){
							pocet[0] = -1;
							break;
						}
					}
					if(pocet[0]==pocet[1] && pocet[2]==pocet[1]){
						delete[] perm;
						break;	
					}
					else{
						same_color.clear();
						j--;
						dir = false;
						delete[] perm;
						continue;
					}
				}
				
				else{
					j++;
					delete[] perm;
					continue;
				}	
			}
			
			for(int i=0; i<3; i++){
				if(m.find(a[x[j]][i])==m.end() || m.find(a[x[j]][i])->second > m.find(x[j])->second){
					perm[l] = b[x[j]][i];
					l++;
					b[x[j]][i] = 0;
					for(int g=0; g<3; g++){
						if(a[a[x[j]][i]][g]==x[j]){
							b[a[x[j]][i]][g] = 0;	
						}
					}
				}
			}
			if((strong.find(x[j])!=strong.end() && !nextPermutationRegular(perm, l)) || !nextPermutationSpecial(perm, l)){
				j--;
				dir = false;
				delete[] perm;
				continue;
			}
			
		}
		
		else if(q==1){
			perm[l] = 3 - (b[x[j]][0]+b[x[j]][1]+b[x[j]][2])%3;
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
					perm[l] = i;
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
					if(zero == 1 && (sum+perm[u])%3 != 0){
						f = false;
					}
					u++;
				}
			}
			if(f){
				u = 0;
				for(int i=0; i<3; i++){
					if(b[x[j]][i] == 0){
						b[x[j]][i] = perm[u];
						for(int g=0; g<3; g++){
							if(a[a[x[j]][i]][g]==x[j]){
								b[a[x[j]][i]][g] = perm[u];	
							}
						}
						if(m.find(a[x[j]][i]) == m.end()){
							w++;
							x[w] = a[x[j]][i];
							m.insert(std::pair<int, int>(x[w], w));
						}
						u++;
					}
				}
				e = true;
				break;	
			}
			
		} while((nextPermutationSpecial(perm, l) && strong.find(x[j])==strong.end()) || nextPermutationRegular(perm, l));
		
		if(e){
			j++;
			dir = true;
		}
		else{
			j--;
			dir = false;
		}
		
		delete[] perm;
	}
	
	delete[] x;
	return true;
}


bool jeKazdyVrcholSilny(int **a, int **b, int k){
	std::set<int> emptySet;
	std::set<int> set1;
	std::set<int> set2;
	std::set<int> r;
	std::set<int>::iterator it;
	for(int i=0; i<k; i++){
		set1.insert(i);
	}
	
	while(!set1.empty()){
		bool t = zafarbenieKostra(a, b, k, *set1.begin(), r, emptySet, emptySet);
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
				std::cout << "CHYBA!\n";
			}
			for(int j=0; j<3; j++){
				if(b[i][j]>3 || b[i][j]<1){
					std::cout << "CHYBA!\n";
				}
				b[i][j] = 0;
			}
		}
	}
	
	return true;
}

bool jeKazdaDvojicaSilna(int **a, int **b, int k){
	std::set<int> emptySet;
	std::set<std::pair<int,int> > set1;
	std::set<std::pair<int,int> > set3;
	std::set<int> set2;
	std::set<int> r;
	std::set<std::pair<int,int> >::iterator it;
	for(int i=0; i<k; i++){
		for(int j=i+1; j<k; j++){
			set1.insert(std::pair<int,int>(i, j));
		}
	}
	set2.insert(0);
	set2.insert(1);
	int start = 0;
	
	while(!set1.empty()){
		bool t = zafarbenieKostra(a, b, k, start, r, set2, emptySet);
		if(!t){
			return false;
		}
		for(it = set1.begin(); it != set1.end(); it++){
			if(r.find((*it).first)!=r.end() || r.find((*it).second)!=r.end()){
				set3.insert(*it);
			}
		}

		set1.swap(set3);
		set3.clear();
		set2.clear();
		r.clear();
		if(!set1.empty()){
			set2.insert((*set1.begin()).first);
			set2.insert((*set1.begin()).second);
		}
		
		for(int i=0; i<k; i++){
			if((b[i][0]+b[i][1]+b[i][2])%3 != 0){
				std::cout << "CHYBA!\n";
			}
			for(int j=0; j<3; j++){
				if(b[i][j]>3 || b[i][j]<1){
					std::cout << "CHYBA!\n";
				}
				b[i][j] = 0;
			}
		}
	}
	
	return true;
}

bool jeKazdyVrcholSlaby(int **a, int **b, int k){
	std::set<int> emptySet;
	std::set<int> set1;
	std::set<int> set2;
	std::set<int> r;
	std::set<int>::iterator it;
	for(int i=0; i<k; i++){
		set1.insert(i);
	}
	set2.insert(k-1);
	int start = 0;
	
	while(!set1.empty()){
		bool t = zafarbenieKostra(a, b, k, start, r, emptySet, set2);
		if(!t){
			return false;
		}
		for(it = r.begin(); it != r.end(); it++){
			if(set1.find(*it) != set1.end()){
				start = *it;
				set1.erase(*it);
			}
		}

		set2.clear();
		r.clear();
		if(!set1.empty()) set2.insert(*set1.begin());
		
		for(int i=0; i<k; i++){
			if((b[i][0]+b[i][1]+b[i][2])%3 != 0){
				std::cout << "CHYBA!\n";
			}
			for(int j=0; j<3; j++){
				if(b[i][j]>3 || b[i][j]<1){
					std::cout << "CHYBA!\n";
				}
				b[i][j] = 0;
			}
		}
	}
	
	return true;
}

bool existujeSpecialne3Zafarbenie(int **a, int **b, int k){
	std::set<int> emptySet;
	std::set<int> r;
	return zafarbenieKostra(a, b, k, 0, r, emptySet, emptySet);
}

