#pragma once

class IRenderer {
	public:
		virtual void init()   = 0;
		virtual void render() = 0;
};
