/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 09.01.18
 *
 */

#ifndef BREW_ANIMATION_H
#define BREW_ANIMATION_H

namespace brew {

/**
 * The play modes of an animation.
 */
enum class PlayMode {
    Normal, //< Regular playback.
    PingPong, //< Play in ping-pong mode.
};

/**
 * A basic class for keyframed animations that supports playback modes, reverse and looping as well as
 * absolute timed keyframe access.
 * @tparam KeyFrameT The key frame type.
 */
template<typename KeyFrameT>
class Animation {
public:
    /**
     * Creates a new animation.
     * @param frameDuration The fixed frame duration.
     * @param initialKeyFrames A list of initial key frames.
     */
    Animation(Real frameDuration, std::initializer_list<KeyFrameT> initialKeyFrames)
    : Animation(frameDuration) {
        addKeyFrames(initialKeyFrames);
    }

    /**
     * Creates a new empty animation.
     * @param frameDuration The fixed frame duration.
     */
    Animation(Real frameDuration)
            : frameDuration(frameDuration), totalTime(0) {
    }

    /**
     * Adds multiple key frames to the animation.
     * @param keyFrames A list of key frames to add.
     */
    void addKeyFrames(std::initializer_list<KeyFrameT> keyFrames) {
        for(const auto& keyFrame : initialKeyFrames) {
            addKeyFrame(keyFrame);
        }
    }

    /**
     * Adds a single key frame.
     * @param keyFrame The key frame to add.
     * @param repeats (optional) The number of frames to repeat this key frame.
     */
    void addKeyFrame(const KeyFrameT& keyFrame, SizeT repeats = 0) {
        keyFrames.push_back(keyFrame);
        totalTime += frameDuration;

        for(SizeT i=0;i<repeats;++i) {
            addKeyFrame(keyFrame);
        }
    }

    /**
     * Resolves the index of a key frame.
     * @param time The absolute time.
     * @param playMode The play mode.
     * @param isLooping Whether the animation should loop.
     * @param reverse Whether the animation should be played in reverse.
     * @return The resolved key frame index.
     */
    SizeT getKeyFrameIndex(Real time, PlayMode playMode = PlayMode::Normal, bool isLooping = true, bool reverse = false) {
        if(keyFrames.empty()) {
            throw IllegalStateException("No key frames defined.");
        }

        if(time < 0) {
            // Do not allow negative values.
            time = 0;
        }

        Real delta;

        if(playMode == PlayMode::Normal) {
            if(!isLooping && time >= totalTime) {
                // Exceeded and should not loop.
                time = totalTime;
            }

            // Clamp the delta time.
            delta = std::fmod(time, totalTime);

            if(reverse) {
                // Reverse the animation.
                delta = totalTime - std::fmod(time, totalTime);
            }
        } else if(playMode == PlayMode::PingPong) {
            Real totalTime2 = totalTime * 2;

            if(!isLooping && time >= totalTime2) {
                // Exceeded and should not loop.
                time = totalTime;
            }

            // Allow 2 * total time for going back.
            delta = std::fmod(time, totalTime2);

            if(delta >= totalTime) {
                // Play reverse direction.
                delta = totalTime - (delta - totalTime);
            }
        }

        if(reverse) {
            // Reverse the animation.
            delta = totalTime - delta;
        }

        return static_cast<SizeT>(std::floor(delta / frameDuration));
    }

    /**
     * Resolves a key frame.
     * @param time The absolute time.
     * @param playMode The play mode.
     * @param isLooping Whether the animation should loop.
     * @param reverse Whether the animation should be played in reverse.
     * @return The resolved key frame.
     */
    const KeyFrameT& getKeyFrame(Real time, PlayMode playMode = PlayMode::Normal, bool isLooping = true, bool reverse = false) {
        return keyFrames[getKeyFrameIndex(time, playMode, isLooping, reverse)];
    }

    /**
     * Sets the fixed frame duration.
     * @param newDuration The new duration.
     */
    void setFrameDuration(Real newDuration) {
        frameDuration = newDuration;
        totalTime = keyFrames.size() * frameDuration;
    }

    /**
     * @return The fixed frame duration.
     */
    inline Real getFrameDuration() const {
        return frameDuration;
    }

    /**
     * Gets the animations total play time.
     * @param playMode The play mode.
     * @return The total play time of this animation.
     */
    inline Real getTotalTime(PlayMode playMode = PlayMode::Normal) const {
        if(playMode == PlayMode::PingPong) {
            return totalTime * 2;
        }

        return totalTime;
    }

private:
    std::vector<KeyFrameT> keyFrames;
    Real frameDuration;
    Real totalTime;
};

} /* namespace brew */

#endif //BOXQUEST_ANIMATION_H
