native_load 'Game.so'
mrb_load    'Input.rb'
mrb_load    'ManagerText.rb'
mrb_load    'TextTable.rb'

Log.info "Game Platform Version: #{MAJOR}.#{MINOR}.#{PATCH}"

Graphics.show

# Establish Text Rendering Interface

dict   = ManagerText.basic_latin_table 'JetBrainsMono-Bold.ttf', 32
line_a = ManagerText.find_text '', dict
line_b = ManagerText.find_text '', dict
status = TextTable.new
status.lines[0] = line_a
status.lines[1] = line_b

# Establish Timer

timer = Timer.new
timer.start

# Establish Main Loop

while true
  # Update Event/Input Processing.
  Input.update
  break if Input.quit?

  # Update Text Rendering.
  Graphics.update
  fps     = sprintf "Average FPS: %.2f", timer.average_fps
  counter = sprintf "Counter: %d", timer.ticks / 60
  line_a  = ManagerText.find_text fps, dict
  line_b  = ManagerText.find_text counter, dict
  status.lines[0] = line_a
  status.lines[1] = line_b
  status.update
  Graphics.draw
  timer.counted_frames += 1
end
