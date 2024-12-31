%module gfx2d
%{
#include <engine/gfx2d.h>
%}

%immutable;
%nodefaultctor;
%nodefaultdtor;
%noimmutable Sprite::x;
%noimmutable Sprite::y;
%noimmutable Sprite::width;
%noimmutable Sprite::height;
%noimmutable Sprite::position;
%noimmutable Sprite::size;
%noimmutable Sprite::rect;
%noimmutable Sprite::origin;
%noimmutable Sprite::rotationDeg;
%noimmutable Sprite::color;
%noimmutable Sprite::animSpeedMS;
%include <engine/gfx2d.h>
