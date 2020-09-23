/*

    heuermh/VCVRack-Plugins.
    Copyright (c) 2020 held jointly by the individual authors.

    This file is part of heuermh/VCVRack-Plugins.

    heuermh/VCVRack-Plugins is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    heuermh/VCVRack-Plugins is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with heuermh/VCVRack-Plugins.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "plugin.hpp"

struct Tick : Module {
  enum ParamIds {
    NUM_PARAMS
  };
  enum InputIds {
    NUM_INPUTS
  };
  enum OutputIds {
    CLOCKOUT_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    CLOCKLED_LIGHT,
    NUM_LIGHTS
  };

  Tick() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  float phase = 0.0f;
  float trigger = 0.0f; // in sec
  int triggerState = 0;
  float TRIGGER_LENGTH = 0.001f; // in sec
  float light = 0.0f; // in sec
  int lightState = 0;
  float LIGHT_LENGTH = 0.05f; // in sec

  void process(const ProcessArgs& args) override {
    // f(0) = 120 BPM or 2 Hz
    float freq = 2.0;

    // Accumulate the phase
    phase += freq * args.sampleTime;
    if (phase >= 1.0f) {
      triggerState = 1;
      lightState = 1;
      phase -= 1.0f;
    }

    if (triggerState) {
      trigger += args.sampleTime;
      if (trigger >= TRIGGER_LENGTH) {
        triggerState = 0;
        trigger = 0.0f;
      }
      outputs[CLOCKOUT_OUTPUT].setVoltage(10.0f);
      lights[CLOCKLED_LIGHT].setBrightness(1.0f);
    }
    else {
      outputs[CLOCKOUT_OUTPUT].setVoltage(0.0f);
      lights[CLOCKLED_LIGHT].setBrightness(0.0f);
    }

    if (lightState) {
      light += args.sampleTime;
      if (light >= LIGHT_LENGTH) {
        lightState = 0;
        light = 0.0f;
      }
      lights[CLOCKLED_LIGHT].setBrightness(1.0f);
    }
    else {
      lights[CLOCKLED_LIGHT].setBrightness(0.0f);
    }
  }
};

struct TickWidget : ModuleWidget {
  TickWidget(Tick* module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Tick.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.08, 29.408)), module, Tick::CLOCKOUT_OUTPUT));

    addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 39.638)), module, Tick::CLOCKLED_LIGHT));
  }
};

Model* modelTick = createModel<Tick, TickWidget>("Tick");
