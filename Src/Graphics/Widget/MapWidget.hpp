#pragma once

#include <unordered_map>
#include <vector>

#include "../../CellLoader/CellKeeper.hpp"
#include "Widget.hpp"

class CellInterlayer;

class MapWidget : public Widget 
{
public:

    explicit MapWidget(const Point pos, 
                       const size_t size_x, 
                       const size_t size_y, 
                       const int scale, 
                       const size_t frame_size_x, 
                       const size_t frame_size_y)
      : Widget          (pos),
        size_x          (size_x),
        size_y          (size_y),
        scale           (scale),
        cur_frame_pos   (0, 0),
        frame_size_x    (frame_size_x),
        frame_size_y    (frame_size_y),
        pixels          (size_x * size_y, Color::Transparent),
        pixel_texture   (new RenderTarget({size_x, size_y})),
        asset_color_map ()
    {}

    // Non-copyable
    MapWidget          (const MapWidget& other) = delete;
    MapWidget operator=(const MapWidget& other) = delete;

    // Non-movable
    MapWidget          (MapWidget&& other) = delete;
    MapWidget operator=(MapWidget&& other) = delete;

    ~MapWidget()
    {
        delete pixel_texture;
    }

    void draw(RenderTarget& render_target) override
    {
        pixel_texture->display();

        // draw map frame
        render_target.drawRect({pos.x - kMapBorderSize, pos.y - kMapBorderSize}, {size_x, size_y}, kMapBorderColor);

        Texture* texture = pixel_texture->getTexture();
        render_target.drawTexture(pos, *texture);

        delete texture;

        render_target.drawRect({pos.x + scale * cur_frame_pos.x / kCellSize, pos.y + scale * cur_frame_pos.y / kCellSize}, 
                               {scale * frame_size_x / kCellSize, scale * frame_size_y / kCellSize}, 
                               kFrameColor,
                               kFrameBorderSize,
                               kFrameBorderColor);
    }

    void push(const EventPtr event) override;

    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    {
        cell_interlayer = _cell_interlayer;
    }

private:

    bool isMouseInFrame(const Point mouse_pos) 
    {
        const Point frame_start = {pos.x + scale * cur_frame_pos.x / kCellSize, pos.y + scale * cur_frame_pos.y / kCellSize};
        const Point frame_size  = {scale * frame_size_x / kCellSize, scale * frame_size_y / kCellSize};

        return mouse_pos.x >= frame_start.x                &&
               mouse_pos.x <= frame_start.x + frame_size.x &&
               mouse_pos.y >= frame_start.y                &&
               mouse_pos.y <= frame_start.y + frame_size.y; 
    }

public:

    static const int kMapBorderSize = 2;

private:
    const Color kFrameColor       = {255, 255, 255, 128};
    const Color kFrameBorderColor = {255, 255, 255, 200};
    const int   kFrameBorderSize  = 2;

    const Color kMapBorderColor = {150, 75, 0, 255};

private:
    const size_t size_x;
    const size_t size_y;
    const int    scale;

    Point        cur_frame_pos;
    const size_t frame_size_x;
    const size_t frame_size_y;

    std::vector<Color> pixels;
    RenderTarget*      pixel_texture;
    CellInterlayer*    cell_interlayer;

    std::unordered_map<const char*, Color> asset_color_map;
};