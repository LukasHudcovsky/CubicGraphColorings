#include <vector>
#include <set>

	/* Funkcia dostane n-ticu (kde n je medzi 1 a 3) cisel z {1, 2, 3} v poli perm, 
	ktore reprezentuju este fixne nezafarbene hrany vrchola. Vygeneruje dalsiu permutaciu (v lexikografickom poradi) pola perm,
	tak aby sa po pridani uz zafarbenych hran k danemu vrcholu boli vsetky tri farby rozne. 
	Ak sa to da tak vrati true, inak s polom nic nerobi a vrati false */
bool nextPermutationRegular(int *perm, int n);


	/* Funkcia dostane n-ticu (kde n je medzi 1 a 3) cisel z {1, 2, 3} v poli perm, 
	ktore reprezentuju este fixne nezafarbene hrany vrchola. Vygeneruje dalsiu permutaciu (v lexikografickom poradi) pola perm,
	tak aby sa po pridani uz zafarbenych hran k danemu vrcholu boli vsetky tri farby rozne, alebo vsetky tri farby rovnake. 
	Ak sa to da tak vrati true, inak s polom nic nerobi a vrati false */
bool nextPermutationSpecial(int *perm, int n);



bool zafarbenieKostra(int **a, int **b, int k, int start, std::set<int> &same_color, std::set<int> strong, std::set<int> weak);


	/*Funkcia pre dany kubicky graf pomocou kostrovej funkcie 3ZafarbenieKostra zisti ci pre neho existuje specialne zafarbenie hran z Froncekovej 
	hypotezy. To je take farbenie farbami 1,2,3 kde okolo kazdeho vrchola su bud tri hrany roznej farby, alebo tri hrany rovnakej farby. 
	Navyse musi platit ze je rovnaky pocet vrcholov ktore maju vsetky hrany farby 1, farby 2 a farby 3*/
bool existujeSpecialne3Zafarbenie(int **a, int **b, int k);


	/*Funkcia pre dany kubicky graf pomocou kostrovej funkcie 3ZafarbenieKostra zisti ci pre neho existuje specialne zafarbenie hran z Froncekovej 
	hypotezy, take ze si navyse vieme pre hociktory jeden vrchol povedat ze chceme aby jeho hrany mali rozne farby.*/
bool jeKazdyVrcholSilny(int **a, int **b, int k);


	/*Funkcia pre dany kubicky graf pomocou kostrovej funkcie 3ZafarbenieKostra zisti ci pre neho existuje specialne zafarbenie hran z Froncekovej 
	hypotezy, take ze si navyse vieme pre hociktore dva vrcholy ze chceme aby hrany okolo 
	kazdeho z tychto mali rozne farby.*/
bool jeKazdaDvojicaSilna(int **a, int **b, int k);


	/*Funkcia pre dany kubicky graf pomocou kostrovej funkcie 3ZafarbenieKostra zisti ci pre neho existuje specialne zafarbenie hran z Froncekovej 
	hypotezy, take ze si navyse vieme pre hociktory jeden vrchol povedat ze chceme aby jeho hrany mali rovnaku farbu.*/
bool jeKazdyVrcholSlaby(int **a, int **b, int k);

