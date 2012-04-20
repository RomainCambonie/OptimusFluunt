#ifndef FLOT2_H_
#define FLOT2_H_

#include <string>
#include <map>
#include "arc.h"
using namespace std;

class Flot
{

public:
	Flot(string filename = "para.txt");
	virtual ~Flot() {};

	/**
	 * @brief: D�termine si l'arc allant de sommetA � sommetB est satur� ou non
	 * @return: true si l'arc est satur�, false sinon
	 * */
	bool isSatured(unsigned int sommetA, unsigned int sommetB) const;

	/**
	 * @brief: Affiche le flot pour debugage
	 */
	void display() const;

	/**
	 * @brief: Ex�cute l'algorithme de Bloch pour rendre le flot complet
	 * @param[in]:
	 * @return:
	 */
	void executeBloch();

	/**
	 * @brief: Ex�cute l'algorithme de Ford-Fulkerson pour rendre le flot maximal
	 * @param[in]:
	 * @return:
	 */
	void executeFordFulkerson();

	/**
	 * @brief: D�termine l'arc de capacit� maximum
	 * @param[in]:
	 * @return: la capacit� maximum
	 */
	unsigned int getCapaciteMax();

private:
	string m_somEntree;
	string m_somSortie;
	unsigned int m_nbSommets; // Nb de sommets dans le flot
	map<string, map<string, Arc> > m_matAdj; // Stockage du flot sous forme de graphe (matrice d'adjacence)
};

#endif /* FLOT2_H_ */
