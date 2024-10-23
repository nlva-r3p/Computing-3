#include "SSandwich.h"

int main(int argc, char* argv[]) {
    SloppySandwich mySandwich;

    SloppySandwich::size currentSize = mySandwich.getSize();
    SloppySandwich::breadType currentBreadType = mySandwich.getBreadType();

    std::cout << "Current sandwich size: " << (currentSize == SloppySandwich::size::regular ? "regular" : "glutton") << std::endl;
    std::cout << "Current bread type: " << (currentBreadType == SloppySandwich::breadType::white ? "white" : 
                       currentBreadType == SloppySandwich::breadType::wheat ? "wheat" : "rye") << std::endl;
    
    mySandwich.setSize(SloppySandwich::size::glutton);
    mySandwich.setBreadType(SloppySandwich::breadType::wheat);
    //mySandwich.setBreadFormat(SloppySandwich::breadFormat::sub);

    currentSize = mySandwich.getSize();
    currentBreadType = mySandwich.getBreadType();

    std::cout << "Current sandwich size: " << (currentSize == SloppySandwich::size::regular ? "regular" : "glutton") << std::endl;
    std::cout << "Current bread type: " << (currentBreadType == SloppySandwich::breadType::white ? "white" : 
                       currentBreadType == SloppySandwich::breadType::wheat ? "wheat" : "rye") << std::endl;


    mySandwich + "Tomato" + "Mustard" + "Ham";

    return 0;
}