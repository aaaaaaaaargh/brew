/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Nov 15, 2016
 *
 */

#ifndef BREW_INPUTDEVICE_H
#define BREW_INPUTDEVICE_H

#include <brew/core/Types.h>
#include <brew/core/EventSource.h>

#include <vector>

namespace brew {

class InputDevice;

/**
 * An event class for input devices.
 */
class InputDeviceEvent {
public:
	/**
	 * The event types.
	 */
	enum class Type {
		DigitalDown, //< A digital button was pressed.
		DigitalUp, //< A digital button was released.
		AnalogMotion, //< An analog input was moved.
		AnalogMotion2D //< A 2D analog motion was detected.
	};

	InputDevice& device; //< The device that triggered the event.

	Type type; //< The event type.

	u16 stateId; //< The primary state id of the input.
    u16 stateId2; //< The optional second state id of the input.
    u16 stateId3; //< The optional third state id of the input.

	Real delta; //< The primary delta value of the input.
    Real delta2; //< The optional second delta value of the input.
    Real delta3; //< The optional third delta value of the input.

	Real absolute; //< The primary absolute value of the input.
	Real absolute2; //< The optional second absolute value of the input.
	Real absolute3; //< The optional third absolute value of the input.
};

/**
 * A listener class for input devices.
 */
class InputDeviceListener {
public:
    /**
     * Called when an event has been triggered.
     * @param event The event that was triggered.
     */
	virtual void onInputDeviceEvent(const InputDeviceEvent& event) = 0;
};

/**
 * A class representing any type of input device.
 * Input devices have a fixed number of analog and digital states that can be listened for changes.
 */
class InputDevice {
	BREW_EVENTSOURCE(InputDeviceListener, InputDeviceEvent);

public:
    /**
     * Creates a new input device.
     * @param numDigitalInputs The number of digital inputs.
     * @param numAnalogInputs The number of analog inputs.
     */
	InputDevice(u16 numDigitalInputs, u8 numAnalogInputs);

    /**
     * Sets an analog state.
     * @param stateId The id of the input state.
     * @param value The new value.
     */
	void setAnalog(u8 stateId, Real value);

    /**
     * Sets two analog states representing x and y axis.
     * @param xStateId The state id of the x axis.
     * @param yStateId The state id of the y axis.
     * @param xValue The new value of the x axis.
     * @param yValue The new value of the y axis.
     */
	void setAnalog2D(u8 xStateId, u8 yStateId, Real xValue, Real yValue);

    /**
     * Sets a digital state.
     * @param stateId The id of the input state.
     * @param value The new value.
     */
	void setDigital(u16 stateId, bool value);

private:
	std::vector<bool> digitalStates;
	std::vector<Real> analogStates;
};

} /* namespace brew */

#endif /* BREW_INPUTDEVICE_H_ */
