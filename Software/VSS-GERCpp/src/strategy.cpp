/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "strategy.h"

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = false;
	robot_radius = 8.0;
	distance_to_stop = 5.0;
	changePose = true;
	goleiro = 0;
	srand(time(NULL));
}

void Strategy::init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name){
	init_sample(main_color, is_debug, real_environment, ip_receive_state, ip_send_debug, ip_send_command, name);
	loop();
}

void Strategy::loop(){
	while(true){
		// DON'T REMOVE receive_data();
		receive_state();
		// DON'T REMOVE receive_Data();'
		
		calc_strategy();
		
		if(!real_environment){
			// DON'T REMOVE send_data();
			send_commands();
			// DON'T REMOVE send_data();
		}else{
			// Put your transmission code here
		}

		// DON'T REMOVE
		if(is_debug)
			send_debug();
		// DON'T REMOVE'
	}
}

float target_dist = 2;
int signal_go = 0;


// campo vai de (10, 0) a (160, 130)
// vetor de 0 graus aponta pra esqueda, aumenta no sentido horário

void Strategy::calc_strategy(){
	if(changePose){
		//changePose = false;
		final = state.ball;
		//final.x = (rand() % 100) + 30;
		//final.y = (rand() % 80) + 30;
		//final.z = rand() % 360;
	}

	btVector3 final_goleiro;
	btVector3 final_atacante;
	btVector3 gol_adversario(160, 65, 0);

	float x_0 = 20;
	float y_min = 45;
	float y_max = 85;

	final_goleiro.x = x_0;
	final_goleiro.y = max(min(state.ball.y, y_max), y_min);
	final_goleiro.z = 0;

	signal_go = 0;
	int atacante = 2;
	final_atacante = ((state.ball - gol_adversario) * ((10.0 + distancePoint(state.ball, gol_adversario)) / distancePoint(state.ball, gol_adversario))) + gol_adversario;
	final_atacante.x = min(max((double) final_atacante.x, 16.0), 154.0);
	final_atacante.y = min(max((double) final_atacante.y, 6.0), 124.0);
//	final_atacante = state.ball;
//	final_atacante.x -= 15;
	final_atacante.z = atan2(65 - state.ball.y, 160 - state.ball.x) * 180 / M_PI + 180;

	if(distancePoint(final_atacante, state.robots[atacante].pose) > target_dist)
	{
		target_dist = 2;
		commands[atacante] = calc_cmd_to(state.robots[atacante].pose, final_atacante, 0);
	}
	else
	{
//		counting++;
		target_dist = 5;
//		if(counting < 100)
//			commands[atacante].left = commands[atacante].right = 0;
//		else
		commands[atacante] = acertar_angulo(state.robots[atacante].pose, final_atacante);
	}

	if(signal_go)
		commands[atacante].right = commands[atacante].left = 50;

//	commands[1] = commands[atacante];
	commands[goleiro] = calc_cmd_to(state.robots[goleiro].pose, final_goleiro, 1);
	//commands[0] = calc_cmd_to(state.robots[0].pose, final, distance_to_stop);
	//commands[2] = calc_cmd_to(state.robots[2].pose, final, distance_to_stop);

	//state.robots[0].pose.show();
	// commands[1]
	// commands[2]
	//debug.robots_final_pose[0] = final;

	printf("*****\n");
	final_atacante.show();
	state.robots[atacante].pose.show();
	for(int i = 0 ; i < 3 ; i++){
		debug.robots_path[i].poses.clear();
	}
	debug.robots_path[goleiro].poses.push_back(state.robots[goleiro].pose);
	debug.robots_path[goleiro].poses.push_back(final_goleiro);
	
	debug.robots_path[atacante].poses.push_back(state.robots[atacante].pose);
	debug.robots_path[atacante].poses.push_back(final_atacante);
}

common::Command Strategy::acertar_angulo(btVector3 act, btVector3 goal){
	Command cmd;

	float cw_diff = 360 + act.z - goal.z;
	if(cw_diff > 360)
		cw_diff -= 360;

	float ccw_diff = 360 + goal.z - act.z;
	if(ccw_diff > 360)
		ccw_diff -= 360;

	if(cw_diff < 3 || ccw_diff < 3)
	{
		cmd.left = 0;
		cmd.right = 0;
		signal_go = 1;
		return cmd;
	}

	if(cw_diff < ccw_diff)
	{
		cmd.left = -(5 + 50.0*(cw_diff / 360));
		cmd.right = (5 + 50.0*(cw_diff / 360));
	}
	else
	{
		cmd.left = (5 + 50.0*(ccw_diff / 360));
		cmd.right = -(5 + 50.0*(ccw_diff / 360));
	}

	return cmd;
}


common::Command Strategy::calc_cmd_to(btVector3 act, btVector3 goal, float distance_to_stop){
	Command cmd;
	float distance_robot_goal;
	float angulation_robot_goal;
	float angulation_robot_robot_goal;

	// Diferença entre angulação do robô e do objetivo
	distance_robot_goal = distancePoint(goal, act);
	angulation_robot_goal = angulation(goal, act);


	angulation_robot_goal -= 180; // 180 if comes from VSS-Simulator
    if(angulation_robot_goal < 0){
    	angulation_robot_goal += 360;
    }

	angulation_robot_robot_goal = act.z - angulation_robot_goal;

	if(angulation_robot_robot_goal > 180){
		angulation_robot_robot_goal -= 360;
	}

	if(angulation_robot_robot_goal < -180){
		angulation_robot_robot_goal += 360;
	}
	
	//cout << angulation_robot_robot_goal << endl;

	// Regras de movimentação

	if(fabs(angulation_robot_robot_goal) <= 135){
		cmd.left = distance_robot_goal - 0.2*(angulation_robot_robot_goal * robot_radius / 2.00);
		cmd.right = distance_robot_goal + 0.2*(angulation_robot_robot_goal * robot_radius / 2.00);
		
		cmd.left *= 0.5;
		cmd.right *= 0.5;

		if(sqrt(cmd.left*cmd.left + cmd.right*cmd.right) < 150)
		{
			float k = sqrt(150 / sqrt(cmd.left*cmd.left + cmd.right*cmd.right));
			cmd.left *= k;
			cmd.right *= k;
		}
	}else{
		if(angulation_robot_robot_goal >= 0){
			cmd.left = 50;
			cmd.right = -50;
		}else{
			cmd.left = -50;
			cmd.right = 50;
		}
	}

	//cmd.left = 1;
	//cmd.right = -1;
	//cmd.left e cmd.right são PWM (0 a 255 para frente) (256 á 252 para trás)

	if(distance_robot_goal < distance_to_stop){
		cmd.left = 0;
		cmd.right = 0;
		changePose = true;
	}

	return cmd;
}
