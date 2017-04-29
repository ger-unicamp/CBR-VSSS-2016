#include <stdio.h>
#include "libs/serial_src/Serial.h"

int main() {
	CSerial serial;
	if(serial.Open(2, 9600))
		AfxMessageBox("Port opened successfully");
	else
		AfxMessageBox("Failed to open port!");
}