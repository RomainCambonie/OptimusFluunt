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
	map<string, set<string> > usableArcs; //Liste des arcs practicables
	list<string> path;
	string keyStart, keyEnd;

	//Liste des arcs praticables
	for (map<string, map<string, Arc> >::const_iterator it = m_matAdj.begin(); it != m_matAdj.end(); it++)
	{
		for (map<string, Arc>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
				if (it2->second.getCapacite() - it2->second.getFlot() > 0)
					usableArcs[it->first].insert(it2->first);
		}
	}
	//TODO nettoyage des arcs non praticables

	//Itérations de l'algorithme
	while (!usableArcs.empty())
	{
		// On choisi l'arc avec la plus faible capacité résiduelle
		unsigned int minResCap = UINT_MAX;
		for(map<string, set<string> >::iterator it = usableArcs.begin(); it != usableArcs.end(); it++)
		{
			for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
			{
				unsigned int resCap = m_matAdj[it->first][*it2].getCapacite() - m_matAdj[it->first][*it2].getFlot();
				if (resCap < minResCap)
				{
					minResCap = resCap;
					keyEnd = it->first;
					keyStart = *it2;
				}
			}
		}

		//On détermine un chemin de E à S passant par l'arc et on met à jour le flot
		path = blochSearchPath(m_somEntree, keyStart, usableArcs);
		list<string> tempPath = blochSearchPath(keyEnd, m_somSortie, usableArcs);
		path.splice(path.end(), tempPath);

		//Elimination des circuits, etc
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

list<string> Flot::blochSearchPath(const string start, const string end, map<string, set<string> > usableArcs)
{
	list<string> path;
	map<string, map<string, Arc>::iterator > exploredVertices;

	path.push_back(start);
	exploredVertices[start] = m_matAdj[start].begin();

	while (path.back() != end)
	{
		bool goOn = true;
		//Choix de l'arc praticable suivant
		while ((exploredVertices[path.back()] != m_matAdj[path.back()].end()) && goOn)
		{
			if (usableArcs[path.back()].count(exploredVertices[path.back()]->first) == 0)
				exploredVertices[path.back()]++;
			else
				goOn = false;
		}
		//Si c'est un cul-de-sac, on dépile
		if (exploredVertices[path.back()] == m_matAdj[path.back()].end())
		{
			path.pop_back();
			if(!path.size())
				return path;
			else if (exploredVertices[path.back()] != m_matAdj[path.back()].end())
				exploredVertices[path.back()]++;
		}
		//Sinon, on empile
		else
		{
			path.push_back(exploredVertices[path.back()]->first);
			if (exploredVertices.count(path.back()))
			{
				if (exploredVertices[path.back()] != m_matAdj[path.back()].end())
					exploredVertices[path.back()]++;
			}
			else
				exploredVertices[path.back()] = m_matAdj[path.back()].begin();
		}
	}

	return path;
}
