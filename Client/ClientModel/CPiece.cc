//
// Created by ubuntu on 17/11/2020.
//

#include "CPiece.h"

CPiece::CPiece(gf::Vector2f position, float size, gf::Color4f color)
        :m_position(position)
        ,m_size(size)
        ,m_color(color)
/*,m_texture(gf::Image())*/{
    type=CPION;

}

void CPiece::render(gf::RenderTarget &target) {
    gf::CircleShape shape;
    shape.setRadius(m_size);
    shape.setPosition(m_position);
    shape.setColor(m_color);
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);
}

void CPiece::setMPosition(const gf::Vector2f &mPosition) {
    m_position = mPosition;
}

const gf::Vector2f &CPiece::getMPosition() const {
    return m_position;
}


CPiece::CPiece() :m_position(gf::Zero)
        ,m_size(0)
        ,m_color(gf::Zero){
}

void CPiece::update(gf::Time time) {

}

bool CPiece::isNotNull() const {
    return this->m_size != 0;
}

CtypePiece CPiece::getType() const {
    return type;
}

void CPiece::setType(CtypePiece type) {
    CPiece::type = type;
}


bool operator==(const CPiece& opL, const CPiece& opR)
{
    if(opL.getMPosition() == opR.getMPosition())
    {
        return true;
    }
    return false;
}