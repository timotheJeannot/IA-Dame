//
// Created by ubuntu on 17/11/2020.
//

#ifndef TEST_GF_CCASE_H
#define TEST_GF_CCASE_H


#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Shapes.h>
#include <gf/RenderTarget.h>
#include "CPiece.h"


class CCase {
public:
    CPiece *m_piece;
    CCase(gf::Vector2f position, float size, gf::Color4f color, CPiece *piece);
    void render(gf::RenderTarget& target);
    const gf::Vector2f &getMPosition() const;
    bool isCaseSelect(gf::Vector2i vector2I) const;
    void deSelected();
    void selected();

private:
    gf::Vector2f m_position; // center of the square
    float m_size;
    gf::Color4f m_color;
    gf::Color4f m_selected;

};


#endif //TEST_GF_CCASE_H
