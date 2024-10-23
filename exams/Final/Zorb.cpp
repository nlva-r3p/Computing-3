// The Zorb game - the base class
#include <iostream>
#include <string>
using namespace std;
class Zorb {
    public:
         // value constructor
         Zorb(int p, int t) : _power(p), _team_id(t) {}
         bool operator< (const Zorb&) const;
         Zorb operator+ (const Zorb&) const;
         int getPower() { return _power; }
         int getTeamID() { return _team_id; }
    friend ostream& operator<< (ostream&, const Zorb&);
    private:
         int _power;
         int _team_id;
};
// operator< usage: Zorb z1, z2; if (z1 < z2) {}
// In the expression z1<z2, "this" Zorb is z1 (the left operand).
// Returns true if "this" Zorb (left operand) has a different team ID
// AND greater power than the other Zorb (right operand).
bool Zorb::operator< (const Zorb& z) const {
    if (this->_team_id == z._team_id)
         return false;
    else
         return this->_power < z._power;
}

// operator+ usage: Zorb z3 = z1 + z2;
// Constructs a new Zorb (here assigned to z3) with the combined power
// of the original two Zorbs (z1 and z2), and the team ID of the stronger of
// the original two Zorbs.
// In the expression z1+z2, "this" Zorb is z1 (the left operand).
Zorb Zorb::operator+ (const Zorb& z) const {
    return Zorb(this->_power + z._power,
                ((*this < z) ? z._team_id : this->_team_id) );
}
