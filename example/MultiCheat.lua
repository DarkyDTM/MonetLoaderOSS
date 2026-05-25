

-- MonetLoader for Android 2.4.1
-- Reference script: MultiCheat
script_name('MultiCheat')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('A multicheat for SA-MP Android. Use /cheats to open menu.')
local imgui = require 'mimgui' -- подключаем библиотеку мимгуи

local encoding = require 'encoding' -- подключаем библиотеку для работы с разными кодировками
encoding.default = 'CP1251' -- задаём кодировку по умолчанию
local u8 = encoding.UTF8 -- это позволит нам писать задавать названия/текст на кириллице

require 'widgets' -- подключить айди виджетов
local sampev = require 'samp.events' -- samp events для подмены синхры
local sf = require 'sampfuncs' -- sampfuncs для айди пакетов

-- немного ffi магии
local ffi = require('ffi')
local gta = ffi.load('GTASA')
ffi.cdef[[
  typedef struct RwV3d {
    float x, y, z;
  } RwV3d;
  // void CPed::GetBonePosition(CPed *this, RwV3d *posn, uint32 bone, bool calledFromCam) - Mangled name
  void _ZN4CPed15GetBonePositionER5RwV3djb(void* thiz, RwV3d* posn, uint32_t bone, bool calledFromCam);
]]

function getBonePosition(ped, bone) -- функция для получения позиции кости педа
  local pedptr = ffi.cast('void*', getCharPointer(ped))
  local posn = ffi.new('RwV3d[1]')
  gta._ZN4CPed15GetBonePositionER5RwV3djb(pedptr, posn, bone, false)
  return posn[0].x, posn[0].y, posn[0].z
end

local SCREEN_W, SCREEN_H = getScreenResolution() -- константы размера экрана
local new = imgui.new -- создаём короткий псевдоним для удобства
local window_state = new.bool() -- создаём буффер для открытия окна
local window_scale = new.float(1.0) -- переменная для изменения размера окна, для удобства

