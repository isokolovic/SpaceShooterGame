#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ss
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		bool HasInit() { return mAlreadyInit; }
		virtual bool HandleEvent(const sf::Event& event);
	protected:
		HUD();
	private:
		virtual void Init(sf::RenderWindow& windowRef);
		bool mAlreadyInit;
	};
}