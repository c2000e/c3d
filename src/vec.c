#include "vec.h"

#define _USE_MATH_DEFINES
#include <math.h>

float radians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}

void Vec2_sub(Vec2 src_a, Vec2 src_b, Vec2 dst)
{
    dst[0] = src_a[0] - src_b[0];
    dst[1] = src_a[1] - src_b[1];
}

void Vec3_copy(Vec3 src, Vec3 dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void Vec3_scale(Vec3 src, float scale, Vec3 dst)
{
    dst[0] = src[0] * scale;
    dst[1] = src[1] * scale;
    dst[2] = src[2] * scale;
}

void Vec3_add(Vec3 src_a, Vec3 src_b, Vec3 dst)
{
    dst[0] = src_a[0] + src_b[0];
    dst[1] = src_a[1] + src_b[1];
    dst[2] = src_a[2] + src_b[2];
}

void Vec3_sub(Vec3 src_a, Vec3 src_b, Vec3 dst)
{
    dst[0] = src_a[0] - src_b[0];
    dst[1] = src_a[1] - src_b[1];
    dst[2] = src_a[2] - src_b[2];
}

void Vec3_mul(Vec3 src_a, Vec3 src_b, Vec3 dst)
{
    dst[0] = src_a[1] * src_b[2] - src_a[2] * src_b[1];
    dst[1] = src_a[2] * src_b[0] - src_a[0] * src_b[2];
    dst[2] = src_a[0] * src_b[1] - src_a[1] * src_b[0];
}

void Vec3_normalize(Vec3 src, Vec3 dst)
{
    float m = Vec3_mag(src);
    if (m > 0.0f)
    {
        dst[0] = src[0] / m;
        dst[1] = src[1] / m;
        dst[2] = src[2] / m;
    }
}

float Vec3_dot(Vec3 src_a, Vec3 src_b)
{
    return src_a[0] * src_b[0] + src_a[1] * src_b[1] + src_a[2] * src_b[2];
}

float Vec3_magSquared(Vec3 src)
{
    return Vec3_dot(src, src);
}

float Vec3_mag(Vec3 src)
{
    return sqrtf(Vec3_magSquared(src));
}

void Mat4_mul(Mat4 src_a, Mat4 src_b, Mat4 dst)
{
    // x basis
    dst[0][0] = src_a[0][0] * src_b[0][0] + src_a[1][0] * src_b[0][1] + src_a[2][0] * src_b[0][2] + src_a[3][0] * src_b[0][3];
    dst[0][1] = src_a[0][1] * src_b[0][0] + src_a[1][1] * src_b[0][1] + src_a[2][1] * src_b[0][2] + src_a[3][1] * src_b[0][3];
    dst[0][2] = src_a[0][2] * src_b[0][0] + src_a[1][2] * src_b[0][1] + src_a[2][2] * src_b[0][2] + src_a[3][2] * src_b[0][3];
    dst[0][3] = src_a[0][3] * src_b[0][0] + src_a[1][3] * src_b[0][1] + src_a[2][3] * src_b[0][2] + src_a[3][3] * src_b[0][3];

    // y basis
    dst[1][0] = src_a[0][0] * src_b[1][0] + src_a[1][0] * src_b[1][1] + src_a[2][0] * src_b[1][2] + src_a[3][0] * src_b[1][3];
    dst[1][1] = src_a[0][1] * src_b[1][0] + src_a[1][1] * src_b[1][1] + src_a[2][1] * src_b[1][2] + src_a[3][1] * src_b[1][3];
    dst[1][2] = src_a[0][2] * src_b[1][0] + src_a[1][2] * src_b[1][1] + src_a[2][2] * src_b[1][2] + src_a[3][2] * src_b[1][3];
    dst[1][3] = src_a[0][3] * src_b[1][0] + src_a[1][3] * src_b[1][1] + src_a[2][3] * src_b[1][2] + src_a[3][3] * src_b[1][3];

    // z basis
    dst[2][0] = src_a[0][0] * src_b[2][0] + src_a[1][0] * src_b[2][1] + src_a[2][0] * src_b[2][2] + src_a[3][0] * src_b[2][3];
    dst[2][1] = src_a[0][1] * src_b[2][0] + src_a[1][1] * src_b[2][1] + src_a[2][1] * src_b[2][2] + src_a[3][1] * src_b[2][3];
    dst[2][2] = src_a[0][2] * src_b[2][0] + src_a[1][2] * src_b[2][1] + src_a[2][2] * src_b[2][2] + src_a[3][2] * src_b[2][3];
    dst[2][3] = src_a[0][3] * src_b[2][0] + src_a[1][3] * src_b[2][1] + src_a[2][3] * src_b[2][2] + src_a[3][3] * src_b[2][3];

    // w basis
    dst[3][0] = src_a[0][0] * src_b[3][0] + src_a[1][0] * src_b[3][1] + src_a[2][0] * src_b[3][2] + src_a[3][0] * src_b[3][3];
    dst[3][1] = src_a[0][1] * src_b[3][0] + src_a[1][1] * src_b[3][1] + src_a[2][1] * src_b[3][2] + src_a[3][1] * src_b[3][3];
    dst[3][2] = src_a[0][2] * src_b[3][0] + src_a[1][2] * src_b[3][1] + src_a[2][2] * src_b[3][2] + src_a[3][2] * src_b[3][3];
    dst[3][3] = src_a[0][3] * src_b[3][0] + src_a[1][3] * src_b[3][1] + src_a[2][3] * src_b[3][2] + src_a[3][3] * src_b[3][3];
}

void Mat4_lookAt(Vec3 camera, Vec3 target, Vec3 up, Mat4 dst)
{
    Vec3 f;
    Vec3_sub(target, camera, f);
    Vec3_normalize(f, f);

    Vec3 s;
    Vec3_mul(f, up, s);
    Vec3_normalize(s, s);

    Vec3 u;
    Vec3_mul(s, f, u);
    Vec3_normalize(s, s);

    // x basis
    dst[0][0] = s[0];
    dst[0][1] = u[0];
    dst[0][2] = -f[0];
    dst[0][3] = 0.0f;

    // y basis
    dst[1][0] = s[1];
    dst[1][1] = u[1];
    dst[1][2] = -f[1];
    dst[1][3] = 0.0f;

    // z basis
    dst[2][0] = s[2];
    dst[2][1] = u[2];
    dst[2][2] = -f[2];
    dst[2][3] = 0.0f;

    // w basis
    dst[3][0] = -Vec3_dot(s, camera);
    dst[3][1] = -Vec3_dot(u, camera);
    dst[3][2] = Vec3_dot(f, camera);
    dst[3][3] = 1.0f;
}

void Mat4_perspective(float fov, float aspect, float near, float far, Mat4 dst)
{
    float tan_half_fov = tanf(fov * 0.5f);

    // x basis
    dst[0][0] = 1.0f / (aspect * tan_half_fov);
    dst[0][1] = 0.0f;
    dst[0][2] = 0.0f;
    dst[0][3] = 0.0f;

    // y basis
    dst[1][0] = 0.0f;
    dst[1][1] = 1.0f / (tan_half_fov);
    dst[1][2] = 0.0f;
    dst[1][3] = 0.0f;

    // z basis
    dst[2][0] = 0.0f;
    dst[2][1] = 0.0f;
    dst[2][2] = -(far + near) / (far - near);
    dst[2][3] = -1.0f;

    // w basis
    dst[3][0] = 0.0f;
    dst[3][1] = 0.0f;
    dst[3][2] = -(2 * far * near) / (far - near);
    dst[3][3] = 0.0f;
}