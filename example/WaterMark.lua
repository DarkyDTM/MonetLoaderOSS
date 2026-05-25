-- MonetLoader for Android 2.0.0
-- Reference script: WaterMark
script_name('WaterMark')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Shows yellow MonetLoader version and loaded scripts with black outline on semi-transparent background.')

require('sa_renderfix') -- for fixed SA render functions


local script_name = {}

function getLoaderVersionAsString()
  if MONET_VERSION ~= nil then
    local ver = MONET_VERSION
    local epoch = math.floor(ver / 1000000)
    local minor = math.floor(math.floor(ver % 1000000) / 1000)
    local patch = ver % 1000

    return 'MonetLoader ' .. tostring(epoch) .. '.' .. tostring(minor) .. '.' .. tostring(patch)
  else
    local ver = getMoonloaderVersion()
    return 'MoonLoader ' .. tostring(ver / 100)
  end
end

function definedStateTitle()
  setTextScale(0.396, 1.8) -- X scale is weird on mobile (thank you, WarDrum!), good scale I found for same look on mobile and PC - XScale = 0.22 * YScale.
                           -- Scale change is incorporated in sa_renderfix, but who knows.
  setTextColour(255, 255, 0, 255)
  setTextJustify(true)
  setTextRightJustify(false)
  setTextCentre(false)
  setTextFont(1)
  setTextWrapx(999)
  setTextDrawBeforeFade(false)
  setTextDropshadow(0, 0, 0, 0, 0)
  setTextEdge(1, 0, 0, 0, 255)
  setTextProportional(true)
end

function definedStateName()
  setTextScale(0.286, 1.3)
  setTextColour(255, 255, 255, 255)
  setTextJustify(true)
  setTextRightJustify(false)
  setTextCentre(false)
  setTextFont(1)
  setTextWrapx(999)
  setTextDrawBeforeFade(false)
  setTextDropshadow(0, 0, 0, 0, 0)
  setTextEdge(1, 0, 0, 0, 255)
  setTextProportional(true)
end

function main()
  local gxt_key = setFreeGxtEntry(getLoaderVersionAsString())

  while true do
    wait(0)
    useRenderCommands(true) -- If we not do this, text will not be erased on start of frame

    local max_width = 0
    local max_height = 25
  
    definedStateTitle()
    local width = getStringWidth(gxt_key)
    if width > max_width then max_width = width end
    displayText(10, 200, gxt_key)

    for i, s in ipairs(script.list()) do
      if script_name[s.name] == nil then
        script_name[s.name] = setFreeGxtEntry(s.name)
      end

      definedStateName()
      width = getStringWidth(script_name[s.name])
      if width > max_width then max_width = width end
      max_height = max_height + 10

      displayText(10, 210 + i * 10, script_name[s.name])
    end

    -- Rect and sprites are always below text
    max_width = max_width + 10
    drawRect(5 + max_width / 2, 200 + max_height / 2, max_width, max_height, 0, 0, 0, 165)
  end
end