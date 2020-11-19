//
// Created by ubuntu on 17/11/2020.
//

#include "CCase.h"

void CCase::render(gf::RenderTarget &target) {
    gf::RectangleShape shape({ m_size, m_size });
    shape.setPosition(m_position);
    shape.setColor(m_color);
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);
}

bool CCase::isCaseSelect(gf::Vector2i vector2I) const {
    int xmin = (int)m_position.x - m_size / 2;
    int xmax = (int)m_position.x + m_size/2;
    int ymin = (int)m_position.y - m_size/2;
    int ymax = (int)m_position.y + m_size/2;

    return(xmin < vector2I.x && vector2I.x < xmax && ymin < vector2I.y && vector2I.y < ymax);
}

const gf::Vector2f &CCase::getMPosition() const {
    return m_position;
}


void CCase::selected() {

    m_selected = m_color;
    m_color = gf::Color::Red;

}
void CCase::deSelected(){
    m_color = m_selected;
}

CCase::CCase(gf::Vector2f position, float size, gf::Color4f color)
        : m_position(position)
        , m_size(size)
        , m_color(color)
{
}
