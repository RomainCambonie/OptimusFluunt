/*
 * arc.cpp
 *
 *  Created on: 19 avr. 2012
 *      Author: Christophe
 */
#include <iostream>
#include "arc.h"

Arc::Arc(unsigned int capacite = 0, unsigned int flot = 0)
{
	if (flot > capacite)
	{
		cerr << "Le flot dépasse la capacité, il sera donc mis à la capacité maximale de l'arc" << endl;
		flot =  capacite;
	}
	m_flot = flot;
	m_capacite = capacite;
}

bool Arc::isSatured() const
{
	if (m_flot == m_capacite) return true;
	return false;
}

ostream& operator<<(ostream& out, const Arc& arc)
{
	out << arc.getCapacite() << "\t" << arc.getFlot();
	return out;
}



