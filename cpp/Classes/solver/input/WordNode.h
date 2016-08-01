#ifndef __WORD_NODE_H__
#define __WORD_NODE_H__

#include "cocos2d.h"
#include "../../Constants.h"

namespace QUAT {

class WordNode : public cocos2d::Layer
{
protected:
	float fontGap,  // Gap between the letters horizontally 
		  fontSize; // Actual font size

	// Pool of letters we use to render each word
	std::vector<cocos2d::Label*> * letterPool;

	// Used to calculate the bounds of all of the letters
	std::vector<cocos2d::Rect*> * bounds;

	// The bounds of the whole word
	cocos2d::Rect * whole;

	std::string * word;

public:

	/**
	 * Changes a letter in a certain position.
	 * @param column Column (0-3) of the letter to change.
	 * @param letter New letter.
	 */
	void changeLetter(int column, std::string letter);

	/**
	 * Replaces the text of this word with a given word.
	 * @param word The four-letter word to change it to.
	 */
	void changeWord(std::string * word);

	/**
	 * Gets a letter from a certain column.
	 * @param column Column (0-3) of the letter to get.
	 * @return [description]
	 */
	const std::string * getLetter(int column);

	/**
	 * Gets the current word displayed by the WordNode.
	 */
	std::string * getWord();

	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	/**
	 * Checks whether a point is in the bounds of the whole word.
	 * @param  point Point in the plane.
	 */
	bool pointInWhole(cocos2d::Point * point);

	/**
	 * Checks whether the point is in any of the letters.
	 * @param  point Point in the plane.
	 * @return       0, 1, 2, 3 for each corresponding letter, or -1 if the
	 *               point is not in any letter.
	 */
	int pointInWord(cocos2d::Point * point);


	/**
	 * Recalculate the bounding boxes for the letters.
	 */
	void recalculateBounds();
	
	WordNode(float fontSize, float fontGap);
	
	static WordNode * create(float fontSize, float fontGap);
};

}

#endif // __WORD_NODE_H__
