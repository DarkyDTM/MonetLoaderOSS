-- Simple RakLogger
script_name("Incoming RakLogger")
script_author("liminaldev")

-- function onReceiveRpc(id, bs)
--   if id == 137 or id == 138 or id == 44 or id == 108 then return end

--   local data = ""
--   while raknetBitStreamGetNumberOfUnreadBits(bs) >= 8 do
--     local v = raknetBitStreamReadInt8(bs)
--     if v < 0 then v = 256 + v end
--     data = data .. string.format("%02X ", v)
--   end

--   while raknetBitStreamGetNumberOfUnreadBits(bs) >= 1 do
--     local v = raknetBitStreamReadBool(bs)
--     if v then
--       data = data .. '1'
--     else
--       data = data .. '0'
--     end
--   end

--   print("IRPC:", tostring(id), "- Data:", data)
-- end

function onSendPacket(id, bs)
  if id ~= 220 then return end

  local data = ""
  while raknetBitStreamGetNumberOfUnreadBits(bs) >= 8 do
    local v = raknetBitStreamReadInt8(bs)
    if v < 0 then v = 256 + v end
    data = data .. string.format("%02X ", v)
  end

  while raknetBitStreamGetNumberOfUnreadBits(bs) >= 1 do
    local v = raknetBitStreamReadBool(bs)
    if v then
      data = data .. '1'
    else
      data = data .. '0'
    end
  end

  print("OPacket:", tostring(id), "- Data:", data)
end

function onReceivePacket(id, bs)
  if id ~= 220 then return end

  local data = ""
  while raknetBitStreamGetNumberOfUnreadBits(bs) >= 8 do
    local v = raknetBitStreamReadInt8(bs)
    if v < 0 then v = 256 + v end
    data = data .. string.format("%02X ", v)
  end

  while raknetBitStreamGetNumberOfUnreadBits(bs) >= 1 do
    local v = raknetBitStreamReadBool(bs)
    if v then
      data = data .. '1'
    else
      data = data .. '0'
    end
  end

  print("IPacket:", tostring(id), "- Data:", data)
end