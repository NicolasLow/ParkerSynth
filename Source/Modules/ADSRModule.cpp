#include "ADSRModule.hpp"
#include "..\LookAndFeel\Colors.hpp"
#include "..\NodeGraphEditor.h"
#include "..\NodeGraphProcessor.h"

ADSRModule::ADSRModule() : Module(ModuleColorScheme::Blue, "ADSR", 1, 1, 0, Point<int>(10, 4), 4) {
	aKnob.setColour(aKnob.backgroundColourId, KNOB_BLUE);
	aKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	aKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	aKnob.addListener(this);
	aKnob.setRotaryParameters(-2.35619f, 2.35619f, true);
	aKnob.setRange(0.0f, 5.0f, 0.01f);
	aKnob.setValue(0.5f);
	aKnob.setLookAndFeel(&laF_Knob);
	addAndMakeVisible(aKnob);
	dKnob.setColour(dKnob.backgroundColourId, KNOB_BLUE);
	dKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	dKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	dKnob.addListener(this);
	dKnob.setRotaryParameters(-2.35619f, 2.35619f, true);
	dKnob.setRange(0.0f, 5.0f, 0.01f);
	dKnob.setValue(0.5f);
	dKnob.setLookAndFeel(&laF_Knob);
	addAndMakeVisible(dKnob);
	sKnob.setColour(sKnob.backgroundColourId, KNOB_BLUE);
	sKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	sKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	sKnob.addListener(this);
	sKnob.setRotaryParameters(-2.35619f, 2.35619f, true);
	sKnob.setRange(0.0f, 1.0f, 0.01f);
	sKnob.setValue(0.5f);
	sKnob.setLookAndFeel(&laF_Knob);
	addAndMakeVisible(sKnob);
	rKnob.setColour(rKnob.backgroundColourId, KNOB_BLUE);
	rKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	rKnob.addListener(this);
	rKnob.setRotaryParameters(-2.35619f, 2.35619f, true);
	rKnob.setRange(0.0f, 5.0f, 0.01f);
	rKnob.setValue(1.0f);
	rKnob.setLookAndFeel(&laF_Knob);
	addAndMakeVisible(rKnob);

	for (int i = 0; i < 9; i++) {
		voices[i].time = 0.0;
		voices[i].lastTime = 0.0;
		voices[i].lastGain = 0.0;
		voices[i].reset = false;
	}
	inputSocketButtons[0]->button.setTooltip("Trigger Velocity");
	inputSocketButtons[0]->SetValueType(ValueType::Velocity);
	outputSocketButtons[0]->button.setTooltip("Velocity");
	outputSocketButtons[0]->SetValueType(ValueType::Velocity);
}

ADSRModule::~ADSRModule(){

}

void ADSRModule::PaintGUI(Graphics &g) {
	g.setFont(boldFont);
	g.setColour(MODULE_FONT_COLOR);
	g.drawFittedText("A", 25, 63, 50, 25, Justification::centred, 1);
	g.drawFittedText("D", 75, 63, 50, 25, Justification::centred, 1);
	g.drawFittedText("S", 125, 63, 50, 25, Justification::centred, 1);
	g.drawFittedText("R", 175, 63, 50, 25, Justification::centred, 1);
}

void ADSRModule::ResizeGUI() {
	aKnob.setBounds(25, 25, 50, 50);
	dKnob.setBounds(75, 25, 50, 50);
	sKnob.setBounds(125, 25, 50, 50);
	rKnob.setBounds(175, 25, 50, 50);
}

