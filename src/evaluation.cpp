#include "evaluation.h"

#include <chess/board.h>

#include <array>
#include <iostream>

enum EPieceType {
    PT_UNKNOWN = 0,
    PT_PAWN = 1,
    PT_ROOK = 2,
    PT_KNIGHT = 3,
    PT_BISHOP = 4,
    PT_QUEEN = 5,
    PT_KING = 6,
    PT_COUNT
};

constexpr std::array<double, PT_COUNT> MATERIAL_SCORES{{
    0.0,
    1.0,
    5.0,
    3.0,
    3.0,
    9.0,
    200.0
}};

double EvaluateMaterial(
    const lczero::Position position
) {
    double score = 0.0;
    const lczero::ChessBoard& board = position.GetBoard();
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (!board.ours().get(i, j) && !board.theirs().get(i, j)) {
                continue;
            }
            EPieceType pieceType = PT_UNKNOWN;
            bool isOurs = (board.ours().get(i, j));
            if (board.pawns().get(i, j)) {
                pieceType = PT_PAWN;
            } else if (board.queens().get(i, j)) {
                pieceType = PT_QUEEN;
            } else if (board.bishops().get(i, j)) {
                pieceType = PT_BISHOP;
            } else if (board.rooks().get(i, j)) {
                pieceType = PT_ROOK;
            } else {
                pieceType = PT_KNIGHT;
            }
            if (isOurs) {
                score += MATERIAL_SCORES[pieceType];
            } else {
                score -= MATERIAL_SCORES[pieceType];
            }
        }
    }
    return score;
}