#ifndef  _QUAT_CONSTANTS_H_
#define  _QUAT_CONSTANTS_H_

/**
 *
 * This file allows you to adjust all aspects of the game's constants
 * like scale, fonts, and sprites from a single place. The goal is that
 * each constant has a nice description that makes it clear exactly
 * where it is used without conveying unnecessary details about the
 * actual implementation.
 *
 */

/*=============================================
=            Executable Parameters            =
=============================================*/
/**
 *
 * Executable parameters are the constants that effect the
 * executable as a whole. None, aside from displaying statistics,
 * have a visual effect on the game.
 *
 */

/**
 * The global name of the executable. Used solely in the window title,
 * but also names the GLContext on mobile (but is not visible to
 * the player.)
 * 
 * Value is a constant string.
 */
#define Q_EXE_NAME "cppquat"

/**
 * The width of the window that the game runs in when compiling
 * to native platforms. This is ignored when compiling for mobile.
 * 
 * Value is a float.
 */
#define Q_WINDOW_WIDTH 562.5
/**
 * The height of the window that the game runs in when compiling
 * to native platforms. This is ignored when compiling for mobile.
 * 
 * Value is a float.
 */
#define Q_WINDOW_HEIGHT 1000

/**
 * The maximum FPS the game can run at. Higher values take more
 * battery but do not have any significant visual effect because
 * of the refresh rate of mobile screens.
 * 
 * Value is a float.
 */
#define Q_MAX_FPS 60.0

/**
 * Whether or not to display runtime statistics provided by the 
 * cocos2dx framework on the screen. Useful to check performance
 * while you are playing.
 * 
 * Value is a boolean (true or false).
 */
#define Q_DISPLAY_STATS false

/*=====  End of Executable Parameters  ======*/

/*==========================================
=            Ratios and Scaling            =
==========================================*/
/**
 *
 * This section is for all aspects of scale calculations. Every user
 * interface element is based on some proportion of the screen size.
 * This is done to allow resolution independence without having to
 * specifically code for it. By changing the values in this section
 * you can adjust the scale and position of most graphical elements.
 *
 */

/*----------  Game-wide adjustments  ----------*/

/**
 * The global font size as a percentage of the screen's width. This
 * exact font size is only used for displaying the current and goal
 * words, but every other UI element is based on some proportion of
 * this font size. In other words, this constant makes all of the
 * text in the game bigger or smaller.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_FONT_SIZE 0.10

/*----------  Main gameplay adjustments  ----------*/
/**
 * All of the ratios specific to solving puzzles, but not any of
 * the screens that branch off from that view.
 */

/**
 * The gap between the letters of both the current and the goal
 * word as a multiplier of the global font size. For example,
 * if the width of the screen were 200:
 * 
 *     (gameWidth * Q_FONT_SIZE) * Q_LETTER_GAP = letterGap
 *     (   200    *    0.10    ) *      1.8     = 36 (as of writing)
 * 
 * Larger values make the gap between the letters bigger.
 * 
 * Value is a float.
 */
#define Q_LETTER_GAP 1.8

/**
 * The y-position of the goal word as a proportion of the screen's
 * height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_GOAL_Y 0.55

/**
 * The gap between the goal word and the current word as a multiplier
 * of the global font size. A larger multiplier puts the goal word
 * and the current word further apart.
 * 
 * Vale is a float.
 */
#define Q_WORDS_GAP 1.6

/**
 * Size of the banner that display's the user's rank as a proportion
 * of the screen's height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_BANNER_HEIGHT 0.08

/**
 * Position of the banner's x-coordinate as a proportion of the 
 * screen's width.
 * 
 * Value is a float between 0 and 1. 
 */
#define Q_BANNER_X 0.88

/**
 * Size of the undo button sprite as a multiplier of the game's
 * global font size.
 * 
 * Value is a float.
 */
#define Q_UNDO_SIZE 0.8

/**
 * Position of the undo button's x-coordinate as a proportion of
 * the screen's width.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_UNDO_X 0.05

/**
 * Size of the definition button as a multiplier of the game's
 * global font size.
 * 
 * Value is a float.
 */
#define Q_DEFINITIONBTN_SIZE 0.7

/**
 * Position of the definition button's x-coordinate as a proportion
 * of the screen's width.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_DEFINITIONBTN_X 0.88

/**
 * Position of the text indicator's y-coordinate as a proportion
 * of the screen's height PLUS the y-coordinate of the current
 * word. The text indicator shows the "Done!" and "Perfect!" text
 * upon completion of a puzzle.
 * 
 * To explain further:
 *     textIndicatorY  = currentWordY + (gameHeight * Q_TEXT_INDICATOR_Y)
 * 
 * Value is a float between 0 and 1.
 */
#define Q_TEXT_INDICATOR_Y 0.10

/**
 * Positiion of the step text's y-coordinate as a proportion
 * of the screen's height. The step text shows the number
 * of steps the user has taken towards the solution and
 * whether they could solve the solution in fewer steps.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_STEPTEXT_DOWN_Y 0.05

/*=====  End of Ratios and Scaling  ======*/


#endif // _QUAT_CONSTANTS_H_