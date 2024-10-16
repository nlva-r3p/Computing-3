#include "SSandwich.h"

SloppySandwich::SloppySandwich() 
    : sandwichSize(size::regular), 
      sandwichBreadType(breadType::white), 
      sandwichBreadFormat(breadFormat::wrap) {}

SloppySandwich::SloppySandwich(size sz, breadType type, breadFormat format) 
    : sandwichSize(sz), 
      sandwichBreadType(type), 
      sandwichBreadFormat(format) {}

SloppySandwich::size SloppySandwich::getSize() const {
    return sandwichSize;
}

SloppySandwich::breadType SloppySandwich::getBreadType() const {
    return sandwichBreadType;
}

SloppySandwich::breadFormat SloppySandwich::getBreadFormat() const {
    return sandwichBreadFormat;
}

void SloppySandwich::setSize(size sz) {
    sandwichSize = sz;
}

void SloppySandwich::setBreadType(breadType type) {
    sandwichBreadType = type;
}

void SloppySandwich::setBreadFormat(breadFormat format) {
    sandwichBreadFormat = format;
}

SloppySandwich& SloppySandwich::operator+(const std::string& additionals) {
    contentsList.push_back(additionals);
    return *this;
}