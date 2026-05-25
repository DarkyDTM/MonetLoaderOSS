#pragma once
#include "CMatrix.h"
#include <algorithm>
#include <cmath>

class CQuaternion {
  public:
  CQuaternion()
      : x(0)
      , y(0)
      , z(0)
      , w(1) {};
  CQuaternion(float _x, float _y, float _z, float _w)
      : x(_x)
      , y(_y)
      , z(_z)
      , w(_w) {};

  void Set(const CMatrix& mat)
  {
    w = std::sqrtf(std::max(0.f, 1.0f + mat.right.x + mat.up.y + mat.at.z)) * 0.5f;
    x = std::sqrtf(std::max(0.f, 1.0f + mat.right.x - mat.up.y - mat.at.z)) * 0.5f;
    y = std::sqrtf(std::max(0.f, 1.0f - mat.right.x + mat.up.y - mat.at.z)) * 0.5f;
    z = std::sqrtf(std::max(0.f, 1.0f - mat.right.x - mat.up.y + mat.at.z)) * 0.5f;

    x = std::copysign(x, mat.at.y - mat.up.z);
    y = std::copysign(y, mat.right.z - mat.at.x);
    z = std::copysign(z, mat.up.x - mat.right.y);
  }

  void Get(CMatrix* mat)
  {
    float sqw = w * w; // v13 = a1 * a1;
    float sqx = x * x; // v14 = a2 * a2;
    float sqy = y * y; // v15 = a3 * a3;
    float sqz = z * z; // v16 = a4 * a4;

    mat->right.x = (sqx - sqy - sqz + sqw); // a5 = v14 - v15 - v16 + v13;
    mat->up.y = (-sqx + sqy - sqz + sqw); // a9 = v15 - v14 - v16 + v13;
    mat->at.z = (-sqx - sqy + sqz + sqw); // a13 = v16 - (v15 + v14) + v13;

    float tmp1 = x * y; // v17 = a2 * a3;
    float tmp2 = z * w; // v18 = a1 * a4;
    mat->up.x = 2.f * (tmp1 + tmp2); // a8 = v18 + v17 + v18 + v17;
    mat->right.y = 2.f * (tmp1 - tmp2); // a6 = v17 - v18 + v17 - v18;

    tmp1 = x * z; // v20 = a2 * a4;
    tmp2 = y * w; // v21 = a1 * a3;
    mat->at.x = 2.f * (tmp1 - tmp2); // a11 = v20 - v21 + v20 - v21;
    mat->right.z = 2.f * (tmp1 + tmp2); // a7 = v21 + v20 + v21 + v20;
    tmp1 = y * z; // v22 = a3 * a4;
    tmp2 = x * w; // v23 = a1 * a2;
    mat->at.y = 2.f * (tmp1 + tmp2); // a12 = v23 + v22 + v23 + v22;
    mat->up.z = 2.f * (tmp1 - tmp2); // a10 = v22 - v23 + v22 - v23;
  }

  float x;
  float y;
  float z;
  float w;
};