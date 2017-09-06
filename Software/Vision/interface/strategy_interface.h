#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

#include "ger_vsss.hpp"

class strategyInterface{
	public:
		// Construtor
		strategyInterface();

		void sendToStrategy(State state);
}

class State{
	public:
		Point2f blue_pos[3], yellow_pos[3], ball_pos;
		float blue_dir[3], yellow_dir[3];

		State();
}