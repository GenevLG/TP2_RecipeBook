#pragma once
#include <string>

class IEvent {	
	public:
		virtual ~IEvent();

		//virtual void DisplayLine() const = 0;
		//virtual std::string GetNextEvent() const = 0;
		//virtual bool DisplayChoice() const = 0;
		virtual std::string* GetChoice(int& count) const = 0;
};
