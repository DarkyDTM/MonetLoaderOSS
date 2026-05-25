#pragma once
#include "CVector.h"
#include <cstdint>

class CMatrix {
  public:
  CVector right;
  std::uint32_t flags;
  CVector up;
  float pad_u;
  CVector at;
  float pad_a;
  CVector pos;
  float pad_p;
  void* m_pAttachMatrix;
  bool m_bOwnsAttachedMatrix;

  CMatrix Inverted()
  {
    float det, invdet;
    CMatrix dst;
    // calculate a few cofactors
    dst.right.x = up.y * at.z - up.z * at.y;
    dst.right.y = at.y * right.z - at.z * right.y;
    dst.right.z = right.y * up.z - right.z * up.y;
    // get the determinant from that
    det = up.x * dst.right.y + at.x * dst.right.z + dst.right.x * right.x;
    invdet = 1.0;
    if (det != 0.0f)
      invdet = 1.0f / det;
    dst.right.x *= invdet;
    dst.right.y *= invdet;
    dst.right.z *= invdet;
    dst.up.x = invdet * (up.z * at.x - up.x * at.z);
    dst.up.y = invdet * (at.z * right.x - at.x * right.z);
    dst.up.z = invdet * (right.z * up.x - right.x * up.z);
    dst.at.x = invdet * (up.x * at.y - up.y * at.x);
    dst.at.y = invdet * (at.x * right.y - at.y * right.x);
    dst.at.z = invdet * (right.x * up.y - right.y * up.x);
    dst.pos.x = -(pos.x * dst.right.x + pos.y * dst.up.x + pos.z * dst.at.x);
    dst.pos.y = -(pos.x * dst.right.y + pos.y * dst.up.y + pos.z * dst.at.y);
    dst.pos.z = -(pos.x * dst.right.z + pos.y * dst.up.z + pos.z * dst.at.z);
    return dst;
  }

  friend CVector operator*(const CVector& vector, const CMatrix& matrix)
  {
    CVector t;
    t.x = matrix.at.x * vector.z + matrix.right.x * vector.x + matrix.up.x * vector.y;
    t.y = matrix.at.y * vector.z + matrix.right.y * vector.x + matrix.up.y * vector.y;
    t.z = matrix.at.z * vector.z + matrix.right.z * vector.x + matrix.up.z * vector.y;
    return t;
  }

  friend CVector& operator*=(CVector& vector, const CMatrix& matrix)
  {
    vector = vector * matrix;
    return vector;
  }
};