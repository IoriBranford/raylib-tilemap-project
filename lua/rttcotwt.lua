-- bomb catch & throw-back game
-- by iori branford

require "pico8"
require "rttcotwt.assets"
require "rttcotwt.bomb"
require "rttcotwt.camera"
require "rttcotwt.enemy"
require "rttcotwt.ninja"
require "rttcotwt.object"
require "rttcotwt.phases"
require "rttcotwt.utility"
require "rttcotwt.world"

function _init()
    cartdata("rttcotwt")
    start_title()
end
