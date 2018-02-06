/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Nov 15, 2016
 *
 */

#include <brew/input/InputDevice.h>
#include <brew/core/Exception.h>

namespace brew {

InputDevice::InputDevice(u16 numDigitalInputs, u8 numAnalogInputs)
: digitalStates(numDigitalInputs, false), analogStates(numAnalogInputs, 0.0){
}

void InputDevice::setAnalog(u8 n, Real value) {
	if(n >= analogStates.size()) {
		throw NotFoundException("No such analog state.");
	}

    Real delta = value - analogStates[n];

	analogStates[n] = value;

    InputDeviceEvent event = { *this, InputDeviceEvent::Type::AnalogMotion2D, 0,0,0, delta,0,0, value,0,0,};
}

void InputDevice::setAnalog2D(u8 x, u8 y, Real xv, Real yv) {
	if(x >= analogStates.size() || y >= analogStates.size()){
		throw NotFoundException("No such analog state.");
	}

	Real deltaX = xv - analogStates[x];
    Real deltaY = yv - analogStates[y];

	analogStates[x] = xv;
	analogStates[y] = yv;

	InputDeviceEvent event = { *this, InputDeviceEvent::Type::AnalogMotion2D, x, y, 0, deltaX, deltaY, 0, xv, yv, 0 };
	fireInputDeviceEvent(event);
}

void InputDevice::setDigital(u16 n, bool value) {
	if(n >= digitalStates.size()){
		throw NotFoundException("No such analog state.");
	}

	if(digitalStates[n] != value) {
		digitalStates[n] = value;
		InputDeviceEvent event = { *this, value ? InputDeviceEvent::Type::DigitalDown : InputDeviceEvent::Type::DigitalUp, n,0,0, 0,0,0, 0,0,0 };
		fireInputDeviceEvent(event);
	}
}

} /* namespace brew */
