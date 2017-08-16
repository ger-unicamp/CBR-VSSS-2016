#include "VSS-Interface/cpp/interface.h"

vss_state::Global_State global_state;

int main(void)
{
    Interface interface;
    //! Define the interface VSS
    interface.createSocketSendState(&global_state);

    while(1)
    {
	    global_state = vss_state::Global_State();
	    global_state.set_id(0);
	    global_state.set_situation(0);
	    global_state.set_origin(true);

	    vss_state::Ball_State *ball_s = global_state.add_balls();
	    ball_s->mutable_pose()->set_x(50);
	    ball_s->mutable_pose()->set_y(50);

		for(int i = 0 ; i < 3 ; i++){
		    vss_state::Robot_State *robot_s = global_state.add_robots_blue();

		    robot_s->mutable_pose()->set_x(i * 10);
		    robot_s->mutable_pose()->set_y(i * 10);
		    robot_s->mutable_pose()->set_yaw(i * 10);

		}

	    for(int i = 0 ; i < 3 ; i++){
	        vss_state::Robot_State *robot_s = global_state.add_robots_yellow();

	        robot_s->mutable_pose()->set_x(i * 10 + 45);
	        robot_s->mutable_pose()->set_y(i * 10 + 45);
	        robot_s->mutable_pose()->set_yaw(i * 10 + 45);
	    }

	    interface.sendState();
	    usleep(10000);
    }
}