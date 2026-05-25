#pragma once
#include "CCopPed.h"
#include "CCutsceneObject.h"
#include "CHeli.h"
#include "CObject.h"
#include "CPed.h"
#include "CPlane.h"
#include "CPool.h"
#include "CVehicle.h"

#include "gta_struct.inl"
namespace CPools {
namespace detail {
  template <bool, typename T1, typename T2>
  struct is_cond {
    using type = T1;
  };

  template <typename T1, typename T2>
  struct is_cond<false, T1, T2> {
    using type = T2;
  };

  template <typename T1, typename T2>
  struct largest {
    using type = typename is_cond<(sizeof(T1) > sizeof(T2)), T1, T2>::type;
  };
}

inline CPool<CPed, CCopPed>* GetPedPool()
{
  return *reinterpret_cast<CPool<CPed, CCopPed>**>(lib_manager::ped_pool);
}

inline CPool<CVehicle, detail::largest<CPlane, CHeli>::type>* GetVehiclePool()
{
  return *reinterpret_cast<CPool<CVehicle, detail::largest<CPlane, CHeli>::type>**>(lib_manager::vehicle_pool);
}

inline CPool<CObject, CCutsceneObject>* GetObjectPool()
{
  return *reinterpret_cast<CPool<CObject, CCutsceneObject>**>(lib_manager::object_pool);
}
}
#include "gta_struct.inl"