-- небольшой стиль для красоты
function imgui.Theme()
  imgui.SwitchContext()
  style = imgui.GetStyle()

  --==[ STYLE ]==--
  style.WindowPadding = imgui.ImVec2(5, 5)
  style.FramePadding = imgui.ImVec2(10, 10)
  style.ItemSpacing = imgui.ImVec2(10, 10)
  style.ItemInnerSpacing = imgui.ImVec2(5, 5)
  style.TouchExtraPadding = imgui.ImVec2(5 * MONET_DPI_SCALE, 5 * MONET_DPI_SCALE)
  style.IndentSpacing = 0
  style.ScrollbarSize = 20 * MONET_DPI_SCALE
  style.GrabMinSize = 20 * MONET_DPI_SCALE

  --==[ BORDER ]==--
  style.WindowBorderSize = 1
  style.ChildBorderSize = 1
  style.PopupBorderSize = 1
  style.FrameBorderSize = 1
  style.TabBorderSize = 1

  --==[ ROUNDING ]==--
  style.WindowRounding = 5
  style.ChildRounding = 5
  style.FrameRounding = 5
  style.PopupRounding = 5
  style.ScrollbarRounding = 5
  style.GrabRounding = 5
  style.TabRounding = 5

  --==[ ALIGN ]==--
  style.WindowTitleAlign = imgui.ImVec2(0.5, 0.5)
  style.ButtonTextAlign = imgui.ImVec2(0.5, 0.5)
  style.SelectableTextAlign = imgui.ImVec2(0.5, 0.5)
  
  --==[ COLORS ]==--
  style.Colors[imgui.Col.Text]                   = imgui.ImVec4(1.00, 1.00, 1.00, 1.00)
  style.Colors[imgui.Col.TextDisabled]           = imgui.ImVec4(0.50, 0.50, 0.50, 1.00)
  style.Colors[imgui.Col.WindowBg]               = imgui.ImVec4(0.07, 0.07, 0.07, 1.00)
  style.Colors[imgui.Col.ChildBg]                = imgui.ImVec4(0.07, 0.07, 0.07, 1.00)
  style.Colors[imgui.Col.PopupBg]                = imgui.ImVec4(0.07, 0.07, 0.07, 1.00)
  style.Colors[imgui.Col.Border]                 = imgui.ImVec4(0.25, 0.25, 0.26, 0.54)
  style.Colors[imgui.Col.BorderShadow]           = imgui.ImVec4(0.00, 0.00, 0.00, 0.00)
  style.Colors[imgui.Col.FrameBg]                = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.FrameBgHovered]         = imgui.ImVec4(0.25, 0.25, 0.26, 1.00)
  style.Colors[imgui.Col.FrameBgActive]          = imgui.ImVec4(0.25, 0.25, 0.26, 1.00)
  style.Colors[imgui.Col.TitleBg]                = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.TitleBgActive]          = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.TitleBgCollapsed]       = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.MenuBarBg]              = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.ScrollbarBg]            = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.ScrollbarGrab]          = imgui.ImVec4(0.00, 0.00, 0.00, 1.00)
  style.Colors[imgui.Col.ScrollbarGrabHovered]   = imgui.ImVec4(0.41, 0.41, 0.41, 1.00)
  style.Colors[imgui.Col.ScrollbarGrabActive]    = imgui.ImVec4(0.51, 0.51, 0.51, 1.00)
  style.Colors[imgui.Col.CheckMark]              = imgui.ImVec4(1.00, 1.00, 1.00, 1.00)
  style.Colors[imgui.Col.SliderGrab]             = imgui.ImVec4(0.21, 0.20, 0.20, 1.00)
  style.Colors[imgui.Col.SliderGrabActive]       = imgui.ImVec4(0.21, 0.20, 0.20, 1.00)
  style.Colors[imgui.Col.Button]                 = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.ButtonHovered]          = imgui.ImVec4(0.21, 0.20, 0.20, 1.00)
  style.Colors[imgui.Col.ButtonActive]           = imgui.ImVec4(0.41, 0.41, 0.41, 1.00)
  style.Colors[imgui.Col.Header]                 = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.HeaderHovered]          = imgui.ImVec4(0.20, 0.20, 0.20, 1.00)
  style.Colors[imgui.Col.HeaderActive]           = imgui.ImVec4(0.47, 0.47, 0.47, 1.00)
  style.Colors[imgui.Col.Separator]              = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.SeparatorHovered]       = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.SeparatorActive]        = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.ResizeGrip]             = imgui.ImVec4(1.00, 1.00, 1.00, 0.25)
  style.Colors[imgui.Col.ResizeGripHovered]      = imgui.ImVec4(1.00, 1.00, 1.00, 0.67)
  style.Colors[imgui.Col.ResizeGripActive]       = imgui.ImVec4(1.00, 1.00, 1.00, 0.95)
  style.Colors[imgui.Col.Tab]                    = imgui.ImVec4(0.12, 0.12, 0.12, 1.00)
  style.Colors[imgui.Col.TabHovered]             = imgui.ImVec4(0.28, 0.28, 0.28, 1.00)
  style.Colors[imgui.Col.TabActive]              = imgui.ImVec4(0.30, 0.30, 0.30, 1.00)
  style.Colors[imgui.Col.TabUnfocused]           = imgui.ImVec4(0.07, 0.10, 0.15, 0.97)
  style.Colors[imgui.Col.TabUnfocusedActive]     = imgui.ImVec4(0.14, 0.26, 0.42, 1.00)
  style.Colors[imgui.Col.PlotLines]              = imgui.ImVec4(0.61, 0.61, 0.61, 1.00)
  style.Colors[imgui.Col.PlotLinesHovered]       = imgui.ImVec4(1.00, 0.43, 0.35, 1.00)
  style.Colors[imgui.Col.PlotHistogram]          = imgui.ImVec4(0.90, 0.70, 0.00, 1.00)
  style.Colors[imgui.Col.PlotHistogramHovered]   = imgui.ImVec4(1.00, 0.60, 0.00, 1.00)
  style.Colors[imgui.Col.TextSelectedBg]         = imgui.ImVec4(1.00, 0.00, 0.00, 0.35)
  style.Colors[imgui.Col.DragDropTarget]         = imgui.ImVec4(1.00, 1.00, 0.00, 0.90)
  style.Colors[imgui.Col.NavHighlight]           = imgui.ImVec4(0.26, 0.59, 0.98, 1.00)
  style.Colors[imgui.Col.NavWindowingHighlight]  = imgui.ImVec4(1.00, 1.00, 1.00, 0.70)
  style.Colors[imgui.Col.NavWindowingDimBg]      = imgui.ImVec4(0.80, 0.80, 0.80, 0.20)
  style.Colors[imgui.Col.ModalWindowDimBg]       = imgui.ImVec4(0.00, 0.00, 0.00, 0.70)
