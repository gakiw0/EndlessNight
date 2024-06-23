#include "TextInput.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

namespace Engine
{
    TextInput::TextInput(const std::string &font, int fontSize, float x, float y,
                         float w, float h, unsigned char r, unsigned char g,
                         unsigned char b, unsigned char a, unsigned char br,
                         unsigned char bg, unsigned char bb, unsigned char ba,
                         float anchorX, float anchorY)
        : IObject(x, y, w, h, anchorX, anchorY),
          font(Resources::GetInstance().GetFont(font, fontSize)),
          text_color(al_map_rgba(r, g, b, a)),
          border_color(al_map_rgba(br, bg, bb, ba)),
          background_color(al_map_rgba(0, 0, 0, 0)),
          cursor_blink_timer(al_create_timer(0.5f))
    {
        al_start_timer(cursor_blink_timer);
    }

    void TextInput::Draw() const
    {
        // Draw background
        al_draw_filled_rounded_rectangle(Position.x - Anchor.x * Size.x,
                                         Position.y - Anchor.y * Size.y,
                                         Position.x + (1 - Anchor.x) * Size.x,
                                         Position.y + (1 - Anchor.y) * Size.y,
                                         5, 5, background_color);
        // Draw border
        al_draw_rounded_rectangle(Position.x - Anchor.x * Size.x,
                                  Position.y - Anchor.y * Size.y,
                                  Position.x + (1 - Anchor.x) * Size.x,
                                  Position.y + (1 - Anchor.y) * Size.y,
                                  5, 5, border_color, 2);

        // テキストの幅を取得
        int text_width = GetTextWidth();
        // テキストの高さの取得
        int text_height = GetTextHeight();
        // 入力欄の中央にテキストを描画するためのX座標を計算
        int text_x = Position.x + (Size.x - text_width) / 2 - Anchor.x * Size.x;
        // 入力欄の中央にテキストを描画するためのY座標を計算（中央揃え）
        int text_y = Position.y + (Size.y - text_height) / 2 - Anchor.y * Size.y;

        // Draw text
        al_draw_text(font.get(), text_color, text_x,
                     text_y, // 下揃えにするためにtext_yを使用
                     0, text.c_str());

        // Draw cursor
        if (focused && show_cursor)
        {
            // cursor_positionまでの部分文字列を取得
            std::string substr = text.substr(0, cursor_position);

            // 部分文字列の幅を取得
            int cursor_x = al_get_text_width(font.get(), substr.c_str());

            al_draw_line(text_x + cursor_x, // テキストのX座標を考慮
                         Position.y - Anchor.y * Size.y,
                         text_x + cursor_x, // テキストのX座標を考慮
                         Position.y - Anchor.y * Size.y + Size.y,
                         text_color, 2);
        }
    }

    int TextInput::GetTextWidth() const
    {
        return al_get_text_width(font.get(), text.c_str());
    }
    int TextInput::GetTextHeight() const
    {
        return al_get_font_line_height(font.get());
    }
    void TextInput::SetText(const std::string &text)
    {
        this->text = text;
        cursor_position = text.size(); // テキスト設定時にカーソル位置も更新
    }
    const std::string &TextInput::GetText() const { return text; }
    int TextInput::GetMaxLength() const { return max_length; }
    void TextInput::SetFocus(bool focus)
    {
        focused = focus;
        show_cursor = focused;
    }
    bool TextInput::IsFocused() const { return focused; }
    void TextInput::OnMouseDown(int button, int mx, int my)
    {
        if (button & 1)
        {
            // マウス座標をオブジェクトの座標系に変換
            float local_x = mx - Position.x + Anchor.x * Size.x;
            float local_y = my - Position.y + Anchor.y * Size.y;

            // マウスがオブジェクトの境界内にあるか判定
            if (local_x >= 0 && local_x <= Size.x && local_y >= 0 &&
                local_y <= Size.y)
            {
                focused = true;
                show_cursor = true;

                // クリックされた位置にカーソルを移動
                int i = 0;
                int text_width = 0;
                while (i < text.size() && text_width <= local_x)
                {
                    text_width =
                        al_get_text_width(font.get(), text.substr(0, i).c_str());
                    i++;
                }
                cursor_position = i; // 文字の右端をクリックしてもカーソルはその文字の前に来るように調整
            }
            else
            {
                focused = false;
                show_cursor = false;
            }
        }
    }

    void TextInput::OnMouseUp(int button, int mx, int my)
    {
        // Do nothing
    }

    void TextInput::OnKeyDown(int keycode)
    {
        if (focused)
        {
            if (keycode == ALLEGRO_KEY_LEFT)
            {
                cursor_position = std::max(0, cursor_position - 1);
            }
            else if (keycode == ALLEGRO_KEY_RIGHT)
            {
                cursor_position = std::min((int)text.size(), cursor_position + 1);
            }
            else if (keycode == ALLEGRO_KEY_BACKSPACE)
            {
                if (cursor_position > 0)
                {
                    text.erase(cursor_position - 1, 1);
                    cursor_position--;
                }
            }
            else if (keycode == ALLEGRO_KEY_DELETE)
            {
                if (cursor_position < text.size())
                {
                    text.erase(cursor_position, 1);
                }
            }
            else if (keycode == ALLEGRO_KEY_HOME)
            {
                cursor_position = 0;
            }
            else if (keycode == ALLEGRO_KEY_END)
            {
                cursor_position = text.size();
            }
        }
    }

    void TextInput::OnKeyUp(int keycode)
    {
        // Do nothing
    }

    void TextInput::OnChar(int unicode)
    {
        if (focused)
        {
            if (max_length > 0 && text.size() >= max_length)
            {
                return;
            }
            text.insert(std::min(cursor_position, (int)text.size()), 1, unicode);
            cursor_position++;
        }
    }

    void TextInput::Update(float dt)
    {
        if (focused && al_get_timer_count(cursor_blink_timer) > 0)
        {
            show_cursor = !show_cursor;
            al_set_timer_count(cursor_blink_timer, 0); // カウントをリセット
        }
    }
} // namespace Engine