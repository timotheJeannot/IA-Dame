//
// Created by ubuntu on 02/11/2020.
//

#ifndef TEST_GF_GRAPH_H
#define TEST_GF_GRAPH_H

#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
using namespace std;


class Graph {
public:
    // Plateau
    gf::Vector2u ScreenSize;
    gf::Window window;
    gf::RenderWindow renderer;
    gf::Vector2f begin;
    // entities
    int sizeCircle;
    float sizeSquare;
    // method
    void printStartPiece();
    void printBoard();
    Graph();
    Graph(gf::Vector2u SSize, const string& gName, gf::Vector2f begin, int sizeC, float sizeS);

};

class GSquare {
public:
    GSquare(gf::Vector2f position, float size, gf::Color4f color)
            : m_position(position)
            , m_size(size)
            , m_color(color)
    {
    }
    void render(gf::RenderTarget& target) {
        gf::RectangleShape shape({ m_size, m_size });
        shape.setPosition(m_position);
        shape.setColor(m_color);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }
private:
    gf::Vector2f m_position; // center of the square
    float m_size;
    gf::Color4f m_color;
};

class GPiece {
public :

    GPiece(gf::Vector2f position, float size, gf::Color4f color)
            :m_position(position)
            ,m_size(size)
            ,m_color(color)
    /*,m_texture(gf::Image())*/{}

    void render(gf::RenderTarget& target) {
        gf::CircleShape shape;
        shape.setRadius(m_size);
        shape.setPosition(m_position);
        shape.setColor(m_color);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }
private:
    gf::Vector2f m_position;
    float m_size;
    gf::Color4f m_color;
    //gf::Texture m_texture;
};



#endif //TEST_GF_GRAPH_H