end

imgui.OnInitialize(function()
  imgui.Theme()
end)

-- ставит коордианты игроку в машине без смещения
function setPlayerCarCoordinatesFixed(x, y, z)
  local ox, oy, oz = getCharCoordinates(PLAYER_PED)
  setCharCoordinates(PLAYER_PED, ox, oy, oz)
  local nx, ny, nz = getCharCoordinates(PLAYER_PED)
  local xoff = nx - ox
  local yoff = ny - oy
  local zoff = nz - oz

  setCharCoordinates(PLAYER_PED, x - xoff, y - yoff, z - zoff)
end

-- GodMode Ped by MonetLoader
local GodModePed = {
  enabled = new.bool(false)
}

GodModePed.activate = function()
  setCharProofs(PLAYER_PED, false, true, true, true, true)

  lua_thread.create(function()
    while GodModePed.enabled[0] do
      wait(0)
      setCharProofs(PLAYER_PED, false, true, true, true, true)
    end
  end)
end

GodModePed.reset = function()
  setCharProofs(PLAYER_PED, false, false, false, false, false)
end


-- GodMode Car by MonetLoader
local GodModeCar = {
  enabled = new.bool(false),
  last_car = nil
}

GodModeCar.activate = function()
  if isCharInAnyCar(PLAYER_PED) then
    GodModeCar.last_car = storeCarCharIsInNoSave(PLAYER_PED)
    setCarProofs(GodModeCar.last_car, false, true, true, true, true)
  end

  lua_thread.create(function()
    while GodModeCar.enabled[0] do
      if isCharInAnyCar(PLAYER_PED) then
        local car = storeCarCharIsInNoSave(PLAYER_PED)
        if car ~= GodModeCar.last_car and GodModeCar.last_car ~= nil and doesVehicleExist(GodModeCar.last_car) then
          setCarProofs(GodModeCar.last_car, false, false, false, false, false)
          GodModeCar.last_car = car
        end

        setCarProofs(car, false, true, true, true, true)
      else
        if GodModeCar.last_car ~= nil and doesVehicleExist(GodModeCar.last_car) then
          setCarProofs(GodModeCar.last_car, false, false, false, false, false)
          GodModeCar.last_car = nil
        end
      end
      wait(0)
    end
  end)
end

GodModeCar.reset = function()
  if GodModeCar.last_car ~= nil and doesVehicleExist(GodModeCar.last_car) then
    setCarProofs(GodModeCar.last_car, false, false, false, false, false)
    GodModeCar.last_car = nil
  end
end


-- AirBrake by MonetLoader on widgets
local AirBrake = {
  enabled = new.bool(false),
  speed = new.float(0.3),
  was_in_car = false,
  last_car = nil
}

AirBrake.getMoveSpeed = function(heading, speed)
  return math.sin(-math.rad(heading)) * speed, math.cos(-math.rad(heading)) * speed
end

AirBrake.reset = function()
  if AirBrake.last_car ~= nil and doesVehicleExist(AirBrake.last_car) and AirBrake.was_in_car then
    freezeCarPosition(AirBrake.last_car, false)
    setCarCollision(AirBrake.last_car, true)
  end
  if not AirBrake.was_in_car then
    freezeCharPosition(PLAYER_PED, false)
    setCharCollision(PLAYER_PED, true)
  end
  AirBrake.was_in_car = false
end

AirBrake.activate = function()
  lua_thread.create(function()
    while AirBrake.enabled[0] do
      AirBrake.processAirBrake()
      wait(0)
    end
  end)
end

