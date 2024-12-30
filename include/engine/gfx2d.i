%module gfx2d
%{
#include <engine/gfx2d.h>
%}

%immutable;
%include <engine/gfx2d.h>

%mutable Sprite::x;
%mutable Sprite::y;
%mutable Sprite::width;
%mutable Sprite::height;
%mutable Sprite::position;
%mutable Sprite::size;
%mutable Sprite::rect;
%mutable Sprite::origin;
%mutable Sprite::rotationDeg;
%mutable Sprite::color;
%mutable Sprite::animSpeedMS;