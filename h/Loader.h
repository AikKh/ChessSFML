#pragma once

#include "Includes.h"

class Loader {
public:
    static const unordered_map<PieceType, Texture> TextureMapper;

private:
    static const Texture LoadImage(string imagePath);
};
