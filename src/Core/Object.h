#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace Aegis{

	class Object
	{
	public:
		void ConnectSignal(const std::string& signal, std::function<void()> callback);
	protected:
		void AddSignal(const std::string& signal);
		void Emit(const std::string& signal);
		
		std::unordered_map<std::string, std::vector<std::function<void()>>> signal_callbacks_;

	};
}
