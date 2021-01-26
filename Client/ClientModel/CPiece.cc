//
// Created by ubuntu on 17/11/2020.
//

#include "CPiece.h"



void CPiece::render(gf::RenderTarget &target) {
    gf::CircleShape shape;
    shape.setRadius(m_size);
    shape.setPosition(m_position);
    if(m_color == gf::Color::Black){
        shape.setOutlineColor(gf::Color::Gray());
    }else{
        shape.setOutlineColor(gf::Color::Black);
    }
    shape.setOutlineThickness(1);
    shape.setColor(m_color);
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);
    if(type == CDAME){
        gf::CircleShape shape2;
        shape2.setRadius(m_size);
        gf::Vector2f twoposition(m_position.x,m_position.y-5);
        shape2.setPosition(twoposition);
        if(m_color == gf::Color::Black){
            shape2.setOutlineColor(gf::Color::Gray());
        }else{
            shape2.setOutlineColor(gf::Color::Black);
        }
        shape2.setOutlineColor(gf::Color::Black);
        shape2.setOutlineThickness(1);
        shape2.setColor(m_color);
        shape2.setAnchor(gf::Anchor::Center);
        target.draw(shape2);
    }

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

const gf::Vector2i &CPiece::getMCase() const {
    return m_case;
}

CPiece::CPiece(const gf::Vector2f &mPosition, float mSize, const gf::Color4f &mColor,
               const gf::Vector2i &mCase) : m_position(mPosition), m_size(mSize), m_color(mColor),
                                            m_case(mCase) {
    type=CPION;
}


bool operator==(const CPiece& opL, const CPiece& opR)
{
    if(opL.getMPosition() == opR.getMPosition())
    {
        return true;
    }
    return false;
}