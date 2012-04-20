/*
 * arc.h
 *
 *  Created on: 19 avr. 2012
 *      Author: Christophe
 */

#ifndef ARC_H_
#define ARC_H_

using namespace std;
class Arc
{
public:
	Arc(unsigned int capacite, unsigned int flot);
	virtual ~Arc() {};

	bool isSatured() const;
	unsigned int getCapacite() const { return m_capacite; };
	unsigned int getFlot() const { return m_flot; };
	void setCapacite(unsigned int capacite) { m_capacite = capacite; };
	void setFlot(unsigned int flot) { m_flot = flot; };
	friend ostream& operator<<(ostream& out, const Arc& arc);

private:
	unsigned int m_capacite;
	unsigned int m_flot;
};



#endif /* ARC_H_ */
