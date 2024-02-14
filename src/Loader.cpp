#include "../h/Loader.h"

#define LOAD_IMAGE(type, path) { type, LoadImage( "sprites/PiecesPNG80/" ## path ) }

const unordered_map<PieceType, Texture> Loader::TextureMapper = {

    LOAD_IMAGE(W_King   , "Chess_klt45.png"),
    LOAD_IMAGE(W_Queen  , "Chess_qll45.png"),
    LOAD_IMAGE(W_Rook   , "Chess_rlt45.png"),
    LOAD_IMAGE(W_Bishop , "Chess_blt45.png"),
    LOAD_IMAGE(W_Knight , "Chess_nlt45.png"),
    LOAD_IMAGE(W_Pawn   , "Chess_plt45.png"),
    LOAD_IMAGE(B_King   , "Chess_kdt45.png"),
    LOAD_IMAGE(B_Queen  , "Chess_qdl45.png"),
    LOAD_IMAGE(B_Rook   , "Chess_rdt45.png"),
    LOAD_IMAGE(B_Bishop , "Chess_bdt45.png"),
    LOAD_IMAGE(B_Knight , "Chess_ndt45.png"),
    LOAD_IMAGE(B_Pawn   , "Chess_pdt45.png"),
};

#undef LOAD_IMAGE

const Texture Loader::LoadImage(string imagePath) {
    sf::Texture texture;

    if (!texture.loadFromFile(imagePath)) {
        cerr << "Failed to load image" << endl;
        exit(EXIT_FAILURE);
    }

    return texture;
}