AirBrake.processAirBrake = function()
  local x1, y1, z1 = getActiveCameraCoordinates()
  local x, y, z = getActiveCameraPointAt()
  local angle = -math.rad(getHeadingFromVector2d(x - x1, y - y1))

  if isCharInAnyCar(PLAYER_PED) then
    local car = storeCarCharIsInNoSave(PLAYER_PED)
    if car ~= AirBrake.last_car and AirBrake.last_car ~= nil and doesVehicleExist(AirBrake.last_car) and AirBrake.was_in_car then
      freezeCarPosition(AirBrake.last_car, false)
      setCarCollision(AirBrake.last_car, true)
    end
    AirBrake.was_in_car = true
    AirBrake.last_car = car
    freezeCarPosition(car, true)
    setCarCollision(car, false)

    local result, var_1, var_2 = isWidgetPressedEx(WIDGET_VEHICLE_STEER_ANALOG, 0)
    if not result then
      var_1 = 0
      var_2 = 0
    end
    local intensity_x = var_1 / 127
    local intensity_y = var_2 / 127

    local cx, cy, cz = getCharCoordinates(PLAYER_PED)
    cx = cx - (math.sin(angle) * AirBrake.speed[0] * intensity_y)
    cy = cy - (math.cos(angle) * AirBrake.speed[0] * intensity_y)
    cx = cx + (math.cos(angle) * AirBrake.speed[0] * intensity_x)
    cy = cy - (math.sin(angle) * AirBrake.speed[0] * intensity_x)
    cz = cz + AirBrake.processSpecialWidgets()

    setPlayerCarCoordinatesFixed(cx, cy, cz)
    setCarHeading(car, math.deg(-angle))

    if intensity_x ~= 0 then
      restoreCameraJumpcut()
    end
  else
    if AirBrake.was_in_car and AirBrake.last_car ~= nil and doesVehicleExist(AirBrake.last_car) then
      freezeCarPosition(AirBrake.last_car, false)
      setCarCollision(AirBrake.last_car, true)
    end
    AirBrake.was_in_car = false
    freezeCharPosition(PLAYER_PED, true)
    setCharCollision(PLAYER_PED, false)

    local result, var_1, var_2 = isWidgetPressedEx(WIDGET_PED_MOVE, 0)
    if not result then
      var_1 = 0
      var_2 = 0
    end
    local intensity_x = var_1 / 127
    local intensity_y = var_2 / 127

    local cx, cy, cz = getCharCoordinates(PLAYER_PED)
    cx = cx - (math.sin(angle) * AirBrake.speed[0] * intensity_y)
    cy = cy - (math.cos(angle) * AirBrake.speed[0] * intensity_y)
    cx = cx + (math.cos(angle) * AirBrake.speed[0] * intensity_x)
    cy = cy - (math.sin(angle) * AirBrake.speed[0] * intensity_x)
    cz = cz + AirBrake.processSpecialWidgets()

    setCharCoordinatesNoOffset(PLAYER_PED, cx, cy, cz)
    setCharHeading(PLAYER_PED, math.deg(-angle))

    if intensity_x ~= 0 then
      restoreCameraJumpcut()
    end
  end
end

AirBrake.processSpecialWidgets = function()
  local delta = 0
  if isWidgetPressed(WIDGET_ZOOM_IN) then
    delta = delta + AirBrake.speed[0] / 2
  end
  if isWidgetPressed(WIDGET_ZOOM_OUT) then
    delta = delta - AirBrake.speed[0] / 2
  end
  return delta
end

-- Reconnect by MonetLoader
local Reconnect = {
  delay = new.float(0),
  abort = false,
  waiting = false,
  remaining = 0,
  reconnecting = true
}

