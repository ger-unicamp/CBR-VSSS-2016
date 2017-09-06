#include "stategy_interface.h"
#include "VSS-Interface/cpp/interface.h"

stategy_interface::stategy_interface(){
}

void stategy_interface::sendToStrategy(State state){
	vss_state::Global_State global_state;

    Interface interface;
    //! Define the interface VSS
    interface.createSocketSendState(&global_state);

    global_state = vss_state::Global_State();
    global_state.set_id(0);
    global_state.set_situation(0);
    global_state.set_origin(true);

    vss_state::Ball_State *ball_s = global_state.add_balls();
    ball_s->mutable_pose()->set_x(state.ball_pos.x);
    ball_s->mutable_pose()->set_y(state.ball_pos.y);

	for(int i = 0 ; i < 3 ; i++){
	    vss_state::Robot_State *robot_s = global_state.add_robots_blue();

	    robot_s->mutable_pose()->set_x(state.blue_pos[i].x);
	    robot_s->mutable_pose()->set_y(state.blue_pos[i].y);
	    robot_s->mutable_pose()->set_yaw(state.blue_dir[i]);

	}

    for(int i = 0 ; i < 3 ; i++){
        vss_state::Robot_State *robot_s = global_state.add_robots_yellow();

	    robot_s->mutable_pose()->set_x(state.yellow_pos[i].x);
	    robot_s->mutable_pose()->set_y(state.yellow_pos[i].y);
	    robot_s->mutable_pose()->set_yaw(state.yellow_dir[i]);
    }

    interface.sendState();
}

State::State(){
	this.ball_pos(0,0);
	for(int i =0; i <3; i++){
		this.blue_pos[i](0,0);
		this.blue_dir[i](0,0);
		this.yellow_pos[i](0,0);
		this.yellow_dir[i](0,0);
	}
}

