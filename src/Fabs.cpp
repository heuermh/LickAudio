/*

    Lick Audio.
    Copyright (c) 2020 held jointly by the individual authors.

    This file is part of Lick Audio.

    Lick Audio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Lick Audio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Lick Audio.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "plugin.hpp"

struct Fabs : Module {
  enum ParamIds {
    NUM_PARAMS
  };
  enum InputIds {
    AMOUNT_INPUT,
    IN_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    OUT_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    NUM_LIGHTS
  };

  Fabs() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs& args) override {
    float amount = inputs[AMOUNT_INPUT].getVoltage();
    amount = clamp(amount, 0.0, 10.0);
    amount = rescale(amount, 0.0, 10.0, 32.0, 2.0);

    float v = inputs[IN_INPUT].getVoltage();
    v = rescale(v, -5.0, 5.0, -1.0, 1.0);
    v = v/(1.0f - fabs(v/amount));
    v = clamp(v, -1.0, 1.0);
    v = rescale(v, -1.0, 1.0, -5.0, 5.0);
    outputs[OUT_OUTPUT].setVoltage(v);
  }
};

struct FabsWidget : ModuleWidget {
  FabsWidget(Fabs* module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Fabs.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 42.0)), module, Fabs::AMOUNT_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 97.253)), module, Fabs::IN_INPUT));
    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 112.253)), module, Fabs::OUT_OUTPUT));
  }
};

Model* modelFabs = createModel<Fabs, FabsWidget>("Fabs");
