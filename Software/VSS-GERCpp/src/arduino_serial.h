/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _ARDUINO_SERIAL_H_
#define _ARDUINO_SERIAL_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <stdexcept>

class SerialSender {
private:
    FILE *file;
    
public:
    SerialSender();
    ~SerialSender();
    void send(int vel_1r, int vel_1l, int vel_2r, int vel_2l, int vel_3r, int vel_3l);
};
#endif