Reconnect.activate = function()
  lua_thread.create(function()
    local ms = 500 + Reconnect.delay[0] * 1000
    if ms <= 0 then
      ms = 100
    end

    Reconnect.waiting = true
    while ms > 0 do
      if ms <= 500 then
        Reconnect.waiting = false
        local bs = raknetNewBitStream()
        raknetBitStreamWriteInt8(bs, sf.PACKET_DISCONNECTION_NOTIFICATION)
        raknetSendBitStreamEx(bs, sf.SYSTEM_PRIORITY, sf.RELIABLE, 0)
        raknetDeleteBitStream(bs)
      end
      if Reconnect.waiting and Reconnect.abort then
        Reconnect.waiting = false
        Reconnect.abort = false
        return
      end
      Reconnect.abort = false

      Reconnect.remaining = ms
      wait(100)
      ms = ms - 100
    end
    Reconnect.waiting = false
    Reconnect.reconnecting = true

    bs = raknetNewBitStream()
    raknetEmulPacketReceiveBitStream(sf.PACKET_CONNECTION_LOST, bs)
    raknetDeleteBitStream(bs)
  end)
end


-- Weather & Time by MonetLoader
local WeatherAndTime = {
  weather = new.int(0),
  time = new.int(0),
  locked_time = 0,
  new_time = false,
  thread = nil
}


-- FlyCar by MonetLoader
local FlyCar = {
  enabled = new.bool(false),
  cars = 0
}

FlyCar.processFlyCar = function()
  local car = storeCarCharIsInNoSave(PLAYER_PED)
  local speed = getCarSpeed(car)

  local result, var_1, var_2 = isWidgetPressedEx(WIDGET_VEHICLE_STEER_ANALOG, 0)
  if result then
    local var_1 = var_1 / -64.0
    local var_2 = var_2 / 64.0
    setCarRotationVelocity(car, var_2, 0.0, var_1)
  end

  if isWidgetPressed(WIDGET_ACCELERATE) and speed <= 200.0 then
    FlyCar.cars = FlyCar.cars + 0.4
  end
  if isWidgetPressed(WIDGET_BRAKE) then
    FlyCar.cars = FlyCar.cars - 0.3
    if FlyCar.cars < 0 then FlyCar.cars = 0 end
  end
  if isWidgetPressed(WIDGET_HANDBRAKE) then
    FlyCar.cars = 0
    setCarRotationVelocity(car, 0.0, 0.0, 0.0)
    setCarRoll(car, 0.0)
  end

  setCarForwardSpeed(car, FlyCar.cars)
end

FlyCar.activate = function()
  lua_thread.create(function()
    while FlyCar.enabled[0] do
      if isCharInAnyCar(PLAYER_PED) then
        FlyCar.processFlyCar()
      else
        FlyCar.cars = 0
      end

      wait(0)
    end
  end)
end

FlyCar.reset = function()
  FlyCar.cars = 0
end


-- NoBike by MonetLoader
local NoBike = {
  enabled = new.bool(false)
}

NoBike.activate = function()
  setCharCanBeKnockedOffBike(PLAYER_PED, true)
  lua_thread.create(function()
    while NoBike.enabled[0] do
      if isCharInAnyCar(PLAYER_PED) then
        if isCarInWater(storeCarCharIsInNoSave(PLAYER_PED)) then
          setCharCanBeKnockedOffBike(PLAYER_PED, false)
        else
          setCharCanBeKnockedOffBike(PLAYER_PED, true)
        end
      end
      wait(0)
    end
  end)
end

NoBike.reset = function()
  setCharCanBeKnockedOffBike(PLAYER_PED, false)
end