void ADSRModule::sliderValueChanged(Slider* slider) {
	if (slider == &aKnob) {
		ngp->lastTweakedModule = this->id;
		ngp->lastTweakedModuleTitle = this->title + "->Attack";
		ngp->lastTweakedParameter = 0;
		ngp->lastTweakedParameterMin = aKnob.getMinimum();
		ngp->lastTweakedParameterMax = aKnob.getMaximum();
		ngp->lastTweakedParameterInc = aKnob.getInterval();
		ngp->lastTweakedParameterValue = aKnob.getValue();
	}
	else if (slider == &dKnob) {
		ngp->lastTweakedModule = this->id;
		ngp->lastTweakedModuleTitle = this->title + "->Decay";
		ngp->lastTweakedParameter = 1;
		ngp->lastTweakedParameterMin = dKnob.getMinimum();
		ngp->lastTweakedParameterMax = dKnob.getMaximum();
		ngp->lastTweakedParameterInc = dKnob.getInterval();
		ngp->lastTweakedParameterValue = dKnob.getValue();
	}
	else if (slider == &sKnob) {
		ngp->lastTweakedModule = this->id;
		ngp->lastTweakedModuleTitle = this->title + "->Sustain";
		ngp->lastTweakedParameter = 2;
		ngp->lastTweakedParameterMin = sKnob.getMinimum();
		ngp->lastTweakedParameterMax = sKnob.getMaximum();
		ngp->lastTweakedParameterInc = sKnob.getInterval();
		ngp->lastTweakedParameterValue = sKnob.getValue();
	}
	else if (slider == &rKnob) {
		ngp->lastTweakedModule = this->id;
		ngp->lastTweakedModuleTitle = this->title + "->Release";
		ngp->lastTweakedParameter = 3;
		ngp->lastTweakedParameterMin = rKnob.getMinimum();
		ngp->lastTweakedParameterMax = rKnob.getMaximum();
		ngp->lastTweakedParameterInc = rKnob.getInterval();
		ngp->lastTweakedParameterValue = rKnob.getValue();
	}
}

void ADSRModule::sliderDragStarted(Slider* slider) {
	if (slider == &aKnob) {
		slider->setMouseCursor(MouseCursor::UpDownResizeCursor);
	}
	else if (slider == &dKnob) {
		slider->setMouseCursor(MouseCursor::UpDownResizeCursor);
	}
	else if (slider == &sKnob) {
		slider->setMouseCursor(MouseCursor::UpDownResizeCursor);
	}
	else if (slider == &rKnob) {
		slider->setMouseCursor(MouseCursor::UpDownResizeCursor);
	}
}

void ADSRModule::sliderDragEnded(Slider* slider) {
	if (slider == &aKnob) {
		slider->setMouseCursor(MouseCursor::NormalCursor);
	}
	else if (slider == &dKnob) {
		slider->setMouseCursor(MouseCursor::NormalCursor);
	}
	else if (slider == &sKnob) {
		slider->setMouseCursor(MouseCursor::NormalCursor);
	}
	else if (slider == &rKnob) {
		slider->setMouseCursor(MouseCursor::NormalCursor);
	}
}

float ADSRModule::GetParameter(int id) {
	switch (id) {
	case 0:
		return aKnob.getValue();
	case 1:
		return dKnob.getValue();
	case 2:
		return sKnob.getValue();
	case 3:
		return rKnob.getValue();
	default:
		return 0.0;
	}
}

void ADSRModule::SetParameter(int id, float value) {
	switch (id) {
	case 0:
		aKnob.setValue(value);
		break;
	case 1:
		dKnob.setValue(value);
		break;
	case 2:
		sKnob.setValue(value);
		break;
	case 3:
		rKnob.setValue(value);
		break;
	default:
		break;
	}
}

double ADSRModule::GetResult(int midiNote, float velocity, int outputID, int voiceID) {
	if (inputs[0].connectedModule >= 0) {
		float gain = ngp->modules[inputs[0].connectedModule]->GetResult(midiNote, velocity, inputs[0].connectedOutput, voiceID);
		double result = 0.0;
		double attack = aKnob.getValue();
		double sustain = sKnob.getValue();
		if (gain > 0.0) {
			if (voices[voiceID].reset == true) {
				voices[voiceID].time = 0.0;
				voices[voiceID].lastGain = 0.0;
				voices[voiceID].lastTime = 0.0;
				voices[voiceID].reset = false;
			}
			if (voices[voiceID].time < attack) {
				result = 1.0 * voices[voiceID].time / attack;
				voices[voiceID].lastGain = result;
				voices[voiceID].lastTime = voices[voiceID].time;
			}
			else if (voices[voiceID].time >= attack) {
				result = jmax(1.0 - (1.0 - sustain) * ((voices[voiceID].time - attack) / dKnob.getValue()), sustain);
				voices[voiceID].lastGain = result;
				voices[voiceID].lastTime = voices[voiceID].time;
			}
			voices[voiceID].time += 1.0 / 44100;
		}
		else {
			result = jmax(voices[voiceID].lastGain - voices[voiceID].lastGain * ((voices[voiceID].time - voices[voiceID].lastTime) / rKnob.getValue()), 0.0);
			voices[voiceID].time += 1.0 / 44100;
			voices[voiceID].reset = true;
		}
		outputs[0] = result;
	}
	else
		outputs[0] = 0.0;

	return outputs[outputID];
}