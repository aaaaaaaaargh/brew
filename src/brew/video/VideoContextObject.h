/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 24.01.18
 *
 */

#ifndef BREW_VIDEOCONTEXTOBJECT_H
#define BREW_VIDEOCONTEXTOBJECT_H

namespace brew {

class VideoContext;

/**
 * An interface for video context objects.
 */
class VideoContextObject {
    friend class VideoContext;

public:
    /**
     * @return The context associated with this object.
     */
    inline VideoContext& getContext() {
        return *context;
    }

private:
    VideoContext* context = nullptr;
};

} /* namespace brew */

#endif //BREW_VIDEOCONTEXTOBJECT_H
