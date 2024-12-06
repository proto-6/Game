#include "Button.h"

void gm::Button::CentralizeText()
{
    this->_text.setPosition(this->_rectangle.getPosition() + this->_rectangle.getSize() / 2.f);
}

void gm::Button::CentralizeTextOrigin()
{
    this->_text.setOrigin
    (
        _text.getGlobalBounds().getSize().x / 2.f + _text.getLocalBounds().getPosition().x,
        _text.getGlobalBounds().getSize().y / 2.f + _text.getLocalBounds().getPosition().y

    );
}

gm::Button::Button(sf::String text)
{
    this->_text.setString(text);
    this->_rectangle.setSize(sf::Vector2f(300, 100));
    this->_rectangle.setFillColor(sf::Color(128, 128, 128)); // Hex: #808080
    this->_rectangle.setOutlineColor(sf::Color(218, 200, 200)); // Hex: #404040, if looking bad then chose #606060
    this->_rectangle.setOutlineThickness(5);
    this->_rectangle.setCornerPointCount(4);
    this->_rectangle.setCornersRadius(4);


    this->original_size = { 300, 100 };


    this->_text.setFillColor(sf::Color(10, 10, 10));
    this->_text.setOutlineColor(sf::Color(5, 5, 5));
    this->_text.setPosition(this->_rectangle.getPosition() + (this->_rectangle.getSize() / 2.f));
    this->_text.setOutlineThickness(1);
    this->_text.setCharacterSize(26);
    CentralizeText();
}

void gm::Button::SetSize(const sf::Vector2f& size)
{
    this->_rectangle.setSize(size);
    
}

void gm::Button::SetPosition(sf::Vector2f pos)
{
    this->_rectangle.setPosition(pos);
    
    
    
    
}

void gm::Button::SetPosition(float x, float y)
{
    this->_rectangle.setPosition(x, y);
    
    /*this->_text.setPosition(this->_rectangle.getPosition() + this->_rectangle.getSize() / 2.f);*/
    CentralizeText();
    this->original_position = { x, y };
}

void gm::Button::SetFont(Font::Type font, GameDataRef _data)
{
    this->_text.setFont(_data->assets.GetFont(font));
    CentralizeTextOrigin();
}

void gm::Button::SetCornerPointCount(unsigned int count)
{
    this->_rectangle.setCornerPointCount(count);
}

void gm::Button::SetCornerRadius(float radius)
{
    this->_rectangle.setCornersRadius(radius);
}

void gm::Button::SetOrigin(sf::Vector2f coords)
{
    this->_rectangle.setOrigin(coords);
    
}


const sf::Vector2f& gm::Button::GetSize()
{
    return sf::Vector2f(this->_rectangle.getSize().x + 5.f, this->_rectangle.getSize().y + 5.f);
}

const sf::Vector2f& gm::Button::GetPosition()
{
    return this->_rectangle.getPosition();
}

unsigned int gm::Button::GetCornerPointCount()
{
    return this->_rectangle.getPointCount();
}

float gm::Button::GetCornerRadius()
{
    return this->_rectangle.getCornersRadius();
}

sf::FloatRect gm::Button::GetGlobalBounds()
{
    sf::Vector2f pos = this->_rectangle.getPosition();
    sf::Vector2f size = this->_rectangle.getSize();
    float outline_thickness = this->_rectangle.getOutlineThickness();
    sf::FloatRect return_val(pos.x - outline_thickness, pos.y - outline_thickness, size.x + outline_thickness * 2, size.y + outline_thickness * 2);
    return return_val;
}

sf::Vector2f gm::Button::GetOrigin()
{
    return this->_rectangle.getOrigin();
}


ButtonName::Type gm::Button::GetButtonType()
{
    if (_text.getString() == "Play") return ButtonName::Type::Play;
    else if (_text.getString() == "Settings") return ButtonName::Type::Settings;
    else if (_text.getString() == "Exit") return ButtonName::Type::Exit;
}

void gm::Button::Hover(sf::Vector2f expected /*300, 100*/, sf::Vector2i mouse_pos, float speed)
{
    SetSize(this->_rectangle.getSize() + speed * (expected - this->_rectangle.getSize()));
    

    SetPosition(original_position - (expected - original_size) / 2.0f);
    /*SetSize(original_size + speed * (hover_size - original_size));*/
}

void gm::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    target.draw(_rectangle, states);
    target.draw(_text, states);
    
}

