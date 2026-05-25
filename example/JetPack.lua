-- MonetLoader for Android 2.0.0
-- Reference script: JetPack
script_name('JetPack')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Allows you to get JetPack by doubletapping fist icon, with sync spoofing for SAMP. In order to control JetPack in SAMP, set layout to adapted.')

local sampev = require('samp.events') -- for spoofing player sync
local widgets = require('widgets') -- for WIDGET_(...)


local was_doubletapped = false

function sampev.onSendPlayerSync(data)
  if data.specialAction == 2 then
    data.specialAction = 0
  end
end

function main()
  while true do
    wait(0)

    if isWidgetDoubletapped(WIDGET_PLAYER_INFO) then
      if not was_doubletapped then
        if isSampAvailable() then
          sampSetSpecialAction(2)
        else
          taskJetpack(PLAYER_PED)
        end
        was_doubletapped = true
      end
    else
      was_doubletapped = false
    end
  end
end