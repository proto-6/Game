#include "Button.h"

void gm::Button::CentralizeText()
{
    this->text.setPosition(this->rectangle.getPosition() + this->rectangle.getSize() / 2.f);
}

void gm::Button::CentralizeTextOrigin()
{
    this->text.setOrigin
    (
        text.getGlobalBounds().getSize().x / 2.f + text.getLocalBounds().getPosition().x,
        text.getGlobalBounds().getSize().y / 2.f + text.getLocalBounds().getPosition().y

    );
}

gm::Button::Button(sf::String text)
    :original_size(sf::Vector2f((300.f * SCREEN_WIDTH) / 1920.f, (100.f * SCREEN_HEIGHT) / 1080.f))
{
    this->text.setString(text);
    
    this->rectangle.setSize(sf::Vector2f((300.f * SCREEN_WIDTH) / 1920.f, (100.f * SCREEN_HEIGHT) / 1080.f));
    this->rectangle.setFillColor(sf::Color(128, 128, 128)); // Hex: #808080
    this->rectangle.setOutlineColor(sf::Color(218, 200, 200)); // Hex: #404040, if looking bad then chose #606060
    this->rectangle.setOutlineThickness(5);
    this->rectangle.setCornerPointCount(4);
    this->rectangle.setCornersRadius(4);




    this->text.setFillColor(sf::Color(10, 10, 10));
    this->text.setOutlineColor(sf::Color(5, 5, 5));
    this->text.setPosition(this->rectangle.getPosition() + (this->rectangle.getSize() / 2.f));
    this->text.setOutlineThickness(1);
    this->text.setCharacterSize(26);
    CentralizeText();
}

void gm::Button::SetSize(const sf::Vector2f& size)
{
    this->rectangle.setSize(size);
    
}

void gm::Button::SetPosition(sf::Vector2f pos)
{
    this->rectangle.setPosition(pos);
    
    CentralizeText();
    
    
}

void gm::Button::SetPosition(float x, float y)
{
    this->rectangle.setPosition(x, y);
    
    /*this->text.setPosition(this->rectangle.getPosition() + this->rectangle.getSize() / 2.f);*/
    CentralizeText();
    this->original_position = { x, y };
}

void gm::Button::SetFont(Font::Type font, GameDataRef data)
{
    this->text.setFont(data->assets.GetFont(font));
    CentralizeTextOrigin();
}

void gm::Button::SetCornerPointCount(unsigned int count)
{
    this->rectangle.setCornerPointCount(count);
}

void gm::Button::SetCornerRadius(float radius)
{
    this->rectangle.setCornersRadius(radius);
}

void gm::Button::SetOrigin(sf::Vector2f coords)
{
    this->rectangle.setOrigin(coords);
    
}


sf::Vector2f gm::Button::GetSize()
{
    return sf::Vector2f(this->rectangle.getSize().x + 5.f, this->rectangle.getSize().y + 5.f);
}

const sf::Vector2f& gm::Button::GetPosition()
{
    return this->rectangle.getPosition();
}

size_t gm::Button::GetCornerPointCount()
{
    return this->rectangle.getPointCount();
}

float gm::Button::GetCornerRadius()
{
    return this->rectangle.getCornersRadius();
}

sf::FloatRect gm::Button::GetGlobalBounds()
{
    sf::Vector2f pos = this->rectangle.getPosition();
    sf::Vector2f size = this->rectangle.getSize();
    float outline_thickness = this->rectangle.getOutlineThickness();
    sf::FloatRect return_val(pos.x - outline_thickness, pos.y - outline_thickness, size.x + outline_thickness * 2, size.y + outline_thickness * 2);
    return return_val;
}

sf::Vector2f gm::Button::GetOrigin()
{
    return this->rectangle.getOrigin();
}


ButtonName::Type gm::Button::GetButtonType()
{
    if (text.getString() == "Play") return ButtonName::Type::Play;
    else if (text.getString() == "Exit") return ButtonName::Type::Exit;
    else if (text.getString() == "Alright") return ButtonName::Type::Alright;
    else return ButtonName::Type::None;
}

void gm::Button::Hover(sf::Vector2f expected /*300, 100*/, sf::Vector2i mouse_pos, float speed)
{
    SetSize(this->rectangle.getSize() + speed * (expected - this->rectangle.getSize()));
    

    SetPosition(original_position - (expected - original_size) / 4.0f);
    /*SetSize(original_size + speed * (hover_size - original_size));*/
}

void gm::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    target.draw(rectangle, states);
    target.draw(text, states);
    
}

