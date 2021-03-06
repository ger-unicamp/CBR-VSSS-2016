#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

#include "ger_vsss.hpp"
#include "VSS-Interface/cpp/interface.h"

class State{
	public:
		Point2f blue_pos[3], yellow_pos[3], ball_pos;
		float blue_dir[3], yellow_dir[3];

		State();
};

class StrategyInterface{
	private:

	vss_state::Global_State global_state;
	Interface interface;

	public:

	// Construtor
	StrategyInterface();

	void sendToStrategy(State state);
};


#endif
