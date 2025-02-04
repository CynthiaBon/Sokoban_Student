#pragma once

/*
	Keywords :
	- struct
*/

struct ShaderData
{
	const char* name;
	const char* vertex_filename;
	const char* fragment_filename;
	const char* geometry_filename;
	bool is_ui;
};