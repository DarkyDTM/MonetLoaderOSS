-- MonetLoader for Android 2.3.0
-- Reference script: 2.3.0 Demo
script_name('2.3.0 Demo')
script_version('1.1')
script_version_number(2)
script_author('The MonetLoader Team')
script_description('Simple demo of new functions in 2.3.0.')

local sf = require('sampfuncs')
local te = require('monetloader').touch_events

local dialog_id = 24916
local dialog_id_font = 24917

local box_x, box_y = 50, 700
local box_w, box_h = 300, 100
local sw, sh = getScreenResolution()

local font_size = 36
local object_render = false

local font = renderCreateFont('Arial', font_size / MONET_DPI_SCALE, 1 + 4) -- We want font size to be same, irrespective of DPI

function show_dialog()
  sampShowDialog(dialog_id, '{FFCC00}MonetLoader 2.3.0 Demo',
    'Toggle object render - ' .. (object_render and '{00FF00}ENABLED' or '{FF0000}DISABLED') .. '\nUnload script\nChange font size - ' .. tostring(font_size),
    'OK', 'Cancel', sf.DIALOG_STYLE_LIST)
end

function main()
  if not isSampLoaded() then script.this:unload() end
  while not isSampAvailable() do wait(0) end
  while true do
    wait(0)

    local res, btn, list = sampHasDialogRespond(dialog_id)
    if res and btn == 1 then
      if list == 0 then
        object_render = not object_render
        show_dialog()
      elseif list == 1 then
        script.this:unload()
      elseif list == 2 then
        sampShowDialog(dialog_id_font, '{FFCC00}Input font size', '{FFFFFF}What font size do you want?', 'OK', 'Back', sf.DIALOG_STYLE_INPUT)
      end
    end

    local res, btn, _, input = sampHasDialogRespond(dialog_id_font)
    if res then
      if btn == 0 then
        show_dialog()
      else
        local new_size = tonumber(input)
        if type(new_size) ~= 'number' then
          sampShowDialog(dialog_id_font, '{FFCC00}Input font size', '{FFFFFF}What font size do you want?\n{FF0000}Error!', 'OK', 'Back', sf.DIALOG_STYLE_INPUT)
        else
          renderReleaseFont(font)
          font_size = new_size
          font = renderCreateFont('Arial', font_size / MONET_DPI_SCALE, 1 + 4)
          show_dialog()
        end
      end
    end

    renderDrawBoxWithBorder(box_x, box_y, box_w, box_h, 0x77FF0000, 2, 0xFFFF0000)
    renderFontDrawText(font, 'Options', box_x + 10, box_y + 10, -1)

    if object_render then
      for _, obj in ipairs(getAllObjects()) do
        if isObjectOnScreen(obj) then
          local sresult, sx, sy = convert3DCoordsToScreenEx(select(2, getObjectCoordinates(obj)))
          if sresult then
            local id = sampGetObjectSampIdByHandle(obj)
            if id ~= -1 then
              renderFontDrawText(font, 'Model: {00FF00}' .. tostring(getObjectModel(obj)) .. '\n{FFFFFF}SAMP ID: {FFFF00}' .. tostring(id), sx, sy, -1)
            else
              renderFontDrawText(font, 'Model: {00FF00}' .. tostring(getObjectModel(obj)) .. '\n{FFFFFF}SAMP ID: {FF0000}Unknown', sx, sy, -1)
            end
          end
        end
      end
    end
  end
end

function onScriptLoad(scr)
  print(scr.id, script.this.id)
  if scr == script.this then
    print('We have loaded! DPI scale:', MONET_DPI_SCALE)
  else
    print(scr.name, 'loaded!')
  end
end

function onScriptTerminate(scr, quit)
  if scr == script.this then
    print('We have terminated, quit:',  quit)
  else
    print(scr.name, 'terminated!')
  end
end

function onExitScript(quit)
  print('Exiting peacefully, quit:', quit)
end

function onQuitGame()
  print('Qutting game. Goodbye!')
end

function onTouch(type, id, x, y)
  if type == te.TOUCH_PUSH and x > box_x and y > box_y and x < box_x + box_w and y < box_y + box_h then
    show_dialog()
    return false
  end
end