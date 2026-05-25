-- MonetLoader for Android 2.0.0
-- Reference script: FlyCar
script_name('FlyCar')
script_version('1.0')
script_version_number(1)
script_author('The MonetLoader Team')
script_description('Make your car a plane! Press RESET arcade button to enable/disable. Make sure to use analog controls!')

local widgets = require('widgets') -- for WIDGET_(...)


local cars = 0
local status = false
local was_pressed = false

function processFlyCar()
    local car = storeCarCharIsInNoSave(PLAYER_PED)
    local speed = getCarSpeed(car)
    setCarHeavy(car, false)
    setCarProofs(car, true, true, true, true, true)
    setCharCanBeKnockedOffBike(car, false)

    local result, var_1, var_2 = isWidgetPressedEx(WIDGET_VEHICLE_STEER_ANALOG, 0)
    if result then
        local var_1 = var_1 / -64.0
        local var_2 = var_2 / 64.0
        setCarRotationVelocity(car, var_2, 0.0, var_1)
    end

    if isWidgetPressed(WIDGET_ACCELERATE) and speed <= 200.0 then
        cars = cars + 0.4
    end
    if isWidgetPressed(WIDGET_BRAKE) then
        cars = cars - 0.3
        if cars < 0 then cars = 0 end
    end
    if isWidgetPressed(WIDGET_HANDBRAKE) then
        cars = 0
        setCarRotationVelocity(car, 0.0, 0.0, 0.0)
        setCarRoll(car, 0.0)
    end

    setCarForwardSpeed(car, cars)
end

function main()
    while true do
        wait(0)
        if isCharInAnyCar(PLAYER_PED) and status then
            processFlyCar()
        else
            cars = 0
        end

        local pressed = isWidgetPressed(WIDGET_ARCADE_RESET)
        if pressed and not was_pressed then
            status = not status
            if status then
                printStringNow('~g~on', 1000)
            else
                printStringNow('~r~off', 1000)

                if isCharInAnyCar(PLAYER_PED) then
                    local car = storeCarCharIsInNoSave(PLAYER_PED)
                    setCarProofs(car, false, false, false, false, false)
                    setCharCanBeKnockedOffBike(car, true)
                end
            end
        end
        was_pressed = pressed
    end
end