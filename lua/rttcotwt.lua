-- bomb catch & throw-back game
-- by iori branford

require "pico8"
require "rttcotwt.assets"
require "rttcotwt.bg"
require "rttcotwt.bomb"
require "rttcotwt.camera"
require "rttcotwt.enemy"
require "rttcotwt.ninja"
require "rttcotwt.object"
require "rttcotwt.phases"
require "rttcotwt.ui"
require "rttcotwt.utility"
require "rttcotwt.world"

return function()
    cartdata("rttcotwt")
    MapInputsToActions {
        ["KAXIS_-LEFT+RIGHT"] = "movex",
        ["KAXIS_-UP+DOWN"] = "movey",
        KEY_Z = "throw",
        KEY_X = "jump"
    }
    start_title()
    while true do
        coroutine.yield()
        pico8_loop()
    end
end
