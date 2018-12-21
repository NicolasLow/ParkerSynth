#ifndef NODE_GRAPH_PROCESSOR
#define NODE_GRAPH_PROCESSOR

#include "Modules\Module.hpp"
#include "Macro.h"
#include <string>

#define NUM_VOICES 9

class NodeGraphEditor;
class NodeGraphProcessor
{
public:
	NodeGraphProcessor();
	~NodeGraphProcessor();

	int currentID;
	int outputModuleID;
	std::vector<Module*> modules;
	bool hasOutModule;

	std::vector<Macro*> macros;

	void SavePreset(bool toPresetFile = true);
	void LoadPreset(bool fromPresetFile = true);
	void InitPreset();

	NodeGraphEditor *nge;

	//Macro Linking
	int lastTweakedModule;
	String lastTweakedModuleTitle;
	int lastTweakedParameter;
	float lastTweakedParameterMin;
	float lastTweakedParameterMax;
	float lastTweakedParameterValue;
	float lastTweakedParameterInc;

	double GetResult(int midiNote, float velocity, int voiceID);

	bool canProcess;

	StringArray saveData;
	int saveDataSize;

private:
	
};

#endif