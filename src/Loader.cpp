#include "../h/Loader.h"

#define LOAD_IMAGE(type, path) { type, LoadImage( "sprites/PiecesPNG80/" ## path ) }

const unordered_map<PieceType, Texture> Loader::WhiteTextureMapper = {

    LOAD_IMAGE(King   , "Chess_klt45.png"),
    LOAD_IMAGE(Queen  , "Chess_qll45.png"),
    LOAD_IMAGE(Rook   , "Chess_rlt45.png"),
    LOAD_IMAGE(Bishop , "Chess_blt45.png"),
    LOAD_IMAGE(Knight , "Chess_nlt45.png"),
    LOAD_IMAGE(Pawn   , "Chess_plt45.png"),
};

const unordered_map<PieceType, Texture> Loader::BlackTextureMapper = {

    LOAD_IMAGE(King   , "Chess_kdt45.png"),
    LOAD_IMAGE(Queen  , "Chess_qdl45.png"),
    LOAD_IMAGE(Rook   , "Chess_rdt45.png"),
    LOAD_IMAGE(Bishop , "Chess_bdt45.png"),
    LOAD_IMAGE(Knight , "Chess_ndt45.png"),
    LOAD_IMAGE(Pawn   , "Chess_pdt45.png"),
};

#undef LOAD_IMAGE

const Texture& Loader::GetTexture(PieceColor color, PieceType type)
{
    return color == White ? WhiteTextureMapper.at(type) : BlackTextureMapper.at(type);
}

const Texture Loader::LoadImage(string imagePath) {
    sf::Texture texture;

    if (!texture.loadFromFile(imagePath)) {
        cerr << "Failed to load image" << endl;
        exit(EXIT_FAILURE);
    }

    return texture;
}