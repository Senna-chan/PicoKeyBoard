/*
 Name:		BTMouse.h
 Created:	1/11/2024 5:44:36 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _BTMouse_h
#define _BTMouse_h

#include <MouseBase.h>
#include <BPLib.h>

class BTMouse_ : public MouseBase
{
private:
	BPLib* bluetooth;
public:
	void begin(BPLib* bluetoothLib);
	void end();
	virtual void sendMouseReport(MouseReport report) override;
};

extern BTMouse_ BTMouse;

#endif

