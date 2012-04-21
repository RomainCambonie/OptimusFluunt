#ifndef FLOT2_H_
#define FLOT2_H_

#include <string>
#include <map>
#include <list>
#include <set>
#include <climits>

#include "arc.h"

using namespace std;

class Flot
{

public:
	Flot(string filename = "para.txt");
	virtual ~Flot() {};

	/**
	 * @brief: Détermine si l'arc allant de sommetA à sommetB est saturé ou non
	 * @return: true si l'arc est saturé, false sinon
	 * */
	bool isSatured(unsigned int sommetA, unsigned int sommetB) const;

	/**
	 * @brief: Affiche le flot pour debugage
	 */
	void display() const;

	/**
	 * @brief: Exécute l'algorithme de Bloch pour rendre le flot complet
	 * @param[in]:
	 * @return:
	 */
	void executeBloch();

	/**
	 * @brief: Exécute l'algorithme de Ford-Fulkerson pour rendre le flot maximal
	 * @param[in]:
	 * @return:
	 */
	void executeFordFulkerson();

	/**
	 * @brief: Détermine l'arc de capacité maximum
	 * @param[in]:
	 * @return: la capacité maximum
	 */
	unsigned int getCapaciteMax();

private:
	string m_somEntree;
	string m_somSortie;
	unsigned int m_nbSommets; // Nb de sommets dans le flot
	map<string, map<string, Arc> > m_matAdj; // Stockage du flot sous forme de graphe (matrice d'adjacence)

	/**
		 * @brief: Recherche d'un chemin de 'start' à 'end' en passant par les arcs spécifiés
		 * @param[in]:sommet de départ, sommet d'arrivée, arcs autorisés
		 * @return:
		 */
	list<string> blochSearchPath(const string start, const string end, map<string, set<string> > usableArcs);
};

#endif /* FLOT2_H_ */
