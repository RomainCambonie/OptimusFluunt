#include "flot2.h"
#include <iostream>

int main(int argc, char*argv[])
{
	string filename = "";
	cout << "Veuillez indiquer le nom du fichier de paramétrage (par défaut para.txt):" << endl;
	cin >> filename;
	Flot test(filename);
	test.display();
	test.executeBloch();
	test.display();
	cout << "Fin du programme." << endl;
}
