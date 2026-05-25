-- MonetLoader for Android 2.1.0
-- Reference script: Simple Button
script_name('2.2.0 Demo')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Simple demo of new events in 2.2.0.')

local te = require('monetloader').touch_events
local box_x, box_y = 50, 700
local box_w, box_h = 300, 100
local sw, sh = getScreenResolution()
local font = renderCreateFont("Arial", 36 / MONET_DPI_SCALE, 1 + 4) -- We want font size to be 36, irrespective of DPI

function main()
  while true do
    wait(0)

    renderDrawBoxWithBorder(box_x, box_y, box_w, box_h, 0x77FF0000, 2, 0xFFFF0000)
    renderFontDrawText(font, "Error", box_x + 10, box_y + 10, -1)

    local samp = isSampLoaded() and isSampAvailable()
    for _, obj in ipairs(getAllObjects()) do
      if isObjectOnScreen(obj) then
        local sresult, sx, sy = convert3DCoordsToScreenEx(select(2, getObjectCoordinates(obj)))
        if sresult then
          local result, id = false, nil
          if samp then
            result, id = sampGetObjectSampIdByHandle(obj)
          end
          if result then
            renderFontDrawText(font, "Model: {00FF00}" .. tostring(getObjectModel(obj)) .. '\n{FFFFFF}SAMP ID: {FFFF00}' .. tostring(id), sx, sy, -1)
          else
            renderFontDrawText(font, "Model: {00FF00}" .. tostring(getObjectModel(obj)) .. '\n{FFFFFF}SAMP ID: {FF0000}Unknown', sx, sy, -1)
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
    a = some_once_more_non_existing_variable * 42
    print('We survived error in onScriptTerminate?')
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
    b = some_non_existing_variable * 42
    print('We survived error?')
    return false
  end
end