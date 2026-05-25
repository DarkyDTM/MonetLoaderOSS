#include "bass_manager.h"
#include "bass.h"
#include <dlfcn.h>

void bass_manager::init()
{
  void* handle = dlopen("libbass.so", RTLD_NOW);
  if (!handle) {
    inited = false;
    return;
  }

  BASS_SetConfig = reinterpret_cast<decltype(BASS_SetConfig)>(dlsym(handle, "BASS_SetConfig"));
  BASS_GetConfig = reinterpret_cast<decltype(BASS_GetConfig)>(dlsym(handle, "BASS_GetConfig"));
  BASS_SetConfigPtr = reinterpret_cast<decltype(BASS_SetConfigPtr)>(dlsym(handle, "BASS_SetConfigPtr"));
  BASS_GetConfigPtr = reinterpret_cast<decltype(BASS_GetConfigPtr)>(dlsym(handle, "BASS_GetConfigPtr"));
  BASS_GetVersion = reinterpret_cast<decltype(BASS_GetVersion)>(dlsym(handle, "BASS_GetVersion"));
  BASS_ErrorGetCode = reinterpret_cast<decltype(BASS_ErrorGetCode)>(dlsym(handle, "BASS_ErrorGetCode"));

  BASS_GetDeviceInfo = reinterpret_cast<decltype(BASS_GetDeviceInfo)>(dlsym(handle, "BASS_GetDeviceInfo"));
  BASS_Init = reinterpret_cast<decltype(BASS_Init)>(dlsym(handle, "BASS_Init"));
  BASS_Free = reinterpret_cast<decltype(BASS_Free)>(dlsym(handle, "BASS_Free"));
  BASS_SetDevice = reinterpret_cast<decltype(BASS_SetDevice)>(dlsym(handle, "BASS_SetDevice"));
  BASS_GetDevice = reinterpret_cast<decltype(BASS_GetDevice)>(dlsym(handle, "BASS_GetDevice"));
  BASS_GetInfo = reinterpret_cast<decltype(BASS_GetInfo)>(dlsym(handle, "BASS_GetInfo"));
  BASS_Start = reinterpret_cast<decltype(BASS_Start)>(dlsym(handle, "BASS_Start"));
  BASS_Stop = reinterpret_cast<decltype(BASS_Stop)>(dlsym(handle, "BASS_Stop"));
  BASS_Pause = reinterpret_cast<decltype(BASS_Pause)>(dlsym(handle, "BASS_Pause"));
  BASS_IsStarted = reinterpret_cast<decltype(BASS_IsStarted)>(dlsym(handle, "BASS_IsStarted"));
  BASS_Update = reinterpret_cast<decltype(BASS_Update)>(dlsym(handle, "BASS_Update"));
  BASS_GetCPU = reinterpret_cast<decltype(BASS_GetCPU)>(dlsym(handle, "BASS_GetCPU"));
  BASS_SetVolume = reinterpret_cast<decltype(BASS_SetVolume)>(dlsym(handle, "BASS_SetVolume"));
  BASS_GetVolume = reinterpret_cast<decltype(BASS_GetVolume)>(dlsym(handle, "BASS_GetVolume"));
#if defined(_WIN32) && !defined(_WIN32_WCE) && !(defined(WINAPI_FAMILY) && WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
  BASS_GetDSoundObject = reinterpret_cast<decltype(BASS_GetDSoundObject)>(dlsym(handle, "BASS_GetDSoundObject"));
#endif

  BASS_Set3DFactors = reinterpret_cast<decltype(BASS_Set3DFactors)>(dlsym(handle, "BASS_Set3DFactors"));
  BASS_Get3DFactors = reinterpret_cast<decltype(BASS_Get3DFactors)>(dlsym(handle, "BASS_Get3DFactors"));
  BASS_Set3DPosition = reinterpret_cast<decltype(BASS_Set3DPosition)>(dlsym(handle, "BASS_Set3DPosition"));
  BASS_Get3DPosition = reinterpret_cast<decltype(BASS_Get3DPosition)>(dlsym(handle, "BASS_Get3DPosition"));
  BASS_Apply3D = reinterpret_cast<decltype(BASS_Apply3D)>(dlsym(handle, "BASS_Apply3D"));

  BASS_PluginLoad = reinterpret_cast<decltype(BASS_PluginLoad)>(dlsym(handle, "BASS_PluginLoad"));
  BASS_PluginFree = reinterpret_cast<decltype(BASS_PluginFree)>(dlsym(handle, "BASS_PluginFree"));
  BASS_PluginEnable = reinterpret_cast<decltype(BASS_PluginEnable)>(dlsym(handle, "BASS_PluginEnable"));
  BASS_PluginGetInfo = reinterpret_cast<decltype(BASS_PluginGetInfo)>(dlsym(handle, "BASS_PluginGetInfo"));

  BASS_SampleLoad = reinterpret_cast<decltype(BASS_SampleLoad)>(dlsym(handle, "BASS_SampleLoad"));
  BASS_SampleCreate = reinterpret_cast<decltype(BASS_SampleCreate)>(dlsym(handle, "BASS_SampleCreate"));
  BASS_SampleFree = reinterpret_cast<decltype(BASS_SampleFree)>(dlsym(handle, "BASS_SampleFree"));
  BASS_SampleSetData = reinterpret_cast<decltype(BASS_SampleSetData)>(dlsym(handle, "BASS_SampleSetData"));
  BASS_SampleGetData = reinterpret_cast<decltype(BASS_SampleGetData)>(dlsym(handle, "BASS_SampleGetData"));
  BASS_SampleGetInfo = reinterpret_cast<decltype(BASS_SampleGetInfo)>(dlsym(handle, "BASS_SampleGetInfo"));
  BASS_SampleSetInfo = reinterpret_cast<decltype(BASS_SampleSetInfo)>(dlsym(handle, "BASS_SampleSetInfo"));
  BASS_SampleGetChannel = reinterpret_cast<decltype(BASS_SampleGetChannel)>(dlsym(handle, "BASS_SampleGetChannel"));
  BASS_SampleGetChannels = reinterpret_cast<decltype(BASS_SampleGetChannels)>(dlsym(handle, "BASS_SampleGetChannels"));
  BASS_SampleStop = reinterpret_cast<decltype(BASS_SampleStop)>(dlsym(handle, "BASS_SampleStop"));

  BASS_StreamCreate = reinterpret_cast<decltype(BASS_StreamCreate)>(dlsym(handle, "BASS_StreamCreate"));
  BASS_StreamCreateFile = reinterpret_cast<decltype(BASS_StreamCreateFile)>(dlsym(handle, "BASS_StreamCreateFile"));
  BASS_StreamCreateURL = reinterpret_cast<decltype(BASS_StreamCreateURL)>(dlsym(handle, "BASS_StreamCreateURL"));
  BASS_StreamCreateFileUser = reinterpret_cast<decltype(BASS_StreamCreateFileUser)>(dlsym(handle, "BASS_StreamCreateFileUser"));
  BASS_StreamFree = reinterpret_cast<decltype(BASS_StreamFree)>(dlsym(handle, "BASS_StreamFree"));
  BASS_StreamGetFilePosition = reinterpret_cast<decltype(BASS_StreamGetFilePosition)>(dlsym(handle, "BASS_StreamGetFilePosition"));
  BASS_StreamPutData = reinterpret_cast<decltype(BASS_StreamPutData)>(dlsym(handle, "BASS_StreamPutData"));
  BASS_StreamPutFileData = reinterpret_cast<decltype(BASS_StreamPutFileData)>(dlsym(handle, "BASS_StreamPutFileData"));

  BASS_MusicLoad = reinterpret_cast<decltype(BASS_MusicLoad)>(dlsym(handle, "BASS_MusicLoad"));
  BASS_MusicFree = reinterpret_cast<decltype(BASS_MusicFree)>(dlsym(handle, "BASS_MusicFree"));

  BASS_RecordGetDeviceInfo = reinterpret_cast<decltype(BASS_RecordGetDeviceInfo)>(dlsym(handle, "BASS_RecordGetDeviceInfo"));
  BASS_RecordInit = reinterpret_cast<decltype(BASS_RecordInit)>(dlsym(handle, "BASS_RecordInit"));
  BASS_RecordFree = reinterpret_cast<decltype(BASS_RecordFree)>(dlsym(handle, "BASS_RecordFree"));
  BASS_RecordSetDevice = reinterpret_cast<decltype(BASS_RecordSetDevice)>(dlsym(handle, "BASS_RecordSetDevice"));
  BASS_RecordGetDevice = reinterpret_cast<decltype(BASS_RecordGetDevice)>(dlsym(handle, "BASS_RecordGetDevice"));
  BASS_RecordGetInfo = reinterpret_cast<decltype(BASS_RecordGetInfo)>(dlsym(handle, "BASS_RecordGetInfo"));
  BASS_RecordGetInputName = reinterpret_cast<decltype(BASS_RecordGetInputName)>(dlsym(handle, "BASS_RecordGetInputName"));
  BASS_RecordSetInput = reinterpret_cast<decltype(BASS_RecordSetInput)>(dlsym(handle, "BASS_RecordSetInput"));
  BASS_RecordGetInput = reinterpret_cast<decltype(BASS_RecordGetInput)>(dlsym(handle, "BASS_RecordGetInput"));
  BASS_RecordStart = reinterpret_cast<decltype(BASS_RecordStart)>(dlsym(handle, "BASS_RecordStart"));

  BASS_ChannelBytes2Seconds = reinterpret_cast<decltype(BASS_ChannelBytes2Seconds)>(dlsym(handle, "BASS_ChannelBytes2Seconds"));
  BASS_ChannelSeconds2Bytes = reinterpret_cast<decltype(BASS_ChannelSeconds2Bytes)>(dlsym(handle, "BASS_ChannelSeconds2Bytes"));
  BASS_ChannelGetDevice = reinterpret_cast<decltype(BASS_ChannelGetDevice)>(dlsym(handle, "BASS_ChannelGetDevice"));
  BASS_ChannelSetDevice = reinterpret_cast<decltype(BASS_ChannelSetDevice)>(dlsym(handle, "BASS_ChannelSetDevice"));
  BASS_ChannelIsActive = reinterpret_cast<decltype(BASS_ChannelIsActive)>(dlsym(handle, "BASS_ChannelIsActive"));
  BASS_ChannelGetInfo = reinterpret_cast<decltype(BASS_ChannelGetInfo)>(dlsym(handle, "BASS_ChannelGetInfo"));
  BASS_ChannelGetTags = reinterpret_cast<decltype(BASS_ChannelGetTags)>(dlsym(handle, "BASS_ChannelGetTags"));
  BASS_ChannelFlags = reinterpret_cast<decltype(BASS_ChannelFlags)>(dlsym(handle, "BASS_ChannelFlags"));
  BASS_ChannelLock = reinterpret_cast<decltype(BASS_ChannelLock)>(dlsym(handle, "BASS_ChannelLock"));
  BASS_ChannelFree = reinterpret_cast<decltype(BASS_ChannelFree)>(dlsym(handle, "BASS_ChannelFree"));
  BASS_ChannelPlay = reinterpret_cast<decltype(BASS_ChannelPlay)>(dlsym(handle, "BASS_ChannelPlay"));
  BASS_ChannelStart = reinterpret_cast<decltype(BASS_ChannelStart)>(dlsym(handle, "BASS_ChannelStart"));
  BASS_ChannelStop = reinterpret_cast<decltype(BASS_ChannelStop)>(dlsym(handle, "BASS_ChannelStop"));
  BASS_ChannelPause = reinterpret_cast<decltype(BASS_ChannelPause)>(dlsym(handle, "BASS_ChannelPause"));
  BASS_ChannelUpdate = reinterpret_cast<decltype(BASS_ChannelUpdate)>(dlsym(handle, "BASS_ChannelUpdate"));
  BASS_ChannelSetAttribute = reinterpret_cast<decltype(BASS_ChannelSetAttribute)>(dlsym(handle, "BASS_ChannelSetAttribute"));
  BASS_ChannelGetAttribute = reinterpret_cast<decltype(BASS_ChannelGetAttribute)>(dlsym(handle, "BASS_ChannelGetAttribute"));
  BASS_ChannelSlideAttribute = reinterpret_cast<decltype(BASS_ChannelSlideAttribute)>(dlsym(handle, "BASS_ChannelSlideAttribute"));
  BASS_ChannelIsSliding = reinterpret_cast<decltype(BASS_ChannelIsSliding)>(dlsym(handle, "BASS_ChannelIsSliding"));
  BASS_ChannelSetAttributeEx = reinterpret_cast<decltype(BASS_ChannelSetAttributeEx)>(dlsym(handle, "BASS_ChannelSetAttributeEx"));
  BASS_ChannelGetAttributeEx = reinterpret_cast<decltype(BASS_ChannelGetAttributeEx)>(dlsym(handle, "BASS_ChannelGetAttributeEx"));
  BASS_ChannelSet3DAttributes = reinterpret_cast<decltype(BASS_ChannelSet3DAttributes)>(dlsym(handle, "BASS_ChannelSet3DAttributes"));
  BASS_ChannelGet3DAttributes = reinterpret_cast<decltype(BASS_ChannelGet3DAttributes)>(dlsym(handle, "BASS_ChannelGet3DAttributes"));
  BASS_ChannelSet3DPosition = reinterpret_cast<decltype(BASS_ChannelSet3DPosition)>(dlsym(handle, "BASS_ChannelSet3DPosition"));
  BASS_ChannelGet3DPosition = reinterpret_cast<decltype(BASS_ChannelGet3DPosition)>(dlsym(handle, "BASS_ChannelGet3DPosition"));
  BASS_ChannelGetLength = reinterpret_cast<decltype(BASS_ChannelGetLength)>(dlsym(handle, "BASS_ChannelGetLength"));
  BASS_ChannelSetPosition = reinterpret_cast<decltype(BASS_ChannelSetPosition)>(dlsym(handle, "BASS_ChannelSetPosition"));
  BASS_ChannelGetPosition = reinterpret_cast<decltype(BASS_ChannelGetPosition)>(dlsym(handle, "BASS_ChannelGetPosition"));
  BASS_ChannelGetLevel = reinterpret_cast<decltype(BASS_ChannelGetLevel)>(dlsym(handle, "BASS_ChannelGetLevel"));
  BASS_ChannelGetLevelEx = reinterpret_cast<decltype(BASS_ChannelGetLevelEx)>(dlsym(handle, "BASS_ChannelGetLevelEx"));
  BASS_ChannelGetData = reinterpret_cast<decltype(BASS_ChannelGetData)>(dlsym(handle, "BASS_ChannelGetData"));
  BASS_ChannelSetSync = reinterpret_cast<decltype(BASS_ChannelSetSync)>(dlsym(handle, "BASS_ChannelSetSync"));
  BASS_ChannelRemoveSync = reinterpret_cast<decltype(BASS_ChannelRemoveSync)>(dlsym(handle, "BASS_ChannelRemoveSync"));
  BASS_ChannelSetLink = reinterpret_cast<decltype(BASS_ChannelSetLink)>(dlsym(handle, "BASS_ChannelSetLink"));
  BASS_ChannelRemoveLink = reinterpret_cast<decltype(BASS_ChannelRemoveLink)>(dlsym(handle, "BASS_ChannelRemoveLink"));
  BASS_ChannelSetDSP = reinterpret_cast<decltype(BASS_ChannelSetDSP)>(dlsym(handle, "BASS_ChannelSetDSP"));
  BASS_ChannelRemoveDSP = reinterpret_cast<decltype(BASS_ChannelRemoveDSP)>(dlsym(handle, "BASS_ChannelRemoveDSP"));
  BASS_ChannelSetFX = reinterpret_cast<decltype(BASS_ChannelSetFX)>(dlsym(handle, "BASS_ChannelSetFX"));
  BASS_ChannelRemoveFX = reinterpret_cast<decltype(BASS_ChannelRemoveFX)>(dlsym(handle, "BASS_ChannelRemoveFX"));

  BASS_FXSetParameters = reinterpret_cast<decltype(BASS_FXSetParameters)>(dlsym(handle, "BASS_FXSetParameters"));
  BASS_FXGetParameters = reinterpret_cast<decltype(BASS_FXGetParameters)>(dlsym(handle, "BASS_FXGetParameters"));
  BASS_FXSetPriority = reinterpret_cast<decltype(BASS_FXSetPriority)>(dlsym(handle, "BASS_FXSetPriority"));
  BASS_FXReset = reinterpret_cast<decltype(BASS_FXReset)>(dlsym(handle, "BASS_FXReset"));

  std::uint32_t old_device = BASS_GetDevice();
  BASS_Init(-1, 44100, BASS_DEVICE_3D, nullptr, nullptr);
  device = BASS_GetDevice();
  BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 2);
  BASS_SetConfig(BASS_CONFIG_NET_TIMEOUT, 10000);
  BASS_SetDevice(old_device);
  
  // do not dlclose, since we use libbass
  inited = true;
}