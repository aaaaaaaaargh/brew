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

#include <brew/input/InputManager.h>
#include <brew/core/Exception.h>

namespace brew {

bool InputManager::Mapping::operator<(const Mapping& other) const {
    return &device < &other.device || state < other.state;
}

const SizeT state2Offset = 10000;

bool InputManager::Mapping2D::operator<(const InputManager::Mapping2D& other) const {
    return &device < &other.device || (state < other.state && state2 + state2Offset < other.state2 + state2Offset);
}

bool InputManager::Mapping2DSource::operator<(const InputManager::Mapping2DSource& other) const {
    return (state < other.state && state2 + state2Offset < other.state2 + state2Offset);
}

void InputListener::onInputEvent(const InputEvent& evt) {
    switch (evt.type) {
        case InputEvent::Type::ButtonDown:
            onButtonDown(evt);
            break;
        case InputEvent::Type::ButtonUp:
            onButtonUp(evt);
            break;
        case InputEvent::Type::AxisMotion:
        case InputEvent::Type::AxisMotion2D:
            onAxisMotion(evt);
            break;
    }
}

InputManager::DeviceListener::DeviceListener(InputManager& manager) :
        manager(manager) {
}

void InputManager::DeviceListener::onInputDeviceEvent(const InputDeviceEvent& evt) {
    InputEvent e = {evt.device, InputEvent::Type::ButtonDown, 0, 0};

    switch (evt.type) {
        case InputDeviceEvent::Type::DigitalDown:
        case InputDeviceEvent::Type::DigitalUp: {
            e.type = evt.type == InputDeviceEvent::Type::DigitalDown ? InputEvent::Type::ButtonDown
                                                                     : InputEvent::Type::ButtonUp;
            Mapping mapping = {evt.device, evt.stateId};
            auto rng = manager.buttonLookup.equal_range(mapping);
            for (auto it = rng.first; it != rng.second; ++it) {
                e.stateId = it->second;

                manager.buttonStates[it->second] = evt.type == InputDeviceEvent::Type::DigitalDown;
                manager.fireInputEvent(e);
            }
            break;
        }
        case InputDeviceEvent::Type::AnalogMotion: {
            e.type = InputEvent::Type::AxisMotion;

            e.delta = evt.delta;

            e.absolute = evt.absolute;

            Mapping mapping = {evt.device, evt.stateId};
            auto rng = manager.axisLookup.equal_range(mapping);
            for (auto it = rng.first; it != rng.second; ++it) {
                e.stateId = it->second;

                manager.axisStates[it->second] = evt.absolute;

                manager.fireInputEvent(e);
            }
        }
        case InputDeviceEvent::Type::AnalogMotion2D: {
            e.type = InputEvent::Type::AxisMotion2D;

            e.delta = evt.delta;
            e.delta2 = evt.delta2;

            e.absolute = evt.absolute;
            e.absolute2 = evt.absolute2;

            Mapping2D mapping = {evt.device, evt.stateId, evt.stateId2};
            auto rng = manager.axis2DLookup.equal_range(mapping);
            for (auto it = rng.first; it != rng.second; ++it) {
                e.stateId = it->second.state;
                e.stateId2 = it->second.state2;

                manager.axisStates[it->second.state] = evt.absolute;
                manager.axisStates[it->second.state2] = evt.absolute2;

                manager.fireInputEvent(e);
            }
        }

    }

}

InputManager::InputManager() :
        listener(std::make_shared<DeviceListener>(*this)) {
}

void InputManager::assertOwnership(const InputDevice& dev) const {
    if (std::find_if(devices.begin(), devices.end(), [&](const std::unique_ptr<InputDevice>& d) {
        return d.get() == &dev;
    }) == devices.end()) {
        throw NotFoundException("No such device.");
    }
}

void InputManager::addButtonMapping(u16 buttonId, const InputDevice& dev, u16 stateId) {

    assertOwnership(dev);

    Mapping mapping = {dev, stateId};
    buttonMappings.insert(std::make_pair(buttonId, mapping));
    buttonLookup.insert(std::make_pair(mapping, buttonId));
}

void InputManager::addAxisMapping(u8 axisId, const InputDevice& dev, u8 stateId) {
    assertOwnership(dev);

    Mapping mapping = {dev, stateId};
    axisMappings.insert(std::make_pair(axisId, mapping));
    axisLookup.insert(std::make_pair(mapping, axisId));
}

void InputManager::addMultiAxisMapping(u8 axisId1, u8 axisId2, const InputDevice& dev, u8 stateId1, u8 stateId2) {
    assertOwnership(dev);

    Mapping2DSource source = {axisId1, axisId1};
    Mapping2D mapping = {dev, stateId1, stateId2};
    axis2DMappings.insert(std::make_pair(source, mapping));
    axis2DLookup.insert(std::make_pair(mapping, source));
}

const InputDevice& InputManager::getDevice(u8 deviceId) const {
    if (deviceId >= devices.size()) {
        throw NotFoundException("No such device.");
    }

    return *devices[deviceId];
}

void InputManager::registerDevice(std::unique_ptr<InputDevice> dev) {
    devices.emplace_back(std::move(dev));
    devices.back()->addInputDeviceListener(listener);
}

void InputManager::unregisterDevice(InputDevice& dev) {

    assertOwnership(dev);

    for (auto it = buttonMappings.begin(); it != buttonMappings.end();) {
        if (&it->second.device == &dev) {
            it = buttonMappings.erase(it);
        } else
            ++it;
    }

    for (auto it = buttonLookup.begin(); it != buttonLookup.end();) {
        if (&it->first.device == &dev) {
            it = buttonLookup.erase(it);
        } else
            ++it;
    }

    for (auto it = axisMappings.begin(); it != axisMappings.end();) {
        if (&it->second.device == &dev) {
            it = axisMappings.erase(it);
        } else
            ++it;
    }

    for (auto it = axisLookup.begin(); it != axisLookup.end();) {
        if (&it->first.device == &dev) {
            it = axisLookup.erase(it);
        } else
            ++it;
    }

    for (auto it = axis2DMappings.begin(); it != axis2DMappings.end();) {
        if (&it->second.device == &dev) {
            it = axis2DMappings.erase(it);
        } else
            ++it;
    }

    for (auto it = axis2DLookup.begin(); it != axis2DLookup.end();) {
        if (&it->first.device == &dev) {
            it = axis2DLookup.erase(it);
        } else
            ++it;
    }

    auto it = std::find_if(devices.begin(), devices.end(), [&](const std::unique_ptr<InputDevice>& d) {
        return d.get() == &dev;
    });

    devices.erase(it);
}

Real InputManager::getAxis(u8 axisId) const {
    auto state = axisStates.find(axisId);
    if (state != axisStates.end()) {
        return state->second;
    }
    return 0;
}

bool InputManager::getButton(u16 buttonId) const {
    auto state = buttonStates.find(buttonId);
    if (state != buttonStates.end()) {
        return state->second;
    }
    return false;
}

} /* namespace brew */
