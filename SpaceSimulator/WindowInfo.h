// #pragma once ensures that this will be included only once in a compilation
#pragma once
#include <string>

/**
*
*/
namespace Init
{
	struct WindowInfo
	{
		std::string name;
		int width, height;
		int position_x, position_y;
		bool isReshapable;

		WindowInfo()
		{
			name = "OpenGL";
			width = 800; height = 600;
			position_x = 300;
			position_y = 300;
			isReshapable = true;
		}

		WindowInfo(std::string name, int start_position_x, int start_position_y, int width, int height, bool is_reshapable)
		{

			this->name = name;
			this->position_x = start_position_x;
			this->position_y = start_position_y;
			this->width = width;
			this->height = height;
			this->isReshapable = is_reshapable;
		}

		WindowInfo(const WindowInfo& windowInfo)
		{
			name = windowInfo.name;
			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;
			width = windowInfo.width;
			height = windowInfo.height;
			isReshapable = windowInfo.isReshapable;
		}

		WindowInfo& operator=(const WindowInfo& windowInfo)
		{

			name = windowInfo.name;

			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;

			width = windowInfo.width;
			height = windowInfo.height;
			isReshapable = windowInfo.isReshapable;

			return *this;
		}

	};
}
