/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _SAMPLE_H_
#define _SAMPLE_H

#include "common.h"
#include "VSS-Interface/cpp/interface.h"
#include "vector"

using namespace std;
using namespace common;

class Sample{
private:
    Interface interface_receive;
    Interface interface_send;
    Interface interface_debug;

    vss_state::Global_State global_state;
	vss_command::Global_Commands global_commands;
	vss_debug::Global_Debug global_debug;

protected:
	string ip_receive_state, ip_send_debug, ip_send_command;
    string main_color;
    bool is_debug;
    bool real_environment;
    int situation;
    string name;
    int flag_init;

    common::State state;
	common::Command commands[3];
    common::Debug debug;

public:
    Sample();

    void init_sample(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name);
    void receive_state();
    void send_commands();
    void send_debug();
};

#endif // _SAMPLE_H_