-- SetSkin by forget. (https://www.blast.hk/threads/22151/)
local SetSkin = {
  skinid = new.int(0)
}

SetSkin.activate = function()
  local bs = raknetNewBitStream()
  raknetBitStreamWriteInt32(bs, select(2, sampGetPlayerIdByCharHandle(PLAYER_PED)))
  raknetBitStreamWriteInt32(bs, SetSkin.skinid[0])
  raknetEmulRpcReceiveBitStream(153, bs)
  raknetDeleteBitStream(bs)
end


-- ESP by MonetLoader
local ESP = {
  BONES = { 3, 4, 5, 51, 52, 41, 42, 31, 32, 33, 21, 22, 23, 2 },
  FONT = renderCreateFont('Arial', SCREEN_H * 0.01, 1 + 4),
  enabled_bones = new.bool(false),
  enabled_boxes = new.bool(false),
  enabled_nicks = new.bool(false)
}

ESP.processESP = function()
  while not isSampAvailable() do wait(0) end

  while true do
    wait(0)

    for _, char in ipairs(getAllChars()) do
      local result, id = sampGetPlayerIdByCharHandle(char)
      if result and isCharOnScreen(char) then
        local opaque_color = bit.bor(bit.band(sampGetPlayerColor(id), 0xFFFFFF), 0xFF000000)

        if ESP.enabled_bones[0] then
          for _, bone in ipairs(ESP.BONES) do
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
        end

        if ESP.enabled_boxes[0] then
          local x, y, z = getOffsetFromCharInWorldCoords(char, 0, 0, 0) -- To get position of char even if he is in car
          local headx, heady = convert3DCoordsToScreen(x, y, z + 1.0)
          local footx, footy = convert3DCoordsToScreen(x, y, z - 1.0)
          local width = math.abs((heady - footy) * 0.25)
          renderDrawBoxWithBorder(headx - width, heady, math.abs(2 * width), math.abs(footy - heady), 0, SCREEN_H * 0.005, opaque_color)
        end

        if ESP.enabled_nicks[0] then
          local hx, hy, hz = getBonePosition(char, 5)
          local hr, headx, heady = convert3DCoordsToScreenEx(hx, hy, hz + 0.25)
          if hr then
            local nickname = sampGetPlayerNickname(id)
            local nametag = nickname .. ' [' .. tostring(id) .. '] - {FF0000}' .. string.format("%.0f", sampGetPlayerHealth(id)) .. 'hp {BBBBBB}' .. string.format("%.0f", sampGetPlayerArmor(id)) .. 'ap'
            local nametag_len = renderGetFontDrawTextLength(ESP.FONT, nametag)
            local nametag_x = headx - nametag_len / 2
            local nametag_y = heady - renderGetFontDrawHeight(ESP.FONT)
            renderFontDrawText(ESP.FONT, nametag, nametag_x, nametag_y, opaque_color)
          end
        end
      end
    end
  end
end

lua_thread.create(ESP.processESP)


-- Menu
imgui.OnFrame(function() return window_state[0] end,
  function(player)
    imgui.SetNextWindowSize(imgui.ImVec2(imgui.GetFontSize() * 70, imgui.GetFontSize() * 50), imgui.Cond.FirstUseEver)
    imgui.Begin(u8'Мультичит для MonetLoader ' .. script.this.version, window_state)
    
    imgui.SetWindowFontScale(window_scale[0])
    imgui.SliderFloat(u8'Размер шрифта', window_scale, 1 / MONET_DPI_SCALE, 3.0)

    if imgui.BeginTabBar('Tabs') then
      if imgui.BeginTabItem(u8'Общее') then -- первая вкладка
        if imgui.Checkbox('AirBrake', AirBrake.enabled) then
          if AirBrake.enabled[0] then
            AirBrake.activate()
          else
            AirBrake.reset()
          end
        end
        imgui.SetNextItemWidth(imgui.GetFontSize() * 15)
        imgui.SliderFloat(u8'Скорость AirBrake', AirBrake.speed, 0.1, 3.5)

        if imgui.Button(u8'Реконнект') and not Reconnect.reconnecting and not Reconnect.waiting then
          Reconnect.activate()
        end
        if Reconnect.waiting then
          imgui.SameLine()
          imgui.Text(string.format(u8'Реконнект через %.2f секунд...', Reconnect.remaining / 1000))
          imgui.SameLine()
          if imgui.Button(u8'Отмена') then
            Reconnect.abort = true
          end
        end

        imgui.SetNextItemWidth(imgui.GetFontSize() * 15)
        imgui.SliderFloat(u8'Задержка реконнекта (в секундах)', Reconnect.delay, 0.0, 30.0)

        if imgui.Button(u8'Установить погоду') then
          forceWeatherNow(WeatherAndTime.weather[0])
        end
        imgui.SameLine()
        imgui.SetNextItemWidth(imgui.GetFontSize() * 8)
        if imgui.InputInt(u8'Погода', WeatherAndTime.weather, 1, 10) then
          if WeatherAndTime.weather[0] < 0 then
            WeatherAndTime.weather[0] = 0
          end
          if WeatherAndTime.weather[0] > 45 then
            WeatherAndTime.weather[0] = 45
          end
        end

        if imgui.Button(u8'Установить время') then
          if WeatherAndTime.thread ~= nil then
            WeatherAndTime.thread:terminate()
          end

          WeatherAndTime.locked_time = WeatherAndTime.time[0]
          WeatherAndTime.thread = lua_thread.create(function()
            WeatherAndTime.new_time = false
            while not WeatherAndTime.new_time do
              setTimeOfDay(WeatherAndTime.locked_time, 0)
              wait(0)
            end
            WeatherAndTime.new_time = false
          end)
        end
        imgui.SameLine()
        imgui.SetNextItemWidth(imgui.GetFontSize() * 8)
        if imgui.InputInt(u8'Время', WeatherAndTime.time, 1, 5) then
          if WeatherAndTime.time[0] < 0 then
            WeatherAndTime.time[0] = 0
          end
          if WeatherAndTime.time[0] > 23 then
            WeatherAndTime.time[0] = 23
          end
        end

        imgui.EndTabItem() -- конец вкладки
      end

      if imgui.BeginTabItem(u8'Пед') then -- вторая вкладка
        if imgui.Checkbox('GodMode', GodModePed.enabled) then
          if GodModePed.enabled[0] then
            GodModePed.activate()
          else
            GodModePed.reset()
          end
        end

        if imgui.Button(u8'Умереть') then
          setCharHealth(PLAYER_PED, 0)
        end

        if imgui.Button(u8'Установить скин') then
          SetSkin.activate()
        end
        imgui.SameLine()
        imgui.SetNextItemWidth(imgui.GetFontSize() * 10)
        imgui.InputInt(u8'Скин', SetSkin.skinid, 1, 50)

        imgui.EndTabItem() -- конец вкладки
      end

      if imgui.BeginTabItem(u8'Транспорт') then -- третья вкладка
        if imgui.Checkbox('GodMode', GodModeCar.enabled) then
          if GodModeCar.enabled[0] then
            GodModeCar.activate()
          else
            GodModeCar.reset()
          end
        end

        if imgui.Checkbox('FlyCar', FlyCar.enabled) then
          if FlyCar.enabled[0] then
            FlyCar.activate()
          else
            FlyCar.reset()
          end
        end

        if imgui.Checkbox('NoBike', NoBike.enabled) then
          if NoBike.enabled[0] then
            NoBike.activate()
          else
            NoBike.reset()
          end
        end

        imgui.EndTabItem() -- конец вкладки
      end

      if imgui.BeginTabItem('ESP') then -- четвертая вкладка
        imgui.Checkbox(u8'Скелеты', ESP.enabled_bones)
        imgui.Checkbox(u8'Коробки', ESP.enabled_boxes)
        imgui.Checkbox(u8'Ники', ESP.enabled_nicks)

        imgui.EndTabItem() -- конец вкладки
      end

      imgui.EndTabBar() -- конец всех вкладок
    end

    imgui.End()
  end
)

function sampev.onSendClientJoin(v, m, n, cr, ak, cv, cr2)
  Reconnect.reconnecting = false
end

function sampev.onSetPlayerTime(h, m)
  WeatherAndTime.new_time = true
end

function sampev.onSetWorldTime(h)
  WeatherAndTime.new_time = true
end

function sampev.onSendPlayerSync(data)
  if AirBrake.enabled[0] then
    local speed = AirBrake.speed[0]
    local mx, my = AirBrake.getMoveSpeed(getCharHeading(PLAYER_PED), speed > 1 and 1 or speed)
    data.moveSpeed.x = mx
    data.moveSpeed.y = my
  end
end

function sampev.onSendVehicleSync(data)
  if AirBrake.enabled[0] then
    local speed = AirBrake.speed[0]
    local mx, my = AirBrake.getMoveSpeed(getCharHeading(PLAYER_PED), speed > 2 and 2 or speed)
    data.moveSpeed.x = mx
    data.moveSpeed.y = my
  end
end

function main()
  sampRegisterChatCommand('cheats', function() window_state[0] = not window_state[0] end)
  
  while true do
    wait(0)
  end
end

