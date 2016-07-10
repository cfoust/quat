#include "Dictionary.h"
#include <fstream>
#include <string>

#include "cocos2d.h"

namespace QUAT {

Dictionary::Dictionary() {
	this->map = new std::map<std::string, int>();
}

/**
 * Checks whether the dictionary contains the given word.
 * @param  word Pointer to a string containing the desired word.
 * @return      Integer representation of relative word frequency.
 */
int Dictionary::contains(std::string * word) {
	if (this->map->find(*word) != this->map->end()) {
		return (*this->map)[*word];
	} else {
		return -1;
	}
}

/**
 * Loads the dictionary from its file.
 */
void Dictionary::loadFromFile() {
	std::ifstream file(cocos2d::FileUtils::getInstance()->fullPathForFilename("dict"));
    std::string str;

    while (std::getline(file, str))
    {
    	std::string word = str.substr(0,4);
    	int freq = std::stoi(str.substr(4));
    	(*this->map)[word] = freq;
    }
}

}