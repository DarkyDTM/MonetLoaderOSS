#pragma once
#include "lib_manager.h"
#include <cstdint>

#define RWFORCEENUMSIZEINT ((std::int32_t)((~((std::uint32_t)0)) >> 1))
#include "gta_struct.inl"
namespace rw {
using RwBool = std::int32_t;
using RwReal = float;

union RwRGBA {
  struct
  {
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
  };
  std::uint8_t col[4];
};

struct RwLLLink {
  RwLLLink* next;
  RwLLLink* prev;
};

struct RwLinkList {
  RwLLLink link;
};

struct RwRaster {
  RwRaster* parent;
  std::uint8_t* cpPixels;
  std::uint8_t* palette;
  std::int32_t width;
  std::int32_t height;
  std::int32_t depth;
  std::int32_t stride;
  std::int16_t nOffsetX;
  std::int16_t nOffsetY;
  std::uint8_t cType;
  std::uint8_t cFlags;
  std::uint8_t cFormat;
  std::int32_t originalWidth;
  std::int32_t originalHeight;
  void* dbEntry;
  std::uint16_t privateFlags;
};

enum RwRasterType {
  rwRASTERTYPENORMAL = 0x00, /**<Normal */
  rwRASTERTYPEZBUFFER = 0x01, /**<Z Buffer */
  rwRASTERTYPECAMERA = 0x02, /**<Camera */
  rwRASTERTYPETEXTURE = 0x04, /**<Texture */
  rwRASTERTYPECAMERATEXTURE = 0x05, /**<Camera texture */
  rwRASTERTYPEMASK = 0x07, /**<Mask for finding type */

  rwRASTERPALETTEVOLATILE = 0x40, /**<If set, hints that the palette will change often */
  rwRASTERDONTALLOCATE = 0x80, /**<If set the raster is not allocated */
  rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/**
 * \ingroup rwraster
 * \ref RwRasterFormat is a set of values and flags which may be combined to
 * specify a raster format. The format chosen for a particular raster depends
 * on the hardware device and the raster type specified at creation time
 * (see API function \ref RwRasterCreate). The format may be retrieved using
 * API function \ref RwRasterGetFormat.
 *
 * The raster format is a packed set of bits which contains the following
 * four pieces of information (these may be combined with bitwise OR):
 *
 * <ol>
 * <li> The pixel color format corresponding to one of the following values:
 *      <ul>
 *      <li> rwRASTERFORMAT1555
 *      <li> rwRASTERFORMAT565
 *      <li> rwRASTERFORMAT4444
 *      <li> rwRASTERFORMATLUM8
 *      <li> rwRASTERFORMAT8888
 *      <li> rwRASTERFORMAT888
 *      <li> rwRASTERFORMAT16
 *      <li> rwRASTERFORMAT24
 *      <li> rwRASTERFORMAT32
 *      <li> rwRASTERFORMAT555
 *      </ul>
 *      This value may be masked out of the raster format using
 *      rwRASTERFORMATPIXELFORMATMASK.
 * <li> The palette depth if the raster is palettized:
 *      <ul>
 *      <li> rwRASTERFORMATPAL4
 *      <li> rwRASTERFORMATPAL8
 *      </ul>
 *      In these cases, the color format refers to that of the palette.
 * <li> Flag rwRASTERFORMATMIPMAP. Set if the raster contains mipmap levels.
 * <li> Flag rwRASTERFORMATAUTOMIPMAP. Set if the mipmap levels were generated
 *      automatically by RenderWare.
 * </ol>
 */
enum RwRasterFormat {
  rwRASTERFORMATDEFAULT = 0x0000, /* Whatever the hardware likes best */

  rwRASTERFORMAT1555 = 0x0100, /**<16 bits - 1 bit alpha, 5 bits red, green and blue */
  rwRASTERFORMAT565 = 0x0200, /**<16 bits - 5 bits red and blue, 6 bits green */
  rwRASTERFORMAT4444 = 0x0300, /**<16 bits - 4 bits per component */
  rwRASTERFORMATLUM8 = 0x0400, /**<Gray scale */
  rwRASTERFORMAT8888 = 0x0500, /**<32 bits - 8 bits per component */
  rwRASTERFORMAT888 = 0x0600, /**<24 bits - 8 bits per component */
  rwRASTERFORMAT16 = 0x0700, /**<16 bits - undefined: useful for things like Z buffers */
  rwRASTERFORMAT24 = 0x0800, /**<24 bits - undefined: useful for things like Z buffers */
  rwRASTERFORMAT32 = 0x0900, /**<32 bits - undefined: useful for things like Z buffers */
  rwRASTERFORMAT555 = 0x0a00, /**<16 bits - 5 bits red, green and blue */

