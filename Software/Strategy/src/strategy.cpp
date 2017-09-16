/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "strategy.h"
#include "arduino_serial.h"
#include <queue>

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = /*false*/ true;
	robot_radius = 8.0;
	distance_to_stop = 5.0;
	changePose = true;
	goleiro = 3;
	srand(time(NULL));
}

void Strategy::init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name){
	init_sample(main_color, is_debug, /*real_environment*/ true, ip_receive_state, ip_send_debug, ip_send_command, name);
	loop();
}



void Strategy::loop(){
	SerialSender *sender;
	if(real_environment){
		sender = new SerialSender();
	}
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
			sender->send(commands[0].right, commands[0].left, commands[1].right, commands[1].left, commands[2].right, commands[2].left);
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
btVector3 gol_adversario(160, 65, 0);


// campo vai de (10, 0) a (160, 130)
// vetor de 0 graus aponta pra esqueda, aumenta no sentido horário

time_t sec;
btVector3 prev_pos;
int id = 0;

queue<btVector3> prev_ball_pos;

void Strategy::calc_strategy(){

	prev_ball_pos.push(state.ball);
	if(prev_ball_pos.size() > 5)
		prev_ball_pos.pop();

	int atacante = 5;

	btVector3 final_goleiro;
	btVector3 final_atacante;

	float x_0 = 20;
	float y_min = 45;
	float y_max = 85;

	final_goleiro.x = x_0;
	final_goleiro.y = max(min(state.ball.y, y_max), y_min);
	final_goleiro.z = 0;

	signal_go = 0;
	final_atacante = state.ball;
/*	final_atacante = ((futuro(state.ball) - gol_adversario) * ((10.0 + distancePoint(futuro(state.ball), gol_adversario)) / distancePoint(futuro(state.ball), gol_adversario))) + gol_adversario;
	final_atacante.x = min(max((double) final_atacante.x, 16.0), 154.0);
	final_atacante.y = min(max((double) final_atacante.y, 6.0), 124.0);*/
//	final_atacante.z = atan2(65 - state.ball.y, 160 - state.ball.x) * 180 / M_PI + 180;

//	commands[atacante - 3] = calc_cmd_to(state.robots[atacante].pose, state.robots[atacante].pose + normalizar(forcaResultante(state.robots[atacante].pose, final_atacante, atacante))*(distancePoint(final_atacante, state.robots[atacante].pose) + 1), 2);
	commands[atacante - 3] = calc_cmd_to(state.robots[atacante].pose, final_atacante, 2);

/*	if(distancePoint(final_atacante, state.robots[atacante].pose) < target_dist)
	{
		target_dist = 5;
		commands[atacante - 3] = acertar_angulo(state.robots[atacante].pose, final_atacante);
	}
	else
	{
		target_dist = 2;
	}

	if(signal_go)
		commands[atacante - 3].right = commands[atacante].left = 50;
*/
/*	if(true)
	{
		target_dist = 2;
//		commands[atacante] = calc_cmd_to(state.robots[atacante].pose, final_atacante, 0);
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

	*/

//	commands[1] = commands[atacante];
	commands[goleiro - 3] = calc_cmd_to(state.robots[goleiro].pose, final_goleiro, 1);
	//commands[0] = calc_cmd_to(state.robots[0].pose, final, distance_to_stop);
	//commands[2] = calc_cmd_to(state.robots[2].pose, final, distance_to_stop);

	//state.robots[0].pose.show();
	// commands[1]
	// commands[2]
	//debug.robots_final_pose[0] = final;

/*	if(time(NULL) - sec >= 2)
	{
		printf("ola\n");
		if(distancePoint(state.robots[atacante].pose, prev_pos) < 2)
		{
			commands[atacante - 3].right = -150;
			commands[atacante - 3].left = -50;			
		}
		else
		{
			sec = time(NULL);
			prev_pos = state.robots[atacante].pose;
		}
	}
*/

	printf("***** %d\n", id++);
	for(int i = 0; i < 6; i++)
		state.robots[i].pose.show();
	for(int i = 0 ; i < 3 ; i++){
		debug.robots_path[i].poses.clear();
	}
/*	debug.robots_path[goleiro].poses.push_back(state.robots[goleiro].pose);
	debug.robots_path[goleiro].poses.push_back(final_goleiro);
	
	debug.robots_path[atacante].poses.push_back(state.robots[atacante].pose);
	debug.robots_path[atacante].poses.push_back(state.robots[atacante].pose + normalizar(forcaResultante(state.robots[atacante].pose, final_atacante, atacante))*(distancePoint(final_atacante, state.robots[atacante].pose) + 1));
*/}

btVector3 Strategy::futuro(btVector3 pos)
{
	return prev_ball_pos.front() + (pos - prev_ball_pos.front())*4;
}

double Strategy::square(double x) { return x*x; }

btVector3 Strategy::normalizar(btVector3 vec)
{
	double mod = sqrt(square(vec.x) + square(vec.y));
	btVector3 retv = vec;
	if(mod != 0)
		retv =  retv * (1 / mod);
	return retv;
}

double Strategy::produto_escalar(btVector3 a, btVector3 b)
{
	return a.x*b.x + a.y*b.y;
}


btVector3 Strategy::forcaResultante(btVector3 pos, btVector3 goal, int meu_robo)
{
	btVector3 retv(0,0,0);
	double robot_radius = 3.0;

	retv.x += 2000 / square(pos.x - 10 - robot_radius);
	retv.x += -2000 / square(160 - pos.x - robot_radius);
	retv.y += 2000 / square(pos.y - robot_radius);
	retv.y += -2000 / square(130 - pos.y - robot_radius);

	for(int i = 0; i < 6; i++)
	{
		if(i == meu_robo)
			continue;

		retv = retv + normalizar(pos - state.robots[i].pose) * (4000 / square(distancePoint(pos, state.robots[i].pose) - 2*robot_radius));
	}

	if(distancePoint(pos, goal))
	{
		retv = retv - normalizar(pos - goal) * (distancePoint(pos, goal)) * 10;
		retv = retv - normalizar(pos - goal) * (100.0 / (distancePoint(pos, goal)));
	}

	double prod = produto_escalar(normalizar(pos - state.ball), normalizar(gol_adversario - state.ball));

	if(prod > 0)
		retv = retv + normalizar(pos - state.ball) * (4000 / square(distancePoint(pos, state.ball) - robot_radius)) * prod;


	return retv;	
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

btVector3 Strategy::gradiente(btVector3 pos, int meu_robo)
{
	btVector3 retv;
	retv.x = potencial(btVector3(pos.x + 1.0, pos.y), meu_robo) - potencial(pos, meu_robo);
	retv.y = potencial(btVector3(pos.x, pos.y + 1.0), meu_robo) - potencial(pos, meu_robo);
	double k = 40 / sqrt(retv.x*retv.x + retv.y*retv.y);
	retv = retv * k;
	return retv;
}

double Strategy::potencial(btVector3 pos, int meu_robo)
{
	double retv = 0;
	retv += 1000 / ((pos.x-10)*(pos.x-10));
	retv += 1000 / ((160 - pos.x)*(160 - pos.x));
	retv += 1000 / (pos.y*pos.y);
	retv += 1000 / ((130 - pos.y)*(130 - pos.y));

	for(int i = 0; i < 6; i++)
	{
		if(i == meu_robo)
			continue;

		if(distancePoint(pos, state.robots[i].pose) != 0)
			retv += 4000 / (distancePoint(pos, state.robots[i].pose)*distancePoint(pos, state.robots[i].pose));
	}
	if(distancePoint(pos, state.ball) != 0)
		retv += -100 / distancePoint(pos, state.ball);

	return retv;
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

		if(sqrt(cmd.left*cmd.left + cmd.right*cmd.right) < 100)
		{
			float k = 100 / sqrt(cmd.left*cmd.left + cmd.right*cmd.right);
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
