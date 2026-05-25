-- MonetLoader for Android 2.1.0
-- Reference script: WallHack
script_name('WallHack')
script_version('1.1')
script_version_number(2)
script_author('The MonetLoader Team')
script_description('Simple box + nametag WallHack.')


local sw, sh = getScreenResolution()
local font = renderCreateFont("Arial", 12, 1 + 4) -- P.S. in MonetLoader only Arial Bold is available (every font is defaulted to it)

function main()
  while not isSampAvailable() do wait(0) end

  while true do
    wait(0)

    for _, char in ipairs(getAllChars()) do
      local result, id = sampGetPlayerIdByCharHandle(char)
      if result and isCharOnScreen(char) then
        local x, y, z = getOffsetFromCharInWorldCoords(char, 0, 0, 0) -- To get position of char even if he is in car

        local headx, heady = convert3DCoordsToScreen(x, y, z + 1.0)
        local footx, footy = convert3DCoordsToScreen(x, y, z - 1.0)
        local width = math.abs((heady - footy) * 0.25)

        local nickname = sampGetPlayerNickname(id)
        local nametag = nickname .. ' [' .. tostring(id) .. '] - {FF0000}' .. string.format("%.0f", sampGetPlayerHealth(id)) .. 'hp {BBBBBB}' .. string.format("%.0f", sampGetPlayerArmor(id)) .. 'ap'
        local nametag_len = renderGetFontDrawTextLength(font, nametag)
        local nametag_x = headx - nametag_len / 2
        local nametag_y = heady - renderGetFontDrawHeight(font) * 1.2
        local opaque_color = bit.bor(bit.band(sampGetPlayerColor(id), 0xFFFFFF), 0xFF000000)

        renderFontDrawText(font, nametag, nametag_x, nametag_y, opaque_color)
        renderDrawBoxWithBorder(headx - width, heady, math.abs(2 * width), math.abs(footy - heady), 0, sh * 0.005, opaque_color)
      end
    end
  end
end