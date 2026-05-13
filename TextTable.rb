# MIT LICENSE - Ralph Desir (c) 2025
# Description: A Rendering object for dynamic text.

class TextTable
  attr_reader   :lines
  attr_reader   :color
  attr_accessor :line_spacing
  attr_accessor :base_x
  attr_accessor :base_y

  def initialize
    @lines        = []
    @line_spacing = 8
    @base_x       = 0
    @base_y       = 0
    @color        = {
                      'red'   => 255,
                      'green' => 255,
                      'blue'  => 255,
                      'alpha' => 255,
                    }
  end

  def update
    refresh_line_color

    @lines.each_with_index do |line, index|
      y_offset = @base_y + line.first.dest.h * index + @line_spacing * index

      line.each_with_index do |text, i|
        text.dest.x  = @base_x + (i * text.dest.w)
        text.dest.y  = y_offset
        text.color.r = @color['red']
        text.color.g = @color['green']
        text.color.b = @color['blue']
        text.color.a = @color['alpha']
        text.update
      end
    end
  end

  private

  def setup_line_color
    @lines.each do |line|
      line.each do |l|
        # This color should be visible for most backgrounds.
        l.color.r = 127
        l.color.g = 127
        l.color.b = 127
      end
    end
  end

  alias :refresh_line_color :setup_line_color
end
