#pragma once
#include "IEvent.h"

class Event : IEvent
{
	private:
	std::string text; // Texte principal
	std::string nextFile; // Fichier suivant	

	public:
		Event(const std::string& eventText, const std::string& next);
		virtual ~Event();
	
		std::string* GetChoice(int& count) const override;
};
