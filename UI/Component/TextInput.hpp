#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <memory>
#include <string>

#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Text.hpp"

namespace Engine
{
	/// <summary>
	/// A simple static text object.
	/// </summary>
	class TextInput : public IObject, public IControl
	{
	protected:
		TextButton *border;
		// Smart pointer to font.
		std::shared_ptr<ALLEGRO_FONT> font;
		std::string text = "";
		int max_length = 10;
		int cursor_position = 0;
		ALLEGRO_COLOR text_color;
		ALLEGRO_COLOR border_color;
		ALLEGRO_COLOR background_color;
		bool focused = false;
		bool show_cursor = false;
		ALLEGRO_TIMER *cursor_blink_timer;

	public:
		/// <summary>
		/// Construct a label object.
		/// </summary>
		/// <param name="font">Font to draw in.</param>
		/// <param name="fontSize">Text's font size.</param>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="w">Width of the text input.</param>
		/// <param name="h">Height of the text input.</param>
		/// <param name="r">Text's color's red value.</param>
		/// <param name="g">Text's color's green value.</param>
		/// <param name="b">Text's color's blue value.</param>
		/// <param name="a">Text's color's alpha value.</param>
		/// <param name="br">Border's color's red value.</param>
		/// <param name="bg">Border's color's green value.</param>
		/// <param name="bb">Border's color's blue value.</param>
		/// <param name="ba">Border's color's alpha value.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left,
		/// while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means
		/// bottom-left, while (1, 1) means bottom-right.</param>
		explicit TextInput(const std::string &font, int fontSize, float x, float y,
						   float w, float h, unsigned char r = 0, unsigned char g = 0,
						   unsigned char b = 0, unsigned char a = 255,
						   unsigned char br = 0, unsigned char bg = 0,
						   unsigned char bb = 0, unsigned char ba = 255,
						   float anchorX = 0, float anchorY = 0);
		/// <summary>
		/// Draw text with loaded font.
		/// </summary>
		void Draw() const override;
		/// <summary>
		/// Return text width.
		/// </summary>
		/// <returns>Width of the text.</returns>
		int GetTextWidth() const;
		/// <summary>
		/// Return text height.
		/// </summary>
		/// <returns>Height of the text.</returns>
		int GetTextHeight() const;
		/// <summary>
		/// Set the text of the text input.
		/// </summary>
		/// <param name="text">The new text to set.</param>
		void SetText(const std::string &text);
		/// <summary>
		/// Get the text of the text input.
		/// </summary>
		/// <returns>The current text.</returns>
		const std::string &GetText() const;
		/// <summary>
		/// Set the max length of the text input.
		/// </summary>
		/// <param name="length">The max length.</param>
		int GetMaxLength() const;
		/// <summary>
		/// Set the focus of the text input.
		/// </summary>
		/// <param name="focus">True if focused, false otherwise.</param>
		void SetFocus(bool focus);
		/// <summary>
		/// Get the focus of the text input.
		/// </summary>
		/// <returns>True if focused, false otherwise.</returns>
		bool IsFocused() const;
		void OnMouseDown(int button, int mx, int my) override;
		void OnMouseUp(int button, int mx, int my) override;
		void OnMouseMove(int mx, int my) override;
		void OnKeyDown(int keycode) override;
		void OnKeyUp(int keycode) override;
		void OnChar(int unicode) override;
		void Update(float dt) override;
	};
} // namespace Engine

#endif // TEXTINPUT_HPP