#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>

class Collider : public sf::Drawable {
public:
    //Basic box collider constructor
    Collider(sf::Vector2f position, sf::Vector2f size, bool isFixed, bool isActive);
    ~Collider();
    //used for physics checks
    static void GlobalCollision();
    //do you want colliders to be displayed?
    static void SetDisplayColliders(bool display);
    //does this collider collide with other?
    bool collides(Collider& other);
    //does this collider collide with other? where and how much?
    bool collides(Collider& other, sf::FloatRect& intersection);

    virtual void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    //set if the object can be moved by collision
    void setFixed(bool isFixed);
    //set if the object is able to collide with others (will still collide with fixed colliders)
    void setActive(bool isActive);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    bool isFixed();
    bool isActive();

protected:
    //the collider bounds
    sf::FloatRect m_collider;
    //immoveable object
    bool m_isFixed;
    //if this is interactable at all
    bool m_isActive;

private:
    //should colliders be displayed?
    static bool m_DisplayColliders;
    //all colliders, for physics updates
    static std::vector<Collider*> m_Colliders;
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};