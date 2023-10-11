#ifndef GUI_H
#define GUI_H

enum button_states {
	BUTTON_IDLE = 0,
	BUTTON_HOVER,
	BUTTON_ACTIVE
};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, 
			sf::Color outline_hover_color = sf::Color::Transparent, 
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText();
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setButtonState();
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void updateTextAsButton(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};


	//  DROPDOWNLIST CLASS  //


	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, 
			float width, float height, 
			sf::Font& font, std::string list[],
			unsigned num_elements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const bool getKeytime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};


	//  TEXTURESELECTOR CLASS  //


	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;

		float gridSize;
		bool active;
		bool hidden;

		gui::Button* hideButton;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		
	public:
		TextureSelector(float x, float y, float width, float height, 
			float gridSize, const sf::Texture* texture_sheet, 
			sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};
}

#endif