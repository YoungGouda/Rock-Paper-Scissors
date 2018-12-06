
#include <utility>
#include "ECS.h"
#include "Components.h"
#include "BitmapFont.h"

struct Label
{
	Label(const SDL_Rect pos, std::string text)
	: position(pos), text(std::move(text))
	{}

	SDL_Rect position;
	std::string text;
};

class GlyphAtlasComponent : public Component
{
	float scale_;
	BitmapFont * bitmap_font_;
	std::vector<Label*> labels_;
public:
	explicit GlyphAtlasComponent(float scaling)
		: scale_(scaling)
	{
		bitmap_font_ = Game::assets->get_bitmap_font();
	}
	
	~GlyphAtlasComponent()
	{}

	void init() override
	{
		if (entity->has_component<OptionsComponent>())
		{
			for (auto& x_link : entity->get_component<OptionsComponent>().current_options->option_links)
			{
				for (auto& y_link : x_link)
				{
					labels_.push_back(new Label(y_link->get_link_dimensions(), y_link->get_text()));
				}
			}
		}
	}

	void draw() override
	{
		for(auto& label : labels_)
		{
			bitmap_font_->render_text(label->position.x, label->position.y, scale_, label->text);
		}
	}
};
