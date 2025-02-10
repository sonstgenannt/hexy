extends Control

@export var growth_factor : float
@export var lerp_speed : float

var _active_color : Color
var _inactive_color = Color.WHITE
var _is_start_vert : bool = false

var _default_scale : Vector2
var _target_scale : Vector2
var _following_mouse = false
var _drag_offset = Vector2.ZERO
var _mat = self.material

var _events_enabled = true

var _uid : int = -1

signal is_clicked(uid : int)

func enable_events(status : bool):
	_events_enabled = status
	
func set_active_color(col : Color):
	_active_color = col

func get_uid() -> int:
	return _uid

func set_uid(val : int) -> void:
	_uid = val

func _ready() -> void:
	_default_scale = self.scale
	_target_scale = _default_scale
	self.pivot_offset = self.size / 2

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	self.scale = self.scale.lerp(_target_scale, 0.1)
	
	if _following_mouse:
		global_position = _clamp_position(get_global_mouse_position() - _drag_offset)

func _clamp_position(pos : Vector2) -> Vector2:
	var vp_rect = get_viewport_rect()
	return Vector2(
		clamp(pos.x, vp_rect.position.x, vp_rect.end.x - (self.size * self.scale).x),
		clamp(pos.y, vp_rect.position.y, vp_rect.end.y - (self.size * self.scale).y)
	)

func set_start_vert_status(status : bool):
	_is_start_vert = status
	if status:
		_mat.set_shader_parameter("color", _active_color)
	else:
		_mat.set_shader_parameter("color", _inactive_color)
		

func _on_mouse_entered() -> void:
	if _events_enabled:
		_target_scale = growth_factor * _default_scale
		#if !_is_start_vert:
			#_mat.set_shader_parameter("color", _active_color)
	
func _on_mouse_exited() -> void:
	if _events_enabled:
		_target_scale = _default_scale
		#if !_is_start_vert:
			#_mat.set_shader_parameter("color", _inactive_color)
	
func _gui_input(event: InputEvent) -> void:
	if event is InputEventMouseButton and _events_enabled:
			if event.button_index == MOUSE_BUTTON_RIGHT:
				if event.is_pressed():
					_following_mouse = true
					_drag_offset = get_global_mouse_position() - global_position
				else:
					_following_mouse = false
			elif event.button_index == MOUSE_BUTTON_LEFT:
				if event.is_pressed():
					emit_signal("is_clicked", get_uid())
