
#pragma once


class Effect {
public:
		virtual void updateAndRender(std::shared_ptr<RenderTarget>) = 0;
};