  rwRASTERFORMATAUTOMIPMAP = 0x1000, /**<RenderWare generated the mip levels */

  rwRASTERFORMATPAL8 = 0x2000, /**<8 bit palettised */
  rwRASTERFORMATPAL4 = 0x4000, /**<4 bit palettised */

  rwRASTERFORMATMIPMAP = 0x8000, /**<Mip mapping on */

  rwRASTERFORMATPIXELFORMATMASK = 0x0f00, /**<The pixel color format
                                           *  (excluding palettised bits) */
  rwRASTERFORMATMASK = 0xff00 /**<The whole format */,
  rwRASTERFORMATFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/**
 * \ingroup rwraster
 * \ref RwRasterLockMode represents the options available for locking
 * a raster so that it may be modified (see API function \ref RwRasterLock). An
 * application may wish to write to the raster, read from the raster or
 * simultaneously write and read a raster (rwRASTERLOCKWRITE | rwRASTERLOCKREAD).
 */
enum RwRasterLockMode {
  rwRASTERLOCKWRITE = 0x01, /**<Lock for writing */
  rwRASTERLOCKREAD = 0x02, /**<Lock for reading */
  rwRASTERLOCKNOFETCH = 0x04, /**<When used in combination with
                               *  rwRASTERLOCKWRITE, asks the driver not to
                               *  fetch the pixel data. This is only useful
                               *  if it is known that ALL the raster data is
                               *  going to be overwritten before the raster
                               *  is unlocked, i.e. from an
                               *  \ref RwRasterSetFromImage call. This flag
                               *  is not supported by all drivers. */
  rwRASTERLOCKRAW = 0x08, /**<When used in combination with
                              rwRASTERLOCKWRITE or rwRASTERLOCKREAD
                              allows access to the raw platform specific
                              pixel format */
  rwRASTERLOCKREADWRITE = (rwRASTERLOCKREAD | rwRASTERLOCKWRITE),
  rwRASTERLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwTexture {
  RwRaster* raster;
  void* dict;
  RwLLLink lInDictionary;
  char name[32];
  char mask[32];
  std::uint32_t filterAddressing;
  std::int32_t refCount;
};

struct RwImage {
  std::int32_t flags;
  std::int32_t width;
  std::int32_t height;
  std::int32_t depth;
  std::int32_t stride;
  std::uint8_t* cpPixels;
  RwRGBA* palette;
};

struct RwOpenGLVertex {
  RwReal x;
  RwReal y;
  RwReal z;
  RwReal rhw;
  union {
    struct {
      std::uint8_t r;
      std::uint8_t g;
      std::uint8_t b;
      std::uint8_t a;
    };
    std::uint32_t emissiveColor;
  };
  RwReal s;
  RwReal t;
};
using RwIm2DVertex = RwOpenGLVertex;
using RxVertexIndex = std::uint16_t;
using RwImVertexIndex = RxVertexIndex;

enum RwRenderState {
  rwRENDERSTATENARENDERSTATE = 0,

