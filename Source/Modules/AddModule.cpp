#include "AddModule.hpp"
#include "..\LookAndFeel\Colors.hpp"
#include "..\NodeGraphEditor.h"
#include "..\NodeGraphProcessor.h"

AddModule::AddModule() : Module(ModuleColorScheme::Grey, "Add", 2, 1, 0, Point<int>(4, 4), 0) {
	add_Image = ImageFileFormat::loadFrom(BinaryData::Math_Add_png, (size_t)BinaryData::Math_Add_pngSize);
	inputSocketButtons[0]->button.setTooltip("Value A");
	inputSocketButtons[0]->SetValueType(ValueType::SimpleValue);
	inputSocketButtons[1]->button.setTooltip("Value B");
	inputSocketButtons[1]->SetValueType(ValueType::SimpleValue);
	outputSocketButtons[0]->button.setTooltip("Result");
	outputSocketButtons[0]->SetValueType(ValueType::SimpleValue);
}

AddModule::~AddModule(){

}

void AddModule::PaintGUI(Graphics &g) {
	g.drawImage(add_Image, 0, 0, 100, 100, 0, 0, 100, 100);
}

void AddModule::ResizeGUI() {

}

float AddModule::GetParameter(int id) {
	return 0.0f;
}

void AddModule::SetParameter(int id, float value) {

}

double AddModule::GetResult(int midiNote, float velocity, int outputID, int voiceID) {
	double a = 0.0f;
	double b = 0.0f;
	if (inputs[0].connectedModule >= 0)
		a = ngp->modules[inputs[0].connectedModule]->GetResult(midiNote, velocity, inputs[0].connectedOutput, voiceID);
	if (inputs[1].connectedModule >= 0)
		b = ngp->modules[inputs[1].connectedModule]->GetResult(midiNote, velocity, inputs[1].connectedOutput, voiceID);

	return a + b;
}