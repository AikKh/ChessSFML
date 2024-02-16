#pragma once

#include "Includes.h"

class Loader {
public:
    static const Texture& GetTexture(PieceColor color, PieceType type);

private:
    static const unordered_map<PieceType, Texture> WhiteTextureMapper;
    static const unordered_map<PieceType, Texture> BlackTextureMapper;

    static const Texture LoadImage(string imagePath);
};
