#ifndef __RANK_THEME_H__
#define __RANK_THEME_H__

#include "../Theme.h"

namespace QUAT {

class Game;

class RankTheme : public Theme
{
private:
  int currentRank;
public:
  RankTheme();
	/**
	 * @brief      Reads values on the game state to determine changes to the
	 *             color scheme or other members. 
	 *
	 * @param      model  The model
	 */
	void update(Game * model);
};

}

#endif // __RANK_THEME_H__
