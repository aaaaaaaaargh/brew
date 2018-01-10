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

#ifndef BREW_INPUTMANAGER_H
#define BREW_INPUTMANAGER_H

#include <brew/input/InputDevice.h>
#include <brew/core/EventSource.h>

#include <memory>
#include <vector>
#include <map>

namespace brew {

/**
 * An event class for input events.
 */
class InputEvent {
public:
	/**
	 * The event types.
	 */
	enum class Type {
		ButtonDown, //< A button was pressed.
		ButtonUp, //< A button was released.
		AxisMotion, //< An axis has been moved.
        AxisMotion2D //< A multi-axis has been moved.
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
 * A listener implementation for input events.
 */
class InputListener {
public:
	/**
	 * Called everytime when an input even has been triggered.
	 * @param event The event that was triggered.
	 */
	virtual void onInputEvent(const InputEvent& event);

	/**
	 * Called when a button has been pressed.
	 * @param event The event that was triggered.
	 */
	virtual void onButtonDown(const InputEvent& evt) = 0;

	/**
	 * Called when a button has been released.
	 * @param event The event that was triggered.
	 */
	virtual void onButtonUp(const InputEvent& evt) = 0;

	/**
	 * Called when an axis was moved.
	 * @param event The event that was triggered.
	 */
	virtual void onAxisMotion(const InputEvent& evt) = 0;
};

/**
 * The input manager acts as an abstraction layer between real peripheral hardware and a more
 * generic interface that unifies inputs into either buttons or axes.
 * Each hardware input state can be associated with one or more buttons or axes.
 */
class InputManager {
    BREW_EVENTSOURCE(InputListener, InputEvent);

public:
    /**
     * Creates a new input manager.
     */
	InputManager();

public:
	/**
	 * Adds a new button mapping for a hardware input state.
	 * @param buttonId The button id to associate with the hardware input.
	 * @param device The input device.
	 * @param stateId The state id of the hardware input.
	 * @throw InputException Raised when the given device is not owned by this manager.
	 */
	void addButtonMapping(u16 buttonId, const InputDevice& device, u16 stateId);

	/**
	 * Adds a new axis mapping for an analog hardware input state.
	 * @param axisId The id of the axis to associate with the hardware input.
	 * @param device The input device.
	 * @param stateId The state id of the hardware input.
	 * @throw InputException Raised when the given device is not owned by this manager.
	 */
	void addAxisMapping(u8 axisId, const InputDevice& device, u8 stateId);

    /**
	 * Adds a new multiaxis mapping for an analog hardware input state.
	 * @param axisId1 The id of the first axis to associate with the hardware input.
     * @param axisId2 The id of the second axis to associate with the hardware input.
	 * @param device The input device.
	 * @param stateId The state id of the hardware input.
	 * @throw InputException Raised when the given device is not owned by this manager.
	 */
    void addMultiAxisMapping(u8 axisId1, u8 axisId2, const InputDevice& device, u8 stateId1, u8 stateId2);

	/**
	 * Gets an input device by its id.
	 * @param deviceId The id of the input device.
	 * @return The input device.
	 * @throw InputException Raised when the given device does not exist.
	 */
	const InputDevice& getDevice(u8 deviceId) const;

    /**
     * Gets the current value of an axis.
     * @param axisId The id of the axis.
     * @return The current value of the axis.
     */
    Real getAxis(u8 axisId) const;

    /**
     * Gets the current state of a button.
     * @param buttonId The id of the button.
     * @return The current button state.
     */
    bool getButton(u16 buttonId) const;

private:
	void assertOwnership(const InputDevice& dev) const;

private:
	class DeviceListener : public InputDeviceListener {
	public:
		DeviceListener(InputManager& manager);
		virtual void onInputDeviceEvent(const InputDeviceEvent& evt);
		InputManager& manager;
	};

	std::shared_ptr<DeviceListener> listener;

protected:
	/**
	 * Registers a new device.
	 * @param device A pointer to the input device.
	 */
	void registerDevice(std::unique_ptr<InputDevice> device);

	/**
	 * Unregisters an input device.
	 * @param device The input device to unregister.
	 */
	void unregisterDevice(InputDevice& device);

protected:
	struct Mapping {
		const InputDevice& device;
		u16 state;
		bool operator < (const Mapping& other) const;
	};

    struct Mapping2DSource {
        u16 state;
        u16 state2;
        bool operator < (const Mapping2DSource& other) const;
    };

    struct Mapping2D {
        const InputDevice& device;
        u16 state;
        u16 state2;
        bool operator < (const Mapping2D& other) const;
    };

	std::vector<std::unique_ptr<InputDevice> > devices;
	std::multimap<u16, Mapping > buttonMappings;
	std::multimap<u8, Mapping > axisMappings;
    std::multimap<Mapping2DSource, Mapping2D> axis2DMappings;

	std::multimap<Mapping, u16> buttonLookup;
	std::multimap<Mapping, u8> axisLookup;
    std::multimap<Mapping2D, Mapping2DSource> axis2DLookup;

	std::map<u16, bool> buttonStates;
	std::map<u8, Real> axisStates;

};

} /* namespace brew */

#endif /* BREW_INPUTMANAGER_H */
