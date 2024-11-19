// The Zorb game - the base class
#include <iostream>
#include <string>
using namespace std;
class Zorb {
    public:
         // value constructor
         Zorb(int p, int t) : _power(p), _team_id(t) {}
         virtual bool operator< (const Zorb&) const;
         virtual Zorb operator+ (const Zorb&) const;
         int getPower() const { return _power; }
         int getTeamID() const { return _team_id; }
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

std::ostream& operator<< (std::ostream& os, const Zorb& z) {
    os << "Zorb(Power: " << z.getPower() << ", TeamID: " << z.getTeamID() << ")";
    return os;
}

class KiloZorb : public Zorb {
     public:
        KiloZorb(int p, int t) : Zorb(p * 1000, t) {}

        bool operator< (const Zorb& z) const override {
            return Zorb::operator<(z);
        }

        Zorb operator+ (const Zorb& z) const override {
            //Zorb temp = Zorb::operator+(z);
            int sumPower = this->getPower() + z.getPower();
            int newTeamID = ((*this < z) ? z.getTeamID() : this->getTeamID());
            return KiloZorb(sumPower / 1000, newTeamID);
        }
};

int main() {
    Zorb zorb1(10, 1);  
    Zorb zorb2(1000, 2);  

    KiloZorb kzorb1(20, 3); 
    KiloZorb kzorb2(5, 4); 
    
    // For some behavioral testings
    Zorb* z1 = &zorb1;
    Zorb* z2 = &zorb2;
    Zorb* kz1 = &kzorb1;
    Zorb* kz2 = &kzorb2;

    std::cout << "Zorb1: " << *z1 << std::endl;
    std::cout << "Zorb2: " << *z2 << std::endl;
    std::cout << "KiloZorb1: " << *kz1 << std::endl;
    std::cout << "KiloZorb2: " << *kz2 << std::endl;

    std::cout << "\n\n" << std::endl;

    if (*z1 < *z2)
        std::cout << "Zorb1 is less than Zorb2" << std::endl;
    else
        std::cout << "Zorb1 is not less than Zorb2" << std::endl;

    if (*kz1 < *kz2)
        std::cout << "KiloZorb1 is less than KiloZorb2" << std::endl;
    else
        std::cout << "KiloZorb1 is not less than KiloZorb2" << std::endl;

    if (*z1 < *kz1)
        std::cout << "Zorb1 is less than KiloZorb1" << std::endl;
    else
        std::cout << "Zorb1 is not less than KiloZorb1" << std::endl;

    std::cout << "\n\n" << std::endl;

    Zorb zorbSum = *z1 + *z2;
    std::cout << "Zorb1 + Zorb2 = " << zorbSum << std::endl;

    Zorb kzorbSum = *kz1 + *kz2;
    std::cout << "KiloZorb1 + KiloZorb2 = " << kzorbSum << std::endl;

    Zorb mixedSum1 = *z1 + *kz1;
    std::cout << "Zorb1 + KiloZorb1 = " << mixedSum1 << std::endl;

    Zorb mixedSum2 = *kz1 + *z2;
    std::cout << "KiloZorb1 + Zorb2 = " << mixedSum2 << std::endl;

    return 0;
}