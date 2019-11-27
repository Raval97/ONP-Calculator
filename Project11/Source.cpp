//zadanie 4.2
#include "libFiles.h"
using namespace std;

int main()
{
	// n->liczba linii zawierajacych wyrazenie arytmetyczne
	unsigned int n;
	// typ-> zmienna wskazujaca na to ktora funkcja ma sie wykonac (z INF do ONP czy z ONP do INF)
	string typ; 
	// utworzenie obiektu
	ifstream file;
	// otwarcie pliku
	f_otworzplik(file, "in1.txt");
	file >> n;
	// dla kazdej lini w zaleznosci od typu wykona sie odpowiednia funkcja
	for (int i = 0; i < n; i++)
	{
		cout << i+1 << " ";
		file >> typ;
		if (typ == "INF:")
			f_from_INF_to_ONP(file);
		else if (typ == "ONP:")
			f_from_ONP_to_INF(file);
		else cout << "zly zapis";
		cout <<endl;
	}
	file.close();

	getchar();
	cin.ignore();
	return 0;
}
