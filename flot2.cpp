/*
 * flot2.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: Christophe
 */
#include "flot2.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

Flot::Flot(string filename)
{
    ifstream file(filename.c_str(), ios::in);
    if(file)
    {
    	m_nbSommets = 0;

    	// TRAITEMENT DES SOMMETS D'ENTREE ET SORTIE
    	if (file.good())
    	{
    		file >> m_somEntree >> m_somSortie;
    		m_nbSommets = 2;
    	}
    	else return;

    	//TRAITEMENT DES SOMMETS "NORMAUX"
    	string sommetDepart, sommetArrivee;
    	unsigned int capacite;
    	while(file.good())
    	{
    		file >> sommetDepart >> sommetArrivee >> capacite;
    		Arc tmpArc(capacite, 0);
    		m_matAdj[sommetDepart].insert(pair<string, Arc> (sommetArrivee, tmpArc));
    	}
    	file.close();
    }
    else cerr << "Erreur à l'ouverture du fichier \"" << filename <<"\" ! "<< endl;
}

bool Flot::isSatured(unsigned int sommetA, unsigned int sommetB) const
{
	// TODO Gérer les erreurs avec des exceptions
	string strA = intToString(sommetA);
	string strB = intToString(sommetB);

	map<string, map<string, Arc> >::const_iterator row = m_matAdj.find(strA);
	if (row == m_matAdj.end()) cerr << "Aucun arc ne part de " << sommetA << "."; return false;

	map<string, Arc>::const_iterator col = (row->second).find(strB);
	if (col == (row->second).end()) cerr << "Aucun arc partant de " << sommetA << "n'arrive à " << sommetB << "."; return false;
	return (col->second).isSatured();
	return false;
}

void Flot::display() const
{
	for(map<string, map<string, Arc> >::const_iterator it = m_matAdj.begin(); it != m_matAdj.end(); ++it)
	{
		for (map<string, Arc>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			cout << it->first << "\t" << it2->first << "\t" << it2->second << endl;
		}
	}
}

void Flot::executeBloch()
{
	// On met le flot de tous les arcs à 0.
	for(map<string, map<string, Arc> >::iterator it = m_matAdj.begin(); it != m_matAdj.end(); ++it)
	{
		for (map<string, Arc>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			(it2->second).setFlot(0);
		}
	}

	unsigned int capResiMin = getCapaciteMax();
	string keyDep, keyArr;

	for(map<string, map<string, Arc> >::iterator it = m_matAdj.begin(); it != m_matAdj.end(); ++it)
	{
		for (map<string, Arc>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			unsigned int comp = (it2->second).getCapacite() - (it2->second).getFlot();
			if (comp < capResiMin)
			{
				capResiMin = comp;
				keyDep = it->first;
				keyArr = it2->first;
			}
		}
	}
}


void Flot::executeFordFulkerson()
{

}

unsigned int Flot::getCapaciteMax()
{
	unsigned int capMax = 0;
	for(map<string, map<string, Arc> >::iterator it = m_matAdj.begin(); it != m_matAdj.end(); ++it)
	{
		for (map<string, Arc>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			if ((it2->second).getCapacite() > capMax) capMax = (it2->second).getCapacite();
	}
	return capMax;
}
