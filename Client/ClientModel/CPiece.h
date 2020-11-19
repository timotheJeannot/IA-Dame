//
// Created by ubuntu on 17/11/2020.
//

#ifndef TEST_GF_CPIECE_H
#define TEST_GF_CPIECE_H


#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Color.h>
#include <gf/Anchor.h>
#include <gf/Shapes.h>
#include <gf/RenderTarget.h>

enum CtypePiece {CPION, CDAME};

class CPiece : public gf::Entity{
public :

    CPiece(gf::Vector2f position, float size, gf::Color4f color);

    CPiece();

    void render(gf::RenderTarget& target);

    void setMPosition(const gf::Vector2f &mPosition);

    const gf::Vector2f &getMPosition() const;

    bool isMSelected() const;

    void update(gf::Time time) override;

    void setMSelected(const gf::Color4f &mSelected);


    bool isNotNull() const;

    CtypePiece getType() const;

    void setType(CtypePiece type);

private:
    gf::Vector2f m_position;
    float m_size;
    gf::Color4f m_color;
    CtypePiece type;
    //gf::Texture m_texture;

};

bool operator== (const CPiece& opL , const CPiece& opR);

#endif //TEST_GF_CPIECE_H
