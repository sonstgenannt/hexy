extends Control

@export var number_of_vertices : int
@export var radius : float
@onready var vertex = preload("res://scenes/vertex.tscn")

var _vert_positions = []
var _vert_children = []

var _lines = []
var _triangle
var _colors

var _game_over = false

var _start_vert = null
var _end_vert = null

@onready var color_player_1 = Color.HOT_PINK
@onready var color_player_2 = Color.DARK_BLUE
@onready var current_player = color_player_1
@onready var line_thickness = 10.0

func trigger_game_over(verts):
	_game_over = true
	var arr = []
	for vert in verts:
		arr.append(vert.position + (vert.size / 2))
	_triangle = PackedVector2Array(arr)
	_colors = PackedColorArray([current_player])
	
	for vert in _vert_children:
		vert.enable_events(false)
	
func switch_current_player():
	if current_player == color_player_1:
		current_player = color_player_2
	else:
		current_player = color_player_1
	for vert in _vert_children:
			vert.set_active_color(current_player)

func calc_polygon_verts():
	var centre = get_viewport_rect().size / 2.0
	var verts = []
	var angle = (2 * PI) / number_of_vertices
	for i in range(number_of_vertices):
		var x = centre.x + (radius * cos(i * angle))
		var y = centre.y + (radius * sin(i * angle))
		verts.append(Vector2(x,y))
	return verts

func _ready() -> void:
	_vert_positions = calc_polygon_verts()
	var i = 0
	for pos in _vert_positions:
		var v = vertex.instantiate()
		v.set_uid(i)
		v.connect("is_clicked", Callable(self, "_on_is_clicked_emitted"))
		self.add_child(v)
		v.global_position = pos
		v.set_active_color(current_player)
		_vert_children.append(v)
		i += 1

func _reset_children_positions():
	for i in range(0, len(_vert_children)):
		_vert_children[i].position = _vert_positions[i]

func _input(event):
	if event is InputEventKey and event.pressed and event.keycode == KEY_R:
		_reset_children_positions()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	queue_redraw()

func check_for_triangles():
	var n = len(_lines)
	for i in range(n):
		for j in range(i + 1, n):
			for k in range(j + 1, n):
				var line_a = _lines[i]
				var line_b = _lines[j]
				var line_c = _lines[k]
				if line_a[1] == line_b[1] and line_b[1] == line_c[1]:
					var verts = [line_a[0][0], line_a[0][1], line_b[0][0], line_b[0][1], line_c[0][0], line_c[0][1]]
					var unique = {}
					for vert in verts:
						unique[vert] = null
					if len(unique.keys()) == 3:
						return [true, unique.keys()]
	return [false, []]

func _draw() -> void:
	if len(_lines) != 0:
		for line in _lines:
			draw_line(line[0][0].position + line[0][0].size / 2, line[0][1].position + line[0][1].size / 2, line[1], line_thickness, true)
	
	if _game_over:
		draw_polygon(_triangle, _colors)

func _on_is_clicked_emitted(uid : int):
	if _start_vert == null:
		_start_vert = _vert_children[uid]
		_start_vert.set_start_vert_status(true)
	else:
		if _end_vert == null:
			## Preventing drawing lines from a vertex to itself
			if uid == _start_vert.get_uid():
				_start_vert.set_start_vert_status(false)
				_start_vert = null
			else:
				_end_vert = _vert_children[uid]
				
				## Ensuring that duplicate lines cannot be drawn
				var can_draw = true
				for line in _lines:
					if line[0] == [_start_vert, _end_vert] or line[0] == [_end_vert, _start_vert]:
						can_draw = false
						break
				if can_draw:
					var player = current_player
					_lines.append([[_start_vert, _end_vert], player])
					var result = check_for_triangles()
					if result[0]:
						trigger_game_over(result[1])
					else:
						switch_current_player()
					
				_start_vert.set_start_vert_status(false)
				_start_vert = null
				_end_vert = null
