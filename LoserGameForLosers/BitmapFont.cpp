#include "stdafx.h"
#include "BitMapFont.h"

BitmapFont::BitmapFont()
{
	//Initialize variables
	map_bitmap_ = nullptr;
	map_new_line_ = 0;
	map_space_ = 0;
}

bool BitmapFont::build_font(BitmapTexture* bitmap)
{
	bool success = true;

	//Lock pixels for access
	if (!bitmap->lock_texture())
	{
		printf("Unable to lock bitmap font texture!\n");
		success = false;
	}
	else
	{
		//Set the background color
		Uint32 bgColor = bitmap->get_pixel32(0, 0);

		//Set the cell dimensions
		int cellW = bitmap->get_width() / 16;
		int cellH = bitmap->get_height() / 16;

		//New line variables
		int top = cellH;
		int baseA = cellH;

		//The current character we're setting
		int currentChar = 0;

		//Go through the cell rows
		for (int rows = 0; rows < 16; ++rows)
		{
			//Go through the cell columns
			for (int cols = 0; cols < 16; ++cols)
			{
				//Set the character offset
				map_chars_[currentChar].x = cellW * cols;
				map_chars_[currentChar].y = cellH * rows;

				//Set the dimensions of the character
				map_chars_[currentChar].w = cellW;
				map_chars_[currentChar].h = cellH;

				//Find Left Side
				//Go through pixel columns
				for (int pCol = 0; pCol < cellW; ++pCol)
				{
					//Go through pixel rows
					for (int pRow = 0; pRow < cellH; ++pRow)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (bitmap->get_pixel32(pX, pY) != bgColor)
						{
							//Set the x offset
							map_chars_[currentChar].x = pX;

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Right Side
				//Go through pixel columns
				for (int pColW = cellW - 1; pColW >= 0; --pColW)
				{
					//Go through pixel rows
					for (int pRowW = 0; pRowW < cellH; ++pRowW)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pColW;
						int pY = (cellH * rows) + pRowW;

						//If a non colorkey pixel is found
						if (bitmap->get_pixel32(pX, pY) != bgColor)
						{
							//Set the width
							map_chars_[currentChar].w = (pX - map_chars_[currentChar].x) + 1;

							//Break the loops
							pColW = -1;
							pRowW = cellH;
						}
					}
				}

				//Find Top
				//Go through pixel rows
				for (int pRow = 0; pRow < cellH; ++pRow)
				{
					//Go through pixel columns
					for (int pCol = 0; pCol < cellW; ++pCol)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (bitmap->get_pixel32(pX, pY) != bgColor)
						{
							//If new top is found
							if (pRow < top)
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom of A
				if (currentChar == 'A')
				{
					//Go through pixel rows
					for (int pRow = cellH - 1; pRow >= 0; --pRow)
					{
						//Go through pixel columns
						for (int pCol = 0; pCol < cellW; ++pCol)
						{
							//Get the pixel offsets
							int pX = (cellW * cols) + pCol;
							int pY = (cellH * rows) + pRow;

							//If a non colorkey pixel is found
							if (bitmap->get_pixel32(pX, pY) != bgColor)
							{
								//Bottom of a is found
								baseA = pRow;

								//Break the loops
								pCol = cellW;
								pRow = -1;
							}
						}
					}
				}

				//Go to the next character
				++currentChar;
			}
		}

		//Calculate space
		map_space_ = cellW / 2;

		//Calculate new line
		map_new_line_ = baseA - top;

		//Lop off excess top pixels
		for (int i = 0; i < 256; ++i)
		{
			map_chars_[i].y += top;
			map_chars_[i].h -= top;
		}

		bitmap->unlock_texture();
		map_bitmap_ = bitmap;
	}

	return success;
}

void BitmapFont::render_text(int x, int y, float sc, std::string text)
{
	//If the font has been built
	if (map_bitmap_ != NULL)
	{
		//Temp offsets
		int curX = x, curY = y;

		//Go through the text
		for (int i = 0; i < text.length(); ++i)
		{
			//If the current character is a space
			if (text[i] == ' ')
			{
				//Move over
				curX += map_space_;
			}
			//If the current character is a newline
			else if (text[i] == '\n')
			{
				//Move down
				curY += map_new_line_;

				//Move back
				curX = x;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)text[i];

				//Show the character
				TextureManager::draw(map_bitmap_->get_texture(), map_chars_[ascii], SDL_Rect{ curX, curY, static_cast<int>(map_chars_[ascii].w * sc), static_cast<int>(map_chars_[ascii].h * sc) }, 0, SDL_FLIP_NONE);

				//Move over the width of the character with one pixel of padding
				curX += map_chars_[ascii].w + 1;
			}
		}
	}
}

SDL_Rect BitmapFont::text_dimensions(const int x, const int y, std::string text)
{
	//Temp offsets
	auto cur_w = 0, cur_h = 0;

	//Go through the text
	for (auto i = 0; i < text.length(); ++i)
	{
		//If the current character is a space
		if (text[i] == ' ')
		{
			//Move over
			cur_w += map_space_;
		}
		//If the current character is a newline
		else if (text[i] == '\n')
		{
			//Move down
			cur_h += map_new_line_;

		}
		else
		{
			//Get the ASCII value of the character
			const int ascii = static_cast<unsigned char>(text[i]);

			//Move over the width of the character with one pixel of padding
			cur_w += map_chars_[ascii].w + 1;
		}
	}
	return SDL_Rect{ x, y, cur_w, cur_h };

}