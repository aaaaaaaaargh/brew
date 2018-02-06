/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 04.09.17
 *
 */

#include <gtest/gtest.h>

#include <brew/math/Math.h>
#include <brew/math/Matrix4.h>
#include <brew/math/Quaternion.h>

using namespace brew;

TEST(Quaternion, ConvertFromToEuler) {
    {
        Quaternion q;
        q.setFromEulerAngles(0, 0, 0);
        Quaternion qr(0, 0, 0, 1);

        EXPECT_EQ(qr, q);
    }

    {
        Quaternion q;
        q.setFromAxisAngle(Vec3(1,1,0), math::deg2Rad(45));
        Quaternion qr(0.382683,0.382683,0,0.92388);
        EXPECT_EQ(qr, q);
    }

    {
        Quaternion q;
        Real yaw = math::deg2Rad(-90);
        Real pitch = math::deg2Rad(52);
        Real roll = math::deg2Rad(34);
        q.setFromEulerAngles(yaw, pitch, roll);

        EXPECT_FLOAT_EQ(q.getYaw(), yaw);
        EXPECT_FLOAT_EQ(q.getPitch(), pitch);
        EXPECT_FLOAT_EQ(q.getRoll(), roll);
    }
}

TEST(Quaternion, ConvertToRotationMatrix) {

    Quaternion q(1,2,3,4);

    Matrix4 mat;
    Matrix4 rmat(
            -25,28,-10,0,
            -20,-19,20,0,
            22,4,-9,0,
            0,0,0,1
    );

    q.toRotationMatrix(mat);

    EXPECT_EQ(mat, rmat);
}

TEST(Quaternion, Conjugate) {
    Quaternion q(1,2,3,4);
    Quaternion eq(1,-2,-3,-4);
    Quaternion c = q.conjugated();

    EXPECT_EQ(eq, c);
}

TEST(Quaternion, Normalize) {
    Quaternion q(1,4,4,-4);
    EXPECT_EQ(7, q.getLength());
}

TEST(Quaternion, Invert) {
    Quaternion q(1,2,3,4);
    Quaternion iq = q.inverted();
    Quaternion expected(-0.0333f, -0.0666f, -0.1f, 0.133f);

    EXPECT_EQ(expected, iq);

    Quaternion iq2 = iq.inverted();

    EXPECT_EQ(q, iq2);
}

