-- MonetLoader for Android 2.0.0
-- Reference script: Lua Shell
script_name('Lua Shell')
script_version('0.1')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Execute Lua code with /lua command.')

function main()
  if not isSampLoaded() then script.this:unload() end
  while not isSampAvailable() do wait(100) end
  sampRegisterChatCommand('lua', function(arg)
    if #arg == 0 then return end
    local print_result = false
    if arg:sub(1, 1) == '=' then
      print_result = true
      arg = 'return ' .. arg:sub(2)
    end

    local chunk, err = load(arg)
    if not chunk then
      sampAddChatMessage('[Lua Shell] Syntax error: ' .. tostring(err), 0xFF6347)
      return
    end

    local result, err = pcall(chunk)
    if not result then
      sampAddChatMessage('[Lua Shell] Error: ' .. tostring(err), 0xFF6347)
    elseif print_result then
        sampAddChatMessage('[Lua Shell] ' .. tostring(err), 0xFFFFFF)
    end
  end)

  wait(-1)
end