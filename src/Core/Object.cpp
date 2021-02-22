#include "Object.h"

#include <iostream>

namespace Aegis{
	void Object::AddSignal(const std::string& signal)
	{
		if (signal_callbacks_.count(signal)) return;
		signal_callbacks_.insert({signal, std::vector<std::function<void()>>()});
	}

	void Object::Emit(const std::string& signal)
	{
		if (signal_callbacks_.count(signal)){
			for (auto& callback : signal_callbacks_[signal]){
				//check if object that ConnectSignald is still valid, if not remove from list
				callback();
			}
		}
	}

	void Object::ConnectSignal(const std::string& signal, std::function<void()> callback)
	{
		if (!signal_callbacks_.count(signal)){
			std::cout << "No valid signal '" << signal << "' to connect to.\n";
			return;
		}

		signal_callbacks_[signal].push_back(callback);
	}
}
