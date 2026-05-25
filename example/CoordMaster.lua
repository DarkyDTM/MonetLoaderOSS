-- MonetLoader for Android 2.0.0
-- Reference script: Simple CoordMaster
script_name('CoordMaster')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Teleport to any point in San Andreas with short steps. Press green button to configure and start.')

local widgets = require('widgets') -- for WIDGET_(...)


local status = false
local was_pressed_menu = false
local was_pressed_tp = false
local speed = 20

function teleportTo(x, y, z)
  if isCharInAnyCar(PLAYER_PED) then
    setCarCoordinates(storeCarCharIsInNoSave(PLAYER_PED), x, y, z)
  else
    setCharCoordinates(PLAYER_PED, x, y, z)
  end
end

function coordMaster(px, py, pz, step, time)
  local x, y, z = getCharCoordinates(PLAYER_PED)
  local d = getDistanceBetweenCoords3d(px, py, pz, x, y, z)
  if d <= step then
    teleportTo(px, py, pz)
  else
    local dx, dy, dz = px - x, py - y, pz - z
    x = x + step / d * dx
    y = y + step / d * dy
    z = z + step / d * dz
    teleportTo(x, y, z)
    wait(time)
    coordMaster(px, py, pz, step, time)
  end
end

function getTargetBlipCoordinatesFixed()
  local bool, x, y, z = getTargetBlipCoordinates(); if not bool then return false end
  requestCollision(x, y); loadScene(x, y, z)
  local bool, x, y, z = getTargetBlipCoordinates()
  return bool, x, y, z
end

function main()
  while true do
    wait(0)

    local pressed_menu = isWidgetPressed(WIDGET_ARCADE_BUTTON)
    if pressed_menu and not was_pressed_menu then
      status = not status
      if status then
        printStringNow('Select speed and press checkmark', 3000)
      end
    end
    was_pressed_menu = pressed_menu

    if status then
      if isWidgetPressed(WIDGET_ZOOM_IN) then -- Plus
        speed = speed + 0.1
        printStringNow('Speed: ' .. tostring(speed), 1000)
      end

      if isWidgetPressed(WIDGET_ZOOM_OUT) then -- Minus
        speed = speed - 0.1
        printStringNow('Speed: ' .. tostring(speed), 1000)
      end

      local pressed_tp = isWidgetPressed(WIDGET_MISSION_START) -- Checkmark
      if pressed_tp and not was_pressed_tp then
        local result, x, y, z = getTargetBlipCoordinatesFixed()
        if result then
          printStringNow('Please wait', 3000)
          coordMaster(x, y, z, speed, 100)
          printStringNow('~g~Teleported to blip', 3000)
          status = false
        end
      end
      was_pressed_tp = pressed_tp
    end
  end
end