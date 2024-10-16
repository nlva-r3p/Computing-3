#ifndef SSANDWICH_H
#define SSANDWICH_H

#include <string>
#include <vector>
#include <iostream>

class SloppySandwich {
public:
    enum class size { regular, glutton };
    enum class breadType { white, wheat, rye };
    enum class breadFormat { wrap, sub, sliced };

    SloppySandwich();
    SloppySandwich(size sz, breadType type, breadFormat format);

    size getSize() const;
    breadType getBreadType() const;
    breadFormat getBreadFormat() const;

    void setSize(size sz);
    void setBreadType(breadType type);
    void setBreadFormat(breadFormat format);

    SloppySandwich& operator+(const std::string& additionals);

private:
    size sandwichSize;
    breadType sandwichBreadType;
    breadFormat sandwichBreadFormat;

    std::vector<std::string> contentsList;
};

#endif //SSANDWICH_H