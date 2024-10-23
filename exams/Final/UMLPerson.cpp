class UMLPerson { // base class
public:
    // constructors and destructor
    UMLPerson() : _firstName("NoName"), _lastName("NoName"),
                  _address("NoAddress"), _IDNumber_(0) {}
		
    UMLPerson(string firstName, string lastName, string address,
              unsigned _IDNumber) :
        _firstName(firstName), _lastName(lastName), _address(address),
        _IDNumber_(_IDNumber) {}
			
    UMLPerson(const UMLPerson&); // copy constructor
			
    ~UMLPerson();


    // Implements lexicographic comparison of UMLPerson objects based on 
    // last name
    bool operator< (const UMLPerson& rhs) const
    { return this->_lastName < rhs._lastName; }

    // Implements equality based on IDNumber
    bool operator== (const UMLPerson& rhs) const
    { return this->_IDNumber == rhs._IDNumber; }

    bool operator== (const unsigned rhs) const
    { return this->_IDNumber == rhs; }

    
    // accessor functions
    string getFirstName() const { return _firstName; }
    string getLastName() const { return _lastName; }
    string getAddress() const { return _address; }
    unsigned get_IDNumber() const { return _IDNumber_; }
		
    void output(ostream& out) const { out << *this; }
				
    friend ostream& operator<< (ostream&, const UMLPerson&);
    friend ofstream& operator<< (ofstream&, const UMLPerson&);
    friend ifstream& operator>> (ifstream&, UMLPerson&);
	
private:
    string _firstName;
    string _lastName;
    string _address;
    unsigned _IDNumber_;
};