  rwRENDERSTATETEXTURERASTER = 1,
  /**<Raster used for texturing (normally used in immediate mode).
   *  The value is a pointer to an \ref RwRaster.
   * Default: NULL.
   */
  rwRENDERSTATETEXTUREADDRESS = 2,
  /**<\ref RwTextureAddressMode: wrap, clamp, mirror or border.
   * Default: rwTEXTUREADDRESSWRAP.
   */
  rwRENDERSTATETEXTUREADDRESSU = 3,
  /**<\ref RwTextureAddressMode in u only.
   * Default: rwTEXTUREADDRESSWRAP.
   */
  rwRENDERSTATETEXTUREADDRESSV = 4,
  /**<\ref RwTextureAddressMode in v only.
   * Default: rwTEXTUREADDRESSWRAP.
   */
  rwRENDERSTATETEXTUREPERSPECTIVE = 5,
  /**<Perspective correction on/off (always enabled on many platforms).
   */
  rwRENDERSTATEZTESTENABLE = 6,
  /**<Z-buffer test on/off.
   * Default: TRUE.
   */
  rwRENDERSTATESHADEMODE = 7,
  /**<\ref RwShadeMode: flat or gouraud shading.
   * Default: rwSHADEMODEGOURAUD.
   */
  rwRENDERSTATEZWRITEENABLE = 8,
  /**<Z-buffer write on/off.
   * Default: TRUE.
   */
  rwRENDERSTATETEXTUREFILTER = 9,
  /**<\ref RwTextureFilterMode: point sample, bilinear, trilinear, etc.
   * Default: rwFILTERLINEAR.
   */
  rwRENDERSTATESRCBLEND = 10,
  /**<\ref RwBlendFunction used to modulate the source pixel color
   *  when blending to the frame buffer.
   * Default: rwBLENDSRCALPHA.
   */
  rwRENDERSTATEDESTBLEND = 11,
  /**<\ref RwBlendFunction used to modulate the destination pixel
   *  color in the frame buffer when blending. The resulting pixel
   *  color is given by the formula
   *  (SRCBLEND * srcColor + DESTBLEND * destColor) for each RGB
   *  component. For a particular platform, not all combinations
   *  of blend function are allowed (see platform specific
   *  restrictions).
   * Default: rwBLENDINVSRCALPHA.
   */
  rwRENDERSTATEVERTEXALPHAENABLE = 12,
  /**<Alpha blending on/off (always enabled on some platforms).
   *  This is normally used in immediate mode to enable alpha blending
   *  when vertex colors or texture rasters have transparency. Retained
   *  mode pipelines will usually set this state based on material colors
   *  and textures.
   * Default: FALSE.
   */
  rwRENDERSTATEBORDERCOLOR = 13,
  /**<Border color for \ref RwTextureAddressMode
   *  \ref rwTEXTUREADDRESSBORDER. The value should be a packed
   *  RwUInt32 in a platform specific format. The macro
   *  RWRGBALONG(r, g, b, a) may be used to construct this using
   *  8-bit color components.
   * Default: RWRGBALONG(0, 0, 0, 0).
   */
  rwRENDERSTATEFOGENABLE = 14,
  /**<Fogging on/off (all polygons will be fogged).
   * Default: FALSE.
   */
  rwRENDERSTATEFOGCOLOR = 15,
  /**<Color used for fogging. The value should be a packed RwUInt32
   *  in a platform specific format. The macro RWRGBALONG(r, g, b, a)
   *  may be used to construct this using 8-bit color components.
   * Default: RWRGBALONG(0, 0, 0, 0).
   */
  rwRENDERSTATEFOGTYPE = 16,
  /**<\ref RwFogType, the type of fogging to use.
   * Default: rwFOGTYPELINEAR.
   */
  rwRENDERSTATEFOGDENSITY = 17,
  /**<Fog density for \ref RwFogType of
   *  \ref rwFOGTYPEEXPONENTIAL or \ref rwFOGTYPEEXPONENTIAL2.
   *  The value should be a pointer to an RwReal in the
   *  range 0 to 1.
   * Default: 1.
   */
  rwRENDERSTATECULLMODE = 20,
  /**<\ref RwCullMode, for selecting front/back face culling, or
   *  no culling.
   * Default: rwCULLMODECULLBACK.
   */
  rwRENDERSTATESTENCILENABLE,
  /**<Stenciling on/off.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: FALSE.
   */
  rwRENDERSTATESTENCILFAIL,
  /**<\ref RwStencilOperation used when the stencil test passes.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: rwSTENCILOPERATIONKEEP.
   */
  rwRENDERSTATESTENCILZFAIL,
  /**<\ref RwStencilOperation used when the stencil test passes and
   *  the depth test (z-test) fails.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: rwSTENCILOPERATIONKEEP.
   */
  rwRENDERSTATESTENCILPASS,
  /**<\ref RwStencilOperation used when both the stencil and the depth
   *  (z) tests pass.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: rwSTENCILOPERATIONKEEP.
   */
  rwRENDERSTATESTENCILFUNCTION,
  /**<\ref RwStencilFunction for the stencil test.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: rwSTENCILFUNCTIONALWAYS.
   */
  rwRENDERSTATESTENCILFUNCTIONREF,
  /**<Integer reference value for the stencil test.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: 0.
   */
  rwRENDERSTATESTENCILFUNCTIONMASK,
  /**<Mask applied to the reference value and each stencil buffer
   *  entry to determine the significant bits for the stencil test.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: 0xffffffff.
   */
  rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
  /**<Write mask applied to values written into the stencil buffer.
   *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
   * Default: 0xffffffff.
   */
  rwRENDERSTATEALPHATESTFUNCTION,
  /**<\ref RwAlphaTestFunction for the alpha test. When a pixel fails,
   * neither the frame buffer nor the Z-buffer are updated.
   * Default: rwALPHATESTFUNCTIONGREATER (GameCube, Xbox, D3D8, D3D9
   * and OpenGL). The default PS2 behaviour is to always update the
   * frame buffer and update the Z-buffer only if a greater than or
   * equal test passes.
   */
  rwRENDERSTATEALPHATESTFUNCTIONREF,
  /**<Integer reference value for the alpha test.
   *  <i> Range is 0 to 255, mapped to the platform's actual range </i>
   * Default: 128 (PS2) 0 (GameCube, Xbox, D3D8, D3D9 and OpenGL).
   */

  rwRENDERSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwShadeMode {
  rwSHADEMODENASHADEMODE = 0,
  rwSHADEMODEFLAT, /**<Flat shading */
  rwSHADEMODEGOURAUD, /**<Gouraud shading */
  rwSHADEMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwTextureFilterMode {
  rwFILTERNAFILTERMODE = 0,
  rwFILTERNEAREST, /**<Point sampled */
  rwFILTERLINEAR, /**<Bilinear */
  rwFILTERMIPNEAREST, /**<Point sampled per pixel mip map */
  rwFILTERMIPLINEAR, /**<Bilinear per pixel mipmap */
  rwFILTERLINEARMIPNEAREST, /**<MipMap interp point sampled */
  rwFILTERLINEARMIPLINEAR, /**<Trilinear */
  rwTEXTUREFILTERMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwFogType {
  rwFOGTYPENAFOGTYPE = 0,
  rwFOGTYPELINEAR, /**<Linear fog */
  rwFOGTYPEEXPONENTIAL, /**<Exponential fog */
  rwFOGTYPEEXPONENTIAL2, /**<Exponential^2 fog */
  rwFOGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwBlendFunction {
  rwBLENDNABLEND = 0,
  rwBLENDZERO, /**<(0,    0,    0,    0   ) */
  rwBLENDONE, /**<(1,    1,    1,    1   ) */
  rwBLENDSRCCOLOR, /**<(Rs,   Gs,   Bs,   As  ) */
  rwBLENDINVSRCCOLOR, /**<(1-Rs, 1-Gs, 1-Bs, 1-As) */
  rwBLENDSRCALPHA, /**<(As,   As,   As,   As  ) */
  rwBLENDINVSRCALPHA, /**<(1-As, 1-As, 1-As, 1-As) */
  rwBLENDDESTALPHA, /**<(Ad,   Ad,   Ad,   Ad  ) */
  rwBLENDINVDESTALPHA, /**<(1-Ad, 1-Ad, 1-Ad, 1-Ad) */
  rwBLENDDESTCOLOR, /**<(Rd,   Gd,   Bd,   Ad  ) */
  rwBLENDINVDESTCOLOR, /**<(1-Rd, 1-Gd, 1-Bd, 1-Ad) */
  rwBLENDSRCALPHASAT, /**<(f,    f,    f,    1   )  f = min (As, 1-Ad) */
  rwBLENDFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwTextureAddressMode {
  rwTEXTUREADDRESSNATEXTUREADDRESS = 0,
  rwTEXTUREADDRESSWRAP, /**<UV wraps (tiles) */
  rwTEXTUREADDRESSMIRROR, /**<Alternate UV is flipped */
  rwTEXTUREADDRESSCLAMP, /**<UV is clamped to 0-1 */
  rwTEXTUREADDRESSBORDER, /**<Border color takes effect outside of 0-1 */
  rwTEXTUREADDRESSMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwStencilOperation {
  rwSTENCILOPERATIONNASTENCILOPERATION = 0,

  rwSTENCILOPERATIONKEEP,
  /**<Do not update the entry in the stencil buffer */
  rwSTENCILOPERATIONZERO,
  /**<Set the stencil-buffer entry to 0 */
  rwSTENCILOPERATIONREPLACE,
  /**<Replace the stencil-buffer entry with reference value */
  rwSTENCILOPERATIONINCRSAT,
  /**<Increment the stencil-buffer entry, clamping to the
   *  maximum value */
  rwSTENCILOPERATIONDECRSAT,
  /**<Decrement the stencil-buffer entry, clamping to zero */
  rwSTENCILOPERATIONINVERT,
  /**<Invert the bits in the stencil-buffer entry */
  rwSTENCILOPERATIONINCR,
  /**<Increment the stencil-buffer entry, wrapping to zero if
   *  the new value exceeds the maximum value */
  rwSTENCILOPERATIONDECR,
  /**<Decrement the stencil-buffer entry, wrapping to the maximum
   *  value if the new value is less than zero */

  rwSTENCILOPERATIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwStencilFunction {
  rwSTENCILFUNCTIONNASTENCILFUNCTION = 0,

  rwSTENCILFUNCTIONNEVER,
  /**<Always fail the test */
  rwSTENCILFUNCTIONLESS,
  /**<Accept the new pixel if its value is less than the value of
   *  the current pixel */
  rwSTENCILFUNCTIONEQUAL,
  /**<Accept the new pixel if its value equals the value of the
   *  current pixel */
  rwSTENCILFUNCTIONLESSEQUAL,
  /**<Accept the new pixel if its value is less than or equal to
   *  the value of the current pixel */
  rwSTENCILFUNCTIONGREATER,
  /**<Accept the new pixel if its value is greater than the value
   *  of the current pixel */
  rwSTENCILFUNCTIONNOTEQUAL,
  /**<Accept the new pixel if its value does not equal the value of
   *  the current pixel */
  rwSTENCILFUNCTIONGREATEREQUAL,
  /**<Accept the new pixel if its value is greater than or equal
   *  to the value of the current pixel */
  rwSTENCILFUNCTIONALWAYS,
  /**<Always pass the test */

  rwSTENCILFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwAlphaTestFunction {
  rwALPHATESTFUNCTIONNAALPHATESTFUNCTION = 0,

  rwALPHATESTFUNCTIONNEVER,
  /**<Always fail the test */
  rwALPHATESTFUNCTIONLESS,
  /**<Accept the new pixel if its alpha value is less than the value of
   *  the reference value */
  rwALPHATESTFUNCTIONEQUAL,
  /**<Accept the new pixel if its alpha value equals the value of the
   *  reference value */
  rwALPHATESTFUNCTIONLESSEQUAL,
  /**<Accept the new pixel if its alpha value is less than or equal to
   *  the value of the reference value */
  rwALPHATESTFUNCTIONGREATER,
  /**<Accept the new pixel if its alpha value is greater than the value
   *  of the reference value */
  rwALPHATESTFUNCTIONNOTEQUAL,
  /**<Accept the new pixel if its alpha value does not equal the value of
   *  the reference value */
  rwALPHATESTFUNCTIONGREATEREQUAL,
  /**<Accept the new pixel if its alpha value is greater than or equal
   *  to the value of the reference value */
  rwALPHATESTFUNCTIONALWAYS,
  /**<Always pass the test */

  rwALPHATESTFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwCullMode {
  rwCULLMODENACULLMODE = 0,

  rwCULLMODECULLNONE,
  /**<Both front and back-facing triangles are drawn. */
  rwCULLMODECULLBACK,
  /**<Only front-facing triangles are drawn */
  rwCULLMODECULLFRONT,
  /**<Only back-facing triangles are drawn */

  rwCULLMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwPrimitiveType {
  rwPRIMTYPENAPRIMTYPE = 0, /**<Invalid primative type */
  rwPRIMTYPELINELIST = 1, /**<Unconnected line segments, each line is specified by
                           * both its start and end index, independently of other lines
                           * (for example, 3 segments specified as 0-1, 2-3, 4-5) */
  rwPRIMTYPEPOLYLINE = 2, /**<Connected line segments, each line's start index
                           * (except the first) is specified by the index of the end of
                           * the previous segment (for example, 3 segments specified as
                           * 0-1, 1-2, 2-3) */
  rwPRIMTYPETRILIST = 3, /**<Unconnected triangles: each triangle is specified by
                          * three indices, independently of other triangles (for example,
                          * 3 triangles specified as 0-1-2, 3-4-5, 6-7-8) */
  rwPRIMTYPETRISTRIP = 4, /**<Connected triangles sharing an edge with, at most, one
                           * other forming a series (for example, 3 triangles specified
                           * as 0-2-1, 1-2-3-, 2-4-3) */
  rwPRIMTYPETRIFAN = 5, /**<Connected triangles sharing an edge with, at most,
                         * two others forming a fan (for example, 3 triangles specified
                         * as 0-2-1, 0-3-2, 0-4-3) */
  rwPRIMTYPEPOINTLIST = 6, /**<Points 1, 2, 3, etc. This is not
                            * supported by the default RenderWare
                            * immediate or retained-mode pipelines
                            * (except on PlayStation 2), it is intended
                            * for use by user-created pipelines */
  rwPRIMITIVETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

#define RwRasterGetWidthMacro(_raster) \
  ((_raster)->width)

#define RwRasterGetHeightMacro(_raster) \
  ((_raster)->height)

#define RwRasterGetStrideMacro(_raster) \
  ((_raster)->stride)

#define RwRasterGetDepthMacro(_raster) \
  ((_raster)->depth)

#define RwRasterGetFormatMacro(_raster) \
  ((((_raster)->cFormat) & (rwRASTERFORMATMASK >> 8)) << 8)

#define RwRasterGetTypeMacro(_raster) \
  (((_raster)->cType) & rwRASTERTYPEMASK)

#define RwRasterGetParentMacro(_raster) \
  ((_raster)->parent)

#define RwRasterGetWidth(_raster) \
  RwRasterGetWidthMacro(_raster)

#define RwRasterGetHeight(_raster) \
  RwRasterGetHeightMacro(_raster)

#define RwRasterGetStride(_raster) \
  RwRasterGetStrideMacro(_raster)

#define RwRasterGetDepth(_raster) \
  RwRasterGetDepthMacro(_raster)

#define RwRasterGetFormat(_raster) \
  RwRasterGetFormatMacro(_raster)

#define RwRasterGetType(_raster) \
  RwRasterGetTypeMacro(_raster)

#define RwRasterGetParent(_raster) \
  RwRasterGetParentMacro(_raster)

#define RwImageSetStrideMacro(_image, _stride) \
  (((_image)->stride = (_stride)), (_image))

#define RwImageSetPixelsMacro(_image, _pixels) \
  (((_image)->cpPixels = (_pixels)), (_image))

#define RwImageSetPaletteMacro(_image, _palette) \
  (((_image)->palette = (_palette)), (_image))

#define RwImageGetWidthMacro(_image) \
  ((_image)->width)

#define RwImageGetHeightMacro(_image) \
  ((_image)->height)

#define RwImageGetDepthMacro(_image) \
  ((_image)->depth)

#define RwImageGetStrideMacro(_image) \
  ((_image)->stride)

#define RwImageGetPixelsMacro(_image) \
  ((_image)->cpPixels)

#define RwImageGetPaletteMacro(_image) \
  ((_image)->palette)

#define RwImageSetStride(_image, _stride) \
  RwImageSetStrideMacro(_image, _stride)

#define RwImageSetPixels(_image, _pixels) \
  RwImageSetPixelsMacro(_image, _pixels)

#define RwImageSetPalette(_image, _palette) \
  RwImageSetPaletteMacro(_image, _palette)

#define RwImageGetWidth(_image) \
  RwImageGetWidthMacro(_image)

#define RwImageGetHeight(_image) \
  RwImageGetHeightMacro(_image)

#define RwImageGetDepth(_image) \
  RwImageGetDepthMacro(_image)

#define RwImageGetStride(_image) \
  RwImageGetStrideMacro(_image)

#define RwImageGetPixels(_image) \
  RwImageGetPixelsMacro(_image)

#define RwImageGetPalette(_image) \
  RwImageGetPaletteMacro(_image)

/* Set true depth information (for fogging, eg) */
#define RwIm2DVertexSetRecipCameraZ(vert, recipz) ((vert)->rhw = (recipz))
#define RwIm2DVertexGetRecipCameraZ(vert) ((vert)->rhw)

/* Set screen space coordinates in a device vertex */
#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)

/* Set texture coordinates in a device vertex */
#define RwIm2DVertexSetU(vert, texU) ((vert)->s = (texU))
#define RwIm2DVertexSetV(vert, texV) ((vert)->t = (texV))
#define RwIm2DVertexGetU(vert) ((vert)->s)
#define RwIm2DVertexGetV(vert) ((vert)->t)

enum RsInputDeviceType : std::int32_t {
  rsKEYBOARD = 0x0,
  rsMOUSE = 0x1,
  rsPAD = 0x2,
};

struct RsInputDevice {
  RsInputDeviceType inputDeviceType;
  RwBool used;
  void* inputEventHandler;
};
struct RsGlobalType {
  const char* appName;
  std::int32_t screenWidth;
  std::int32_t screenHeight;
  std::int32_t maxFPS;
  RwBool quit;
  void* ps;
  RsInputDevice keyboard;
  RsInputDevice mouse;
  RsInputDevice pad;
};

inline RsGlobalType* RsGlobal()
{
  return reinterpret_cast<RsGlobalType*>(lib_manager::rsglobal);
}

inline RwBool RwRenderStateGet(RwRenderState state, void* value)
{
  return GTA_FUNC_AT(RwRenderStateGet, lib_manager::rw_render_state_get)(state, value);
}
inline RwBool RwRenderStateSet(RwRenderState state, void* value)
{
  return GTA_FUNC_AT(RwRenderStateGet, lib_manager::rw_render_state_set)(state, value);
}

inline RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, std::int32_t numVertices, RwImVertexIndex* indices, std::int32_t numIndices)
{
  return GTA_FUNC_AT(RwIm2DRenderIndexedPrimitive, lib_manager::rwim2d_render_indexed_primitive)(primType, vertices, numVertices, indices, numIndices);
}
inline RwReal RwIm2DGetNearScreenZ()
{
  return GTA_FUNC_AT(RwIm2DGetNearScreenZ, lib_manager::rwim2d_get_near_screen_z)();
}

inline RwBool RwRasterDestroy(RwRaster* raster)
{
  return GTA_FUNC_AT(RwRasterDestroy, lib_manager::rw_raster_destroy)(raster);
}
inline RwRaster* RwRasterCreate(std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t flags)
{
  return GTA_FUNC_AT(RwRasterCreate, lib_manager::rw_raster_create)(width, height, depth, flags);
}
inline RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image)
{
  return GTA_FUNC_AT(RwRasterSetFromImage, lib_manager::rw_raster_set_from_image)(raster, image);
}
inline std::uint8_t* RwRasterLock(RwRaster* raster, std::uint8_t level, std::int32_t mode)
{
  return GTA_FUNC_AT(RwRasterLock, lib_manager::rw_raster_lock)(raster, level, mode);
}
inline RwRaster* RwRasterUnlock(RwRaster* raster)
{
  return GTA_FUNC_AT(RwRasterUnlock, lib_manager::rw_raster_unlock)(raster);
}

inline RwImage* RwImageCreate(std::int32_t width, std::int32_t height, std::int32_t depth)
{
  return GTA_FUNC_AT(RwImageCreate, lib_manager::rw_image_create)(width, height, depth);
}
inline RwImage* RwImageAllocatePixels(RwImage* image)
{
  return GTA_FUNC_AT(RwImageAllocatePixels, lib_manager::rw_image_allocate_pixels)(image);
}
inline RwImage* RwImageFindRasterFormat(RwImage* ipImage, std::int32_t nRasterType,
    std::int32_t* npWidth, std::int32_t* npHeight, std::int32_t* npDepth, std::int32_t* npFormat)
{
  return GTA_FUNC_AT(RwImageFindRasterFormat, lib_manager::rw_image_find_raster_format)(ipImage, nRasterType,
      npWidth, npHeight, npDepth, npFormat);
}
inline RwBool RwImageDestroy(RwImage* image)
{
  return GTA_FUNC_AT(RwImageDestroy, lib_manager::rw_image_destroy)(image);
}

inline RwImage* RtPNGImageRead(const char* imageName)
{
  return GTA_FUNC_AT(RtPNGImageRead, lib_manager::rt_png_image_read)(imageName);
}
}
#include "gta_struct.inl"
#undef RWFORCEENUMSIZEINT