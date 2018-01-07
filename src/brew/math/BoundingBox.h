/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Feb 11, 2016
 *
 */

#ifndef BREW_BOUNDINGBOX_H
#define BREW_BOUNDINGBOX_H

#include <brew/math/Vec3.h>
#include <brew/math/Matrix4.h>

#include <brew/core/Exception.h>

namespace brew {

/**
 * This class represents an axis aligned bounding box.
 * Typically, axis aligned bounding boxes can be used to check for intersections with geometry on a very fast but rough level.
 * For example, if you just need to pick an object from the scene, an axis aligned bounding box might be perfectly fine.
 * If you want to pick certain sides of the object then you would need a more advanced approach like ray queries.
 **/
class BoundingBox {
public:
	/**
	 * Corners of the bounding box. Lowercase literals mean upper/left/back sides, uppercase literals mean lower/right/front sides.
	 */
	enum class Corner {
		xyz,
		Xyz,
		xYz,
		xyZ,
		XYz,
		XyZ,
		xYZ,
		XYZ,
		Invalid
	};

public:
	BoundingBox();
	BoundingBox(const Vec3& min, const Vec3& max);
	BoundingBox(const BoundingBox& other) = default;
	inline virtual ~BoundingBox() {}

	/**
	 * Arthmetic operations.
	 */
	BoundingBox& operator = (const BoundingBox& other);
	BoundingBox& operator += (const BoundingBox& other);
	BoundingBox operator += (const Vec3& point);
	BoundingBox operator + (const BoundingBox& other) const;
	BoundingBox operator + (const Vec3& point) const;
	BoundingBox operator *= (const Matrix4& transform);
	BoundingBox operator * (const Matrix4& transform) const;

	bool operator == (const BoundingBox& other) const;

	inline bool operator != (const BoundingBox& other) const {
		return !operator==(other);
	}

	/**
	 * Sets the minimum (upper left back edge of the box).
	 * @param the new minimum value
	 */
	void setMinimum(const Vec3& min);

	/**
	 * @return the minimum (upper left back edge of the box).
	 */
	inline const Vec3& getMinimum() const {
		return min;
	}

	/**
	 * Sets the maximum (lower right front edge of the box).
	 * @param the new maximum value
	 */
	void setMaximum(const Vec3& max);

	/**
	 * @return the maximum (lower right front edge of the box).
	 */
	inline const Vec3& getMaximum() const {
		return max;
	}

	/**
	 * @param upperX true for right side, false for left side.
	 * @param upperY true for lower side, false for upper side.
	 * @param upperZ true for front side, false for back side.
	 * @return the correct enum value described by the three arguments.
	 */
	static Corner corner(bool upperX, bool upperY, bool upperZ);

	/**
	 * @param corner one of the enum values describing the corner. A lowercase letter indicates the dimensional minimum, uppercase means maximum (left/right, top/bottom, back/front).
	 * @return a point describing the exact position of the given corner.
	 */
	Vec3 getCorner(const Corner& corner) const;
	inline Vec3 getCorner(bool upperX, bool upperY, bool upperZ) const {
		return getCorner(corner(upperX, upperY, upperZ));
	}

	/**
	 * @return a vector describing the exact center of this bounding box.
	 */
	Vec3 getCenter() const;

	/**
	 * Sets the extents of the bounding box by specifying a minimum and maximum point in space.
	 * @param min the minimum (upper left front) edge
	 * @param max the maxumum (lower right back) edge
	 */
	void set(const Vec3& min, const Vec3& max);

	/**
	 * @param point a point in 3D space
	 * @return true if the point is inside this bounding box.
	 */
	bool contains(const Vec3& point) const;

	/**
	 * @param other another bounding box
	 * @return true if others extents are completely inside this bounding box.
	 */
	bool contains(const BoundingBox& other) const;

	/**
	 * @param other bounding box to check for intersection with this one.
	 * @return true if there is any intersection between this and other
	 */
	bool intersects(const BoundingBox& other) const;

	/**
	 * @return true if the extents of the bounding box are within finite space.
	 */
	bool isFinite() const;

private:
	Vec3 min;
	Vec3 max;

private:
	friend std::ostream& operator << (std::ostream& stream, const BoundingBox& bbox);

public:
	/**
	 * A bounding box of infinite dimensions. Can be used like a nullptr-like structure.
	 */
	static const BoundingBox INF;
};

/**
 * Stream implementation for bounding boxes.
 * @param stream The output stream to write to.
 * @param bbox The bounding box.
 * @return The stream for chaining.
 */
std::ostream& operator << (std::ostream& stream, const BoundingBox& bbox);

} /* namespace brew */

#endif /* BREW_BOUNDINGBOX_H */
