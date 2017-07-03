/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "iostream"
#include "math.h"
#include "VSS-Interface/cpp/interface.h"

using namespace std;

namespace common{
    enum { NONE = 0, GOAL_TEAM1 = 1, GOAL_TEAM2 = 2, FAULT_TEAM1 = 3, FAULT_TEAM2 = 4, PENALTY_TEAM1 = 5, PENALTY_TEAM2 = 6 };
    
    //! This struct represents a Vector in R^3.
    struct btVector3{
        //! Data: x, y, z.
        float x, y, z;
        //! Default constructor: btVector3 bt3;
        btVector3(){
            x = y = z = 0;
        };
        //! Construtor XYZ: btVector3 bt3(x, y, z);
        btVector3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        };
        //! Constructor copy: btVector3 bt3(btVector3(x, y, z));
        btVector3(btVector3 *b){
            x = b->x;
            y = b->y;
            z = b->z;
        };
        //! Default function: prints all variables.
        void show(){
            printf("btVector3(%f, %f, %f)\n", x, y, z);
        };

        btVector3 operator + (btVector3 a)
        {
        	return btVector3(x + a.x, y + a.y, z + a.z);
        }
        
        btVector3 operator - (btVector3 a)
        {
        	return btVector3(x - a.x, y - a.y, z - a.z);
        }

        btVector3 operator * (double k)
        {
        	return btVector3(k * x, k * y, z);
        }
    };


    //! This strcut represets the pose that one robot can handle. Pos and Vel.
    struct Robot{
        //! Data: Pose
        btVector3 pose;
        //! Data: V_Pose
        btVector3 v_pose;

        //! Default constructor: Robot t;
        Robot(){
            pose = btVector3(0, 0, 0);
            v_pose = btVector3(0, 0, 0);
        };

        //! Constructor 2: Robot t(btVector3(x, y, yaw), btVector3(x, y, yaw))
        Robot(btVector3 pose, btVector3 v_pose){
            this->pose = pose;
            this->v_pose = v_pose;
        };

        //! Constructor copy: Robot t(Robot());
        Robot(Robot *r){
            pose = r->pose;
            v_pose = r->v_pose;
        };

        //! Default function: prints all variables.
        void show(){
            printf("Robot:\n");
            printf("Pose:\n");
            pose.show();
            printf("V_Pose:\n");
            v_pose.show();
        }
    };

    //! This is a simple structure responsible for represent a path: vector of poses. 
	struct Path{
		vector<btVector3> poses;
		Path(){};
		Path(Path *path){
			poses = path->poses;
		};
		void show(){
			for(int i = 0 ; i < poses.size() ; i++)
			cout << "(" << poses.at(i).x << ", " << poses.at(i).y << ", " << poses.at(i).z << ")" << endl;
		}
	};

    //! This is a simple structure that represents a Debug packet
    struct Debug{
        btVector3 robots_step_pose[3];
        btVector3 robots_final_pose[3];
        Path robots_path[3];
        Debug(){};
    };

    //! This struct represents the state that the workspace can handle.
    struct State{
        //! All robots by vision
        Robot robots[6];
        //! All robots by kalman
        Robot robots_kalman[6];
        //! Pos ball by vision
        btVector3 ball;
        //! Vel ball by vision
        btVector3 v_ball;
        //! Pos ball by kalman
        btVector3 ball_kalman;
        //! Vel ball by kalman
        btVector3 v_ball_kalman;
        //! Default constructor: State s;
        State(){};
        /* TODO: outros construtores*/
        //! Default function: prints all variables.
        void show(){
            cout << "Robots Team 1:" << endl;
            for(int i = 0 ; i < 3 ; i++){
                robots[i].show();
            }
            cout << "Robots Team 1 Kalman:" << endl;
            for(int i = 0 ; i < 3 ; i++){
                robots_kalman[i].show();
            }
            cout << "Robots Team 2:" << endl;
            for(int i = 3 ; i < 6 ; i++){
                robots[i].show();
            }
            cout << "Robots Team 2 Kalman" << endl;
            for(int i = 3 ; i < 6 ; i++){
                robots_kalman[i].show();
            }
            cout << "Ball:" << endl;
            ball.show();
            ball_kalman.show();
        };
    };

    struct Command{
        float left;
        float right;
        Command(){
            left = right = 0;
        };
        Command(float left, float right){
            this->left = left;
            this->right = right;
        };
        Command(Command *cmd){
            left = cmd->left;
            right = cmd->right;
        };
        void show(){
            cout << "Command (" << left << ", " << right << ")" << endl;
        };
    };

    //! Estimate distance between a set of points.
    double distancePoint(btVector3, btVector3);

    //! Estimate midpoint between a set of points.
    btVector3 midpoint(btVector3, btVector3);

    //! Estimate angle between two straight lines.
    double angulation(btVector3, btVector3);

    //! Estimate angle between two straight lines in radian.
    double radian(btVector3, btVector3);

    State Global_State2State(vss_state::Global_State global_state, string main_color);
}

#endif
