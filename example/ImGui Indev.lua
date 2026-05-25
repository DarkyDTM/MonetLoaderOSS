local imgui = require 'imgui' -- загружаем библиотеку

-- в этой функции осуществляется вся работа с ImGui
-- она вызывается каждый кадр, но только если imgui.Process равен true
function imgui.OnDrawFrame()
  imgui.Begin('Моё окошко :D') -- новое окно с заголовком 'My window'
  imgui.Text('Hello world') -- простой текст внутри этого окна
  imgui.End() -- конец окна
end

function main()
  imgui.Process = true -- ImGui будет обрабатываться, пока imgui.Process равен true
  -- в этом примере мы просто активируем ImGui сразу же после загрузки игры
end