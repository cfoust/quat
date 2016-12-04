#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <map>
#include <string>

namespace QUAT {

class Dictionary
{
private:
	std::map<std::string, int> * map;
public:
	Dictionary();

	/**
	 * Checks whether the dictionary contains the given word.
	 * @param  word Pointer to a string containing the desired word.
	 * @return      Integer representation of relative word frequency or -1 if
	 *              the map does not contain the word.
	 */
	int contains(std::string * word);

	/**
	 * Loads the dictionary from its file.
	 */
	void loadFromFile();
};

}

#endif // __DICTIONARY_H__
