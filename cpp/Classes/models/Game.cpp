#include "Game.h"

namespace QUAT {

Game::Game() {
	this->dictionary = new Dictionary();
	
	this->dictionary->loadFromFile();

	this->puzzle = new Puzzle(this->dictionary);
	this->user = new User();
}

bool Game::canLoadFromLocal() {
	return false;
}

Puzzle * Game::getPuzzle() {
	return this->puzzle;
}

User * Game::getUser() {
	return this->user;
}

void Game::loadFromLocal() {

}

void Game::newPuzzle() {

}

void Game::saveToLocal() {

}

}