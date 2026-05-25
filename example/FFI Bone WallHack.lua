-- MonetLoader for Android 2.1.0
-- Reference script: FFI Bone WallHack
script_name('FFI Bone WallHack')
script_version('1.1')
script_version_number(2)
script_author('The MonetLoader Team')
script_description('Bone + nametag WallHack that gets bone positions with FFI.')

local ffi = require('ffi')
local gta = ffi.load('GTASA')
ffi.cdef[[
  typedef struct RwV3d {
    float x, y, z;
  } RwV3d;
  // void CPed::GetBonePosition(CPed *this, RwV3d *posn, uint32 bone, bool calledFromCam) - Mangled name
  void _ZN4CPed15GetBonePositionER5RwV3djb(void* thiz, RwV3d* posn, uint32_t bone, bool calledFromCam);
]]

function getBonePosition(ped, bone)
  local pedptr = ffi.cast('void*', getCharPointer(ped))
  local posn = ffi.new('RwV3d[1]')
  gta._ZN4CPed15GetBonePositionER5RwV3djb(pedptr, posn, bone, false)
  return posn[0].x, posn[0].y, posn[0].z
end

local bones = { 3, 4, 5, 51, 52, 41, 42, 31, 32, 33, 21, 22, 23, 2 }
local sw, sh = getScreenResolution()
local font = renderCreateFont("Arial", 12, 1 + 4) -- P.S. in MonetLoader only Arial Bold is available (every font is defaulted to it)

function main()
  while not isSampAvailable() do wait(0) end

  while true do
    wait(0)

    for _, char in ipairs(getAllChars()) do
      local result, id = sampGetPlayerIdByCharHandle(char)
      if result and isCharOnScreen(char) then
        local opaque_color = bit.bor(bit.band(sampGetPlayerColor(id), 0xFFFFFF), 0xFF000000)
        for _, bone in ipairs(bones) do
          local x1, y1, z1 = getBonePosition(char, bone)
          local x2, y2, z2 = getBonePosition(char, bone + 1)
          local r1, sx1, sy1 = convert3DCoordsToScreenEx(x1, y1, z1)
          local r2, sx2, sy2 = convert3DCoordsToScreenEx(x2, y2, z2)
          if r1 and r2 then
            renderDrawLine(sx1, sy1, sx2, sy2, 3, opaque_color)
          end
        end

        local x1, y1, z1 = getBonePosition(char, 2)
        local r1, sx1, sy1 = convert3DCoordsToScreenEx(x1, y1, z1)
        if r1 then
          local x2, y2, z2 = getBonePosition(char, 41)
          local r2, sx2, sy2 = convert3DCoordsToScreenEx(x2, y2, z2)
          if r2 then
            renderDrawLine(sx1, sy1, sx2, sy2, 3, opaque_color)
          end
        end
        if r1 then
          local x2, y2, z2 = getBonePosition(char, 51)
          local r2, sx2, sy2 = convert3DCoordsToScreenEx(x2, y2, z2)
          if r2 then
            renderDrawLine(sx1, sy1, sx2, sy2, 3, opaque_color)
          end
        end

        local hx, hy, hz = getBonePosition(char, 5)
        local hr, headx, heady = convert3DCoordsToScreenEx(hx, hy, hz + 0.25)
        if hr then
          local nickname = sampGetPlayerNickname(id)
          local nametag = nickname .. ' [' .. tostring(id) .. '] - {FF0000}' .. string.format("%.0f", sampGetPlayerHealth(id)) .. 'hp {BBBBBB}' .. string.format("%.0f", sampGetPlayerArmor(id)) .. 'ap'
          local nametag_len = renderGetFontDrawTextLength(font, nametag)
          local nametag_x = headx - nametag_len / 2
          local nametag_y = heady - renderGetFontDrawHeight(font)
          renderFontDrawText(font, nametag, nametag_x, nametag_y, opaque_color)
        end
      end
    end
  end
end