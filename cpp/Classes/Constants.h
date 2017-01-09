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

#define Q_FONT_PATH "fonts/Arimo-Regular.ttf"
#define Q_ICON_PATH "fonts/font-awesome.ttf"

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
 * The amount of padding around each letter in the current word as
 * a multiplier of the global font size. Essentially controls how
 * big the border/background is around each letter.
 * 
 * Value is a float.
 */
#define Q_CURRENT_PADDING 1.5

/**
 * The corner radius of the border around each letter as a multiplier
 * of the global font size. 
 * 
 * Value is a float.
 */
#define Q_CURRENT_BORDER_RADIUS 0.40

/**
 * The thickness of the border around each letter of the current word
 * as a multiplier of the global font size.
 * 
 * Value is a float.
 */
#define Q_CURRENT_BORDER_WIDTH 0.06

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
 * Value is a float.
 */
#define Q_WORDS_GAP 1.6

/**
 * File path for the banner sprite. 
 * 
 * Value is a constant string.
 */
#define Q_BANNER_SPRITEFILE "banner.png"

/**
 * Size of the banner that display's the user's rank as a proportion
 * of the screen's height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_BANNER_HEIGHT 0.08

/**
 * Size of the rank text on the banner as a proportion of the banner's
 * height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_BANNER_FONT 0.3

/**
 * The y-coordinate of the rank text as a proportion of the banner's
 * height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_BANNER_RANK_Y 0.58

/**
 * Position of the banner's x-coordinate as a proportion of the 
 * screen's width.
 * 
 * Value is a float between 0 and 1. 
 */
#define Q_BANNER_X 0.88

/**
 * Name of the file that has the undo sprite.
 * 
 * Value is a constant string.
 */
#define Q_UNDO_SPRITEFILE "undo.png"

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
#define Q_DEFINITIONBTN_SIZE 0.9

/**
 * Position of the definition button's x-coordinate as a proportion
 * of the screen's width.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_DEFINITIONBTN_X 0.88

/**
 * Font size of the text indicator, which shows
 * when a user enters an invalid word or finishes a puzzle,
 * as a multiplier of the global font size.
 * 
 * Value is a float.
 */
#define Q_TEXT_INDICATOR_FONT 0.40

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
 * The font size of the step indicator's subtext (it just says "steps")
 * as a proportion of the global font size.
 * 
 * Value is a float.
 */
#define Q_STEPTEXT_SUB_FONT 0.4

/**
 * The font size of the text that shows the number of steps as a
 * multiplier of the subtext font size above.
 * 
 * Value is a float.
 */
#define Q_STEPTEXT_STEP_FONT 1.5

/**
 * Position of the step text's y-coordinate as a proportion
 * of the screen's height. The step text shows the number
 * of steps the user has taken towards the solution and
 * whether they could solve the solution in fewer steps.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_STEPTEXT_DOWN_Y 0.05

/**
 * Size (diameter) of the menu button as a proportion of the 
 * screen's width. The menu button is just an empty circle.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_MENUBTN_SIZE 0.035

/**
 * Distance of center of menu button from top-left corner of
 * screen as a proportion of the screen's width. Distance is not
 * diagonal but is the same distance for x and y. (i.e, a distance
 * of 10px means that the menu button is at y = screenHeight - 10
 * and x = screenWidth - 10).
 * 
 * Value is a float between 0 and 1.
 */
#define Q_MENUBTN_OFFSET 0.07

/**
 * Thickness of the line that delineates the menu button's circle
 * as a multiplier of the menu button's size.
 * 
 * Value is a float.
 */
#define Q_MENUBTN_THICKNESS 0.1

/**
 * Opacity of the menu button circle's line.
 * 
 * Value is an integer from 0 to 255.
 */
#define Q_MENUBTN_OPACITY 180

/**
 * Height of the keyboard as a proportion of the screen's height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_HEIGHT 0.3

/**
 * Height of each individual key on the keyboard as a proportion
 * of the keyboard's total height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_KEY_HEIGHT 0.27

/**
 * Width of each individual key as a proportion of the width of the
 * whole keyboard.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_KEY_WIDTH 0.08

/**
 * Horizontal gap between each key on the keyboard as a proportion
 * of the width of the keyboard.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_KEY_X_GAP 0.02

/**
 * Gap between the rows of keys as a proportion of the keyboard's
 * height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_KEY_Y_GAP 0.07

/**
 * Size of the font on each key as a proportion of the key's height.
 * 
 * Value is a float between 0 and 1.
 */
#define Q_KEYBOARD_KEY_FONT 0.5

/**
 * Ratio of the keyboard's height to the keyboard's width.
 * 
 * keyboardWidth = keyboardHeight * Q_KEYBOARD_X_Y_RATIO
 * 
 * This is only used when we're on a pretty wide device. For the
 * most part we match keyboard width to screen width.
 * 
 * Value is a float.
 */
#define Q_KEYBOARD_X_Y_RATIO 2.265

/*=====  End of Ratios and Scaling  ======*/

/*=========================================
=            Animation Timings            =
=========================================*/

/**
 * Amount of time it takes for keyboard to slide up 
 * and down.
 * 
 * Value is a float in seconds.
 */
#define Q_KEYBOARD_SLIDE 0.08

/**
 * Amount of time it takes for the text indicator, which shows
 * when a user enters an invalid word or finishes a puzzle, to
 * fade away or fade in.
 * 
 * Value is a float in seconds.
 */
#define Q_TEXT_INDICATOR_FADE 0.75

/**
 * Amount of time it takes for the banner to slide up
 * in order to change the displayed rating. In other words,
 * it takes double this value in seconds for the full animation
 * of changing the rank.
 * 
 * Value is a float in seconds.
 */
#define Q_BANNER_SLIDE 0.75

/**
 * Amount of time it takes for the exploding circle to grow
 * large and dissipate.
 * 
 * Value is a float in seconds.
 */
#define Q_BANNER_EXPLODE 1.0f

/*=====  End of Animation Timings  ======*/


#endif // _QUAT_CONSTANTS_H_
