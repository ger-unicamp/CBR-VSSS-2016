/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "sample.h"

using namespace std;
using namespace common;

class Strategy : public Sample{
	/*
		Sample :: string main_color;
		Sample :: bool is_debug;
		Sample :: bool real_environment;
		Sample :: int situation;

		Sample :: common::State state;
		Sample :: common::Command commands[3];
		Sample :: common::Debug debug;
	*/
protected:
	float robot_radius;
	float distance_to_stop;
	int goleiro;

	btVector3 final;
	bool changePose;
public:
	Strategy();	

	void init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name);
	void loop();
	void calc_strategy();

	btVector3 futuro(btVector3 pos);
	double produto_escalar(btVector3 a, btVector3 b);
	double square(double x);
	btVector3 normalizar(btVector3 vec);
	btVector3 forcaResultante(btVector3 pos, btVector3 goal, int meu_robo);
	common::Command acertar_angulo(btVector3 act, btVector3 goal);
	btVector3 gradiente(btVector3 pos, int meu_robo);
	double potencial(btVector3 pos, int meu_robo);
	common::Command calc_cmd_to(btVector3 init, btVector3 final, float distance_to_stop = 10.0);
};

#endif // _STRATEGY_H_
