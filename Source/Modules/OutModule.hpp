#pragma once

#include "Module.hpp"
#include "..\LookAndFeel\Knob.hpp"

class OutModule : public Module, public SliderListener {
public:
	OutModule();
	~OutModule();

	void PaintGUI(Graphics &g) override;
	void ResizeGUI() override;

	void sliderValueChanged(Slider* slider) override;
	void sliderDragStarted(Slider* slider) override;
	void sliderDragEnded(Slider* slider) override;

	float GetParameter(int id) override;
	void SetParameter(int id, float value) override;

	double GetResult(int midiNote, float velocity, int outputID, int voiveID) override;

private:
};