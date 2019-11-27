#include "libFiles.h"

//algorytm przeksztalcania wyrazen arytmetycznych i instrukcji przypisania z INF do ONP    file-plik bedacy zrodlem danych
void f_from_INF_to_ONP(ifstream &file)
{
	// text->przechowuje wyrazenie arytmetyczne  a->zmienna wskazujaca na czesci skladowe zmiennej text   out->rozwiazanie
	string text, a, out;
	//tworzenie stosu przechowujacego operatory
	std::stack < std::string > stos;
	// pobranie z pliku wyrazenia arytmetycznego
	getline(file, text);
	// dlu->dlugosc wyrazenia arytmetycznego
	int dlu = text.size();
	// wyswietlenie poczatku rozwiazania
	cout << "INF:" << text;
	for (int i = dlu; i < 30; i++)
		cout << " ";
	cout << "\t ONP: ";
	if (f_poprawnosc(text, dlu, "INF") == false)
		cout << "ERROR";
	else
	{
		for (int i = 0; i < dlu; i++)
		{
			// petla wykona sie w zaleznosci od symbolu
			switch (text[i])
			{
				// dla pauzy nie wykona sie nic
			case ' ': break;
				// nawias otwarty zostanie dodany do stosu
			case '(':
				stos.push("(");
				break;
				// przy nawiasie zamknietym zostana wypisane wszystkie operatory ze stosu az do napotkania otwarcia nawiasu
			case ')':
				while (stos.top() != "(")
				{
					out += stos.top();
					stos.pop();
				}
				// nawias otwarcia zostanie usuniety ze stosu
				stos.pop();
				break;
				// Jeœli odczytanym elementem jest inny operator, to:
				// dopóki na stosie jest jakiœ juz jakis operator i:
				//	-odczytany operator ma ³¹cznoœæ lewostronn¹ oraz priorytet ni¿szy lub równy operatorowi na stosie,
				//	-lub odczytany operator ma ³¹cznoœæ prawostronn¹ i priorytet ni¿szy od operatora na stosie,
				// to pobieramy ze stosu operator i przesy³amy go na wyjœcie
				// Po tej operacji odczytany operator umieszczamy na stosie.
			case '=':;
			case '<':;
			case '>':;
			case '+':;
			case '-':;
			case '*':;
			case '/':;
			case '%':;
			case '^':;
			case '~':
				a = text[i];
				if (!stos.empty())
				{
					while ((stos.top() != "(") &&
						(((f_ope_lacz(a) == 1) && (f_ope_prio(a) < f_ope_prio(stos.top())))
					  || ((f_ope_lacz(a) == 2) && (f_ope_prio(a) <= f_ope_prio(stos.top())))))
					{
						out += stos.top();
						stos.pop();
						if (stos.empty())
							break;
					}
				}
				stos.push(a);
				break;
				// jezeli symbolem jest litera to przesylamy ja na wyjscie
			default:  out += text[i];
				break;
			}
			// wypisane zostana wszystkie pozostale operatory na stosie
			if (i == (dlu - 1))
			{
				while (!stos.empty())
				{
					out += stos.top();
					stos.pop();
				}
			}
		}
		// wyswietlenie rozwiazania
		cout << out;
	}
}
//algorytm przeksztalcania wyrazen arytmetycznych i instrukcji przypisania z ONP do INF     file-plik bedacy zrodlem danych
void f_from_ONP_to_INF(ifstream &file)
{
	// tworzenie stosu przechowujacego operatory
	std::stack < std::string > stos;
	// tworzenie stosu przechowujacego priorytety zmiennych pomocniczych b i c w zaleznosci od wystepujacego operatora
	std::stack < int > stos_prio;
	// text->przechowuje wyrazenie arytmetyczne  a->zmienna wskazujaca na czesci skladowe zmiennej text  b,c->zmienne pomocniecze laczace znaki
	string text, a, b, c;
	// pobranie z pliku wyrazenia arytmetycznego
	getline(file, text);
	// dlu->dlugosc wyrazenia arytmetycznego
	int dlu = text.size();
	// wyswietlenie poczatku rozwiazania
	cout << "ONP:" << text;
	for (int i = dlu; i < 30; i++)
		cout << " ";
	cout << "\t INF: ";
	if (f_poprawnosc(text, dlu, "ONP") == false)
		cout << "ERROR";
	else
	{
		for (int i = 0; i < dlu; i++)
		{
			a = text[i];
			// petla wykona sie w zaleznosci od symbolu
			switch (text[i])
			{
				// dla pauzy i nawiasow nie wykona sie nic
			case ' ':;
			case '(':;
			case ')':
				break;
				// dla operatorow: gdy priorytet operatora  jest wiêkszy od priorytetu elementu bedacego w glowie stosu 
				// to element ten bierzemy w nawias, a takze jezeli priorytet operatora jest wiêkszy lub równy od priorytetu 
				// elementu bedacego przed glowa stosu to element ten tez bierzemy w nawias
			case '=':;
			case '<':;
			case '>':;
			case '+':;
			case '-':;
			case '*':;
			case '/':;
			case '%':;
			case '^':
				// gdy priorytet operatora  jest wiêkszy od priorytetu elementu bedacego w glowie stosu to element ten bierzemy w nawias
				// zmienna b zawiera w nawiasie wyrazenie ktore jest pozniej usuwane ze stosu
				if (f_ope_prio(a) >= stos_prio.top())
				{
					b = "(" + stos.top() + ")"; stos.pop();
				}
				// w przeciwnym razie zmienna b jest rowna wyrazeniu ktore pozniej jest usuwane ze stosu
				else
				{
					b = stos.top(); stos.pop();
				}
				// jezeli priorytet operatora jest wiêkszy lub równy od priorytetu elementu bedacego przed glowa stosu to element ten tez bierzemy w nawias
				// zmienna c zawiera w nawiasie wyrazenie ktore jest pozniej usuwane ze stosu
				if (f_ope_prio(a) > stos_prio.top())
				{
					c = "(" + stos.top() + ")"; stos.pop();
				}
				// w przeciwnym razie zmienna c jest rowna wyrazeniu ktore pozniej jest usuwane ze stosu
				else
				{
					c = stos.top(); stos.pop();
				}
				// w zaleznosci od zasad opisanych wyzej zmienna b przyjmuje wartosc dwoch ostatnich elementow stosu (czyli b oraz c) + ewentualne nawiasy
				b = c + text[i] + b;
				// b jest przypisane do stosu wyrazen, a do stosu priorytetow zamieniona zostaje glowa na wartosc rowna badanemu operatorowi
				stos.push(b);
				stos_prio.pop(); stos_prio.push(f_ope_prio(a));
				break;
				// jezeli operatorem jest ~ to do glowy stosu zostaje przed wyrazeniem dopisany operator (w celu poprawnosci kodu)
			case '~':
				stos.top() = a + stos.top();
				// jezeli ~ jest ostatnim znakiem to zostanie dopisany przed rozwiazaniem
				if (i == dlu - 1)
					b = stos.top() + b;
				break;
				// jezeli symbolem jest litera to zostanie dodana do obydwu stosow
			default:   stos.push(a); stos_prio.push(7); //b = b + text[i];
				break;
			}
		}
		cout << b;
	}
}
// sprawdza poprawnosc wyrazenia arytmetycznego, zwraca z=true jezeli jest poprawne
bool f_poprawnosc(string text, int n, string notacja)
{
	bool z = true;
	// ope->ilosc operatorow, lit->ilosc liter, a->zmienna pomocnicza podczas liczenia nawiasow
	int ope = 0, lit = 0, a = 0;
	// petla zlicza operatory
	for (int i = 0; i < n; i++)
	{
		if ((text[i] == '+') || (text[i] == '-') || (text[i] == '%') ||
			(text[i] == '*') || (text[i] == '/') || (text[i] == '^') ||
			(text[i] == '<') || (text[i] == '>') || (text[i] == '='))
		{
			ope++;
			// dla notacji ONP operator moze wystapic dopiero po dwoch literach (wyjatkiem jest znak ~)
			if (notacja == "ONP")
				if (ope >= lit)
					z = false;
		}
		// petla zlicza litery
		else if (isalpha(text[i]))
			lit++;
		// jezeli w wyrazenie wystepuje podane nizej znki to wyrazenie jest nie poprawne
		else if ((text[i] == '|') || (text[i] == '[') || (text[i] == ']') || (text[i] == '!') || (text[i] == '&') || (text[i] == '_'))
			z = false;
		// dla notacji INF w razie wystepowania kazdy nawias musi buc otwarty i zamkniety
		if (notacja == "INF")
		{
			if (text[i] == '(')
				a++;
			if (text[i] == ')')
			{
				// sprawdzenie czy nawias zostal otwarty
				if (a == 0)
				{
					z = false; break;
				}
				else a--;
			}
		}
	}
	// sprawdzenie czy nawias zostal zamkniety
	if (a > 0)
		z = false;
	// operatorow powinno byc o jeden mniej od ilosci liter (z wyjatkiem znaku ~)
	if ((ope >= lit) || (lit - 1 > ope))
		z = false;
	return z;
}
// funkcja zwraca piorytet w w zaleznosci od operatora->zmienna c
int f_ope_prio(string c)
{
	if (c == "=") return 1;
	else if ((c == "<") || (c == ">")) return 2;
	else if ((c == "-") || (c == "+")) return 3;
	else if ((c == "*") || (c == "/") || (c == "%")) return 4;
	else if (c == "^") return 5;
	else if (c == "~") return 6;
	else return 7;
}
// funkcja zwrca 1-dla operatorow prawostronnych lub 2-dla operatorow lewostronnych
int f_ope_lacz(string c)
{
	if ((c == "=") || (c == "~") || (c == "^")) return 1;
	else if ((c == "<") || (c == ">") || (c == "-") || (c == "+")
		|| (c == "*") || (c == "/") || (c == "%")) return 2;
	else cout << "niepoprawny operator";
}
//otwiera plik o podanej nazwie
void f_otworzplik(ifstream &plik, string nazwa)
{
	plik.open(nazwa);
	if (!plik)
	{
		cout << "\n nie udalo sie otworzyc pliku !";
		cin.ignore();
		getchar();
		exit(0);
	}
}