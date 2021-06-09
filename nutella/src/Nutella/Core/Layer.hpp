#pragma once

#include "Nutella/Events/Event.hpp"
#include "Nutella/Core/Timestep.hpp"

namespace Nutella {
	class Layer {
	  public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnEvent(Event& e) {};

		virtual void OnImGuiRender() {};

		inline const std::string getName() { return m_DebugName; }

	  private:
		std::string m_DebugName;
	};

} // namespace Nutella
