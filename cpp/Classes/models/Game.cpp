#include "Game.h"

#include "Theme.h"

#include "themes/RankTheme.h"

namespace QUAT {

Game::Game() {
	this->dictionary = new Dictionary();
	
	this->dictionary->loadFromFile();

	this->puzzle = new Puzzle(this->dictionary);

	this->puzzleManager = new PuzzleManager(this->puzzle);
	this->puzzleManager->init();

	this->user = new User();

	// Initialize the vector of themes
	this->themes = new std::map<std::string, Theme *>();

	// Create the default rank theme and add it to our map of themes
	(*this->themes)[std::string("RANK")] = new RankTheme();

	// Sets the game's theme to be RANK (this is just a placeholder)
	this->setTheme(new std::string("RANK"));

	// Update the theme to reflect the user's current rank
	// This, too, can be moved at some point. It probably should not be in
	// the constructor. 
	this->theme->update(this);

  this->saveToLocal();
  this->loadFromLocal();
}

bool Game::canLoadFromLocal() {
  string path = this->getSaveFileName();
  return cocos2d::FileUtils::getInstance()->isFileExist(path);
}

Puzzle * Game::getPuzzle() {
	return this->puzzle;
}

User * Game::getUser() {
	return this->user;
}

Dictionary * Game::getDictionary() {
	return this->dictionary;
}

std::string Game::getSaveFileName() {
  string path = cocos2d::FileUtils::getInstance()->getWritablePath();
  return std::string(path + "save.quat");
}
void Game::loadFromLocal() {
  string path = this->getSaveFileName();
  ifstream input(path);

  input.close();
}

Theme * Game::getTheme() {
	return this->theme;
}

void Game::updateTheme() {
	this->theme->update(this);
}

void Game::setTheme(std::string * themeName) {
	this->theme = (*this->themes)[*themeName];
}

void Game::newPuzzle() {
	this->puzzleManager->fill(this->user->getRealRank());
}

void Game::saveToLocal() {
  string path = this->getSaveFileName();
  ofstream output(path);
  output.close();
}

}
