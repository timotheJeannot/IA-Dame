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

class CPiece : public gf::Entity {
public :


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
    gf::Vector2i m_case;

public:
    const gf::Vector2i &getMCase() const;
    CPiece(const gf::Vector2f &mPosition, float mSize, const gf::Color4f &mColor,
           const gf::Vector2i &mCase);
    //gf::Texture m_texture;

};

bool operator== (const CPiece& opL , const CPiece& opR);

#endif //TEST_GF_CPIECE_H
