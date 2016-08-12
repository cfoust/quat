#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#include "cocos2d.h"
#include "../Constants.h"

#include <string>

namespace QUAT {

class Definition : public cocos2d::Layer
{
private:
	cocos2d::Label * word,       // Holds the text for the actual word
				   * pos,        // The word's part of speech
				   * definition; // The word's definition

	float fontSize, // The global font size
		  width;	// The width of this definition

public:

	/**
	 * @brief      Fills the definition object with new information.
	 *
	 * @param[in]  word        The word to show.
	 * @param[in]  POS         The word's part of speech.
	 * @param[in]  definition  The word's definition.
	 */
	void setWord(std::string word, std::string POS, std::string definition);

	/**
	 * @brief      Get the Definition's total height.
	 *
	 * @return     The total height.
	 */
	float getTotalHeight();

	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	Definition(float fontSize, float width);
	
	static Definition * create(float fontSize, float width);
};

}

#endif // __DEFINITION_H__
