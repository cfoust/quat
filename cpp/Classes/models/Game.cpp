#include "Game.h"

namespace QUAT {

Game::Game() {
	this->dictionary = new Dictionary();
	
	this->dictionary->loadFromFile();

	this->puzzle = new Puzzle(this->dictionary);

	this->puzzleManager = new PuzzleManager(this->puzzle);
	this->puzzleManager->init();

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

Dictionary * Game::getDictionary() {
	return this->dictionary;
}

void Game::loadFromLocal() {

}

void Game::newPuzzle() {
	this->puzzleManager->fill(this->user->getRealRank());
}

void Game::saveToLocal() {

}

}