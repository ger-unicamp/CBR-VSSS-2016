/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "sstream"
#include "strategy.h"
#include "boost.h"

bool argParse(int argc, char** argv, string *color, bool *debug, string *ip_receive_state, string *ip_send_debug, string *ip_send_command, string *name);

int main(int argc, char** argv){
	string color;
    bool debug = false;
    string name;
    string ip_receive_state, ip_send_debug, ip_send_command;

	if(argParse(argc, argv, &color, &debug, &ip_receive_state, &ip_send_debug, &ip_send_command, &name)){
        if(color == "yellow" || color == "blue"){
		    Strategy strategy;
		    strategy.init(color, debug, false, ip_receive_state, ip_send_debug, ip_send_command, name);
        }else{
            cerr << "ERROR: Your main color must be yellow or blue." << endl;
        }
	}else{
		cerr << "ERROR: You must enter a main color." << endl;
	}

	return 0;
}

bool argParse(int argc, char** argv, string *color, bool *debug, string *ip_receive_state, string *ip_send_debug, string *ip_send_command, string *name){
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("debug,d", "(Optional) open the debug rotine")
        ("name,n", bpo::value<std::string>()->default_value("sample"), "(Optional) Specify the name of the strategy.")
        ("ip_receive_state,i", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Vision.")
        ("ip_send_debug,I", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Viewer.")
        ("ip_send_command,s", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Simulator.")
        ("color,c", bpo::value<std::string>()->default_value(" "), "(Required) Specify the main color of your team, may be yellow or blue.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        std::cout << desc << std::endl;
        return false;
    }

    if (vm.count("debug")){
        *debug = true;
    }

    *name = vm["name"].as<string>();  

    *ip_receive_state = vm["ip_receive_state"].as<string>();    

    *ip_send_debug = vm["ip_send_debug"].as<string>();

    *ip_send_command = vm["ip_send_command"].as<string>();
    
    *color = vm["color"].as<string>();

    if(*color == " "){
        return false;
    }

    return true;
}